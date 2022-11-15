#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

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

typedef struct 
{
    int x;
    int y;
} Coordinates;

Image readImage(FILE *f, int height, int width);
void freeImage(Image I);
Coordinates getCoordinates(Image I);
void printPixels(Image I);
void createImage(BMPHeader header, BMPInfo info, Image I);
void freemanArray(Image I);

#endif