#include <stdio.h>
#include <stdlib.h>

#ifndef _BMP_H_
#define _BMP_H_

typedef struct
{
    char name[2];
    unsigned int size;
    int garbage;
    unsigned int offsetbits;
} BMPHeader;

typedef struct
{
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitcount;
    unsigned int compression;
    unsigned int sizeimage;
    unsigned int xpelspermeter;
    unsigned int ypelspermeter;
    unsigned int colorsused;
    unsigned int colorsimportant;
} BMPInfo;

void readBMPHeader (FILE* file, BMPHeader *header, BMPInfo *info);
void printBMPHeader (char* name, BMPHeader header, BMPInfo info);

#endif