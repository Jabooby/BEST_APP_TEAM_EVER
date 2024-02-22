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
	int retour;
	
    printf("-> Debut!\n");
	
	//TEST pgm prepondante
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
		//~ else
			//~ printf("ERREUR\n");
	

	//TEST pgm crer negatif
		//~ printf("TEST creer_negatif : ");
		//~ int matrice_creer_negatif[MAX_HAUTEUR][MAX_LARGEUR] = {{9,9,9},
															   //~ {9,9,9},
															   //~ {9,9,9}};
		//~ int lignes_creer_negatif = 3;
		//~ int colonnes_creer_negatif = 3;
		//~ int maxval_creer_negatif = 10;
		
		//~ retour = pgm_creer_negatif(matrice_creer_negatif, lignes_creer_negatif, colonnes_creer_negatif, maxval_creer_negatif);	
		//~ printf("-> Retour: ");

		//~ if (retour == OK)
			//~ printf("-> OK\n");
		//~ else 
			//~ printf("-> ERREUR\n");
	
	//TEST pgm rotation 90
		//~ printf("TEST_pivoter90 : ");
		//~ int matrice_pivoter90[MAX_HAUTEUR][MAX_LARGEUR] =     {{1,2,3},
															   //~ {4,5,6},
															   //~ {7,8,9}};
		//~ int lignes_pivoter90 = 3;
		//~ int colonnes_pivoter90 = 3;
		//~ int sens_pivoter90 = 0;
		
		//~ retour = pgm_pivoter90(matrice_pivoter90, &lignes_pivoter90, &colonnes_pivoter90, sens_pivoter90);
		//~ printf("-> Retour: ");
		//~ printf("Contenu de la matrice :\n");
			
		//~ if (retour == OK)
			//~ printf("-> OK\n");
		//~ else 
			//~ printf("-> ERREUR\n");
					

	///TEST pour ppm

	//TEST ppm ecriture
	//~ printf("ppm_ecriture : ");
	//~ char nom_ppm_ecrire[MAX_CHAINE] = "test_ppm.ppm";
	//~ struct RGB matrice_ppm_ecrire[MAX_HAUTEUR][MAX_LARGEUR] = {
		//~ {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
		//~ {{10, 11, 12}, {13, 14, 15}, {16, 17, 18}},
		//~ {{19, 20, 21}, {22, 23, 24}, {25, 26, 27}}
	//~ };
	//~ int lignes_ppm_ecrire = 3;
	//~ int colonnes_ppm_ecrire = 3;
	//~ int maxval_ppm_ecrire = 100;
	//~ struct MetaData metadonnees_ppm_ecrire;
	//~ strncpy(metadonnees_ppm_ecrire.auteur, "Charles", MAX_CHAINE);
	//~ strncpy(metadonnees_ppm_ecrire.dateCreation, "2003-09-02", MAX_CHAINE);
	//~ strncpy(metadonnees_ppm_ecrire.lieuCreation, "Bureau", MAX_CHAINE);


	//~ retour = ppm_ecrire(nom_ppm_ecrire, matrice_ppm_ecrire, lignes_ppm_ecrire, colonnes_ppm_ecrire, maxval_ppm_ecrire, metadonnees_ppm_ecrire);
	//~ printf("-> Retour: ");
	
	//~ if (retour == OK)
			//~ printf("-> OK\n");
		//~ else 
			//~ printf("-> ERREUR\n");
	
	
	//TEST ppm_sont_identiques
	printf("ppm_sont_identiques : ");
	int lignes_ppm_sont_identiques1 = 3;
	int colonnes_ppm_sont_identiques1 = 3;
	struct RGB matrice_ppm_sont_identiques1[MAX_HAUTEUR][MAX_LARGEUR] = 
	{
		{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
		{{10, 11, 12}, {13, 14, 15}, {16, 17, 18}},
		{{19, 20, 21}, {22, 23, 24}, {25, 26, 27}}
	};
	
	int lignes_ppm_sont_identiques2 = 3;
	int colonnes_ppm_sont_identiques2 = 3;
	struct RGB matrice_ppm_sont_identiques2[MAX_HAUTEUR][MAX_LARGEUR] = 
	{
		{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
		{{10, 11, 12}, {13, 14, 15}, {16, 17, 18}},
		{{19, 20, 21}, {22, 23, 24}, {25, 26, 27}}
	};
	retour = ppm_sont_identiques(matrice_ppm_sont_identiques1, lignes_ppm_sont_identiques1, colonnes_ppm_sont_identiques1, 
							     matrice_ppm_sont_identiques2, lignes_ppm_sont_identiques2, colonnes_ppm_sont_identiques2);
	
	printf("-> Retour: ");
	if (retour == OK)
			printf("-> OK\n");
		else 
			printf("-> ERREUR\n");						     
	
	
    printf("-> Fin!\n");

    return 0;
}
