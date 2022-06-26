/*
 * processing.h
 *
 * Created by Mateus Nunes de B Magalhaes on 28/09/19.
 * Copyright © 2019 mateusnbm. All rights reserved.
 *
 */

#ifndef processing_h
#define processing_h

#include "image.h"



void convolve(NBMImage * image, float * kernel, uint8_t m, uint8_t n);



#endif /* processing_h */
