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

    //printPixels(I);
    
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

Coordinates getCoordinates(Image I)
{
    int found = 1;
    Coordinates coordinate = {0, 0};

        for (int i = 0; i < I.height; i++)
        {
            for (int j = 0; j < I.width; j++)
            {
                if (found == 1)
                {
                    if (I.rgb[i][j].red == 255 && I.rgb[i][j].green == 0 && I.rgb[i][j].blue == 0)
                    {
                    
                        found = 0;
                        coordinate.x = j;
                        coordinate.y = i;
                        break;
                    }
                }
            }
        }
    return coordinate;
}

void printPixels(Image I) {
    for (int i = 0; i < I.height; i++ )
    {
        for (int j = 0; j < I.width; j++ )
        {
            printf("Ligne %d Colonne %d : %u %u %u \n", i, j, I.rgb[i][j].red, I.rgb[i][j].green, I.rgb[i][j].blue);
        }
    }
}

void createImage(BMPHeader header, BMPInfo info, Image I)
{
    FILE *f = fopen("newPixel.bmp", "w");
    fwrite(header.name, 2, 1, f);
    fwrite(&header.size, 3 * sizeof(int), 1, f);
    fwrite(&info, sizeof(BMPInfo), 1, f);

    for (int i = I.height - 1; i >= 0; i--)
    {
        fwrite(I.rgb[i], I.width, sizeof(RGB), f);
    }
    fclose(f);
}



void freemanArray(Image I) {
    int array[100] = {};
    int k = 0;
    Coordinates coordinate = getCoordinates(I); // x/j: 17, y/i: 17
    int i = coordinate.y;
    int j = coordinate.x;
    printf("i : %d, j : %d \n", i, j);
    // En haut 
    if (I.rgb[i + 1][j].red == 255 && I.rgb[i + 1][j].green == 0 && I.rgb[i + 1][j].blue == 0)
    {
        printf("0");
        array[k] = 0;
        i++;
    }
    // En haut à droite 
    else if (I.rgb[i + 1][j+1].red == 255 && I.rgb[i + 1][j+1].green == 0 && I.rgb[i + 1][j+1].blue == 0)
    {
        printf("1");
        array[k] = 1;
        i++;
        j++;
    }
    // A droite
    else if (I.rgb[i][j + 1].red == 255 && I.rgb[i][j + 1].green == 0 && I.rgb[i][j + 1].blue == 0)
    {
        printf("2");
        array[k] = 2;
        j++;
    }
    // En bas à droite
    else if (I.rgb[i - 1][j + 1].red == 255 && I.rgb[i - 1][j + 1].green == 0 && I.rgb[i - 1][j + 1].blue == 0)
    {
        printf("3");
        array[k] = 3;
        i--;
        j++;
    }
    // En bas
    else if (I.rgb[i - 1][j].red == 255 && I.rgb[i - 1][j].green == 0 && I.rgb[i - 1][j].blue == 0)
    {
        printf("4");
        array[k] = 4;
        i--;
    }
    // En bas à gauche
    else if (I.rgb[i - 1][j - 1].red == 255 && I.rgb[i - 1][j - 1].green == 0 && I.rgb[i - 1][j - 1].blue == 0)
    {
        printf("5");
        array[k] = 5;
        i--;
        j--;
    }
    // A gauche
    else if (I.rgb[i][j - 1].red == 255 && I.rgb[i][j - 1].green == 0 && I.rgb[i][j - 1].blue == 0)
    {
        printf("6");
        array[k] = 6;
        j--;
    }
    // En haut à gauche
    else if (I.rgb[i + 1][j - 1].red == 255 && I.rgb[i + 1][j - 1].green == 0 && I.rgb[i + 1][j - 1].blue == 0)
    {
        printf("7");
        array[k] = 7;
        i++;
        j--;
    }
    k++;
}
   
    
