#include "divers.h" 
#include "histo.h"
#include "couleurs.h"

/* Commentaire */
int calcul_nombre_image()
{
	DIR *rep = NULL;
	char images[1000][100] ;
	int nbimage = 0;
    int i;
	struct dirent *fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */

	rep = opendir("./Images");		 /* Ouverture d'un dossier */
	if (rep == NULL)
	{ /* Si le dossier n'a pas pu être ouvert */
		fprintf(stderr, "Erreur lors de l'ouverture du dossier\n");
		exit(0);
	}
	else
	{
		printf("Le dossier a ete ouvert avec succes\n");
	}
	while ((fichierLu = readdir(rep)) != NULL)
	{
		if (strcmp(fichierLu->d_name, ".") != 0 && strcmp(fichierLu->d_name, "..") != 0)
		{
			strcpy(images[nbimage],fichierLu->d_name);
			nbimage++;
		}
	}
	
	if (closedir(rep) == -1)
	{ /* S'il y a eu un souci avec la fermeture */
		fprintf(stderr, "Erreur lors de la fermeture du fichier \n");
		exit(0);
	}
	
	return nbimage;
}


char **place_nom_image_tab(int nb_image)
{
	DIR *rep = NULL;
	int nbimage = 0;
	char **images = (char **)malloc(sizeof(char *) * nb_image);
	struct dirent *fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */
	rep = opendir("./Images");		 /* Ouverture d'un dossier */
	if (rep == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du dossier\n");
	}

	while ((fichierLu = readdir(rep)) != NULL)
	{
		if (strcmp(fichierLu->d_name, ".") != 0 && strcmp(fichierLu->d_name, "..") != 0)
		{
			images[nbimage] = fichierLu->d_name;
			nbimage++;
		}
	}
	if (closedir(rep) == -1)
	{ /* S'il y a eu un souci avec la fermeture */
		fprintf(stderr, "Erreur lors de la fermeture du fichier \n");
	}
	return images;
}

char *recuperation_image_indice_formatage(int i)
{
	DIR *rep = NULL;
	char *image = (char *)malloc(sizeof(char) * 256);
	char *image_source = (char *)malloc(sizeof(char) * 256);
	int nbimage = 0;
	struct dirent *fichierLu = NULL; // Déclaration d'un pointeur vers la structure dirent.
	rep = opendir("./Images");		 // Ouverture d'un dossier
	while ((fichierLu = readdir(rep)) != NULL)
	{
		if ((strcmp(fichierLu->d_name, ".") != 0) && (strcmp(fichierLu->d_name, "..") != 0))
		{
			if (nbimage == i)
			{
				strcpy(image_source, "./Images/");
				image = fichierLu->d_name;
				strcat(image_source, image);
				return image_source;
			}
			nbimage++;
		}
	}
	closedir(rep);		// Fermeture du dossier
	free(image_source); // Libération de la mémoire allouée pour image_source si y'a une erreur
	return NULL;
}


void affichage_image(int nombre_image)
{
	int i;
	for (i = 0; i < nombre_image; i++)
	{
		char *image_src = recuperation_image_indice_formatage(i);
		printf("%s\n", image_src);
		CImg<unsigned char> image1(image_src);
		compare_image(image1);
		free(image_src);
	}
}



void affichage_fichier()
{
	FILE *fichier = fopen("couleurs.txt", "r");
	int couleur_rgb_fichier[3];
	char nom_image_fichier[100];
	if (fichier == NULL)
	{
		printf("Erreur d'ouverture du fichier\n");
		exit(0);
	}
	while (fscanf(fichier, "%s %d %d %d", nom_image_fichier, &couleur_rgb_fichier[0], &couleur_rgb_fichier[1], &couleur_rgb_fichier[2]) == 4)
	{

		printf("%s %d %d %d \n", nom_image_fichier, couleur_rgb_fichier[0], couleur_rgb_fichier[1], couleur_rgb_fichier[2]);
	}
	fclose(fichier);
	fichier = NULL;
}

char *recuperation_image_nom_indice_formatage(int i)
{
	DIR *rep = NULL;
	char *image = (char *)malloc(sizeof(char) * 256);
	int nbimage = 0;
	struct dirent *fichierLu = NULL; // Déclaration d'un pointeur vers la structure dirent.
	rep = opendir("./Images");		 // Ouverture d'un dossier
	while ((fichierLu = readdir(rep)) != NULL)
	{
		if ((strcmp(fichierLu->d_name, ".") != 0) && (strcmp(fichierLu->d_name, "..") != 0))
		{
			if (nbimage == i)
			{
				image = fichierLu->d_name;
				closedir(rep);
				return image;
			}
			nbimage++;
		}
	}
	closedir(rep);		// Fermeture du dossier
	return NULL;
}

int verification_argument_fichier(char * image){
	int i;
	int nb_image;
	DIR *rep = NULL;
	struct dirent * fichierLu = NULL;
	rep = opendir("./Images");
	nb_image = calcul_nombre_image();
	while ((fichierLu = readdir(rep)) != NULL){
		if ( strcmp(fichierLu->d_name,image) == 0){
			closedir(rep);
			return 1;
		}
	}
	closedir(rep);
	return 0;
	
}
