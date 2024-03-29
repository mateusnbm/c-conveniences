/*
 * image-convolution.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 3/14/17.
 * Copyright © 2017 mateusnbm. All rights reserved.
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "processing.h"

int main(int argc, const char * argv[]) {

    NBMImage * image = NULL;

    loadImageFromPath("NBMDemos/images/teste.png", &image);
    //loadImageFromPath("NBMDemos/images/a3x3x1.png", &image);
    //loadImageFromPath("NBMDemos/images/a3x3x8.png", &image);
    //loadImageFromPath("NBMDemos/images/parrot1bit.png", &image);
    //loadImageFromPath("NBMDemos/images/parrot4bit.png", &image);
    //loadImageFromPath("NBMDemos/images/lena220x220.png", &image);
    //loadImageFromPath("NBMDemos/images/pen8bit.png", &image);
    //loadImageFromPath("NBMDemos/images/house.png", &image);

    if (image != NULL) {

        NBMImage * duplicate = duplicateImage(image);

        if (duplicate != NULL) {

            float kernel[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

            convolve(duplicate, kernel, 3, 3);

            persistImage(image, "NBMDemos/images/mateus_original.png", ImageFileFormatPNG);
            persistImage(duplicate, "NBMDemos/images/mateus_duplicate.png", ImageFileFormatPNG);

        }

        releaseImage(image);

    }

    /*


    FILE * img_bin = fopen("NBMDemos/images/lena220x220.png", "rb");

    if (img_bin == NULL) { return -1; }

    fseek(img_bin, 0, SEEK_END);
    long int img_size = ftell(img_bin);
    long int data_size = img_size+1;
    unsigned char * data = (unsigned char *) malloc(sizeof(unsigned char)*data_size);
    fseek(img_bin, 0, SEEK_SET);
    fread(data, sizeof(unsigned char), img_size, img_bin);
    data[data_size-1] = 0;
    printf("the file has %li bytes\n", img_size);

    CxImage * image = new CxImage;

    bool success = byteArrayToCxImage(*image, data, img_size, false);

    if (success) {

        printf("success... read the fucking file... \n");

        long long int img_id = 0;

        getWrapper(&img_id, image);

        if (img_id != 0) {

            printf("success... image was wrapped... image id: %li\n", img_id);

        }

    } else {

        delete image;

    }

    fclose(img_bin);
    */

    return 0;

}
