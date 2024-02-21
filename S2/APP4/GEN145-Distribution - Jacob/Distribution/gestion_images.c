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
    int lignes2, colonnes2;
    int maxval;
    int histogramme[MAX_VALEUR+1];
    char nom[MAX_CHAINE] = "test.pgm";
    struct MetaData metadonnees;
    

	int retour;

    printf("-> Debut!\n");

	// exemple d'appel de fonction
    retour = pgm_lire(nom, image1, &lignes1, &colonnes1, &maxval, &metadonnees);

	// exemple detraitement d'un code de retour (erreur ou reussite)
	printf("-> Retour: ");
	if (retour == OK)
		printf("-> OK");
	else
		printf("-> ERREUR");
	printf("\n");
	//pgm_creer_histogramme(image1, lignes1, colonnes1, histogramme);
	printf("pgm_couleur_preponderante: %i \n", pgm_couleur_preponderante(image1, lignes1, colonnes1));
	pgm_eclaircir_noircir(image1, lignes1, colonnes1, maxval, -9);
	

    printf("-> Fin!\n");

    return 0;
}
