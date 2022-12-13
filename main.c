#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/bmp.h"
#include "headers/image.h"
#include "headers/calculation.h"
#include "headers/gcode.h"

int main(int argc, char *argv[])
{
    BMPHeader header;
    BMPHeader *headerptr = &header;
    BMPInfo info;
    BMPInfo *infoptr = &info;
    Coordinates *coordinates = (Coordinates *)malloc(sizeof(Coordinates) * 500);
    FILE *file = NULL;
    int targetDistance = 0;
    int l = 0;
    if(argc == 3) {
        char *fileName = (char *)malloc(strlen("img/") + strlen(argv[1]) + 2);
        strcpy(fileName, "img/");
        strcat(fileName, argv[1]);
        targetDistance = atoi(argv[2]);
        file = fopen(fileName, "rb");
        free(fileName);
    }
    else
    {
        printf("Wrong use : ./main fileName distance\n");
        printf("Le fichier ouvert sera un coeur avec une distance de 5 par défaut\n\n");
        targetDistance = 5;
        file = fopen("img/heart.bmp", "rb");
    }
    readBMPHeader(file, headerptr, infoptr);
    printBMPHeader(header.name, header, info);

    fseek(file, header.offsetbits, SEEK_SET);
    Image image = readImage(file, info.height, info.width);

    // createImage(header, info, image);

    coordinates = figureCoordinates(image, &l, targetDistance);
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