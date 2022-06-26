/*
 *
 * processing.cpp
 *
 * Created by Mateus Nunes de B Magalhaes on 28/09/19.
 * Copyright © 2019 mateusnbm. All rights reserved.
 *
 */

#include "processing.h"

#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#define MAX(A, B) (((A) > (B)) ? (A) : (B))

uint8_t * extendEdges( uint8_t * stream, uint32_t w, uint32_t h, uint8_t m, uint8_t n ) {

    uint32_t frameWidth  = ( w + ( 2 * n ) );
    uint32_t frameHeight = ( h + ( 2 * m ) );
    uint32_t frameLength = ( frameWidth * frameHeight );

    uint8_t  v  = ( 0             );
    uint32_t ll = ( w * ( h - 1 ) );

    uint8_t * f = (uint8_t *) malloc( sizeof(uint8_t) * frameLength );

    if ( f != NULL ) {

        for ( int i = 0, index = 0; i < frameHeight; i++ ) {

            for ( int j = 0; j < frameWidth; j++, index++ ) {

                uint32_t nthLine = w * ( i - n );

                char top    = ( i < n                    );
                char left   = ( j < m                    );
                char bottom = ( i >= ( frameHeight - n ) );
                char right  = ( j >= ( frameWidth  - m ) );
                char center = ( !left && ! right         );

                if ( top    && left   ) { v = stream[( 0                   )]; } else
                if ( top    && center ) { v = stream[( j - m               )]; } else
                if ( top    && right  ) { v = stream[( w - 1               )]; } else
                if ( bottom && left   ) { v = stream[( ll                  )]; } else
                if ( bottom && center ) { v = stream[( ll + j - m          )]; } else
                if ( bottom && right  ) { v = stream[( ll + w - 1          )]; } else
                if ( left             ) { v = stream[( nthLine             )]; } else
                if ( right            ) { v = stream[( nthLine + w - 1     )]; } else
                                        { v = stream[( nthLine + ( j - m ) )]; }

                f[index] = v;

            }

        }

    }

    return f;

}

uint8_t * convolve( uint8_t * stream, uint32_t w, uint32_t h, float * kernel, uint8_t m, uint8_t n ) {

    uint8_t * r = ( uint8_t * ) malloc( sizeof(uint8_t) * w * h );

    int ii, ij;
    int ki, kj;

    int ii_min, ii_max, ij_min, ij_max;
    int ki_min, ki_max, kj_min, kj_max;

    int kernel_margin_i = (m / 2);
    int kernel_margin_j = (n / 2);

    if ( r != NULL ) {

        for (ii = 0; ii < image->height; ii++) {

            ii_min = MAX((ii - kernel_margin_i), 0);
            ii_max = MIN((ii + kernel_margin_i), (image->height-1));

            for (ij = 0; ij < image->width; ij++) {

                result = 0;

                ij_min = MAX((ij - kernel_margin_j), 0);
                ij_max = MIN((ij + kernel_margin_j), (image->width-1));

                ki_min = kernel_margin_i - (ii - ii_min);
                ki_max = kernel_margin_i + (ii_max - ii);
                kj_min = kernel_margin_j - (ij - ij_min);
                kj_max = kernel_margin_j + (ij_max - ij);

                for (ki = ki_min; ki < ki_max; ki++) {

                    for (kj = kj_min; kj < kj_max; kj++) {

                        int fi = ((ii - m) + ki);
                        int fj = ((ij - n) + kj);

                        int fd = (image->width * fi) + fj;
                        int kd = (m * ki) + kj;

                        result += (image->r[fd] * kernel[kd]);

                    }

                }

            }

        }

    }


    return r;


    /*
    uint32_t i0 = (  n / 2 );
    uint32_t iN = ( i0 + h );
    uint32_t j0 = (  m / 2 );
    uint32_t jN = ( j0 + w );

    for (int i = i0; i < iN; i++) {

        for (int j = j0; j < jN; j++) {

            uint32_t sum = 0;

            for (int ki = 0; ki < n; ki++) {

                for (int kj = 0; kj < m; kj++) {

                    sum += 0;

                }

            }

            //

        }

    }
    */

    return NULL;

}

void convolve(NBMImage * image, float * kernel, uint8_t m, uint8_t n) {

    uint8_t padI = ( m / 2 );
    uint8_t padJ = ( n / 2 );

    NBMImage * ext = (NBMImage *) malloc(sizeof(NBMImage));

    if ( ext != NULL ) {

        ext->width  = ( image->width  + n - 1 );
        ext->height = ( image->height + m - 1 );

        ext->r = extendEdges(image->r, image->width, image->height, padI, padJ);
        ext->g = extendEdges(image->g, image->width, image->height, padI, padJ);
        ext->b = extendEdges(image->b, image->width, image->height, padI, padJ);

        if ( ext->r != NULL && ext->g != NULL && ext->b != NULL ) {

            uint8_t * nr = convolve(ext->r, ext->width, ext->height, kernel, m, n);
            uint8_t * ng = convolve(ext->g, ext->width, ext->height, kernel, m, n);
            uint8_t * nb = convolve(ext->b, ext->width, ext->height, kernel, m, n);

            if ( nr != NULL && ng != NULL && nb != NULL ) {

                free(image->r);
                free(image->g);
                free(image->b);

                image->r = nr;
                image->g = ng;
                image->b = nb;

                persistImage(extended, "NBMDemos/images/mateus_extended.png", ImageFileFormatPNG);

            } else {

                free(nr);
                free(ng);
                free(nb);

            }

        } else {

            free(ext->r);
            free(ext->g);
            free(ext->b);

        }

    }

 }
