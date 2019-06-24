/*
 *
 * image.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 6/23/19.
 * Copyright © 2019 mateusnbm. All rights reserved.
 *
 */

#include "image.h"
#include <CxImage/CxImage/ximage.h>

/*
 *
 * ...
 *
 * @param data ...
 *
 */

ImageFileFormat discoverImageFileFormatFromData(const unsigned char * data) {

	ImageFileFormat format = ImageFileFormatUnknown;

	const unsigned char pngHeader[] =				{ 0x89, 0x50, 0x4E, 0x47 };
	const unsigned char jpgHeader[] =				{ 0xFF, 0xD8, 0xFF };
	const unsigned char bmpHeader[] =				{ 0x42, 0x4D };
	const unsigned char tiffBigEndianHeader[] =		{ 0x4D, 0x4D, 0x00, 0x2A };
	const unsigned char tiffLittleEndianHeader[] =	{ 0x49, 0x49, 0x2A, 0x00 };

	if (memcmp(data, pngHeader, sizeof(pngHeader)) == 0) {

		format = ImageFileFormatPNG;

	} else if (memcmp(data, jpgHeader, sizeof(jpgHeader)) == 0) {

		format = ImageFileFormatJPG;

	} else if (memcmp(data, bmpHeader, sizeof(bmpHeader)) == 0) {

		format = ImageFileFormatBMP;

	} else if (memcmp(data, tiffBigEndianHeader, sizeof(tiffBigEndianHeader)) == 0) {

		format = ImageFileFormatTIFFBigEndian;

	} else if (memcmp(data, tiffLittleEndianHeader, sizeof(tiffLittleEndianHeader)) == 0) {

		format = ImageFileFormatTIFFLittleEndian;

	}

	return format;

}

/*
 *
 * ...
 *
 * @param fileFormat ...
 *
 */

uint32_t translateFileFormatToCxImageFormat(ImageFileFormat fileFormat) {

	uint32_t format = CXIMAGE_FORMAT_UNKNOWN;

	switch (fileFormat) {

		case ImageFileFormatPNG:
			format = CXIMAGE_FORMAT_PNG;
			break;

		case ImageFileFormatJPG:
			format = CXIMAGE_FORMAT_JPG;
			break;

		case ImageFileFormatBMP:
			format = CXIMAGE_FORMAT_BMP;
			break;

		case ImageFileFormatTIFFBigEndian:
		case ImageFileFormatTIFFLittleEndian:
			format = CXIMAGE_FORMAT_TIF;
			break;

	}

	return format;

}

/*
 * ...
 *
 * @param path ...
 *
 * @return ...
 *
 */

long int calculateBinaryStreamSize(FILE * file_pointer) {

	long int size = -1L;
	long int original_location = ftell(file_pointer);

	if (original_location != -1L && fseek(file_pointer, 0, SEEK_END) == 0) {

		size = ftell(file_pointer);

		if (fseek(file_pointer, original_location, SEEK_SET) != 0) {

			size = -1L;

		}

	}

	return size;

}

/*
 *
 * ...
 *
 * @param path ...
 * @param data ...
 * @param len ...
 *
 */

void loadDataFromFilePath(char * path, unsigned char ** data, long int * len) {

	long int read = 0;
	long int size = 0;
	unsigned char * buffer = NULL;
	FILE * file_pointer = fopen(path, "rb");

	if (file_pointer != NULL) {

		size = calculateBinaryStreamSize(file_pointer);

		if (size != -1L) {

			buffer = (unsigned char *) malloc(sizeof(unsigned char)*size);

			if (buffer != NULL) {

				read = fread(buffer, sizeof(unsigned char), size, file_pointer);

				if (read == size) {

					*len = size;
					*data = buffer;

				} else {

					free(buffer);

				}

			}

		}

	}

	fclose(file_pointer);

}

/*
 *
 * ...
 *
 * @param image ...
 * @param cxImage ...
 *
 */

