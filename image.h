#include <stdio.h>
#include <stdlib.h>

#ifndef _IMAGE_H_
#define _IMAGE_H_

typedef struct
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} RGB;

typedef struct
{
    int height;
    int width;
    RGB **rgb;
} Image;

Image readImage(FILE *f, int height, int width);
void freeImage(Image I);

#endif