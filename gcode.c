#include "headers/gcode.h"

/// @brief Create a txt file with our coordinates that we allow us to run G-Code
/// @param coord : Coordinates of our figure
/// @param l : Number of coordinates
void createGCode(Coordinates *coord, int l)
{
    FILE *f = fopen("result/gcode.txt", "w");

    if(f == NULL) {
        printf("Error when reading...!\n");
        exit(-1);
    }

    for (int i = 0; i < l; i++)
    {
        if (i < 10)
        {
            fprintf(f, "N0%d G01 X%d Y%d\n", i, coord[i].x, coord[i].y);
        }
        else
        {
            fprintf(f, "N%d G01 X%d Y%d\n", i, coord[i].x, coord[i].y);
        }
    }
    if (l < 10)
    {
        fprintf(f, "N0%d G01 X%d Y%d", l, coord[0].x, coord[0].y);
    }
    else
    {
        fprintf(f, "N%d G01 X%d Y%d", l, coord[0].x, coord[0].y);
    }
    printf("Le fichier gcode.txt a bien été enregistré sous le dossier result\n");
    fclose(f);
}