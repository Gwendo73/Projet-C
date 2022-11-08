#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

void readBMPHeader(FILE *bitmapfile, BMPHeader *header, BMPInfo *info)
{ 
    if (bitmapfile == NULL)
    {
        printf("Error when reading...!\n");
        exit(-1);
    }
    fread(&header->name, sizeof(char), 2, bitmapfile);
    fread(&header->size, 12, 1, bitmapfile);
    fread(info, sizeof(BMPInfo), 1, bitmapfile);
}

void printBMPHeader(char name[2], BMPHeader header, BMPInfo info)
{
    printf("Type de bitmap\n");
    printf("%c%c\n", name[0], name[1]);
    printf("Taille de bitmap on octets:\n");
    printf("%u\n", header.size);
    printf("reserved1 :\n");
    printf("%d\n", header.garbage);
    printf("Data offset de la bitmap\n");
    printf("%u\n\n", header.offsetbits);

    printf("Taille de l'entete:\n");
    printf("%u\n", info.size);
    printf("Largeur de l'image:\n");
    printf("%u\n", info.width);
    printf("Hauteur de l'image:\n");
    printf("%u\n", info.height);
    printf("Nombre de planes:\n");
    printf("%d\n", info.planes);
    printf("Bits par pixels:\n");
    printf("%d\n", info.bitcount);
    printf("Mode de compression:\n");
    printf("%u\n", info.compression);
    printf("Taille de l'image:\n");
    printf("%u\n", info.sizeimage);
    printf("Pixels horizontaux:\n");
    printf("%u\n", info.xpelspermeter);
    printf("Pixels verticaux:\n");
    printf("%u\n", info.ypelspermeter);
    printf("Palette:\n");
    printf("%u\n", info.colorsused);
    printf("Important:\n");
    printf("%u\n", info.colorsimportant);
}