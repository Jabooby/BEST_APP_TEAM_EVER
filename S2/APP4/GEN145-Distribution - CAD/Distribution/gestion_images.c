/********
Fichier: gestion_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Date: 28 octobre 2023
Description: Fichier de distribution pour GEN145.
********/

#include <stdio.h>
#include <string.h> // pour strcpy
#include "bibliotheque_images.h"

int image1[MAX_HAUTEUR][MAX_LARGEUR];
int image2[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB1[MAX_HAUTEUR][MAX_LARGEUR];
struct RGB imageRGB2[MAX_HAUTEUR][MAX_LARGEUR];

int main()
{
    int lignes1, colonnes1;
    int lignes2, colonnes2;
    //~ int maxval;
    //~ int histogramme[MAX_VALEUR+1];
    //~ char nom[MAX_CHAINE];
    //~ struct MetaData metadonnees;
	//~ int matrice[MAX_HAUTEUR][MAX_LARGEUR]= {{1,2,3},
											//~ {4,5,6},
											//~ {7,8,9}};
	int retour;
	
    printf("-> Debut!\n");

	//~ // exemple d'appel de fonction
    //~ retour = pgm_lire(nom, image1, 
                      //~ &lignes1, &colonnes1, 
                      //~ &maxval, &metadonnees);
      
    //TEST pgm_ecrire                                   
		//~ strcpy(nom, "test.pgm");
		//~ lignes1 = 3;
		//~ colonnes1 = 3;
		//~ maxval = 10;
		//~ strcpy(metadonnees.auteur, "Charles");
		//~ strcpy(metadonnees.dateCreation, "2006-09-08");
		//~ strcpy(metadonnees.lieuCreation, "studio");
		//~ retour = pgm_ecrire(nom, matrice, lignes1, colonnes1, maxval, metadonnees);
           
	//TEST copier
		int matrice1[MAX_HAUTEUR][MAX_LARGEUR]= {{1,2,3},
												 {4,5,6},
												 {7,8,9}};
		int matrice2[MAX_HAUTEUR][MAX_LARGEUR]=	{{0,0,0},
												 {0,0,0},
												 {0,0,0}};
		lignes1  = 3;
		colonnes1 = 3;	
		int *p_lignes2 = &lignes2;		
		int *p_colonnes2 = &colonnes2;		 
		retour = pgm_copier(matrice1, lignes1, colonnes1, 
							matrice2, p_lignes2, p_colonnes2);

	// exemple detraitement d'un code de retour (erreur ou reussite)
	printf("-> Retour: ");
	if (retour == OK)
		printf("-> OK");
	else if (retour == ERREUR_FICHIER)
		printf("-> ERREUR_FICHIER\n");
	else if (retour == ERREUR_FORMAT)
		printf("-> ERREUR_FORMAT\n");
	else if (retour == ERREUR_TAILLE)
		printf("-> ERREUR_TAILLE\n");	



    printf("-> Fin!\n");

    return 0;
}
