/*
 * image.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 6/23/17.
 * Copyright © 2019 mateusnbm. All rights reserved.
 *
 */

#ifndef image_h
#define image_h

#include <CxImage/CxImage/ximage.h>

/*
 *
 * Enumerates the supported image file formats.
 *
 */

typedef enum {

    ImageFileFormatUnknown,
    ImageFileFormatTIFFLittleEndian,
    ImageFileFormatTIFFBigEndian,
    ImageFileFormatPNG,
    ImageFileFormatJPG,
    ImageFileFormatBMP

} ImageFileFormat;

/*
 *
 * Data structure containing the memory blocks needed to allow our library
 * to load, manipulate and persist images.
 *
 */

typedef struct {

    unsigned int width;
    unsigned int height;

    unsigned char * r;
    unsigned char * g;
    unsigned char * b;

} NBMImage;

/*
 *
 * Generates an image representation (NBMImage) from the image
 * referenced by the given file path. This function supports the
 * PNG, JPEG, BMP and TIFF file formats.
 *
 * If the image was successfully loaded, the image pointer will
 * reference a valid instance of the structure NBMImage, initialized
 * with the data extracted from the file at the given path.
 *
 * @param path Path to an image file.
 * @param image Address of a pointer to an NBMImage data structure.
 *
 */

void loadImageFromPath(char * path, NBMImage ** image);

/*
 *
 * This function writes an (NBMImage) image to a given file path.
 *
 * @param image The NBMImage to persist.
 * @param path The path to store the image.
 * @param format The format of the file.
 *
 * @return Returns 0 when the operation succeeds.
 *
 */

 char persistImage(NBMImage * image, char * path, ImageFileFormat format);

/*
 *
 * ...
 *
 * @param image ...
 *
 */

NBMImage * duplicateImage(NBMImage * image);

/*
 *
 * Releases the dynamically allocated memory referenced by the
 * image data structure and, also, the given pointer.
 *
 * @param image Pointer to a NBMImage.
 *
 */

void releaseImage(NBMImage * image);

#endif /* image_h */
