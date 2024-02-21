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
    //int lignes2, colonnes2;
    int maxval;
    //~ int histogramme[MAX_VALEUR+1];
    char nom[MAX_CHAINE];
    struct MetaData metadonnees;
	int matrice[MAX_HAUTEUR][MAX_LARGEUR]= {{1,2,3},
											{4,5,6},
											{7,8,9}};
	int retour;
	
    printf("-> Debut!\n");

	//~ // exemple d'appel de fonction
    //~ retour = pgm_lire(nom, image1, 
                      //~ &lignes1, &colonnes1, 
                      //~ &maxval, &metadonnees);
      
    //TEST pgm_ecrire                                   
		printf("TEST pgm_ecrire: ");
		strcpy(nom, "test.pgm");
		lignes1 = 3;
		colonnes1 = 3;
		maxval = 10;
		strcpy(metadonnees.auteur, "Charles");
		strcpy(metadonnees.dateCreation, "2006-09-08");
		strcpy(metadonnees.lieuCreation, "studio");
		retour = pgm_ecrire(nom, matrice, lignes1, colonnes1, maxval, metadonnees);
        
        printf("-> Retour: ");
		if (retour == OK)
			printf("-> OK\n");
		else if (retour == ERREUR_FICHIER)
			printf("-> ERREUR_FICHIER\n");
		else if (retour == ERREUR_FORMAT)
			printf("-> ERREUR_FORMAT\n");
		else if (retour == ERREUR_TAILLE)
			printf("-> ERREUR_TAILLE\n");
		else if (retour == ERREUR)
			printf("-> ERREUR\n");	
          
           
	
	//~ //TEST pgm prepondante
		//~ printf("TEST pgm_prepondante : ");
		//~ int matrice_prepondante[MAX_HAUTEUR][MAX_LARGEUR] = {{1,2,3},
														     //~ {4,2,6},
															 //~ {7,8,9}};
		//~ int lignes_prepondante = 3;
		//~ int colonnes_prepondante = 3;
		
		//~ retour = pgm_couleur_preponderante(matrice_prepondante, lignes_prepondante, colonnes_prepondante);			
		//~ printf("-> Retour: ");
		
		//~ if (retour != ERREUR)
			//~ printf("Valeur de preponderante : %d\n", retour);
	

	//TEST pgm crer negatif
		printf("TEST creer_negatif : ");
		int matrice_creer_negatif[MAX_HAUTEUR][MAX_LARGEUR] = {{9,9,9},
															   {9,9,9},
															   {9,9,9}};
		int lignes_creer_negatif = 3;
		int colonnes_creer_negatif = 3;
		int maxval_creer_negatif = 10;
		
		retour = pgm_creer_negatif(matrice_creer_negatif, lignes_creer_negatif, colonnes_creer_negatif, maxval_creer_negatif);	
		printf("-> Retour: ");
		printf("Contenu de la matrice :\n");
		for (int i = 0; i < lignes_creer_negatif; i++) {
			for (int j = 0; j < colonnes_creer_negatif; j++) {
				printf("%d ", matrice_creer_negatif[i][j]);
			}	
	
		}
		
		
		if (retour == OK)
			printf("-> OK\n");
		else 
			printf("-> ERREUR\n");
	
	//TEST pgm rotation 90
		printf("TEST_pivoter90 : ");
		int matrice_pivoter90[MAX_HAUTEUR][MAX_LARGEUR] =     {{1,2,3},
															   {4,5,6},
															   {7,8,9}};
		int lignes_pivoter90 = 3;
		int colonnes_pivoter90 = 3;
		int sens_pivoter90 = 0;
		
		retour = pgm_pivoter90(matrice_pivoter90, &lignes_pivoter90, &colonnes_pivoter90, sens_pivoter90);
		printf("-> Retour: ");
		printf("Contenu de la matrice :\n");
		for (int i = 0; i < lignes_pivoter90; i++) {
			for (int j = 0; j < colonnes_pivoter90; j++) {
				printf("%d ", matrice_pivoter90[i][j]);
			}	
			printf("\n");
		}
		
		
		if (retour == OK)
			printf("-> OK\n");
		else 
			printf("-> ERREUR\n");
					
//TEST ppm_ecrire                                   
		printf("TEST pgm_ecrire: ");
		strcpy(nom, "test_1.ppm");
		lignes1 = 3;
		colonnes1 = 3;
		maxval = 10;
		struct RGB matrice_ppm_ecrire[MAX_HAUTEUR][MAX_LARGEUR];
		
		retour = ppm_lire(nom, matrice_ppm_ecrire, &lignes1, &colonnes1, &maxval, &metadonnees);
		
		strcpy(metadonnees.auteur, "Charles");
		strcpy(metadonnees.dateCreation, "2006-09-08");
		strcpy(metadonnees.lieuCreation, "chezmoisti");
		retour = ppm_ecrire(nom, matrice_ppm_ecrire, lignes1, colonnes1, maxval, metadonnees);
        
        printf("-> Retour: ");
        
        
		if (retour == OK)
			printf("-> OK\n");
		else if (retour == ERREUR_FICHIER)
			printf("-> ERREUR_FICHIER\n");
		else if (retour == ERREUR_FORMAT)
			printf("-> ERREUR_FORMAT\n");
		else if (retour == ERREUR_TAILLE)
			printf("-> ERREUR_TAILLE\n");
		else if (retour == ERREUR)
			printf("-> ERREUR\n");

			
			
	//~ // exemple detraitement d'un code de retour (erreur ou reussite)
	//~ printf("-> Retour: ");
	//~ if (retour == OK)
		//~ printf("-> OK");
	//~ else if (retour == ERREUR_FICHIER)
		//~ printf("-> ERREUR_FICHIER\n");
	//~ else if (retour == ERREUR_FORMAT)
		//~ printf("-> ERREUR_FORMAT\n");
	//~ else if (retour == ERREUR_TAILLE)
		//~ printf("-> ERREUR_TAILLE\n");	



    printf("-> Fin!\n");

    return 0;
}
