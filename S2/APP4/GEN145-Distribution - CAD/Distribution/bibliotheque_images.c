/********
Fichier: bibliotheque_images.c
Auteurs: Domingo Palao Munoz
         Charles-Antoine Brunet
Modifier par: Jacob Turcotte & Charle-Ariel Dion
Date: 16 février 2023
Description: Fichier de distribution pour GEN145.
Fichier définie les fonctions appelées et utilisées par gestion_images.c.
Elles permettent de lire, écrire, copier, créer, pivoter (et plus) les fichiers d'image PGM et PPM.
********/

#include "bibliotheque_images.h"

//Fonctions local


/*
 * @brief Fonction qui va permettre de lire les fichiers de type PGM (Portable Gray Map);
 * 
 * @param nom_fichier[]: prend un tableau de char (string) qui sera le nom du fichier que nous allons lire;
 * @param matrice[MAX_HAUTEUR][MAX_LARGEUR]: Tableau de type int, 2D qui va storer les valeurs de chaque pixel (0 à 255) en grayscale;
 * @param *p_lignes: Pointeur de ligne de type int;
 * @param *p_colonnes: Pointeur de colonnes de type int;
 * @param *p_maxval: Pointeur vers la valeur maximal d'un pixel;
 * @param *p_metadonnees: Pointeur de type struct MetaData (3 variables, Auteur, date de création et leiu de création)(voir .h pour la struct);
 * 
 * @return int: la fonction retourne un chiffre pour dire si il a eu une erreur ou non (voir le .h)
 */
int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
	
    return OK;
}

///DEBUT PGM Ecrire
	int string_length(const char* str) {
		int length = 0;
		// Loop jusqua fin
		while (*str != '\0') {
			length++;
			str++;
		}
		return length;
	}
int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
	int Donnee_Presente = 0;
	
	//Ouvir fichier
	FILE *fichier = fopen(nom_fichier, "w");
	if (fichier == NULL)
	{
		return ERREUR_FICHIER;
	}
	
	
	//valid info avant d'ecrire Format
	//Valide valeur max
		if ((maxval < 0) || (maxval > MAX_VALEUR)){
			return ERREUR_FORMAT;}
	//Valide grosseurs du champ auteur est correct
		if (string_length(metadonnees.auteur)> MAX_CHAINE){
			return ERREUR_FORMAT;}
		
	//check si date int et bon format yyyy-mm-dd
		int date_lengh = string_length(metadonnees.dateCreation);
		
		if (date_lengh != 10)
			return ERREUR_FORMAT; 
			
		for (int i=0; i<10; i++)
		{
		if (i < 4 && (metadonnees.dateCreation[i] < '0' || metadonnees.dateCreation[i] > '9'))
			return ERREUR_FORMAT;
		if (i == 4 && (metadonnees.dateCreation[i] != '-'))
			return ERREUR_FORMAT;
		if (i > 4 && i < 7 && (metadonnees.dateCreation[i] < '0' || metadonnees.dateCreation[i] > '9'))
			return ERREUR_FORMAT;
		if (i == 7 && (metadonnees.dateCreation[i] != '-'))
			return ERREUR_FORMAT;	
		if (i > 7 && (metadonnees.dateCreation[i] < '0' || metadonnees.dateCreation[i] > '9'))
			return ERREUR_FORMAT;	
		}
		

	//Check s'il y a un commentaire a ecrire
		if (string_length(metadonnees.auteur) > 0 && string_length(metadonnees.dateCreation) && string_length(metadonnees.lieuCreation)){
			Donnee_Presente = 1;
		}
	
	
	//Ecrire MetaData
		if (Donnee_Presente == 1){
			fprintf(fichier, "#%s; %s; %s\n", metadonnees.auteur, metadonnees.dateCreation, metadonnees.lieuCreation);
		}
	
	
	//Ecrire Format
	fprintf(fichier, "P2\n%d %d\n%d\n", colonnes, lignes, maxval);
	
	
	//Validation grandeur Hauteur et Largeur
	
	//Ecrire donnees de la matrice
		for(int j=0; j < lignes; j++){
			for (int i=0; i < colonnes; i++){
				if (matrice[j][i] >= 0 && matrice[j][i]<= maxval){
					fprintf(fichier,"%d ", matrice[j][i]);}
				else{
					return ERREUR_FORMAT;
				}
			}
			fprintf(fichier, "\n");
				
		}
		
	//ferme le fichier
		fclose(fichier);
	
	return OK;
}
///FIN de PGM Ecrire

///DEBUT PGM Copier
int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, 
			   int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
	//declare variables
		int i;
		int j;
	//verifie si lignes & colonnes sont de grandeur approprier
		if (lignes1 > MAX_HAUTEUR || lignes1 < 1 || 
		    colonnes1 > MAX_LARGEUR || colonnes1 < 1){
			return ERREUR_FORMAT;} //a verifier si bon type d<erreur		
	
	//copie lignes et colones dans pointeur respectif
		*p_lignes2 = lignes1;
		*p_colonnes2 = colonnes1;
		
	//copie la matrice
		for (i = 0; i<colonnes1; i++){
			for (j = 0; j<lignes1; j++){
			matrice2[i][j] = matrice1[i][j];
			}
		}
		
	//afficher matrice copier (pour debugger)
		printf("Contenu de la matrice :\n");
		for (i = 0; i < lignes1; i++) {
			for (j = 0; j < colonnes1; j++) {
				printf("%d ", matrice2[i][j]);
			}
			printf("\n");
		}
	
    return OK;
}
///FIN PGM COPIER
int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int histogramme[MAX_VALEUR+1])
{
    return OK;
}

int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes)
{
    return OK;
}

int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur)
{
    return OK;
}

int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval)
{
    return OK;
}

int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes)
{
    return OK;
}

int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
    return OK;
}

int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
    return OK;
}

// Operations pour les images couleurs
int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
    return OK;
}

int ppm_ecrire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
    return OK;
}

int ppm_copier(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
    return OK;
}

int ppm_sont_identiques(struct RGB matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, struct RGB matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
    return OK;
}

int ppm_pivoter90(struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
    return OK;
}
