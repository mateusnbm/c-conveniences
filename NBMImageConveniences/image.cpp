/*
 *
 * image.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 23/06/19.
 * Copyright © 2019 mateusnbm. All rights reserved.
 *
 */

#include "image.h"

/*
 *
 * Minimum bits per pixel that the formats accepts.
 *
 * @param format The image file format.
 *
 * @return Minimum bits per pixel that the formats accepts.
 *
 */

unsigned char minimumBppForFileFormat(ImageFileFormat format) {

	uint8_t bpp;

    switch (format) {

		case ImageFileFormatBMP:
			bpp = 24;
			break;

		case ImageFileFormatJPG:
			bpp = 8;
			break;

		case ImageFileFormatUnknown:
		case ImageFileFormatPNG:
		case ImageFileFormatTIFFBigEndian:
		case ImageFileFormatTIFFLittleEndian:
			bpp = 1;
			break;

	}

    return bpp;

}

/*
 *
 * Discovers the image file format of a given data stream.
 *
 * @param data The data stream.
 *
 * @return The file format.
 *
 */

ImageFileFormat discoverImageFileFormatFromData(const uint8_t * data) {

	ImageFileFormat format = ImageFileFormatUnknown;

	const uint8_t pngHeader[] 				= { 0x89, 0x50, 0x4E, 0x47 };
	const uint8_t jpgHeader[] 				= { 0xFF, 0xD8, 0xFF       };
	const uint8_t bmpHeader[] 				= { 0x42, 0x4D             };
	const uint8_t tiffBigEndianHeader[] 	= { 0x4D, 0x4D, 0x00, 0x2A };
	const uint8_t tiffLittleEndianHeader[] 	= { 0x49, 0x49, 0x2A, 0x00 };

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
 * Translates our own ImageFileFormat enumeration to CxImage's enumeration.
 *
 * @param fileFormat The image file format.
 *
 * @param The CxImage format.
 *
 */

uint32_t translateImageFormatToCxImageFormat(ImageFileFormat fileFormat) {

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
 * Calculates the size of a given file.
 *
 * @param file_pointer The file stream.
 *
 * @return Returns either the number of bytes in the file or -1.
 *
 */

long int calculateBinaryStreamLength(FILE * file_pointer) {

	long int length = -1L;
	long int original_location = ftell(file_pointer);

	if (original_location != -1L && fseek(file_pointer, 0, SEEK_END) == 0) {

		length = ftell(file_pointer);

		if (fseek(file_pointer, original_location, SEEK_SET) != 0) {

			length = -1L;

		}

	}

	return length;

}

/*
 *
 * Opens a file at a given path and loads its content into a buffer.
 *
 * @param path Path to a file.
 * @param data Returns a pointer to a buffer.
 * @param len Returns the number of bytes in the stream.
 *
 */

void loadDataFromFilePath(char * path, unsigned char ** data, long int * len) {

	long int read = 0;
	long int length = 0;
	unsigned char * buffer = NULL;
	FILE * file_pointer = fopen(path, "rb");

	*data = NULL;

	if (file_pointer != NULL) {

		length = calculateBinaryStreamLength(file_pointer);

		if (length != -1L) {

			buffer = (unsigned char *) malloc(sizeof(unsigned char)*length);

			if (buffer != NULL) {

				read = fread(buffer, sizeof(unsigned char), length, file_pointer);

				if (read == length) {

					*len = length;
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
 * Creates a NBMImage from a CxImage with 1 bpp.
 *
 * @param cxImage The CxImage.
 * @param image Pointer to the NBMImage.
 *
 * @return Returns 0 if the operation was successful and -1 otherwise.
 *
 */

char loadImageFrom1BppCxImage(CxImage * cxImage, NBMImage * image) {

	char status = 0;

	unsigned char * baddr = cxImage->GetBits();
	unsigned char * caddr = cxImage->GetBits();

	unsigned int  byteIndex  = 0;
	unsigned char byteValue  = 0;
	unsigned char bitIndex   = 0;
	unsigned char bitValue   = 0;
	unsigned int  colorIndex = 0;

	unsigned char bpp    	  = cxImage->GetBpp();
	unsigned int  width  	  = cxImage->GetWidth();
	unsigned int  height 	  = cxImage->GetHeight();
	unsigned int  length      = (width * height);
	unsigned int  bytesPerRow = cxImage->GetEffWidth();

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

		for (int row = (height-1), index = 0; row >= 0; row--) {

			caddr = (baddr + (row * bytesPerRow));

			for (int column = 0; column < width; column++, index++) {

				byteIndex  = (column >> 3);
				byteValue  = caddr[byteIndex];
				bitIndex   = (7 - (column % 8));
				bitValue   = ((byteValue & (0x1 << bitIndex)) >> bitIndex);
				colorIndex = (bitValue * sizeof(RGBQUAD));

				r[index] = (unsigned char) bmpColorTable[colorIndex+2];
				g[index] = (unsigned char) bmpColorTable[colorIndex+1];
				b[index] = (unsigned char) bmpColorTable[colorIndex+0];

			}

		}

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
 * Creates a NBMImage from a CxImage with 4 bpp.
 *
 * @param cxImage The CxImage.
 * @param image Pointer to the NBMImage.
 *
 * @return Returns 0 if the operation was successful and -1 otherwise.
 *
 */

char loadImageFrom4BppCxImage(CxImage * cxImage, NBMImage * image) {

	char status = 0;

	unsigned char * baddr = cxImage->GetBits();
	unsigned char * caddr = cxImage->GetBits();

	unsigned int  byteIndex  = 0;
	unsigned char byteValue  = 0;
	unsigned char lsbIndex   = 0;
	unsigned char quadValue  = 0;
	unsigned int  colorIndex = 0;

	unsigned char bpp 		  = cxImage->GetBpp();
	unsigned int  width 	  = cxImage->GetWidth();
	unsigned int  height 	  = cxImage->GetHeight();
	unsigned int  length 	  = (width * height);
	unsigned int  bytesPerRow = cxImage->GetEffWidth();

	unsigned char * bmpHeader     = (unsigned char *) cxImage->GetDIB();
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

		for (int row = (height-1), index = 0; row >= 0; row--) {

			caddr = (baddr + (row * bytesPerRow));

			for (int column = 0; column < width; column++, index++) {

				byteIndex  = (column >> 1);
				byteValue  = caddr[byteIndex];

				lsbIndex   = ((1 - (column % 2)) * 4);
				quadValue  = ((byteValue & (0x0F << lsbIndex)) >> lsbIndex);
				colorIndex = (quadValue * sizeof(RGBQUAD));

				r[index] = (unsigned char) bmpColorTable[colorIndex+2];
				g[index] = (unsigned char) bmpColorTable[colorIndex+1];
				b[index] = (unsigned char) bmpColorTable[colorIndex+0];

			}

		}

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
 * Creates a NBMImage from a CxImage with 8 bpp.
 *
 * @param cxImage The CxImage.
 * @param image Pointer to the NBMImage.
 *
 * @return Returns 0 if the operation was successful and -1 otherwise.
 *
 */

char loadImageFrom8BppCxImage(CxImage * cxImage, NBMImage * image) {

	char status = 0;

	unsigned char * baddr = cxImage->GetBits();
	unsigned char * caddr = cxImage->GetBits();

	unsigned int colorIndex = 0;

	unsigned char bpp 		  = cxImage->GetBpp();
	unsigned int  width 	  = cxImage->GetWidth();
	unsigned int  height 	  = cxImage->GetHeight();
	unsigned int  length 	  = (width * height);
	unsigned int  bytesPerRow = cxImage->GetEffWidth();

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

		for (int row = (height-1), index = 0; row >= 0; row--) {

			caddr = (baddr + (row * bytesPerRow));

			for (int column = 0; column < width; column++, index++) {

				colorIndex = ((*caddr++) * sizeof(RGBQUAD));

				r[index]   = (unsigned char) bmpColorTable[colorIndex+2];
				g[index]   = (unsigned char) bmpColorTable[colorIndex+1];
				b[index]   = (unsigned char) bmpColorTable[colorIndex+0];

			}

		}

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
 * Creates a NBMImage from a CxImage with 24 bpp.
 *
 * @param cxImage The CxImage.
 * @param image Pointer to the NBMImage.
 *
 * @return Returns 0 if the operation was successful and -1 otherwise.
 *
 */

char loadImageFrom24BppCxImage(CxImage * cxImage, NBMImage * image) {

	char status = 0;

	unsigned char * baddr = cxImage->GetBits();
	unsigned char * caddr = cxImage->GetBits();

	unsigned char bpp 		 = cxImage->GetBpp();
	unsigned int width 		 = cxImage->GetWidth();
	unsigned int height 	 = cxImage->GetHeight();
	unsigned int length 	 = (width * height);
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

		for (int row = (height-1), index = 0; row >= 0; row--) {

			caddr = (baddr + (row * bytesPerRow));

			for (int column = 0; column < width; column++, index++) {

				b[index] = (unsigned char) (*caddr++);
				g[index] = (unsigned char) (*caddr++);
				r[index] = (unsigned char) (*caddr++);

			}

		}

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
			status = loadImageFrom1BppCxImage(cxImage, image);
			break;

		case 4:
			status = loadImageFrom4BppCxImage(cxImage, image);
			break;

		case 8:
			status = loadImageFrom8BppCxImage(cxImage, image);
			break;

		case 24:
			status = loadImageFrom24BppCxImage(cxImage, image);
			break;

	}

	return status;

}

/*
 *
 * Creates a CxImage with 24 bpp from a NBMImage.
 *
 * @param image The source NBMImage.
 * @param cxImage The destination CxImage.
 * @param format The desired cxImage format.
 *
 */

void load24BppCxImageFromImage(NBMImage * image, CxImage * cxImage, ImageFileFormat format) {

	if (cxImage != NULL && image != NULL) {

		long int row = 0;
		long int column = 0;
		long int pindex = 0;

		uint32_t width = (uint32_t) image->width;
		uint32_t height = (uint32_t) image->height;
		uint32_t cxImageFormat  = translateImageFormatToCxImageFormat(format);

		cxImage->Create(width, height, 24, cxImageFormat);

		unsigned char * baddr = cxImage->GetBits();
		unsigned char * caddr = cxImage->GetBits();
		unsigned int bytesPerRow = cxImage->GetEffWidth();

        for (row = 0; row < height; row++) {

            caddr = baddr + (height - 1 - row) * bytesPerRow;

			for (column = 0; column < width; column++, pindex++) {

                *caddr++ = static_cast <uint8_t> (image->b[pindex]);
                *caddr++ = static_cast <uint8_t> (image->g[pindex]);
                *caddr++ = static_cast <uint8_t> (image->r[pindex]);

			}

		}

	}

}

/*
 *
 * Creates a CxImage from a NBMImage.
 *
 * @param image The source NBMImage.
 * @param cxImage The destination CxImage.
 * @param format The desired cxImage format.
 *
 */

void loadCxImageFromImage(NBMImage * image, CxImage * cxImage, ImageFileFormat format) {

	load24BppCxImageFromImage(image, cxImage, format);

}

/*
 *
 * Generates a NBMImage representation from the image at the given
 * file path. This function supports PNG, JPEG, BMP and TIFF formats.
 *
 * If the image was properly loaded, the pointer will reference a valid
 * instance of a NBMImage data structure, otherwise, will point to NULL.
 *
 * @param path Path to the image file.
 * @param image Address of a pointer to a NBMImage.
 *
 */

void loadImageFromPath(char * path, NBMImage ** image) {

	long int length = 0;
	unsigned char * buffer = NULL;
	CxImage * cxImage = new CxImage;

	*image = NULL;

	loadDataFromFilePath(path, &buffer, &length);

	if (buffer != NULL) {

		ImageFileFormat imageFileFormat = discoverImageFileFormatFromData(buffer);
		uint32_t cxImageFormat = translateImageFormatToCxImageFormat(imageFileFormat);

		if (cxImage->Decode(buffer, (unsigned int) length, cxImageFormat) == true) {

			NBMImage * img = (NBMImage *) malloc(sizeof(NBMImage));

			if (img != NULL) {

				if (loadImageFromCxImage(img, cxImage) == 0) {

					*image = img;

				}

			}

		}

	}

	free(buffer);

}

/*
 *
 * Writes a NBMImage to the given file path.
 *
 * @param image The image to persist.
 * @param path The path to store the image.
 * @param format The file format to write.
 *
 * @return Returns 0 when the write operation succeeds.
 *
 */

char persistImage(NBMImage * image, char * path, ImageFileFormat format) {

	char status = -1;
	CxImage * cxImage = new CxImage;
	FILE * file_pointer = fopen(path, "wb+");
	uint32_t cxImageFormat  = translateImageFormatToCxImageFormat(format);

	if (file_pointer != NULL && format != ImageFileFormatUnknown) {

		int32_t length = 0;
		uint8_t * data = NULL;
		uint32_t wrote = 0;

		loadCxImageFromImage(image, cxImage, format);

		cxImage->Encode(data, length, cxImageFormat);
		cxImage->SetXDPI(72);
		cxImage->SetYDPI(72);

		wrote = fwrite(data, sizeof(unsigned char), length, file_pointer);

		if (wrote == length) {

			cxImage->Destroy();
			delete cxImage;
			free(data);
			fclose(file_pointer);

			status = 0;

		}

	}

	return status;

}

/*
 *
 * Creates a duplicate (deep copy) of a NBMImage.
 *
 * @param image The image to duplicate.
 *
 */

NBMImage * duplicateImage(NBMImage * image) {

	NBMImage * duplicate = NULL;

	if (image != NULL) {

		duplicate = (NBMImage *) malloc(sizeof(NBMImage));

		if (duplicate != NULL) {

			char fail = 0;

			uint32_t w = image->width;
			uint32_t h = image->height;
			uint32_t l = ((w * h) * sizeof(uint8_t));

			duplicate->width = w;
			duplicate->height = h;

			duplicate->r = (uint8_t *) malloc(l);
			duplicate->g = (uint8_t *) malloc(l);
			duplicate->b = (uint8_t *) malloc(l);

			fail = duplicate->r == NULL || duplicate->g == NULL || duplicate->b == NULL;

			if (fail == 0) {

				void * a = memcpy(duplicate->r, image->r, l);
				void * b = memcpy(duplicate->g, image->g, l);
				void * c = memcpy(duplicate->b, image->b, l);

				fail = a == NULL || b == NULL || c == NULL;

			}

			if (fail == 1) {

				free(duplicate->r);
				free(duplicate->g);
				free(duplicate->b);
				free(duplicate);

				duplicate = NULL;

			}

		}

	}

	return duplicate;

}

/*
 *
 * Releases the given NBMImage.
 *
 * @param image The image to release.
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
