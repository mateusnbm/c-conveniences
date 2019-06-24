/*
 * image.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 6/23/17.
 * Copyright © 2019 mateusnbm. All rights reserved.
 *
 */

#ifndef image_h
#define image_h

typedef enum {

    ImageFileFormatUnknown,
    ImageFileFormatTIFFLittleEndian,
    ImageFileFormatTIFFBigEndian,
    ImageFileFormatPNG,
    ImageFileFormatJPG,
    ImageFileFormatBMP

} ImageFileFormat;

typedef struct {

    unsigned char bpp;
    unsigned int width;
    unsigned int height;

    unsigned char * r;
    unsigned char * g;
    unsigned char * b;

} NBMImage;

/*
 *
 * ...
 *
 * @param path ...
 * @param image ...
 *
 */

void loadImageFromPath(char * path, NBMImage ** image);

/*
 *
 * ...
 *
 * @param image ...
 *
 */

void releaseImage(NBMImage * image);

#endif /* image_h */
