#include<stdio.h> // Librairie In Out standard 
#include <math.h> // Librairie permettant les opérations de mathématiques anciennes 
#include <dirent.h> // Librairie permettant la manipulation des fichiers / repertoires 
#include <string.h> // Librairie permettant la manipulation des strings :)
#include "CImg.h" // Librairie recommandée par J.Romuald afin de manipuler les images 
using namespace cimg_library; // ?? mais obligatoire 
/**
 * @file        main.cpp
 * @brief       Contient la fonction main ainsi que toutes les autres fonction
 * @author      Sinclair MOULAGER <sinclair.moulager@etu.univ-st-etienne.fr>
 * @version     1
 * @date        2022
*/
int calcul_nombre_image(){
	DIR* rep = NULL;
	char ** images;
	int nbimage=0;
    struct dirent* fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */
    rep = opendir("./Images"); /* Ouverture d'un dossier */
    if (rep == NULL){ /* Si le dossier n'a pas pu être ouvert */
		fprintf(stderr,"Erreur lors de l'ouverture du dossier\n");
	}
	else{
		printf("Le dossier a ete ouvert avec succes\n");
	}
	
	while ((fichierLu = readdir(rep)) != NULL){
		if( strcmp(fichierLu->d_name,".")!=0 && strcmp(fichierLu->d_name,"..") != 0 ){
			images[nbimage] = fichierLu->d_name;
			nbimage++;
		}	
	}
    if (closedir(rep) == -1){ /* S'il y a eu un souci avec la fermeture */
		fprintf(stderr,"Erreur lors de la fermeture du fichier \n");
	}
	return nbimage;
}


char ** place_nom_image_tab(){
 	DIR* rep = NULL;
	char ** images;
	int nbimage=0;
    struct dirent* fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */
    rep = opendir("./Images"); /* Ouverture d'un dossier */
    if (rep == NULL){ 
		fprintf(stderr,"Erreur lors de l'ouverture du dossier\n");
	}
	while ((fichierLu = readdir(rep)) != NULL){
		if( strcmp(fichierLu->d_name,".")!=0 && strcmp(fichierLu->d_name,"..") != 0 ){
			images[nbimage] = fichierLu->d_name;
			nbimage++;
		}	
	}
    if (closedir(rep) == -1){ /* S'il y a eu un souci avec la fermeture */
		fprintf(stderr,"Erreur lors de la fermeture du fichier \n");  
	}
	return images;
}
CImg<unsigned char>  symetriegauche(CImg<unsigned char> image){
	int i,j;
	CImg<unsigned char> image_return;
	for (i=0; i<image.width();i++){ // On parcours sur la largeur de l'image
		for (j=0; j<image.height();j++){ // On parcours sur la hauteur de l'image
			image_return(i,j,0)=image(j,i,0); // Symetrie pour rouge (0)
			image_return(i,j,1)=image(j,i,1); // Symetrie pour vert (1)
			image_return(i,j,2)=image(j,i,2); // Symetrie pour bleu (2)
		}
	}
	printf("La taille de votre image est de %d en hauteur et %d en largeur \n",image.width(), image.height());
	return image_return;
}
int compare(CImg<unsigned char> image,CImg<unsigned char> image2){
	int i,j;
	int acc = 0 , valeurpixel = 0;
	for ( i=0; i<image.width() || i<image2.width();i++){
		for(j=0;j<image.height() || j<image2.height(); j++ ) {
			/*printf("%d\n",image(j,i,0));*/
			printf("%d %d %d\n",image(i,j,0),image2(i,j,0),abs(image(i,j,0)-image2(i,j,0)));
			valeurpixel = valeurpixel + abs(image(i,j,0)-image2(i,j,0));
			acc++;
		}
	}
	printf("La valeur moyen de vos pixels sont %d \n",valeurpixel/acc);
	return 1;
}

/* 
Marche pas 
*/

