#include <stdio.h>	// Librairie In Out standard
#include <math.h>	// Librairie permettant les opérations de mathématiques anciennes
#include <dirent.h> // Librairie permettant la manipulation des fichiers / repertoires
#include <string.h> // Librairie permettant la manipulation des strings :)
#include "CImg.h"	// Librairie recommandée par J.Romuald afin de manipuler les images

#define MAX 1000
using namespace cimg_library; // ?? mais obligatoire


typedef struct couleurs{
    char * nom;
    int r;
    int g;
    int b;
}couleurs;


void compare_image(CImg<unsigned char> image2);
void compare_image_et_insertion(CImg<unsigned char> image2, char nom[]);
void enlever_image(int ligne,int nb_image);
void verification_image_fichier(char **nom_images, int nb_image);
void compare_image_plus_proche(char * image_original);

void tri_image(char nom_images[][100],int * r , int * g , int * b ,int actuelle );