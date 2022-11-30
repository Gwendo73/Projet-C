#include "calculation.h"

void freemanArray(Image I)
{
    int *vectors = (int *)malloc(sizeof(int) * 500);
    Coordinates *figure = (Coordinates *)malloc(sizeof(Coordinates) * 100);
    int k = 0;
    int l = 0;
    double directingCoefficient = 0;
    float P[2] = {0, 0};
    Coordinates coordinate = getCoordinates(I);
    Coordinates newCoordinate = {coordinate.y, coordinate.x};
    Coordinates startCoord = {newCoordinate.x, newCoordinate.y};
    Coordinates interCoord = {0, 0};
    vectors[k] = freemanCase(I, &newCoordinate.x, &newCoordinate.y, -1);
    k++;
    while (coordinate.x != newCoordinate.y || coordinate.y != newCoordinate.x)
    {
        if (k > 0) { // Si distance superieur à XXX alors on change de point de départ
            figure[l] = startCoord;
            startCoord.x = newCoordinate.x;
            startCoord.y = newCoordinate.y;
            l++;
        }
        vectors[k] = freemanCase(I, &newCoordinate.x, &newCoordinate.y, vectors[k - 1]);
        /// Nouvelles fonctions
        interCoord = barycentre(startCoord, newCoordinate);
        directingCoefficient = coefdir(startCoord, interCoord);
        P = projection(directingCoefficient);
        interCoord = coordIntersection(P, interCoord); // remplacer intercoord
        /// 
        k++;
    }
    int *newVectors = (int *)malloc(sizeof(int) * k);
    Coordinates *newFigure = (Coordinates *)malloc(sizeof(Coordinates) * l);
    for (int i = 0; i < k; i++)
    {
        newVectors[i] = vectors[i];
        printf("%d", newVectors[i]);
    }
    for (int i = 0; i < l; i++)
    {
        newFigure[i] = figure[i];
    }
    free(vectors);
    free(figure);
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

// Calcul du coefficent directeur de la droite partant du barycentre et perpendiculaire à (D,A)

double coefdir(Coordinates coordinateA, Coordinates coordinateB)
{
    return ((coordinateB.x - coordinateA.x) / (coordinateB.y - coordinateA.y));
}

// Calcul de la dictance entre le barycentre et la point évalué.

double distance(Coordinates coordinateI, Coordinates coordinateJ)
{
    return sqrt(pow((coordinateJ.x - coordinateI.x), 2) + pow((coordinateJ.x - coordinateI.y), 2));
}

// Retourne les projections sur x et y 

float* projection(double dirCo)
{
    double theta = atan(dirCo);
    float *proj = (float *)malloc(sizeof(float) * 2);
    proj[0] = cos(theta); // projection sur x
    proj[1] = sin(theta); // projection sur y
    return proj;
}


 // P : Tableau des projections multipliés par un facteur entier dans un while de la boucle main (si question demander à César)

Coordinates coordIntersection (float* P, Coordinates coordBary)
{
    Coordinates inter = {coordbary.x * P[0], coordbary.y * P[1]};
    return inter;     
}


//- évaluer les 8 cases autour du point de coordonées inter calculées à la fonction CoordIntersection
//- Regarder si une d'entre elles est rouge 
//- Si oui, calcul de la distance entre inter et le barycentre 
//- Si non, passage au point suivant 

float Evaluation (Coordinates inter, Image I, Coordinates coordbary, double dst)
{
    float d;
    int found = 0;

    if (I.rgb[inter.x][inter.y].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        found = 1;
    }
    // Droite
    else if (I.rgb[inter.x][inter.y+1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        found = 1;
    }
    //Diagonale droite bas
    else if (I.rgb[inter.x+1][inter.y+1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        found = 1;
    }
    //Bas
    else if (I.rgb[inter.x+1][inter.y].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        found = 1;
    }
    //Diagonale gauche bas
    else if (I.rgb[inter.x+1][inter.y-1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        found = 1;
    }
    //Gauche
    else if (I.rgb[inter.x][inter.y-1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        found = 1;
    }
    //Diagonale gauche haut 
    else if (I.rgb[inter.x-1][inter.y-1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        found = 1;
    }
    //Haut 
    else if (I.rgb[inter.x-1][inter.y].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        found = 1;
    }
    //Diagonale haut droite
    else if (I.rgb[inter.x-1][inter.y+1].red == 255 && I.rgb[inter.x][inter.y].green == 0 && I.rgb[inter.x][inter.y].blue == 0){
        found = 1;
    }

    if(found == 1) {
        d = distance(coordbary, inter);
    }
    else {
        d = -1;
    }

    return d;
}