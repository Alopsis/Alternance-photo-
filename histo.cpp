#include "histo.h" 
#include "couleurs.h" 
#include "divers.h" 


float compare_histograms(char * image1, char * image2)
{
	CImg<unsigned char> img1(image1);
	CImg<unsigned char> img2(image2);
	CImg<unsigned char> hist1 = img1.get_histogram(256); // fait l'histogramme de l'img 1
	CImg<unsigned char> hist2 = img2.get_histogram(256); // fait l'histogramme de l'img 2
	float proche;
	float distance = 0.0;
	int i;
	for (i = 0; i < 256; i++)
	{ // calcul de la distance euclidienne entre les 2 histo --> SOMME((xB -xA)^2 + (yB - yA)^2)
		distance = distance + pow(hist1(i) - hist2(i), 2);
	}
	
	distance = sqrt(distance); // Racine de distance pour la formule de la distance euclidienne
	printf("distance = %f",distance);
	proche = distance / sqrt(255 * 255 * 256); // puisque ce sont les bins possibles
	printf("proche = %f\n",proche);
	// retourne la distance noramlisé entre 1 et 0

	return proche;
	
	
}


float compare_histograms2(CImg<unsigned char> img1, char *image2)
{
	CImg<unsigned char> hist1 = img1.get_histogram(256); // fait l'histogramme de l'img 1
	CImg<unsigned char> img2("Images/04.jpg");
	CImg<unsigned char> hist2 = img2.get_histogram(256); // fait l'histogramme de l'img 2
	float proche;
	float distance = 0.0;
	printf("On va ouvrir l'image : %s \n", image2);
	// calcul de la distance euclidienne entre les 2 histo
	for (int i = 0; i < 256; i++)
	{
		distance += pow(hist1(i) - hist2(i), 2); // SOMME((xB -xA)^2 + (yB - yA)^2)
	}
	distance = sqrt(distance);				   // Racine de distance pour la formule de la distance euclidienne
	proche = distance / sqrt(255 * 255 * 256); // puisque ce sont les bins possibles
	// printf("L'image est proche a : %f\n",proche); // print de la valeur sur le terminal
	//  retourne la distance des images  ||| valeur entre 0 et 1
	return proche;
}


void creation_histogramme_image(char * image_reference){
	histo  hist[1000];
	int nb_image;
	int i;
	int acc = 0;
	char  image1[100] ="./Images/";
	char  image2[100] ="./Images/";
	char * image_trantante;
	strcat(image1,image_reference);

	nb_image = calcul_nombre_image();
	for(i=0;i<nb_image;i++){
		strcpy(image2,"");
		image_trantante = recuperation_image_indice_formatage(i);
		strcat(image2,image_trantante);
		
		if ( strcmp(image1, image2) != 0){
			hist[i].nom = image_trantante;
			hist[i].valeur = compare_histograms(image1,image2);
			printf("->%f \n",hist->valeur);
		}
	}
	
	for(i=0;i<nb_image;i++){
		if(strcmp(image1,recuperation_image_indice_formatage(i)) != 0 ){
			printf("%s et %f \n",hist[i].nom,hist[i].valeur);
		}
	}
	printf("Fin de traitement \n");
	trier_histogramme(hist);
	printf("L'image la plus proche histogrammement parlant est l'image %s \n",hist[0].nom);
}


void trier_histogramme(histo hist[1000]){
	/* Ici faire le tri ! */

}