float compare_histograms(CImg<unsigned char> img1, CImg<unsigned char> img2) {
  	CImg<unsigned char> hist1 = img1.get_histogram(256); // fait l'histogramme de l'img 1
  	CImg<unsigned char> hist2 = img2.get_histogram(256); // fait l'histogramme de l'img 2
	//float proche;
	float  distance = 0.0;
	int i;
  	for (i = 0; i < 256; i++) {  // calcul de la distance euclidienne entre les 2 histo --> SOMME((xB -xA)^2 + (yB - yA)^2)
    	distance = distance + pow(hist1(i) - hist2(i), 2); 
  	}
	/*
  	distance = sqrt(distance); // Racine de distance pour la formule de la distance euclidienne 
	printf("%f\n",distance);
	proche = distance / sqrt(255 * 255 * 256); // puisque ce sont les bins possibles 
 	printf("L'image est proche a : %f\n",proche);
 	// retourne la distance noramlisé entre 1 et 0 
	
  	return proche;
	*/
	return 0.0;
}

/* 
Marche pas 
*/

float compare_histograms2(CImg<unsigned char> img1, char * image2) {
  	CImg<unsigned char> hist1 = img1.get_histogram(256); // fait l'histogramme de l'img 1
  	CImg<unsigned char> img2("Images/04.jpg");
  	CImg<unsigned char> hist2 = img2.get_histogram(256); // fait l'histogramme de l'img 2
	float proche;
	float distance = 0.0;
	printf("On va ouvrir l'image : %s \n" ,image2);
  	// calcul de la distance euclidienne entre les 2 histo 
  	for (int i = 0; i < 256; i++) {
    	distance += pow(hist1(i) - hist2(i), 2); // SOMME((xB -xA)^2 + (yB - yA)^2)
  	}
  	distance = sqrt(distance); // Racine de distance pour la formule de la distance euclidienne 
	proche = distance / sqrt(255 * 255 * 256); // puisque ce sont les bins possibles 
  	//printf("L'image est proche a : %f\n",proche); // print de la valeur sur le terminal 
  	// retourne la distance des images  ||| valeur entre 0 et 1 
  	return proche;
}
char * recuperation_image_indice_formatage(int i){
	DIR* rep = NULL;
	char * image = ( char * ) malloc(sizeof(char) * 256);
	char * image_source = (char*) malloc(sizeof(char) * 256);
	int nbimage=0;
    struct dirent* fichierLu = NULL; // Déclaration d'un pointeur vers la structure dirent. 
    rep = opendir("./Images"); // Ouverture d'un dossier 
	while ((fichierLu = readdir(rep)) != NULL){
		if( (strcmp(fichierLu->d_name,".")!=0) && (strcmp(fichierLu->d_name,"..") != 0) ){
			if(nbimage == i ){
				strcpy(image_source,"./Images/");
				image = fichierLu->d_name;
				strcat(image_source,image);
				return image_source;
			}
			nbimage++;
		}		
	}
	closedir(rep); // Fermeture du dossier
    free(image_source); // Libération de la mémoire allouée pour image_source si y'a une erreur 
    return NULL;
} 
void compare_image(CImg <unsigned char> image2){
	int width1 = image2.width();
	int height1 = image2.height();
	int i , j ;
	int red = 0;
	int  green = 0;
	int  blue = 0;
	for( i = 0 ; i < height1 ; i++ ){
		for( j = 0 ; j < width1 ; j++ ){
	  	    //printf("Pixel (%d,%d) - Rouge: %d, Vert: %d, Bleu: %d\n", i, j, image2(i,j,0,0), image2(i,j,0,1), image2(i,j,0,2));
			red = red + image2(j,i,0,0);
			green = green + image2(j,i,0,1);
			blue = blue + image2(j,i,0,2);
			//printf("Pixel vert = %d \n",image2(i,j,0,2));
		}
	}
	red = red / ( width1 * height1 );
	green = green / ( width1 * height1 );
	blue = blue / ( width1 * height1 );
	printf("Pixel rgb moyen de l'image : (R: %d, G: %d , B: %d )\n",red,green,blue);
	
}
int main() {
	CImg<unsigned char> ("Images/04.jpg"); // On lit l'image fournit en parametre
		
	int i , nombre_image;
	//char * image_src;
	nombre_image = calcul_nombre_image();
	//printf("test ( si pas de printf ici y'a un seg fault ) \n");
	
for(i=0;i<nombre_image;i++){
		char * image_src = recuperation_image_indice_formatage(i);
		printf("%s\n",image_src);
		CImg <unsigned char> image1(image_src);
		compare_image(image1);
		free(image_src);
	}
	exit(0);
}