char loadImageFromCxImage(NBMImage * image, CxImage * cxImage) {

	char status = 0;

	int row = 0;
	int column = 0;
	int lindex = 0;
	unsigned char * baddr = cxImage->GetBits();
	unsigned char * caddr = cxImage->GetBits();

	unsigned char bpp = cxImage->GetBpp();
	unsigned int width = cxImage->GetWidth();
	unsigned int height = cxImage->GetHeight();
	unsigned int length = (width * height);
	unsigned int bytesPerRow = cxImage->GetEffWidth();

	unsigned char * bmpHeader = (unsigned char *) cxImage->GetDIB();
	unsigned char * bmpColorTable = (bmpHeader + sizeof(BITMAPINFOHEADER));

	unsigned char * r = (unsigned char *) malloc(sizeof(unsigned char)*length);
	unsigned char * g = (unsigned char *) malloc(sizeof(unsigned char)*length);
	unsigned char * b = (unsigned char *) malloc(sizeof(unsigned char)*length);

	if (r == NULL || g == NULL || b == NULL) {

		status = -1;

		free(r);
		free(g);
		free(b);

	} else {

		printf("bpp %d\n", bpp);
		printf("bytes per row %d\n", bytesPerRow);

		switch (bpp) {

			case 1: {

				for (row = (height-1); row >= 0; row--) {

					caddr = (baddr + (row * bytesPerRow));

					for (column = 0; column < width; column++, lindex++) {

						unsigned int byteIndex = (column >> 3);
						unsigned char byteValue = caddr[byteIndex];
						unsigned char bitIndex = (8 - (column % 8));
						unsigned char bitOffset = (bitIndex-1);
						unsigned char bitValue = ((byteValue & (0x1 << bitOffset)) >> bitOffset);
						unsigned int colorIndex = (bitValue * sizeof(RGBQUAD));

						r[lindex] = (unsigned char) bmpColorTable[colorIndex];
						g[lindex] = r[lindex];
						b[lindex] = r[lindex];

					}

				}

			} break;

			case 4: {

				unsigned char * baddr_ = (unsigned char *) cxImage->GetDIB();
				unsigned char * caddr_ = (unsigned char *) (baddr_ + sizeof(BITMAPINFOHEADER));

				for (row = (height-1); row >= 0; row--) {

					caddr = (baddr + (row * bytesPerRow));

					for (column = 0; column < width; column++, lindex++) {

						uint8_t iDstVal = caddr[(column*bpp >> 3)];
		                uint8_t pos = (uint8_t)(4 * (1 - column % 2));
		                iDstVal &= (0x0F << pos);
		                uint8_t idx = (uint8_t)(iDstVal >> pos);
		                int32_t ldx = idx * sizeof(RGBQUAD);

						r[lindex] = (unsigned char) caddr_[ldx];
						g[lindex] = r[lindex];
						b[lindex] = r[lindex];

					}

				}

			} break;

			case 8:

				for (row = (height-1); row >= 0; row--) {

					caddr = (baddr + (row * bytesPerRow));

					for (column = 0; column < width; column++, lindex++) {

						r[lindex] = (unsigned char) (*caddr++);
						g[lindex] = r[lindex];
						b[lindex] = r[lindex];

					}

				}

				break;

			case 24:

				for (row = (height-1); row >= 0; row--) {

					caddr = (baddr + (row * bytesPerRow));

					for (column = 0; column < width; column++, lindex++) {

						r[lindex] = (unsigned char) (*caddr++);
						g[lindex] = (unsigned char) (*caddr++);
						b[lindex] = (unsigned char) (*caddr++);

					}

				}

				break;

		}

		image->bpp = bpp;
		image->width = width;
		image->height = height;

		image->r = r;
		image->g = g;
		image->b = b;

	}

	return status;

}

/*
 *
 * ...
 *
 * @param path ...
 * @param image ...
 *
 */

void loadImageFromPath(char * path, NBMImage ** image) {

	long int length = 0;
	unsigned char * buffer = NULL;
	CxImage * cxImage = new CxImage;

	ImageFileFormat imageFileFormat;
	uint32_t cxImageFormat;
	NBMImage * img;

	loadDataFromFilePath(path, &buffer, &length);

	if (buffer != NULL) {

		imageFileFormat = discoverImageFileFormatFromData(buffer);
		cxImageFormat = translateFileFormatToCxImageFormat(imageFileFormat);

		if (cxImage->Decode(buffer, (unsigned int) length, cxImageFormat) == true) {

			img = (NBMImage *) malloc(sizeof(NBMImage));

			if (img != NULL) {

				if (loadImageFromCxImage(img, cxImage) == 0) {

					*image = img;

				}

			}

		}

	}

	cxImage->Destroy();
	delete cxImage;
	free(buffer);

}

/*
 *
 * ...
 *
 * @param image ...
 *
 */

void releaseImage(NBMImage * image) {

	if (image != NULL) {

		free(image->r);
		free(image->g);
		free(image->b);

		free(image);

	}

}
