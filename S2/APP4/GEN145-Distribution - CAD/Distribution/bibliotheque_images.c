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
	
	
	//Check s'il y a un commentaire a ecrire
		if (string_length(metadonnees.auteur) > 0 || string_length(metadonnees.dateCreation) > 0 || string_length(metadonnees.lieuCreation) > 0){
			Donnee_Presente = 1;
		}
	
	
	if (Donnee_Presente == 1){
		//Valide grosseurs du champ auteur est correct
			if (string_length(metadonnees.auteur)> MAX_CHAINE){
				return ERREUR_FORMAT;}
			
		//check si date int et bon format yyyy-mm-dd
			if (string_length(metadonnees.dateCreation) > 0){
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
			}
		//Valide grosseurs du champ lieucreation est correct
			if (string_length(metadonnees.lieuCreation)> MAX_CHAINE){
				return ERREUR_FORMAT;}
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
			return ERREUR_TAILLE;} 		
	
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

///DEBUT pgm_creer_histogramme
int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int histogramme[MAX_VALEUR+1])
{
	//verifie si lignes & colonnes sont de grandeur approprier
		if (lignes > MAX_HAUTEUR || lignes < 1 || 
		    colonnes > MAX_LARGEUR || colonnes < 1){
			return ERREUR_TAILLE;}
	
	//creation de l'historigramme
	int index = 0;
	for (int i=0; i<lignes; i++){
		for (int j=0; j<colonnes; j++){
			index = matrice[i][j];
			if (index > (MAX_VALEUR+1) || index < 0){
				return ERREUR;
				}
			histogramme[index]++;
		}
	}
	
    return OK;
}
/// FIN pgm_creer_historigramme


///DEBUT pgm_couleur_preponderante
int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes)
{
	//Initialisation des variables
		int valeur = -1; //-1 = erreur
		int histogramme[MAX_VALEUR+1];
		int retour = pgm_creer_histogramme(matrice, lignes, colonnes, histogramme);
	
	//pgm_creer verifie les donnees alors pas besoin de faire une double verification
		 if (retour == ERREUR)
			return ERREUR;
	
	//compte le nombre de fois qu'une couleur apparait	
		for(int i=0; i < lignes; i++){
			for (int j=0; j < colonnes; j++){
				//store la plus grosse valeur dans valeur
				if (matrice[i][j] > valeur){
					valeur = matrice[i][j];
					}
				
			}
		}
	
    return valeur;
}
///FIN pgm_couleur_preponderante



///DEBUT pgm_eclaircir_noircir
int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur)
{
	//verifie si lignes & colonnes sont de grandeur approprier
		if (lignes > MAX_HAUTEUR || lignes < 1 || 
		    colonnes > MAX_LARGEUR || colonnes < 1){
			return ERREUR_TAILLE;} 
	
	//ajustement de la matrice avec valeur
		for(int i=0; i < lignes; i++){
			for (int j=0; j < colonnes; j++){
				matrice[i][j] = matrice[i][j] + valeur;
				//extremitees
				if (matrice[i][j] > maxval)
					matrice[i][j] = maxval;
				if (matrice[i][j] < 0)
					matrice[i][j] = 0;	
			}
		}
	
	
    return OK;
}
///FIN pgm_eclaircir_noircir

///DEBUT pgm_creer_negatif
int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval)
{
	
	//verifie si lignes & colonnes sont de grandeur approprier
		if (lignes > MAX_HAUTEUR || lignes < 1 || 
		    colonnes > MAX_LARGEUR || colonnes < 1){
			return ERREUR_TAILLE;} 
	//verif de maxval
		if (maxval < 1 || maxval > MAX_VALEUR)
			return ERREUR;
	//reecriture de l'image
		for(int i=0; i < lignes; i++){
			for (int j=0; j < colonnes; j++){
				//empeche l'ecriture de negatif, plus petite valeur c'est 0 et plus grande maxval
				if (matrice[i][j] > maxval)
					return ERREUR;
				
				matrice[i][j] = maxval - matrice[i][j];
		
			}
		}
	
	
    return OK;
}
///FIN pgm_creer_negatif

///DEBUT pgm_extraire
int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes)
{
	
	//ajouter jacob ici
    return OK;
}
///FIN pgm_extraire

///DEBUT pgm_sont_identiques
int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, 
						int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
	//verifie si lignes & colonnes sont de grandeur approprier
		if (lignes1 > MAX_HAUTEUR || lignes1 < 1 || 
		    colonnes1 > MAX_LARGEUR || colonnes1 < 1){
			return ERREUR_FORMAT;} 
	
	//verifie si lignes1 et 2, et colonnes 1 et 2 sont identique
		if (lignes1 != lignes2 || colonnes1 != colonnes2)
			return DIFFERENTES;
			
	//verifie pixel
		for (int i=0; i< lignes1; i++){
			for(int j=0; j<colonnes1; j++){
				if (matrice1[i][j] != matrice2[i][j])
					return DIFFERENTES;
			}
		}
		
	
    return IDENTIQUES;
}
///FIN pgm_sont_identiques


///DEBUT pgm_pivoter90
int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
	
	//verifie si lignes & colonnes sont de grandeur approprier
		if (*p_lignes > MAX_HAUTEUR || *p_lignes < 1 || 
		    *p_colonnes > MAX_LARGEUR || *p_colonnes < 1){
			return ERREUR_FORMAT;}
	//creer matrice intermediaire
		int lignes_inter = *p_colonnes;
		int colonnes_inter = *p_lignes;
		int matrice_inter[MAX_HAUTEUR][MAX_LARGEUR];
		
	//ecriture de la matrice
		for (int i=0; i < *p_lignes; i++){
			for(int j=0; j < *p_colonnes; j++){
				if (sens == 1){
					matrice_inter[j][*p_lignes-1-i] = matrice[i][j];}
				if (sens == 0)
					matrice_inter[*p_colonnes-1-j][i] = matrice[i][j];
			}
		}
		
		for (int x = 0; x < lignes_inter; x++) {
			for (int y = 0; y < colonnes_inter; y++) {
				printf("%d ", matrice_inter[x][y]);
			}	
			printf("\n");
		}

	//copie matrice intermediaire dans la matrice
	int retour = pgm_copier(matrice_inter, lignes_inter, colonnes_inter, 
							matrice, p_lignes, p_colonnes);
	if (retour != OK)
		return ERREUR;
		
	
    return OK;
}
///FIN pgm_pivoter90


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
