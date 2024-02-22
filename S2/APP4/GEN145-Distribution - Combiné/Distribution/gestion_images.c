/********
Fichier: gestion_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 28 octobre 2023
Description: Fichier de distribution pour GEN145.
********/

#include <stdio.h>
#include "bibliotheque_images.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];

int main()
{
	int lignes1, colonnes1;
    int lignes2 = 2, colonnes2 = 2;
    int lignes3 = 2, colonnes3 = 2;
    int lignesRGB, colonnesRGB, maxValRGB;
    int lignesRGB2, colonnesRGB2, maxValRGB2;
    int maxval = 25;
    int histogramme[MAX_VALEUR+1];
    char nom[MAX_CHAINE] = "test.pgm";
    char nomPPM[MAX_CHAINE] = "test.ppm";
    char nomEcrire[MAX_CHAINE] = "testExtrait.pgm";
    struct MetaData metadonnees;
    struct MetaData metadonneesRGB;
    

	int retour;

    printf("-> Debut!\n");

	// exemple d'appel de fonction
    retour = pgm_lire(nom, image1, &lignes1, &colonnes1, &maxval, &metadonnees);
    ppm_lire(nomPPM, imageRGB1, &lignesRGB, &colonnesRGB, &maxValRGB, &metadonneesRGB);
	ppm_copier(imageRGB1, lignesRGB, colonnesRGB, imageRGB2, &lignesRGB2, &colonnesRGB2);

	
	//pgm_creer_histogramme(image1, lignes1, colonnes1, histogramme);
	printf("pgm_couleur_preponderante: %i \n", pgm_couleur_preponderante(image1, lignes1, colonnes1));
	retour = pgm_extraire(image1, lignes2, colonnes2, lignes3, colonnes3, &lignes1, &colonnes1);
	strcpy(metadonnees.auteur, "Charles");
	strcpy(metadonnees.dateCreation, "2006-09-08");
	strcpy(metadonnees.lieuCreation, "studio"); 
	retour = pgm_ecrire(nomEcrire, image1, lignes1, colonnes1, maxval, metadonnees);

	printf("-> Retour: ");
	if (retour == OK)
		printf("-> OK");
	else
		printf("-> ERREUR");
	printf("\n");
    printf("-> Fin!\n");

    return 0;
}
