#include <stdio.h>
#include <stdlib.h>
#include "headers/bmp.h"
#include "headers/image.h"
#include "headers/calculation.h"
#include "headers/gcode.h"

int main(int argc, char *argv[])
{
    FILE *file = fopen("img/coeur.bmp", "rb");
    BMPHeader header;
    BMPHeader *headerptr = &header;
    BMPInfo info;
    BMPInfo *infoptr = &info;
    Coordinates *coordinates = (Coordinates *)malloc(sizeof(Coordinates) * 500);
    int l = 0;

    readBMPHeader(file, headerptr, infoptr);
    // printBMPHeader(header.name, header, info);

    fseek(file, header.offsetbits, SEEK_SET);
    Image image = readImage(file, info.height, info.width);

    // createImage(header, info, image);

    coordinates = figureCoordinates(image, &l);
    Coordinates *coordinatesAdapted = (Coordinates *)malloc(sizeof(Coordinates) * l);
    for (int i = 0; i < l; i++)
    {
        coordinatesAdapted[i] = coordinates[i];
    }
    free(coordinates);

    createGCode(coordinatesAdapted, l);
    free(coordinatesAdapted);

    fclose(file);
    freeImage(image);
    return 0;
}