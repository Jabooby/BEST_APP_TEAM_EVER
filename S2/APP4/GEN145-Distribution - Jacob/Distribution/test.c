#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/* LABO_1 Not to do (clique le + sur le côté)
 * PLEASE DONT DO THAT EW It hurt me to type this shit -JT
 * 

int main(void)
{
	int i1, i2, i3, i4, i5, i6, i7, i8, i9;
	FILE *fpLecture, *fpEcriture;
	
	if ( (fpLecture = fopen("Labo_1.txt", "r")) == NULL)
	{
		fprintf(stderr, "Error opening read file. \n");
		exit(1);
	}
	fscanf(fpLecture, "%i %i %i %i %i %i %i %i %i", &i1, &i2, &i3, &i4, &i5, &i6, &i7, &i8, &i9);
	printf("The values are: %i, %i, %i, %i, %i, %i, %i, %i and %i. \n", i1, i2, i3, i4, i5, i6, i7, i8, i9);
 
	if  ( (fpEcriture = fopen("Ecriture_Labo_1.text", "w")) == NULL)
	{
		fprintf(stderr, "Error opening write file. \n");
		exit(1);
	}
	fprintf(fpEcriture, "%i %i %i \n%i %i %i \n%i %i %i \n", i1, i2, i3, i4, i5, i6, i7, i8, i9);
	fclose(fpLecture);
	fclose(fpEcriture);
	return(0);
}
*/
/* Do this instead
int main(void)
{
	int matriceInt[3][3];
	int i;
	int j;
	FILE *fpLecture, *fpEcriture;
	
	if ( (fpLecture = fopen("Labo_1.txt", "r")) == NULL)
	{
		fprintf(stderr, "Error opening read file. \n");
		exit(1);
	}
	printf("The values are: ");
	for(i = 0; i<3; i++)
	{
		for(j = 0; j <3; j++)
		{
			fscanf(fpLecture, "%i", &matriceInt[i][j]);
			printf("%i ", matriceInt[i][j]);
		}
	}
	if  ( (fpEcriture = fopen("Ecriture_Labo_1.txt", "w")) == NULL)
	{
		fprintf(stderr, "Error opening write file. \n");
		exit(1);
	}
	for(i = 0; i<3; i++)
	{
		for(j = 0; j <3; j++)
		{
			fprintf(fpEcriture, "%i ", matriceInt[i][j]);
		}
		fprintf(fpEcriture, "\n");
	}
	fclose(fpLecture);
	fclose(fpEcriture);
	return(0);
}
*/
/* Or this (tha bestest way) 
#define MAX_LARGEUR 3
#define MAX_HAUTEUR 3
#define OK 0
#define ERREUR -1
int lireInt(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR]);
int copieInt(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR]);*/

/*int main(void)
{
	int matriceInt[MAX_HAUTEUR][MAX_LARGEUR]; //création de la matrice qui va storer les 9 int
	lireInt("Labo_1.txt", matriceInt); //lecture
	copieInt("Ecriture_Labo_1.txt", matriceInt);//copie
	return(0); //terminé
}*/
/*
 * @brief Fonction qui va permettre de lire les fichiers de type txt et retourne les 9 premiers chiffres (voir MAX_HAUTEUR et MAX_LARGEUR);
 * 
 * @param nom_fichier[]: prend un tableau de char (string) qui sera le nom du fichier que nous allons lire;
 * @param matrice[MAX_HAUTEUR][MAX_LARGEUR]: Tableau de type int, 2D qui va storer les valeurs des 9 int;
 * 
 * @return int: la fonction retourne un chiffre pour dire si il a eu une erreur ou non 
 */
/*int lireInt(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR])
{
	int status = OK;
	int i, j;
	FILE *fpLecture;
	//ouverture
	if ( (fpLecture = fopen(nom_fichier, "r")) == NULL)
	{
		fprintf(stderr, "Error opening read file. \n");
		status = ERREUR;
	}
	//affiche les valeurs storées dans la console
	printf("The values are: ");
	for(i = 0; i<MAX_HAUTEUR; i++)
	{
		for(j = 0; j <MAX_LARGEUR; j++)
		{
			fscanf(fpLecture, "%i", &matrice[i][j]);
			printf("%i ", matrice[i][j]);
		}
	}
	//retourne status pour savoir si il a eu une erreur
	return (status);
}*/
/*
 * @brief Fonction qui va permettre d'écrire des fichiers de type txt et copie les 9 chiffres  d'une matrice (voir MAX_HAUTEUR et MAX_LARGEUR);
 * 
 * @param nom_fichier[]: prend un tableau de char (string) qui sera le nom du fichier que nous allons écrire;
 * @param matrice[MAX_HAUTEUR][MAX_LARGEUR]: Tableau de type int, 2D qui va être les valeurs que nous voulons copier;
 * 
 * @return int: la fonction retourne un chiffre pour dire si il a eu une erreur ou non 
 */
