/*
 *
 * image.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 6/23/19.
 * Copyright © 2019 mateusnbm. All rights reserved.
 *
 */

#include "image.h"

/*
 *
 * This function returns the minimum number of bits per pixels that each
 * supported image file format accepts.
 *
 * @param format The image file format.
 *
 * @return Minimum bits per pixels that the formats accepts.
 *
 */

unsigned char minimumBppForFileFormat(ImageFileFormat format) {

	unsigned char bpp;

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
 * Translates our own ImageFileFormat enumeration to the CxImage proprietary
 * file format enumeration.
 *
 * @param fileFormat The image file format.
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
 * @param path Path to a file.
 *
 * @return This function returns the number of bytes in the file at the given
 *         path or '-1L' if it fails to computer the file's length.
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
 * Opens a file at a given path and loads its content into a buffer of
 * unsigned chars. The number of bytes read is returned through a pointer to
 * an integer.
 *
 * @param path Path to a file.
 * @param data Address of a pointer to an array of unsigned chars.
 * @param len Pointer to an integer that will be updated with the number
 *        of bytes read from the file.
 *
 */

void loadDataFromFilePath(unsigned char ** data, long int * len, char * path) {

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

				b[lindex] = (unsigned char) (*caddr++);
				g[lindex] = (unsigned char) (*caddr++);
				r[lindex] = (unsigned char) (*caddr++);

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
 * ...
 *
 * @param image ...
 * @param path ...
 *
 */

void load24BppCxImageFromImage(CxImage * cxImage, NBMImage * image, ImageFileFormat format) {

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
 * ...
 *
 * @param cxImage ...
 * @param image ...
 *
 */

void loadCxImageFromImage(CxImage * cxImage, NBMImage * image, ImageFileFormat format) {

	load24BppCxImageFromImage(cxImage, image, format);

}

/*
 *
 * Generates an image representation (NBMImage) from the image
 * referenced by the given file path. This function supports the
 * PNG, JPEG, BMP and TIFF file formats.
 *
 * If the image was successfully loaded, the image pointer will
 * reference a valid instance of the structure NBMImage initialized,
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

	*image = NULL;

	loadDataFromFilePath(&buffer, &length, path);

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
 * This function writes a NBMImage to a given file path. The current
 * implementation will store all images with 24 bits per pixel and 72
 * dots per inch on both x and y axis.
 *
 * @param image The NBMImage to persist.
 * @param path The path to store the image.
 * @param format The format of the file.
 *
 * @return Returns 0 when the operation succeeds.
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
		long int wrote = 0;

		loadCxImageFromImage(cxImage, image, format);
		cxImage->Encode(data, length, cxImageFormat);
		cxImage->SetXDPI(72);
		cxImage->SetYDPI(72);

		//image.SetCodecOption(COMPRESSION_JPEG, CXIMAGE_FORMAT_TIF);
        //image.SetJpegQuality(90);
		//image.SetCodecOption(8, CXIMAGE_FORMAT_PNG);
		//image.SetJpegQuality(90);

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
 * ...
 *
 * @param image ...
 *
 */

NBMImage * duplicateImage(NBMImage * image) {

	NBMImage * duplicate = NULL;

	if (image != NULL) {

		duplicate = (NBMImage *) malloc(sizeof(NBMImage));

		if (duplicate != NULL) {

			char fail = 0;

			unsigned int w = image->width;
			unsigned int h = image->height;
			unsigned int l = ((w * h) * sizeof(unsigned char));

			duplicate->width = w;
			duplicate->height = h;

			duplicate->r = (unsigned char *) malloc(l);
			duplicate->g = (unsigned char *) malloc(l);
			duplicate->b = (unsigned char *) malloc(l);

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
