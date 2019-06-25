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
 * Extracts relevant information from the CxImage and uses it to
 * generate an image representation that conforms to our own image
 * data structure. The CxImage must have 1 bits per pixel (bpp).
 *
 * @param image A pointer to a NBMImage.
 * @param cxImage A pointer to a CxImage.
 *
 * @return Returns 0 if the operation was successful and -1, otherwise.
 *
 */

char loadImageFrom1BppCxImage(NBMImage * image, CxImage * cxImage) {

	char status = 0;

	int row = 0;
	int column = 0;
	int lindex = 0;
	unsigned char * baddr = cxImage->GetBits();
	unsigned char * caddr = cxImage->GetBits();

	unsigned int byteIndex = 0;
	unsigned char byteValue = 0;
	unsigned char bitIndex = 0;
	unsigned char bitValue = 0;
	unsigned int colorIndex = 0;

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

		for (row = (height-1); row >= 0; row--) {

			caddr = (baddr + (row * bytesPerRow));

			for (column = 0; column < width; column++, lindex++) {

				byteIndex = (column >> 3);
				byteValue = caddr[byteIndex];
				bitIndex = (7 - (column % 8));
				bitValue = ((byteValue & (0x1 << bitIndex)) >> bitIndex);
				colorIndex = (bitValue * sizeof(RGBQUAD));

				r[lindex] = (unsigned char) bmpColorTable[colorIndex];
				g[lindex] = r[lindex];
				b[lindex] = r[lindex];

			}

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
 * Extracts relevant information from the CxImage and uses it to
 * generate an image representation that conforms to our own image
 * data structure. The CxImage must have 4 bits per pixel (bpp).
 *
 * @param image A pointer to a NBMImage.
 * @param cxImage A pointer to a CxImage.
 *
 * @return Returns 0 if the operation was successful and -1, otherwise.
 *
 */

char loadImageFrom4BppCxImage(NBMImage * image, CxImage * cxImage) {

	char status = 0;

	int row = 0;
	int column = 0;
	int lindex = 0;
	unsigned char * baddr = cxImage->GetBits();
	unsigned char * caddr = cxImage->GetBits();

	unsigned int byteIndex = 0;
	unsigned char byteValue = 0;
	unsigned char lsbIndex = 0;
	unsigned char bitValue = 0;
	unsigned int colorIndex = 0;

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

		for (row = (height-1); row >= 0; row--) {

			caddr = (baddr + (row * bytesPerRow));

			for (column = 0; column < width; column++, lindex++) {

				byteIndex = ((column * 4) >> 3);
				byteValue = caddr[byteIndex];
				lsbIndex = ((1 - (column % 2)) * 4);
				bitValue = ((byteValue & (0xF << lsbIndex)) >> lsbIndex);
				colorIndex = (bitValue * sizeof(RGBQUAD));

				r[lindex] = (unsigned char) bmpColorTable[colorIndex];
				g[lindex] = r[lindex];
				b[lindex] = r[lindex];

			}

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
 * Extracts relevant information from the CxImage and uses it to
 * generate an image representation that conforms to our own image
 * data structure. The CxImage must have 8 bits per pixel (bpp).
 *
 * @param image A pointer to a NBMImage.
 * @param cxImage A pointer to a CxImage.
 *
 * @return Returns 0 if the operation was successful and -1, otherwise.
 *
 */

char loadImageFrom8BppCxImage(NBMImage * image, CxImage * cxImage) {

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

	unsigned char * r = (unsigned char *) malloc(sizeof(unsigned char)*length);
	unsigned char * g = (unsigned char *) malloc(sizeof(unsigned char)*length);
	unsigned char * b = (unsigned char *) malloc(sizeof(unsigned char)*length);

	if (r == NULL || g == NULL || b == NULL) {

		status = -1;

		free(r);
		free(g);
		free(b);

	} else {

		for (row = (height-1); row >= 0; row--) {

			caddr = (baddr + (row * bytesPerRow));

			for (column = 0; column < width; column++, lindex++) {

				r[lindex] = (unsigned char) (*caddr++);
				g[lindex] = r[lindex];
				b[lindex] = r[lindex];

			}

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
 * Extracts relevant information from the CxImage and uses it to
 * generate an image representation that conforms to our own image
 * data structure. The CxImage must have 24 bits per pixel (bpp).
 *
 * @param image A pointer to a NBMImage.
 * @param cxImage A pointer to a CxImage.
 *
 * @return Returns 0 if the operation was successful and -1, otherwise.
 *
 */

char loadImageFrom24BppCxImage(NBMImage * image, CxImage * cxImage) {

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

	unsigned char * r = (unsigned char *) malloc(sizeof(unsigned char)*length);
	unsigned char * g = (unsigned char *) malloc(sizeof(unsigned char)*length);
	unsigned char * b = (unsigned char *) malloc(sizeof(unsigned char)*length);

	if (r == NULL || g == NULL || b == NULL) {

		status = -1;

		free(r);
		free(g);
		free(b);

	} else {

		for (row = (height-1); row >= 0; row--) {

			caddr = (baddr + (row * bytesPerRow));

			for (column = 0; column < width; column++, lindex++) {

				r[lindex] = (unsigned char) (*caddr++);
				g[lindex] = (unsigned char) (*caddr++);
				b[lindex] = (unsigned char) (*caddr++);

			}

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
 * Extracts relevant information from the CxImage and uses it to
 * generate an image representation that conforms to our own image
 * data structure. This function acts as a proxy for the functions
 * that load the image based on the number of bits per pixel (bpp).
 *
 * @param image Pointer to a NBMImage.
 * @param cxImage Pointer to a CxImage.
 *
 * @return Returns 0 if the operation was successful and -1, otherwise.
 *
 */

char loadImageFromCxImage(NBMImage * image, CxImage * cxImage) {

	char status = 0;

	switch (cxImage->GetBpp()) {

		case 1:
			status = loadImageFrom1BppCxImage(image, cxImage);
			break;

		case 4:
			status = loadImageFrom4BppCxImage(image, cxImage);
			break;

		case 8:
			status = loadImageFrom8BppCxImage(image, cxImage);
			break;

		case 24:
			status = loadImageFrom24BppCxImage(image, cxImage);
			break;

	}

	return status;

}

/*
 *
 * Generates an image representation (NBMImage) from the image
 * referenced by the given file path. This function supports the
 * PNG, JPEG, BMP and TIFF file formats.
 *
 * If the image was successfully loaded, the image pointer will
 * reference a valid instance of the structure NBMImage initialized
 * with the data extracted from the file at the given path.
 *
 * @param path Path to an image file.
 * @param image Address of a pointer to an NBMImage data structure.
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
 * @param path ...
 *
 */

 char persistImage(NBMImage * image, char * path) {

	 // ...

	 return 0;

 }

/*
 *
 * Releases the dynamically allocated memory referenced by the
 * image data structure and, also, the given pointer.
 *
 * @param image Pointer to a NBMImage.
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
