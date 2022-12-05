#include "gcode.h"

void createGCode(Coordinates *coord, int l)
{
    FILE *f = fopen("gcode.txt", "w");

    for (int i = 0; i < l; i++)
    {
        if (i < 10)
        {
            fprintf(f, "N0%d G01 X%d Y%d", i, coord[i].x, coord[i].y);
        } 
        else 
        {
            fprintf(f, "N%d G01 X%d Y%d", i, coord[i].x, coord[i].y);
        }
        if(i < l - 1) {
            fprintf(f, "\n");
        }
    }
    fclose(f);
}