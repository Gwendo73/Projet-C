#include "calculation.h"

int freemanCase(Image I, int *x, int *y, int previous)
{
    int value = 0;
    // printf("x : %d, y : %d, %u %u %u\n", *x, *y, I.rgb[*x][*y].red, I.rgb[*x][*y].blue, I.rgb[*x][*y].green);
    //  Right
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
    // printf("%d\n", value);
    return value;
}

/* Calcul des coordonées du barycentre entre 2 points (fonction intermédiaire)*/

Coordinates barycentre(Coordinates coordinateA, Coordinates coordinateB)
{
    Coordinates bary;
    bary.x = (coordinateA.x + coordinateB.x) / 2;
    bary.y = (coordinateA.y + coordinateB.y) / 2;
    return bary;
}

double coefdir(Coordinates coordinateA, Coordinates coordinateB)
{
    return ((coordinateB.x - coordinateA.x) / (coordinateB.y - coordinateA.y));
}

double distance(Coordinates coordinateI, Coordinates coordinateJ)
{
    return sqrt(pow((coordinateJ.x - coordinateI.x), 2) + pow((coordinateJ.x - coordinateI.y), 2));
}

int perpendiculaire(double codir)
{
    int x1, y1, x2, y2;
    double theta;
    theta = atan(codir);
    x1 = cos(theta);
    y1 = sin(theta);
    x2 = -cos(theta);
    y2 = -sin(theta);
}