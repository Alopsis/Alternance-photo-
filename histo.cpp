#include "histo.h" 
#include "couleurs.h" 
#include "divers.h" 


float compare_histograms(char * image1, char * image2)
{
	CImg<unsigned char> img1(image1);
	CImg<unsigned char> img2(image2);
	CImg<unsigned char> hist1 = img1.get_histogram(256);
	CImg<unsigned char> hist2 = img2.get_histogram(256);
	float proche;
	float distance = 0.0;
	int i;
	for (i = 0; i < 256; i++)
	{ 
		distance = distance + pow(hist1(i) - hist2(i), 2);
	}
	distance = sqrt(distance); 
	proche = distance / sqrt(255 * 255 * 256); 
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
			hist[acc].nom = image_trantante;
			hist[acc].valeur = compare_histograms(image1,image2);
			acc++;
		}
	}
	trier_histogramme(hist);
	printf("L'image la plus proche histogrammement parlant est l'image %s \n",hist[0].nom);
}


void trier_histogramme(histo hist[1000]){
	int z = 1;
	int nb_image;
	int valeur_acc;
	char * nom_acc;
	int i;
	nb_image = calcul_nombre_image();

	/* tentative de tri a bulllooooss */
	while ( z != 0 ){
		z=0;
		for(i=1;i<nb_image-1;i++){
			if ( hist[i-1].valeur < hist[i].valeur){
				z = 1;
				valeur_acc = hist[i-1].valeur;
				nom_acc = hist[i-1].nom;
				hist[i-1].valeur = hist[i].valeur;
				hist[i-1].nom = hist[i].nom;
				hist[i].valeur = valeur_acc; 
				hist[i].nom = nom_acc;
			}
		}
	}


}