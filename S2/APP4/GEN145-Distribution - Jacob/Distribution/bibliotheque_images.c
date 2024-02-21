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

int string_length(const char* str) 
{
	int length = 0;
	// Loop jusqua fin
	while (*str != '\0') {
		length++;
		str++;
	}
	return length;
}
int stringCompare(char *str1, char *str2)
{
	int same = IDENTIQUES; //va être retourné 0 si pareille, 1 si différent
	int i = 0;  // integer d'incrémentation 
    while(str1[i]!='\0' && str2[i]!='\0')  //tant que str1 et str2 n'est pas à la fin de leur string 
    {  
       if(str1[i] != str2[i])  //vérification que le caractère est identique
       {  
           same = DIFFERENTES;  //pas pareille
           break;  
       }  
       i++;  
    } 
    if(str1[i]!='\0' || str2[i]!='\0') //pas la même longueur
    {
		same = DIFFERENTES;
	}
    return same;
}

int verifLigneColonne(int nbLignes, int nbColonnes)
{
	if((nbLignes <= 256 && nbLignes > 0) || (nbColonnes  <= 256 && nbColonnes > 0))
		return OK;
	else
		return ERREUR;
}
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
	int status = OK;
	int i, j, compteur;
	int decalage;
	char str[MAX_CHAINE];
	char c;
	
	FILE *fpLecture;
	//ouverture de lecture
	if ( (fpLecture = fopen(nom_fichier, "r")) == NULL)
	{
		fprintf(stderr, "Error opening read file. \n");
		status = ERREUR_FICHIER;
		return(status);
	}
	//METADATA DÉBUT
	c = fgetc(fpLecture); // lecture du premier caractère pour commentaire||Metadata
	if( c == '#')
	{
		compteur = 0;
		decalage = 0;
		for(i = 0; i < (MAX_CHAINE * 3); i++)
		{
			c = fgetc(fpLecture);
			if( c == ';')
			{
				decalage = i + 1;
				compteur++;
			}
			else if ( c =='\n' || c =='\0' || c == '\r')
				i = (MAX_CHAINE * 3);
			else
			{
				switch(compteur)
				{
					case(0):
						p_metadonnees->auteur[i-decalage] = c;
						break;
					case(1):
						p_metadonnees->dateCreation[i-decalage] = c;
						break;
					case(2):
						p_metadonnees->lieuCreation[i-decalage] = c;
						break;
				}
			}
		}
		//printf("%s;%s;%s\n", p_metadonnees->auteur, p_metadonnees->dateCreation, p_metadonnees->lieuCreation);
	}
	else
	{
		ungetc(c, fpLecture);
	}
	//METADATA FIN
	//VALIDE DÉBUT
	fgets(str, 3, fpLecture);
	//printf("%s et %s", str, VAR_PGM);
	if(stringCompare(str, VAR_PGM) == IDENTIQUES)
	{
		c = fgetc(fpLecture);
		if(c == '\0' || c == ' ' || c == '\n' || c == '\r')
		{
			fscanf(fpLecture, "%i",p_colonnes);
			c = fgetc(fpLecture);
			if(c == '\0' || c == ' ' || c == '\n' || c == '\r')
			{
				fscanf(fpLecture, "%i", p_lignes);
				c = fgetc(fpLecture);
				if(c == '\0' || c == ' ' || c == '\n' || c == '\r')
				{
					fscanf(fpLecture, "%i", p_maxval);
					//printf("Colonne: %i \n Ligne: %i \n Max. Valeur: %i \n", *p_colonnes, *p_lignes, *p_maxval);
				}
				else
				{
					status = ERREUR_FORMAT;
					return(status);
				}
			}
			else
			{
				status = ERREUR_FORMAT;
				return(status);
			}
		}
		else
		{
			status = ERREUR_FORMAT;
			return(status);
		}
	}
	else
	{
		status = ERREUR_FORMAT;
		return(status);
	}
	if(!(*p_maxval > 0 && *p_maxval <= MAX_VALEUR))
	{
		status = ERREUR_FORMAT;
		return(status);
	}
	else if (!(( *p_colonnes > 0 && *p_colonnes <= MAX_LARGEUR) && (*p_lignes > 0 && *p_lignes <= MAX_HAUTEUR)))
	{
		status = ERREUR_TAILLE;
		return(status);
	}
	//VALIDE FIN
	//SAVE DONNÉES DÉBUT
	for(i = 0; i < *p_lignes; i++)
	{
		for(j = 0; j < *p_colonnes; j++)
		{
			fscanf(fpLecture, "%i", &matrice[i][j]);
			if(!(matrice[i][j] >= 0 && matrice[i][j] <= *p_maxval))
			{
				status = ERREUR_FORMAT;
				return(status);
			}
			//printf("%i ", matrice[i][j]);
		}
		//printf("\n");
	}
	//SAVE DONNÉES FIN
	fclose(fpLecture); //fin de lecture
	return (status);
}

//CAD
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
		//Valide grosseurs des champs auteur
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
		
			//Valid si integer
		//ajout ici
		
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
		
	//close le fichier
	fclose(fichier);
	
	return OK;
}
//CAD
int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
    return OK;
}
//JT A tester
int pgm_creer_histogramme(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int histogramme[MAX_VALEUR+1])
{
	int i,j;
	if(verifLigneColonne(lignes,colonnes) != OK)
		return ERREUR_TAILLE;
	else
	{
		for(i = 0; i < MAX_VALEUR+1; i++)
		{
			histogramme[i] = 0;
		}
		for(i = 0; i < lignes; i++)
		{
			for(j = 0; j < colonnes; j++)
			{
				if(!(matrice[i][j] >= 0 && matrice[i][j] <= MAX_VALEUR))
				{
					return(ERREUR_FORMAT);
				}
				else
					histogramme[matrice[i][j]]++;
				//printf("Histo: %i, matrice: %i\n", histogramme[matrice[i][j]], matrice[i][j]);
			}
		}
	}
    return OK;
}
//JT A tester
int pgm_couleur_preponderante(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes)
{
	int i;
	int histogramme[MAX_VALEUR+1];
	int valPreponderante = -1;
	int index = -1;
	if(pgm_creer_histogramme(matrice, lignes, colonnes, histogramme) != OK)
	{
		return ERREUR_TAILLE;
	}
	else
	{
		for(i = 0; i < MAX_VALEUR+1; i++)
		{
			if(valPreponderante < histogramme[i])
			{
				valPreponderante = histogramme[i];
				//printf("val Pre: %i, Histo: %i, Index: %i \n", valPreponderante, histogramme[i], index);
				index = i;
			}
		}
	}
    return index;
}

//A tester
int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur)
{
	int i,j;
	int valeurNouvelle;
	struct MetaData metadonnees;
	strcpy(metadonnees.auteur, "Charles");
	strcpy(metadonnees.dateCreation, "2006-09-08");
	strcpy(metadonnees.lieuCreation, "studio");
	char nom[MAX_CHAINE] = "testEcNo.pgm";
	if(verifLigneColonne(lignes,colonnes) != OK)
		return ERREUR_TAILLE;
	else
	{
		for(i = 0; i < lignes; i++)
		{
			for(j = 0; j < colonnes; j++)
			{
				valeurNouvelle = matrice[i][j] + valeur;
				if(valeurNouvelle < 0 )
				{
					valeurNouvelle = 0;
				}
				else if (valeurNouvelle > maxval)
				{
					valeurNouvelle = maxval;
				}
				matrice[i][j] = valeurNouvelle;
			}
		}
	}
    return (pgm_ecrire(nom, matrice,lignes, colonnes, maxval, metadonnees));
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
