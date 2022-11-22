#include "calculation.h"

void freemanArray(Image I)
{
    int *vectors = (int *)malloc(sizeof(int) * 500);
    int k = 0;
    Coordinates coordinate = getCoordinates(I);
    Coordinates newCoordinate = {coordinate.y, coordinate.x};
    Coordinates startCoord;
    vectors[k] = freemanCase(I, &newCoordinate.x, &newCoordinate.y, -1);
    k++;
    while (coordinate.x != newCoordinate.y || coordinate.y != newCoordinate.x)
    {
        startCoord = newCoordinate;
        vectors[k] = freemanCase(I, &newCoordinate.x, &newCoordinate.y, vectors[k - 1]);
        coefdir(startCoord, newCoordinate);
        k++;
    }
    int *newVectors = (int *)malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++)
    {
        newVectors[i] = vectors[i];
        printf("%d", newVectors[i]);
    }
    free(vectors);
    free(newVectors);
}

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

float* perpendiculaire(double codir)
{
    float Proj[2]
    double theta = atan(codir);
    Proj[0] = cos(theta);    // projection sur x
    Proj[1] = sin(theta);    // projection sur y 
    return Proj;
}


// P : Tableau des projections multipliés par un facteur entier dans un while de la boucle main (si question demander à César)

 Coordinates CoordIntersection (int* P, Coordinates coordbary)
 {
    Coordinates inter;
    inter.x = coordbary.x * P[0];
    inter.y = coordbary.y * P[1];
    return inter;     
    }
 
float Evaluation (Coordinates inter, Image I, Coordinates coordbary, double dst)
{
    float d; 
    if (I.rgb[inter.x][inter.y].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        d = distance(coordbary, inter);
    }
    // Droite
    if (I.rgb[inter.x][inter.y+1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        d = distance(coordbary, inter);
    }
    //Diagonale droite bas
    if (I.rgb[inter.x+1][inter.y+1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        d = distance(coordbary, inter);
    }
    //Bas
    if (I.rgb[inter.x+1][inter.y].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        d = distance(coordbary, inter);
    }
    //Diagonale gauche bas
    if (I.rgb[inter.x+1][inter.y-1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        d = distance(coordbary, inter);
    }
    //Gauche
    if (I.rgb[inter.x][inter.y-1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        d = distance(coordbary, inter);
    }
    //Diagonale gauche haut 
    if (I.rgb[inter.x-1][inter.y-1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        d = distance(coordbary, inter);
    }
    //Haut 
    if (I.rgb[inter.x-1][inter.y].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        d = distance(coordbary, inter);
    }
    //Diagonale haut droite
    if (I.rgb[inter.x-1][inter.y+1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        d = distance(coordbary, inter);
    }
    //if ()

}