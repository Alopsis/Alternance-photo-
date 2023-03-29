#include <stdio.h>	// Librairie In Out standard
#include <math.h>	// Librairie permettant les opérations de mathématiques anciennes
#include <dirent.h> // Librairie permettant la manipulation des fichiers / repertoires
#include <string.h> // Librairie permettant la manipulation des strings :)
#include "CImg.h"	// Librairie recommandée par J.Romuald afin de manipuler les images

#define MAX 1000
using namespace cimg_library; // ?? mais obligatoire


void verification_image_fichier_forme(char **nom_images, int nb_image);
void enlever_image_forme(int ligne,int nb_image);
void compare_image_et_insertion_forme(CImg<unsigned char> image2, char nom[]);