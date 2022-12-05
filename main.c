#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "image.h"
#include "calculation.h"
#include "gcode.h"


int main()
{
    FILE *bitmapfile = fopen("coeur.bmp", "rb");
    BMPHeader header;
    BMPHeader *headerptr = &header;
    BMPInfo info;
    BMPInfo *infoptr = &info;
    int l = 0;


    readBMPHeader(bitmapfile, headerptr, infoptr);
    //printBMPHeader(header.name, header, info);

    fseek(bitmapfile, header.offsetbits, SEEK_SET);
    Image image = readImage(bitmapfile, info.height, info.width);

    //getCoordinates(image);
    //createImage(header, info, image);
    Coordinates *coordinates = (Coordinates *)malloc(sizeof(Coordinates) * 500);
    coordinates = freemanArray(image, &l);
    Coordinates *coordinatesAdapted = (Coordinates *)malloc(sizeof(Coordinates) * l);
    for (int i = 0; i < l; i++)
    {
        coordinatesAdapted[i] = coordinates[i];
        printf("%d, x : %d, y : %d\n", i + 1, coordinatesAdapted[i].x, coordinatesAdapted[i].y);
    }
    free(coordinates);

    createGCode(coordinatesAdapted, l);
    free(coordinatesAdapted);

    fclose(bitmapfile);
    freeImage(image);
    return 0;
}