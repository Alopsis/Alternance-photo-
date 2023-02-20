#include<stdio.h>
#include <math.h>
#include <dirent.h>
#include <string.h>
#include "CImg.h"
using namespace cimg_library;

int  halogramme_réactif(){// exemple lib CImg.h 
	  CImg<unsigned char> image("Images/02.jpg"), visu(500,400,1,3,0);
  	const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
  	image.blur(2.5);
  	CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile");
  	while (!main_disp.is_closed() && !draw_disp.is_closed()) {
    	main_disp.wait();
    	if (main_disp.button() && main_disp.mouse_y()>=0) {
     		const int y = main_disp.mouse_y();
      		visu.fill(0).draw_graph(image.get_crop(0,y,0,0,image.width()-1,y,0,0),red,1,1,0,255,0);
      		visu.draw_graph(image.get_crop(0,y,0,1,image.width()-1,y,0,1),green,1,1,0,255,0);
      		visu.draw_graph(image.get_crop(0,y,0,2,image.width()-1,y,0,2),blue,1,1,0,255,0).display(draw_disp);
    	}
	}
  return 0;
}
int calcul_nombre_image(){
	DIR* rep = NULL;
	char ** images;
	int nbimage=0;
    struct dirent* fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */

    rep = opendir("./Images"); /* Ouverture d'un dossier */

    if (rep == NULL){ /* Si le dossier n'a pas pu être ouvert */
        
	}    
	printf("Le dossier a ete ouvert avec succes\n");
	
	
	while ((fichierLu = readdir(rep)) != NULL){
		if( strcmp(fichierLu->d_name,".")!=0 && strcmp(fichierLu->d_name,"..") != 0 ){
			images[nbimage] = fichierLu->d_name;
			nbimage++;
		}	
	}
    if (closedir(rep) == -1){ /* S'il y a eu un souci avec la fermeture */
       
	}
	return nbimage;
}

char ** place_nom_image_tab(){
 	DIR* rep = NULL;
	char ** images;
	int nbimage=0;
    struct dirent* fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */

    rep = opendir("./Images"); /* Ouverture d'un dossier */

    if (rep == NULL){ /* Si le dossier n'a pas pu être ouvert */
	}
	while ((fichierLu = readdir(rep)) != NULL){
		if( strcmp(fichierLu->d_name,".")!=0 && strcmp(fichierLu->d_name,"..") != 0 ){
			images[nbimage] = fichierLu->d_name;
			nbimage++;
		}	
	}
    if (closedir(rep) == -1){ /* S'il y a eu un souci avec la fermeture */
       
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

float compare_histograms(CImg<unsigned char> img1, CImg<unsigned char> img2) {
  CImg<unsigned char> hist1 = img1.get_histogram(256); // fait l'histogramme de l'img 1
  CImg<unsigned char> hist2 = img2.get_histogram(256); // fait l'histogramme de l'img 2
	float proche;
  // calcul de la distance euclidienne entre les 2 histo 
	float distance = 0.0;
  for (int i = 0; i < 256; i++) {
    distance += pow(hist1(i) - hist2(i), 2); // SOMME((xB -xA)^2 + (yB - yA)^2)
  }
  distance = sqrt(distance); // Racine de distance pour la formule de la distance euclidienne 
	proche = distance / sqrt(255 * 255 * 256); // puisque ce sont les bins possibles 
  printf("L'image est proche a : %f\n",proche);

  // Return the normalized distance (in the range [0, 1])
  return proche;
}


float compare_histograms2(CImg<unsigned char> img1, char * image2) {
  CImg<unsigned char> hist1 = img1.get_histogram(256); // fait l'histogramme de l'img 1
  CImg<unsigned char> img2(image2);
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
  printf("L'image est proche a : %f\n",proche);
 
  // tourne la distance des images  ||| valeur entre 0 et 1 
  return proche;
}



int main() {
	
	CImg<unsigned char> image("Images/01.jpg"); // On lit l'image fournit en parametre
	CImg<unsigned char> image2("Images/02.jpg");
	char test[200] = "Images/03.jpg";
	CImg<unsigned char> imagetest(test);
CImg <unsigned char>* imageatest;
	char ** liste_image;
	char ** liste_lien_image;
	char  transitoire[50];
	char * liste_imagee;
	int i;
	int nombre_image;
	char image_src[200];
	liste_image = place_nom_image_tab();
	nombre_image = calcul_nombre_image();
	for(i=0;i<nombre_image;i++){
		printf("%s\n",liste_image[i]);
	}
	for(i=0;i<nombre_image ; i++ ){
		strcpy(image_src,"Images/");
		
		strcat(image_src,liste_image[i]);
		printf("Nous allons voir \"%s\" \n",image_src);
		strcpy(liste_lien_image[i],image_src);
		//compare_histograms2(image2,image_src);
		//compare_histograms2(image2,image_src);		
	}	
	for(i=0;i<nombre_image;i++){
		printf("%s\n",liste_lien_image[i]);
		compare_histograms2(image2,liste_lien_image[i]);
	}
	//compare_histograms2(image,liste_image[0]);

	exit(EXIT_SUCCESS);
}