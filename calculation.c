#include "headers/calculation.h"

/// @brief Calculate the best solution to represent our figure with coordinates
/// @param I : BMP Image
/// @param l : Number of coordinates
/// @param targetDistance : Minimum distance of the perpendicular
/// @return the coordinates of our new figure

Coordinates *figureCoordinates(Image I, int *l, int distanceTarget)
{
    // Value of the vector
    int value = 0;
    // Memory allocation for our figure points
    Coordinates *figure = malloc(sizeof(Coordinates) * 500);
    int k = 0;
    // Distance between barycentre and nearest perpendicular point
    float distance = 0;
    // Trigonometry projection
    float *P = (float *)malloc(sizeof(float) * 2);
    // First coordinates to intercept on the bmp
    Coordinates coordinate = getFirstCoordinates(I);
    // Cuurent coordinates of our route
    Coordinates currentCoordinates = {coordinate.x, coordinate.y};
    // Coordinates of the previous starting point remembered
    Coordinates startCoord = {currentCoordinates.x, currentCoordinates.y};
    // Coordinates of the barycentre between the currentCoordinates and the start Coordinates
    Coordinates baryCoord = {0, 0};
    value = nextPixel(I, &currentCoordinates.y, &currentCoordinates.x, -1);
    k++;
    figure[*l] = startCoord;
    *l += 1;
    while (coordinate.x != currentCoordinates.x || coordinate.y != currentCoordinates.y)
    {
        // Reaching next colored pixel
        value = nextPixel(I, &currentCoordinates.y, &currentCoordinates.x, value);
        // Calculate Barycentre
        baryCoord = barycentre(startCoord, currentCoordinates);
        // Calculate Trigonometry
        P = projection(startCoord, baryCoord);
        // Calculate perpendicular distance
        distance = research(I, baryCoord, P);
        if (distance > distanceTarget)
        {
            figure[*l] = currentCoordinates;
            startCoord.x = currentCoordinates.x;
            startCoord.y = currentCoordinates.y;
            *l += 1;
        }
        k++;
    }
    return figure;
}

/// @brief Check if the 8 pixels around the current pixels is also a colored pixel
/// @param I : BMP Image
/// @param x : x coordinate
/// @param y : y coordinate
/// @param previous : previous pixel
/// @return the vector between the current pixel and the next colored pixel but also return the new coordinates with pointer
int nextPixel(Image I, int *x, int *y, int previous)
{
    int value = 0;
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
    return value;
}

/// @brief Calculate the barycentre between 2 coordinates
/// @param coordinatesA
/// @param coordinatesB
/// @return coordinates of the barycentre
Coordinates barycentre(Coordinates coordinatesA, Coordinates coordinatesB)
{
    Coordinates bary;
    bary.x = (coordinatesA.x + coordinatesB.x) / 2;
    bary.y = (coordinatesA.y + coordinatesB.y) / 2;
    return bary;
}

/// @brief Calculate the distance between 2 coordinates
/// @param coordinatesA
/// @param coordinatesB
/// @return the distance between 2 coordinates
float distance(Coordinates coordinatesA, Coordinates coordinatesB)
{
    return sqrt(pow((coordinatesB.x - coordinatesA.x), 2) + pow((coordinatesB.y - coordinatesA.y), 2));
}

/// @brief Calculate the projection of the perpendicular of the barycentre
/// @param coordinatesA
/// @param coordinatesB
/// @return trigonometry projection on x and y
float *projection(Coordinates coordinatesA, Coordinates coordinatesB)
{
    // Vérifier projection du coefficient directeur avec Clem
    float coefficientX = coordinatesB.x - coordinatesA.x;
    float coefficientY = coordinatesB.y - coordinatesA.y;
    float *proj = (float *)malloc(sizeof(float) * 2);
    if (coefficientX == 0)
    {
        proj[0] = 0;
        proj[1] = 1;
    }
    else if (coefficientY == 0)
    {
        proj[0] = 1;
        proj[1] = 0;
    }
    else
    {
        // Calculate the directing coefficient of the perpendicular of the barycentre
        float theta = atan(coefficientY / coefficientX);
        proj[0] = sin(theta); // X projection
        proj[1] = cos(theta); // Y Projection
    }
    return proj;
}

