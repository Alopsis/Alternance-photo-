#include <stdio.h>	// Librairie In Out standard
#include <math.h>	// Librairie permettant les opérations de mathématiques anciennes
#include <dirent.h> // Librairie permettant la manipulation des fichiers / repertoires
#include <string.h> // Librairie permettant la manipulation des strings :)
#include "CImg.h"	// Librairie recommandée par J.Romuald afin de manipuler les images
#include "couleurs.h"
#include "divers.h" 
#include "histo.h"

#define MAX 1000
using namespace cimg_library; // ?? mais obligatoire
/**
 * @file        main.cpp
 * @brief       Contient la fonction main ainsi que toutes les autres fonction
 * @author      Sinclair MOULAGER <sinclair.moulager@etu.univ-st-etienne.fr>
 * @version     1
 * @date        2022
 */

int main(int argc , char * argv[])
{

	CImg <unsigned char>image_originel("Images/04.jpg"); // On lit l'image fournit en parametre
	int nombre_image;
	int choix;
	char **nom_toutes_les_images;
	if(argc<2){
		printf("<image a test> \n");
		exit(0);
	}
	if ( verification_argument_fichier(argv[1]) == 1){
		printf("Votre image est valide ! \n");
	}else {
		printf("Votre image est invalide ! \n");
		exit(0);
	}

	/*********************************/
	/*Ici on compte le nombre d'image*/
	/*********************************/
	nombre_image = calcul_nombre_image();
	/**************************************/
	/*Ici on print uniquement les couleurs*/
	/**************************************/
	//affichage_image(nombre_image);

	/*************************************************************/
	/*Ici on stock toutes les images ( les noms ) dans un tableau*/
	/*************************************************************/

	nom_toutes_les_images = place_nom_image_tab(nombre_image);

	printf("Comment voulez vous trier les images ? ( 1 pour couleur | 2 pour histogramme | 3 pour forme ) \n");
	scanf("%d",&choix);

	if(choix == 1 ){
		/*********************************************************************/
		/*Ici on va verifier que toutes les images sont dans le fichier texte*/
		/*********************************************************************/

		verification_image_fichier(nom_toutes_les_images, nombre_image);
		/*Fonction qui trie et rempli un tableau avec les valeurs les plus proches */
		compare_image_plus_proche(argv[1]);
	}
	else if( choix == 2 ){

	}
	else if ( choix == 3 ){

	}else {
		printf("Votre demande est Incorrect \n");
	}


	exit(0);
}