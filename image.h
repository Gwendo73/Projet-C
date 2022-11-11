#include <stdio.h>
#include <stdlib.h>

#ifndef _IMAGE_H_
#define _IMAGE_H_

// RGB becomes BGR because we read the file upside-down
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
void getCoordinates(Image I);

#endif