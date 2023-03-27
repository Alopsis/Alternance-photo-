#include "couleurs.h"
#include "histo.h"
#include "divers.h" 



void compare_image(CImg<unsigned char> image2)
{
	int width1 = image2.width();
	int height1 = image2.height();
	int i, j;
	int red = 0;
	int green = 0;
	int blue = 0;
	for (i = 0; i < height1; i++)
	{
		for (j = 0; j < width1; j++)
		{
			// printf("Pixel (%d,%d) - Rouge: %d, Vert: %d, Bleu: %d\n", i, j, image2(i,j,0,0), image2(i,j,0,1), image2(i,j,0,2));
			red = red + image2(j, i, 0, 0);
			green = green + image2(j, i, 0, 1);
			blue = blue + image2(j, i, 0, 2);
			// printf("Pixel vert = %d \n",image2(i,j,0,2));
		}
	}
	red = red / (width1 * height1);
	green = green / (width1 * height1);
	blue = blue / (width1 * height1);
	printf("Pixel rgb moyen de l'image : (R: %d, G: %d , B: %d )\n", red, green, blue);
}

void compare_image_et_insertion(CImg<unsigned char> image2, char nom[])
{
	int width1 = image2.width();
	int height1 = image2.height();
	int i, j;
	int red = 0;
	int green = 0;
	int blue = 0;
	FILE *fichier;

	/**********************/
	/* Partie Comparaison */
	/**********************/
	for (i = 0; i < height1; i++)
	{
		for (j = 0; j < width1; j++)
		{
			red = red + image2(j, i, 0, 0);
			green = green + image2(j, i, 0, 1);
			blue = blue + image2(j, i, 0, 2);
		}
	}
	red = red / (width1 * height1);
	green = green / (width1 * height1);
	blue = blue / (width1 * height1);

	/********************/
	/* Partie insertion */
	/********************/
	fichier = fopen("couleurs.txt", "a");
	fprintf(fichier, "%s %d %d %d\n", nom, red, green, blue);
	fclose(fichier);
}



void enlever_image(int ligne,int nb_image)

/* Faire les regles d'or du malloc ici :)*/
{
	int i = 0;
	int acc = 0;
	FILE *fichier;
	char nom_recup[1000][100]; // [nb_image+1];
	int * tab1 = (int *	) malloc((nb_image+1)*sizeof(int));
	int * tab2 = (int *	) malloc((nb_image+1)*sizeof(int));
	int * tab3 = (int *	) malloc((nb_image+1) * sizeof(int));
	fichier = fopen("couleurs.txt", "r");
	if(fichier == NULL) {
		printf("erreur d'ouverture du fichier \n");
		exit(0);
	}
	while (	fscanf(fichier,"%s %d %d %d",nom_recup[acc],&tab1[acc],&tab2[acc],&tab3[acc]) == 4 )
	{
			printf("acc = %d et %s\n",acc,nom_recup[acc]);
			acc++;

	}
	fclose(fichier);
	fichier = fopen("couleurs.txt","w");
	for(i=0;i<acc;i++){
		if(i != ligne ){
			fprintf(fichier,"%s %d %d %d\n",nom_recup[i],tab1[i],tab2[i],tab3[i]);
		}
	}
}



void verification_image_fichier(char **nom_images, int nb_image)
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


void compare_image_plus_proche(char * image_original) {
    int i = 0;
    int nb_image;
    char nom_images[1000][100]; /* 1000 images avec un nom de 100 c max */
    int * r =(int *) malloc(100 * sizeof(int)); 
    int * g =(int *) malloc(100 * sizeof(int));
    int * b =(int *) malloc(100 * sizeof(int));
    int image_actuelle = -1 ;
    FILE * fich;
    nb_image = calcul_nombre_image();
    fich = fopen("couleurs.txt","r");
    if (fich == NULL) {
        printf("Erreur d'ouverture du fichier couleurs.txt\n");
        exit(0);
    }

    while (fscanf(fich, "%s %d %d %d", nom_images[i], &r[i], &g[i], &b[i]) == 4) {
        printf("-> \"%s\" \n", nom_images[i]);
		
        if (strcmp(nom_images[i], image_original) == 0) {
            image_actuelle = i;
        }
        i++;
    }
	printf("Il y a %d images ! \n",i);
	tri_image(nom_images,r,g,b,image_actuelle);
	printf("apres tri\n");

    free(r); // Libère la mémoire allouée pour les valeurs de couleur
    free(g);
    free(b);
}


void tri_image(char nom_images[][100],int * r , int * g , int * b ,int actuelle ){
	int i;
	int img_plus_proche = -1 ;
	int plus_gros_div= 1000; 
	int nb_image;

	nb_image = calcul_nombre_image();
	

	
	for(i=0;i<nb_image;i++){
		printf("%s %d %d %d \n",nom_images[i],r[i],g[i],b[i]);
		if(i != actuelle ){
			if(abs(r[i] - r[actuelle] ) + abs(g[i] - g[actuelle]) + abs(b[i] - b[actuelle]) < plus_gros_div){
				img_plus_proche = i;
			}
		}
	}
	printf("l'image la plus proche pixelement parlant est la %s ( N°%d ) \n",nom_images[img_plus_proche],img_plus_proche);
	return ;
}