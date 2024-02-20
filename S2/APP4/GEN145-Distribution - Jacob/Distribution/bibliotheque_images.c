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
		printf("%s;%s;%s\n", p_metadonnees->auteur, p_metadonnees->dateCreation, p_metadonnees->lieuCreation);
	}
	else
	{
		ungetc(c, fpLecture);
	}
	//METADATA FIN
	//VALIDE DÉBUT
	fgets(str, 3, fpLecture);
	printf("%s et %s", str, VAR_PGM);
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
					printf("Colonne: %i \n Ligne: %i \n Max. Valeur: %i \n", *p_colonnes, *p_lignes, *p_maxval);
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
			printf("%i ", matrice[i][j]);
		}
		printf("\n");
	}
	//SAVE DONNÉES FIN
	fclose(fpLecture); //fin de lecture
	return (status);
}

int pgm_ecrire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, struct MetaData metadonnees)
{
    return OK;
}

int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes2, int *p_colonnes2)
{
    return OK;
}

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