/*int copieInt(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR])
{
	int status = OK;
	int i, j;
	FILE *fpEcriture;
	//Ouverture de fichier en écriture
	if ( (fpEcriture = fopen(nom_fichier, "w")) == NULL)
	{
		fprintf(stderr, "Error opening write file. \n");
		status = ERREUR;
	}
	//copie chaque valeur de la matrice dans le fichier
	for(i = 0; i<MAX_HAUTEUR; i++)
	{
		for(j = 0; j <MAX_LARGEUR; j++)
		{
			fprintf(fpEcriture, "%i ", matrice[i][j]);
		}
		fprintf(fpEcriture, "\n");
	}
	//retourne status pour savoir si il a eu une erreur
	return (status);
}
*/
#define NB_ADRESSES 3
#define NB_ELEMENTS 6
#define MAX_CHAR_ELEMENT 64
#define MAX_CHAR_LIGNE (NB_ELEMENTS * MAX_CHAR_ELEMENT)
#define SEPERATION_CHAR ';'

#define OK 0
#define ERREUR -1

struct Adresse 
{
	char numCivique[MAX_CHAR_ELEMENT];
	char nomRue[MAX_CHAR_ELEMENT];
	char appartement[MAX_CHAR_ELEMENT];
	char ville[MAX_CHAR_ELEMENT];
	char province[MAX_CHAR_ELEMENT];
	char codePostal[MAX_CHAR_ELEMENT];
};

int lireAdresses(char nom_fichier[], char matriceAdresses[NB_ADRESSES][MAX_CHAR_LIGNE]);
int copieDansStruct(char matriceAdresses[NB_ADRESSES][MAX_CHAR_LIGNE], struct Adresse lstAdresses[NB_ADRESSES]);

int main(void)
{
	char matriceAdresses[NB_ADRESSES][MAX_CHAR_LIGNE]; //création de la matrice qui va storer les 9 int
	struct Adresse lstAdresses[NB_ADRESSES];
	lireAdresses("AdressesCiviques.txt", matriceAdresses); //lecture
	copieDansStruct(matriceAdresses, lstAdresses);
	return(0); //terminé
}
int lireAdresses(char nom_fichier[], char matriceAdresses[NB_ADRESSES][MAX_CHAR_LIGNE])
{
	int status = OK;
	int i;
	FILE *fpLecture;
	//ouverture
	if ( (fpLecture = fopen(nom_fichier, "r")) == NULL)
	{
		fprintf(stderr, "Error opening read file. \n");
		status = ERREUR;
	}
	for(i = 0; i < NB_ADRESSES; i++)
	{
		fgets(matriceAdresses[i], MAX_CHAR_LIGNE, fpLecture);
		printf("%s\n", matriceAdresses[i]);
	}
	return (status);
}
int copieDansStruct(char matriceAdresses[NB_ADRESSES][MAX_CHAR_LIGNE], struct Adresse lstAdresses[NB_ADRESSES])
{
	int status = OK;
	int i, j, compteur, decalage = 0;
	for(i = 0; i < NB_ADRESSES; i++)
	{
		compteur = 0;
		decalage = 0;
		for(j = 0; j < MAX_CHAR_LIGNE; j++)
		{
			if(matriceAdresses[i][j] == SEPERATION_CHAR)
			{
				compteur++;
				decalage = j+1;
				matriceAdresses[i][j] = '\0';
			}
			else
			{
				switch(compteur)
				{
					case 0:
						lstAdresses[i].numCivique[j-decalage] = matriceAdresses[i][j];
						printf(lstAdresses[i].numCivique); //pas de problème
						break;
					case 1:
						lstAdresses[i].nomRue[j-decalage] = matriceAdresses[i][j];
						printf(lstAdresses[i].nomRue); // erreur bizarre au 8ieme caractère ... pas capable de le trouver
						break;
					case 2:
						lstAdresses[i].appartement[j-decalage] = matriceAdresses[i][j];
						printf(lstAdresses[i].appartement); //Problématique aussi
						break;
					case 3:
						lstAdresses[i].ville[j-decalage] = matriceAdresses[i][j];
						printf(lstAdresses[i].ville);//all good
						break;
					case 4:
						lstAdresses[i].province[j-decalage] = matriceAdresses[i][j];
						printf(lstAdresses[i].province); // problématique???? teh fuck
						break;
					case 5:
						lstAdresses[i].codePostal[j-decalage] = matriceAdresses[i][j];
						printf(lstAdresses[i].codePostal); // all good
						if((j-decalage) >= 6)
							j = MAX_CHAR_LIGNE;
						break;
				}
			}
		}
	}
	return(status);
}
