#include <stdio.h>	// Librairie In Out standard
#include <math.h>	// Librairie permettant les opérations de mathématiques anciennes
#include <dirent.h> // Librairie permettant la manipulation des fichiers / repertoires
#include <string.h> // Librairie permettant la manipulation des strings :)
#include "CImg.h"	// Librairie recommandée par J.Romuald afin de manipuler les images

#define MAX 1000
using namespace cimg_library; // ?? mais obligatoire



int calcul_nombre_image();
char **place_nom_image_tab(int nb_image);
char *recuperation_image_indice_formatage(int i);
void affichage_image(int nombre_image);
void affichage_fichier();
int verification_argument_fichier(char * image);