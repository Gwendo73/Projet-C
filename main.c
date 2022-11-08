#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "image.h"

void getCoordinates(Image I);

void getCoordinates(Image I) {
    int coordinates[2][2] = {0};
    int k = 0;
    for (int i = 0; i < I.height; i++)
    {
        for (int j = 0; j < I.width; j++)
        {
            if (I.rgb[i][j].red == 255 && I.rgb[i][j].green == 0 && I.rgb[i][j].blue == 0) {
                coordinates[k][0] = j;
                coordinates[k][1] = i;
                k++;
            }
        }
    }
    for (int k = 0; k < 2; k++) {
        printf("Coordonnée x : %d \nCoordonnée y : %d \n\n", coordinates[k][0], coordinates[k][1]);
    }
}



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