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
    int *vectors = (int *)malloc(sizeof(int) * 500);
    int k = 0;
    Coordinates coordinate = getCoordinates(I);
    int x = coordinate.y;
    int y = coordinate.x;
    vectors[k] = freemanCase(I, &x, &y, -1);
    k++;
    while (coordinate.x != x || coordinate.y != y)
    {
        vectors[k] = freemanCase(I, &x, &y, vectors[k - 1]);
        k++;
    }
    int *newVectors = (int *)malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++) {
        newVectors[i] = vectors[i];
        printf("%d", newVectors[i]);
    }
    free(vectors);
    free(newVectors);
}

int freemanCase (Image I, int* x, int* y, int previous) {

    int value = 0;
    //printf("x : %d, y : %d, %u %u %u\n", *x, *y, I.rgb[*x][*y].red, I.rgb[*x][*y].blue, I.rgb[*x][*y].green);
    // Right
    if (I.rgb[*x][*y + 1].red == 255 && I.rgb[*x][*y + 1].green == 0 && I.rgb[*x][*y + 1].blue == 0 && previous != 4)
    {
        value = 0;
        *y += 1;
    }
    
    // Down Right
    else if (I.rgb[*x + 1][*y + 1].red == 255 && I.rgb[*x + 1][*y + 1].green == 0 && I.rgb[*x + 1][*y + 1].blue == 0 && previous != 5)
    {
        value = 1;
        *x += 1;
        *y += 1;
    }
    // Down
    else if (I.rgb[*x + 1][*y].red == 255 && I.rgb[*x + 1][*y].green == 0 && I.rgb[*x + 1][*y].blue == 0 && previous != 6)
    {
        value = 2;
        *x += 1;
    }
    // Down Left
    else if (I.rgb[*x + 1][*y - 1].red == 255 && I.rgb[*x + 1][*y - 1].green == 0 && I.rgb[*x + 1][*y - 1].blue == 0 && previous != 7)
    {
        value = 3;
        *x += 1;
        *y -= 1;
    }
    // Left
    else if (I.rgb[*x][*y - 1].red == 255 && I.rgb[*x][*y - 1].green == 0 && I.rgb[*x][*y - 1].blue == 0 && previous != 0)
    {
        value = 4;
        *y -= 1;
    }
    // Up Left
    else if (I.rgb[*x - 1][*y - 1].red == 255 && I.rgb[*x - 1][*y - 1].green == 0 && I.rgb[*x - 1][*y - 1].blue == 0 && previous != 1)
    {
        value = 5;
        *x -= 1;
        *y -= 1;
    }
    // Up
    else if (I.rgb[*x - 1][*y].red == 255 && I.rgb[*x - 1][*y].green == 0 && I.rgb[*x - 1][*y].blue == 0 && previous != 2)
    {
        value = 6;
        *x -= 1;
    }
    // Up Right
    else if (I.rgb[*x - 1][*y + 1].red == 255 && I.rgb[*x - 1][*y + 1].green == 0 && I.rgb[*x - 1][*y + 1].blue == 0 && previous != 3)
    {
        value = 7;
        *x -= 1;
        *y += 1;
    }
    //printf("%d\n", value);
    return value;
}

