#include "histo.h" 
#include "couleurs.h" 
#include "divers.h" 


float compare_histograms(CImg<unsigned char> img1, CImg<unsigned char> img2)
{
	CImg<unsigned char> hist1 = img1.get_histogram(256); // fait l'histogramme de l'img 1
	CImg<unsigned char> hist2 = img2.get_histogram(256); // fait l'histogramme de l'img 2
	// float proche;
	float distance = 0.0;
	int i;
	for (i = 0; i < 256; i++)
	{ // calcul de la distance euclidienne entre les 2 histo --> SOMME((xB -xA)^2 + (yB - yA)^2)
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