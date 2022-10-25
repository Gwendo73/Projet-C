#include <stdio.h>
#include <stdlib.h>
 
typedef struct
{
    char name[2];
    unsigned int size;
    int garbage1;
    unsigned int offsetbits;
} bmpheader;

typedef struct
{
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitcount;
    unsigned int compression;
    unsigned int sizeimage;
    unsigned int xpelspermeter;
    unsigned int ypelspermeter;
    unsigned int colorsused;
    unsigned int colorsimportant;
} bmpinfo;

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGB;

typedef struct {
    int height;
    int width;
    RGB **rgb;
} Image;

Image readImage(FILE *f, int height, int width);
void freeImage(Image I);
void RGBImageToGray(Image I);
void BlackAndWhite(bmpheader header, bmpinfo info, Image I);
void readbmpheader(char *bitmapfilename);

Image readImage(FILE *f, int height, int width)
{
    printf("Début de lecture sur ReadImage\n");
    Image I;
    I.rgb = (RGB**) malloc(height * sizeof(void *));
    I.height = height;
    I.width = width;

    for (int i = height - 1; i >= 0; i--) {
        I.rgb[i] = (RGB*) malloc(width * sizeof(RGB));
        fread(I.rgb[i], width, sizeof(RGB), f);
    }
    printf("Fin de lecture sur ReadImage\n");
    return I;
}

void freeImage(Image I) {
    printf("Début de lecture sur freeImage\n");
    for (int i = I.height - 1; i >= 0; i--) {
        free(I.rgb[i]);
    }
    free(I.rgb);
    printf("Fin de lecture sur freeImage\n");
}

unsigned char grayscale(RGB rgb) {
    return ((0.2126 * rgb.red) + (0.7152 * rgb.green) + (0.0722 * rgb.blue));
}

void RGBImageToGray(Image I) {
    printf("Début de lecture sur RGBImageToGray\n");
    for (int i = 0; i < I.height; i++) {
        for (int j = 0; j < I.width; j++) {
            I.rgb[i][j].red = grayscale(I.rgb[i][j]);
            I.rgb[i][j].green = grayscale(I.rgb[i][j]);
            I.rgb[i][j].blue = grayscale(I.rgb[i][j]);
        }
    }
    printf("Fin de lecture sur RGBImageToGray\n");
}

void BlackAndWhite(bmpheader header, bmpinfo info, Image I)
{
    printf("Début de lecture sur BlackAndWhite\n");
    FILE *f = fopen("nonRecommend.bmp", "w");
    fwrite(header.name, 2, 1, f);
    fwrite(&header.size, 3 * sizeof(int), 1, f);
    fwrite(&info, sizeof(bmpinfo), 1, f);

    RGBImageToGray(I);

    for (int i = I.height - 1; i >= 0; i--)
    {
        fwrite(I.rgb[i], I.width, sizeof(RGB), f);
    }
    fclose(f);
    printf("Fin de lecture sur BlackAndWhite\n");
}
void readbmpheader(char *bitmapfilename)
{
    FILE *bitmapfile;
    bmpheader header;
    bmpinfo info;
    bitmapfile = fopen(bitmapfilename, "rb");
    if (bitmapfile == NULL)
    {
        printf("Error when reading...!\n");
        exit(-1);
    }

    fread(&header.name, sizeof(char), 2, bitmapfile);
    printf("Type de bitmap\n");
    printf("%c%c\n", header.name[0], header.name[1]);
    fread(&header.size, 12, 1, bitmapfile);
    printf("Taille de bitmap on octets:\n");
    printf("%u\n", header.size);
    printf("reserved1 :\n");
    printf("%d\n", header.garbage1);
    printf("Data offset de la bitmap\n");
    printf("%u\n\n", header.offsetbits);

    fread(&info, sizeof(bmpinfo), 1, bitmapfile);
    printf("Taille de l'entete:\n");
    printf("%u\n", info.size);
    printf("Largeur de l'image:\n");
    printf("%u\n", info.width);
    printf("Hauteur de l'image:\n");
    printf("%u\n", info.height);
    printf("Nombre de planes:\n");
    printf("%d\n", info.planes);
    printf("Bits par pixels:\n");
    printf("%d\n", info.bitcount);
    printf("Mode de compression:\n");
    printf("%u\n", info.compression);
    printf("Taille de l'image:\n");
    printf("%u\n", info.sizeimage);
    printf("Pixels horizontaux:\n");
    printf("%u\n", info.xpelspermeter);
    printf("Pixels verticaux:\n");
    printf("%u\n", info.ypelspermeter);
    printf("Palette:\n");
    printf("%u\n", info.colorsused);
    printf("Important:\n");
    printf("%u\n", info.colorsimportant);


    fseek(bitmapfile, header.offsetbits, SEEK_SET);
    Image image = readImage(bitmapfile, info.height, info.width);
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            printf("%d %d %d /", image.rgb[i][j].red, image.rgb[i][j].green, image.rgb[i][j].blue);
        }
        printf("\n");
    }
    BlackAndWhite(header, info, image);
    fclose(bitmapfile);
    freeImage(image);
}

int main()
{
    readbmpheader("Gndal.bmp");
    return 0;
}