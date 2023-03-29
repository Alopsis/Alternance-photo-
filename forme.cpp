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
	int rgb_red[9], rgb_green[9], rgb_blue[9];
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
	fichier = fopen("couleurs_forme.txt", "r");
	while (fscanf(fichier, "%s",nom_image) == 1 && 
		   fscanf(fichier,"%d %d %d %d %d %d %d %d %d",&rgb_red[0],&rgb_red[1],&rgb_red[2],&rgb_red[3],&rgb_red[4],&rgb_red[5],&rgb_red[6],&rgb_red[7],&rgb_red[8]) == 9 &&
		   fscanf(fichier,"%d %d %d %d %d %d %d %d %d",&rgb_green[0],&rgb_green[1],&rgb_green[2],&rgb_green[3],&rgb_green[4],&rgb_green[5],&rgb_green[6],&rgb_green[7],&rgb_green[8]) == 9 &&
		   fscanf(fichier,"%d %d %d %d %d %d %d %d %d",&rgb_blue[0],&rgb_blue[1],&rgb_blue[2],&rgb_blue[3],&rgb_blue[4],&rgb_blue[5],&rgb_blue[6],&rgb_blue[7],&rgb_blue[8]) == 9
		   )
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
			//enlever_image_forme(ligne,nb_image);
			/* a refaire ! */
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
			strcat(source,nom_images[i]);
			printf("L'image \"%s\" doit etre mise\n", nom_images[i]);
			CImg<unsigned char> image1(source);
			compare_image_et_insertion_forme(image1,nom_images[i]);
			/* a refairle !*/
		}
	}
}

void enlever_image_forme(int ligne,int nb_image){

}

