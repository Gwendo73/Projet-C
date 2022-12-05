#include "calculation.h"

Coordinates* freemanArray(Image I, int *l)
{
    int value = 0;
    Coordinates *figure = malloc(sizeof(Coordinates) * 500);
    int k = 0;
    float distance = 0;
    float *P = (float *)malloc(sizeof(float) * 2);
    Coordinates coordinate = getCoordinates(I);
    Coordinates newCoordinate = {coordinate.x, coordinate.y};
    Coordinates startCoord = {newCoordinate.x, newCoordinate.y};
    Coordinates baryCoord = {0, 0};
    value = freemanCase(I, &newCoordinate.y, &newCoordinate.x, -1);
    k++;
    figure[*l] = startCoord;
    *l += 1;
    while (coordinate.x != newCoordinate.x || coordinate.y != newCoordinate.y)
    {
        value = freemanCase(I, &newCoordinate.y, &newCoordinate.x, value);
        /// Nouvelles fonctions
        baryCoord = barycentre(startCoord, newCoordinate);
        P = projection(startCoord, baryCoord);
        distance = recherche(I, baryCoord, P);
        if (distance > 10)
        { // Si distance superieur à XXX alors on change de point de départ
            figure[*l] = newCoordinate;
            startCoord.x = newCoordinate.x;
            startCoord.y = newCoordinate.y;
            *l += 1;
        }
        ///
        k++;
    }
    return figure;
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


// Calcul de la dictance entre le barycentre et la point évalué.

float distance(Coordinates coordinateI, Coordinates coordinateJ)
{
    return sqrt(pow((coordinateJ.x - coordinateI.x), 2) + pow((coordinateJ.y - coordinateI.y), 2));
}

// Retourne les projections sur x et y

float *projection(Coordinates coordinateA, Coordinates coordinateB)
{
    // Vérifier projection du coefficient directeur avec Clem
    float coefficientX = coordinateB.x - coordinateA.x;
    float coefficientY = coordinateB.y - coordinateA.y;
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
        // Calcul du coefficent directeur de la droite partant du barycentre et perpendiculaire à (D,A)
        float theta = atan(coefficientY / coefficientX);
        proj[0] = sin(theta); // projection sur x
        proj[1] = cos(theta); // projection sur y
    }

    //printf("P[0] : %f, P[1] : %f\n", proj[0], proj[1]);
    return proj;
}

//- Evaluer les 8 cases autour du point de coordonées inter calculées à la fonction CoordIntersection
//- Regarder si une d'entre elles est rouge
//- Si oui, calcul de la distance entre inter et le barycentre
//- Si non, passage au point suivant

float evaluation(Coordinates inter, int x, int y, Image I, Coordinates coordBary)
{
    float d = 0;
    int found = 0;
    if (x + 1 >= I.height || y + 1 >= I.width || x - 1 <= -1 || y - 1 <= -1)
    {
        d = -1;
    }
    else
    {
        if (I.rgb[x][y].red == 255 && I.rgb[x][y].green == 0 && I.rgb[x][y].blue == 0)
        {
            found = 1;
        }
            // Droite
        else if (I.rgb[x][y + 1].red == 255 && I.rgb[x][y + 1].green == 0 && I.rgb[x][y + 1].blue == 0)
        {
            found = 1;
        }
            // Diagonale droite bas
        else if (I.rgb[x + 1][y + 1].red == 255 && I.rgb[x + 1][y + 1].green == 0 && I.rgb[x + 1][y + 1].blue == 0)
        {
            found = 1;
        }
            // Bas
        else if (I.rgb[x + 1][y].red == 255 && I.rgb[x + 1][y].green == 0 && I.rgb[x + 1][y].blue == 0)
        {
            found = 1;
        }
            // Diagonale gauche bas
        else if (I.rgb[x + 1][y - 1].red == 255 && I.rgb[x + 1][y - 1].green == 0 && I.rgb[x + 1][y - 1].blue == 0)
        {
            found = 1;
        }
            // Gauche
        else if (I.rgb[x][y - 1].red == 255 && I.rgb[x][y - 1].green == 0 && I.rgb[x][y - 1].blue == 0)
        {
            found = 1;
        }
            // Diagonale gauche haut
        else if (I.rgb[x - 1][y - 1].red == 255 && I.rgb[x - 1][y - 1].green == 0 && I.rgb[x - 1][y - 1].blue == 0)
        {
            found = 1;
        }
            // Haut
        else if (I.rgb[x - 1][y].red == 255 && I.rgb[x - 1][y].green == 0 && I.rgb[x - 1][y].blue == 0)
        {
            found = 1;
        }
            // Diagonale haut droite
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

float recherche(Image I, Coordinates coordBary, float *P)
{
    int j = 0;
    int i = 1;
    float d = -1;
    Coordinates inter = {coordBary.x + P[0], coordBary.y + P[1]}; // P : Tableau des projections multipliés par un facteur entier dans un while de la boucle main (si question demander à César)
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
        d = evaluation(newCoord, newCoord.y, newCoord.x, I, coordBary);
        j++;
    }
    return d;
}
