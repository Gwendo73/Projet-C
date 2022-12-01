#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"

void freemanArray(Image I);
int freemanCase(Image I, int *x, int *y, int previous);
Coordinates barycentre(Coordinates coordinateA, Coordinates coordinateB);
double coefdir(Coordinates coordinateA, Coordinates coordinateB);
double distance(Coordinates coordinateA, Coordinates coordinateB);
float* projection(double dirCo);
float Evaluation (Coordinates inter, Image I, Coordinates coordBary);
float recherche(Image I, Coordinates coordBary, float *P);