void compare_image_et_insertion_forme(CImg<unsigned char> image2, char nom[]){
	int width1 = image2.width();
	int height1 = image2.height();
	int i, j;
	 unsigned long int **rgb_red  = (unsigned  long int ** ) malloc ( sizeof(unsigned  long int *));
	 unsigned  long int **rgb_green = (unsigned  long int ** ) malloc ( sizeof(unsigned  long int *));
	 unsigned long int **rgb_blue = (unsigned  long int ** ) malloc ( sizeof(unsigned  long int *));
	 unsigned long int ** test = ( unsigned long int ** ) malloc ( sizeof(unsigned  long int *));
	FILE *fichier;

	for(i=0;i<3;i++){
		rgb_red[i]  = ( unsigned  long int * ) calloc ( 3,sizeof(unsigned  long int));
		rgb_green[i] = ( unsigned  long int * ) calloc ( 3,sizeof(unsigned  long int));
		rgb_blue[i] = ( unsigned  long int * ) calloc ( 3,sizeof(unsigned  long int));
		 test[i]= ( unsigned  long int * ) calloc ( 3,sizeof(unsigned  long int));
	}
	/**********************/
	/* Partie Comparaison */
	/**********************/
	/* a changer ! */
	/*printf("Debut de la simple boucle \n");
	for(i=0;i<10;i++){
		if(i == 9 ){
			printf("->%d \n",(i/(10/3))-1);
		}else {
		printf("%d \n",i/(10/3));
		}
	}
	printf("Fin de la simple boucle \n");
	printf("Debut de la double boucle \n");
	for(i=0;i<10;i++){
				printf(" %deme etape ! \n",i);

		for(j=0;j<10;j++){
			if ( j == 9 && i == 9 ){
				printf(" %d et %d \n",(i/(10/3))-1,(j/(10/3))-1);
			}
			else if( j == 9){
				printf(" %d et %d \n",(i/(10/3)) , (j/(10/3))-1);
			}else if ( i == 9){
				printf(" %d et %d \n",(i/(10/3))-1,(j/(10/3)));
			}else {
				printf(" %d et %d \n",(i/(10/3)), (j/(10/3)));

			}
		}
		printf("\n");
	}*/
	printf("Debut de la grosse fctn \n");
	printf(" %d et %d \n",width1,height1);
	for (i = 0; i < width1; i++)
	{
		for (j = 0; j < height1; j++)
		{	
			printf("%d et %d \n",i,j);
			//printf("Itt et %d et %d \n",i,j);
			if ( i == width1-1 && j == height1-1){
				rgb_red[(i/(width1/3))-1][(j/(height1/3))-1] = rgb_red[(i/(width1/3))-1][(j/(height1/3))-1] + image2(j, i, 0, 0);
				rgb_green[(i/(width1/3))-1][(j/(height1/3))-1] = rgb_green[(i/(width1/3))-1][(j/(height1/3))-1] + image2(j, i, 0, 1);
				rgb_blue[(i/(width1/3))-1][(j/(height1/3))-1] = rgb_blue[(i/(width1/3))-1][(j/(height1/3))-1] + image2(j, i, 0, 2);
			}else if ( i == width1-1){
				rgb_red[(i/(width1/3))-1][(j/(height1/3))] = rgb_red[(i/(width1/3))-1][(j/(height1/3))] + image2(j, i, 0, 0);
				rgb_green[(i/(width1/3))-1][(j/(height1/3))] = rgb_green[(i/(width1/3))-1][(j/(height1/3))] + image2(j, i, 0, 1);
				rgb_blue[(i/(width1/3))-1][(j/(height1/3))] = rgb_blue[(i/(width1/3))-1][(j/(height1/3))] + image2(j, i, 0, 2);
			}else if ( j == height1-1){
				rgb_red[(i/(width1/3))][(j/(height1/3))-1] = rgb_red[(i/(width1/3))][(j/(height1/3))-1] + image2(j, i, 0, 0);
				rgb_green[(i/(width1/3))][(j/(height1/3))-1] = rgb_green[(i/(width1/3))][(j/(height1/3))-1] + image2(j, i, 0, 1);
				rgb_blue[(i/(width1/3))][(j/(height1/3))-1] = rgb_blue[(i/(width1/3))][(j/(height1/3))-1] + image2(j, i, 0, 2);
			}else {
				rgb_red[(i/(width1/3))][(j/(height1/3))] = rgb_red[(i/(width1/3))][(j/(height1/3))] + image2(j, i, 0, 0);
				rgb_green[(i/(width1/3))][(j/(height1/3))] = rgb_green[(i/(width1/3))][(j/(height1/3))] + image2(j, i, 0, 1);
				rgb_blue[(i/(width1/3))][(j/(height1/3))] = rgb_blue[(i/(width1/3))][(j/(height1/3))] + image2(j, i, 0, 2);
			}
			
		}
	}
	/*
	for(i=0;i<9;i++){
		rgb_red[i] = rgb_red[i] / ((width1 * height1)/9);
		rgb_green[i] = rgb_green[i] / ((width1 * height1)/9);
		rgb_blue[i] = rgb_blue[i] / ((width1 * height1)/9);
	}
	*/
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
		printf("%ld ",test[i][j]);

		}
		printf("\n");
		//printf("%d %d %d\n",rgb_red[i],rgb_green[i],rgb_blue[i]);
	}

	/* Fin a changer */
	/********************/
	/* Partie insertion */
	/********************/
	fichier = fopen("couleurs_forme.txt", "a");
	/*fprintf(fichier,"%s\n",nom);
   	fprintf(fichier,"%d %d %d %d %d %d %d %d %d\n",rgb_red[0],rgb_red[1],rgb_red[2],rgb_red[3],rgb_red[4],rgb_red[5],rgb_red[6],rgb_red[7],rgb_red[8]);
   	fprintf(fichier,"%d %d %d %d %d %d %d %d %d\n",rgb_green[0],rgb_green[1],rgb_green[2],rgb_green[3],rgb_green[4],rgb_green[5],rgb_green[6],rgb_green[7],rgb_green[8]);
   	fprintf(fichier,"%d %d %d %d %d %d %d %d %d\n",rgb_blue[0],rgb_blue[1],rgb_blue[2],rgb_blue[3],rgb_blue[4],rgb_blue[5],rgb_blue[6],rgb_blue[7],rgb_blue[8]);
*/
	fclose(fichier);
	for(i=0;i<3;i++){
		free(rgb_red[i]);
		free(rgb_green[i]);
		free(rgb_blue[i]);
		free(test[i]);

	}
	free(rgb_red);
	free(rgb_green);
	free(rgb_blue);
	free(test);
}