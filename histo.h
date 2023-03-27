#include <stdio.h>	
#include <math.h>	// Librairie permettant les opérations de mathématiques anciennes
#include <dirent.h> // Librairie permettant la manipulation des fichiers / repertoires
#include <string.h> // Librairie permettant la manipulation des strings :)
#include "CImg.h"	// Librairie recommandée par J.Romuald afin de manipuler les images


#define MAX 1000
using namespace cimg_library; // ?? mais obligatoire
/**
 * @file        main.cpp
 * @brief       Contient la fonction main ainsi que toutes les autres fonction
 * @author      Sinclair MOULAGER <sinclair.moulager@etu.univ-st-etienne.fr>
 * @version     1
 * @date        2022
 */



float compare_histograms(CImg<unsigned char> img1, CImg<unsigned char> img2);
float compare_histograms2(CImg<unsigned char> img1, char *image2);