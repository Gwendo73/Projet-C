#include <stdlib.h>
#include <math.h>
#include "image.h"

#ifndef _CALCULATION_H_
#define _CALCULATION_H_

Coordinates* freemanArray(Image I, int *l);
int freemanCase(Image I, int *x, int *y, int previous);
Coordinates barycentre(Coordinates coordinateA, Coordinates coordinateB);
float distance(Coordinates coordinateA, Coordinates coordinateB);
float *projection(Coordinates coordinateA, Coordinates coordinateB);
float evaluation(Coordinates inter, int x, int y, Image I, Coordinates coordBary);
float recherche(Image I, Coordinates coordBary, float *P);

#endif