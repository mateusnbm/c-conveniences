/*
 *
 * image.h
 *
 * Created by Mateus Nunes de B Magalhaes on 23/06/19.
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
 * Data structure representing an image.
 *
 */

typedef struct {

    uint32_t width;
    uint32_t height;

    uint8_t * r;
    uint8_t * g;
    uint8_t * b;

} NBMImage;

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

void loadImageFromPath(char * path, NBMImage ** image);

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

 char persistImage(NBMImage * image, char * path, ImageFileFormat format);

/*
 *
 * Creates a duplicate (deep copy) of a NBMImage.
 *
 * @param image The image to duplicate.
 *
 */

NBMImage * duplicateImage(NBMImage * image);

/*
 *
 * Releases the given NBMImage.
 *
 * @param image The image to release.
 *
 */

void releaseImage(NBMImage * image);

#endif /* image_h */
