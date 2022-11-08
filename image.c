#include <stdio.h>
#include <stdlib.h>
#include "image.h"

Image readImage(FILE *f, int height, int width)
{
    Image I;
    I.rgb = (RGB **)malloc(height * sizeof(void *));
    I.height = height;
    I.width = width;

    for (int i = height - 1; i >= 0; i--)
    {
        I.rgb[i] = (RGB *)malloc(width * sizeof(RGB));
        fread(I.rgb[i], width, sizeof(RGB), f);
    }
    return I;
}

void freeImage(Image I)
{
    for (int i = I.height - 1; i >= 0; i--)
    {
        free(I.rgb[i]);
    }
    free(I.rgb);
}

void getCoordinates(Image I)
{
    int coordinates[2][2] = {0};
    int k = 0;
    for (int i = 0; i < I.height; i++)
    {
        for (int j = 0; j < I.width; j++)
        {
            if (I.rgb[i][j].red == 255 && I.rgb[i][j].green == 0 && I.rgb[i][j].blue == 0)
            {
                coordinates[k][0] = j;
                coordinates[k][1] = i;
                k++;
            }
        }
    }
    for (int k = 0; k < 2; k++)
    {
        printf("Coordonnée x : %d \nCoordonnée y : %d \n\n", coordinates[k][0], coordinates[k][1]);
    }
}