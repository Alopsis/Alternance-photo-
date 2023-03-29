#include <stdio.h>
#include <stdlib.h>
#include "forme.h" 
#include "divers.h"
#include "couleurs.h" 
#include "histo.h"

void verification_image_fichier_forme(char **nom_images, int nb_image)
{
	int ligne = 0;
	int i;
	char * nom_image = NULL;
	int tab[MAX];
	int acc = 0;
	int rgb_red, rgb_green, rgb_blue;
	char  source[500];
	FILE *fichier = NULL;

	nom_image =(char * ) malloc(500* sizeof(char));
	if(nom_image == NULL){
		printf("erreur d'alloc memoire ! \n");
	}

	for (i = 0; i < nb_image; i++)
	{
		tab[i] = 0;
	}

	/****************************************/
	/*Affichage des valeurs de nom_images[i]*/
	/****************************************/
	for (i = 0; i < nb_image; i++)
	{
		printf(" ->> %s\n", nom_images[i]);
	}
	printf("\n\n");

	/**********************************************************************/
	/*Boucle permettant de savoir si l'image doit etre traitée ou enlevée */
	/**********************************************************************/
	fichier = fopen("couleurs.txt", "r");
	while (fscanf(fichier, "%s %d %d %d", nom_image, &rgb_red, &rgb_green, &rgb_blue) == 4)
	{
		
		acc = 0;
		for (i = 0; i < nb_image; i++)
		{
			if (strcmp(nom_image, nom_images[i]) == 0)
			{
				tab[i] = 1;
				break;
			}
			else
			{
				acc++;
			}
		}
		if (acc == nb_image)
		{
			printf("L'image %s doit etre enlevée\n", nom_image);
			enlever_image(ligne,nb_image);
			printf("fin\n");
			/******************************************/
			/*IMAGES A RETIRER DANS LE FICHIER A GERER*/
			/******************************************/
		}
		ligne++;
	}
	fclose(fichier);

	/****************************************/
	/*Affichage des valeurs de nom_images[i]*/
	/****************************************/
	printf("\n\n");
	for (i = 0; i < nb_image; i++)
	{
		printf("->>> %s\n", nom_images[i]);
	}
	for (i = 0; i < nb_image; i++)
	{
		if (tab[i] == 0)
		{
			strcpy(source,"./Images/");
			printf("test1\n");
			strcat(source,nom_images[i]);
			printf("L'image \"%s\" doit etre mise\n", nom_images[i]);
			CImg<unsigned char> image1(source);
			compare_image_et_insertion(image1,nom_images[i]);
			printf("fin\n");
		}
	}
}