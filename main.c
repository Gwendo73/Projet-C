#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "image.h"


int main()
{
    FILE *bitmapfile = fopen("pixel.bmp", "rb");
    BMPHeader header;
    BMPHeader *headerptr = &header;
    BMPInfo info;
    BMPInfo *infoptr = &info;

    readBMPHeader(bitmapfile, headerptr, infoptr);
    //printBMPHeader(&header.name, header, info);

    fseek(bitmapfile, header.offsetbits, SEEK_SET);
    Image image = readImage(bitmapfile, info.height, info.width);

    getCoordinates(image);
    
    fclose(bitmapfile);
    freeImage(image);
    return 0;
}