/// @brief Evaluate 8 pixels around current pixel.
/// If one is colored, calculate the distance between the pixel and the bary center,
/// @param inter : Coordinates of a point on the perpendicular on the barycentre
/// @param x : x coordinate of inter
/// @param y : y coordinate of inter
/// @param I : BMP Image
/// @param coordBary : Barycentre Coordinates
/// @return -1 : if no pixel found
/// distance : if pixel found
float evaluation(Image I, Coordinates inter, int x, int y, Coordinates coordBary)
{
    float d = 0;
    int found = 0;
    if (x + 1 >= I.height || y + 1 >= I.width || x - 1 <= -1 || y - 1 <= -1)
    {
        d = -1;
    }
    else
    {
        // Current
        if (I.rgb[x][y].red == 255 && I.rgb[x][y].green == 0 && I.rgb[x][y].blue == 0)
        {
            found = 1;
        }
        // Right
        else if (I.rgb[x][y + 1].red == 255 && I.rgb[x][y + 1].green == 0 && I.rgb[x][y + 1].blue == 0)
        {
            found = 1;
        }
        // Down Right
        else if (I.rgb[x + 1][y + 1].red == 255 && I.rgb[x + 1][y + 1].green == 0 && I.rgb[x + 1][y + 1].blue == 0)
        {
            found = 1;
        }
        // Down
        else if (I.rgb[x + 1][y].red == 255 && I.rgb[x + 1][y].green == 0 && I.rgb[x + 1][y].blue == 0)
        {
            found = 1;
        }
        // Down Left
        else if (I.rgb[x + 1][y - 1].red == 255 && I.rgb[x + 1][y - 1].green == 0 && I.rgb[x + 1][y - 1].blue == 0)
        {
            found = 1;
        }
        // Left
        else if (I.rgb[x][y - 1].red == 255 && I.rgb[x][y - 1].green == 0 && I.rgb[x][y - 1].blue == 0)
        {
            found = 1;
        }
        // Up Left
        else if (I.rgb[x - 1][y - 1].red == 255 && I.rgb[x - 1][y - 1].green == 0 && I.rgb[x - 1][y - 1].blue == 0)
        {
            found = 1;
        }
        // Up
        else if (I.rgb[x - 1][y].red == 255 && I.rgb[x - 1][y].green == 0 && I.rgb[x - 1][y].blue == 0)
        {
            found = 1;
        }
        // Up Right
        else if (I.rgb[x - 1][y + 1].red == 255 && I.rgb[x - 1][y + 1].green == 0 && I.rgb[x - 1][y + 1].blue == 0)
        {
            found = 1;
        }
    }

    if (found == 1)
    {
        d = distance(coordBary, inter);
    }
    else
    {
        d = -1;
    }

    return d;
}

/// @brief Search the distance between the barycentre and the nearest colored pixel
/// @param I : BMP Image
/// @param coordBary : Coordinates of the Barycentre
/// @param P : Trigonometry projection
/// @return distance
float research(Image I, Coordinates coordBary, float *P)
{
    int j = 0;
    int i = 1;
    float d = -1;
    // P : Tableau des projections multipliés par un facteur entier dans un while de la boucle main (si question demander à César)
    Coordinates inter = {coordBary.x + P[0], coordBary.y + P[1]};
    Coordinates newCoord = {0, 0};

    while (d == -1)
    {
        if (j % 2 == 0)
        {
            newCoord.x = i * P[0] + inter.x;
            newCoord.y = i * P[1] + inter.y;
        }
        else
        {
            newCoord.x = -i * P[0] + inter.x;
            newCoord.y = -i * P[1] + inter.y;
            i++;
        }
        d = evaluation(I, newCoord, newCoord.y, newCoord.x, coordBary);
        j++;
    }
    return d;
}
