#include <stdio.h>	
#include <math.h>	// Librairie permettant les opérations de mathématiques anciennes
#include <dirent.h> // Librairie permettant la manipulation des fichiers / repertoires
#include <string.h> // Librairie permettant la manipulation des strings :)
#include "CImg.h"	// Librairie recommandée par J.Romuald afin de manipuler les images


#define MAX 1000
using namespace cimg_library; // ?? mais obligatoire

typedef struct {
    char * nom ;
    float valeur;
}histo;



float compare_histograms(char * image1, char * image2);
float compare_histograms2(CImg<unsigned char> img1, char *image2);
void creation_histogramme_image(char * image_reference);
void trier_histogramme(histo  hist[1000]);