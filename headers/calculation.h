#include <stdlib.h>
#include <math.h>
#include "image.h"

#ifndef _CALCULATION_H_
#define _CALCULATION_H_

Coordinates* figureCoordinates(Image I, int *l);
int nextPixel(Image I, int *x, int *y, int previous);
Coordinates barycentre(Coordinates coordinatesA, Coordinates coordinatesB);
float distance(Coordinates coordinatesA, Coordinates coordinatesB);
float *projection(Coordinates coordinatesA, Coordinates coordinatesB);
float evaluation(Image I, Coordinates inter, int x, int y, Coordinates coordBary);
float research(Image I, Coordinates coordBary, float *P);

#endif