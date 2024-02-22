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
	int length = 0; // valeur qui garde le compte
	// Loop jusqua fin
	while (*str != '\0') {
		length++;
		str++;
	}
	return length; //retourne la longueur du string
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
	if((nbLignes <= 256 && nbLignes >= 0) || (nbColonnes  <= 256 && nbColonnes >= 0)) //vérification que les lignes et colonnes ne dépassent pas 256
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
int pgm_lire(char nom_fichier[], int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes,
				int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
{
	int status = OK; // pas nécessaire peut être enlevé plus tard
	int i, j, compteur; //pour les boucles for et compteur pour savoir quelle info du metadata on lit présentement 
	int decalage; //decalage de l'incrémentation pour le metaadata
	char str[MAX_CHAINE]; //string pour comparer le format
	char c; //charactère intermédiaire
	
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
					case(0): //auteur
						p_metadonnees->auteur[i-decalage] = c;
						break;
					case(1): //date de création
						p_metadonnees->dateCreation[i-decalage] = c;
						break;
					case(2): //lieu de création
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
		printf("HEHE\n");
		
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
int pgm_copier(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1,int matrice2[MAX_HAUTEUR][MAX_LARGEUR],
				int *p_lignes2, int *p_colonnes2)
{
	//declare variables
		int i;
		int j;
	//verifie si lignes & colonnes sont de grandeur approprier
		if (lignes1 > MAX_HAUTEUR || lignes1 < 1 || 
		    colonnes1 > MAX_LARGEUR || colonnes1 < 1){
			return ERREUR;} //a verifier si bon type d<erreur		
	
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
		/*printf("Contenu de la matrice :\n");
		for (i = 0; i < lignes1; i++) {
			for (j = 0; j < colonnes1; j++) {
				printf("%d ", matrice2[i][j]);
			}
			printf("\n");
		}*/
	
    return OK;
}
//JT 
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
//JT 
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

//JT
int pgm_eclaircir_noircir(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval, int valeur)
{
	int i,j;
	int valeurNouvelle;
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
    return (OK);
}
//CAD
int pgm_creer_negatif(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes, int colonnes, int maxval)
{
    return OK;
}
//JT
int pgm_extraire(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int lignes2, int colonnes2, int *p_lignes, int *p_colonnes)
{
	int i,j, x, y;
	int ligneExtraction = (lignes2 - lignes1)+1;
	int colonneExtraction = (colonnes2 - colonnes1)+1;
	int matriceIntermediaire[MAX_HAUTEUR][MAX_LARGEUR];
	//Vérification de tailles des matrices
	if((verifLigneColonne(lignes1,colonnes1) != OK) || (verifLigneColonne(lignes2,colonnes2) != OK) ||
	 (verifLigneColonne(*p_lignes, *p_colonnes) != OK))
		return ERREUR_TAILLE;
	//vérification que le point 1 est "plus petit" que point 2
	else if((lignes1 > lignes2) || (colonnes1 > colonnes2))
		return ERREUR;
	//vérification que les points de la nouvelle matrice sont à l'intérieur des dimensions de l'ancienne
	else if((lignes1 > *p_lignes) || (colonnes1 > *p_colonnes)||(lignes2 > *p_lignes) || (colonnes2 > *p_colonnes))
		return ERREUR;
	//vérification que la différences entres le point 1 et 2 est plus petite ou égal à l'ancienne
	else if((ligneExtraction > *p_lignes) || (colonneExtraction > *p_colonnes))
		return ERREUR;
	else
	{
		//déplace valeur de matrice dans une matrice intermédiaire
		y = 0;
		for(i = lignes1; i <= lignes2; i++)
		{
			x = 0;
			for(j = colonnes1; j <= colonnes2; j++)
			{
				matriceIntermediaire[y][x] = matrice[i][j];
				x++;
			}
			y++;
		}
		//déplace valeur matrice intermédiaire dans matrice finale
		for(i = 0; i < ligneExtraction; i++)
		{
			for(j = 0; j < colonneExtraction; j++)
			{
				matrice[i][j] = matriceIntermediaire[i][j];
				printf("%i ", matrice[i][j]);
			}
			printf("\n");
		}
		*p_lignes = ligneExtraction;
		*p_colonnes = colonneExtraction;
	}
	
    return OK;
}
//CAD
int pgm_sont_identiques(int matrice1[MAX_HAUTEUR][MAX_LARGEUR], int lignes1, int colonnes1, int matrice2[MAX_HAUTEUR][MAX_LARGEUR], int lignes2, int colonnes2)
{
    return OK;
}
//CAD
int pgm_pivoter90(int matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int sens)
{
    return OK;
}

// Operations pour les images couleurs
int ppm_lire(char nom_fichier[], struct RGB matrice[MAX_HAUTEUR][MAX_LARGEUR], int *p_lignes, int *p_colonnes, int *p_maxval, struct MetaData *p_metadonnees)
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
	if(stringCompare(str, VAR_PPM) == IDENTIQUES)
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
			fscanf(fpLecture, "%i", &matrice[i][j].valeurR);
			if(!(matrice[i][j].valeurR >= 0 && matrice[i][j].valeurR <= *p_maxval))
			{
				status = ERREUR_FORMAT;
				return(status);
			}
			fscanf(fpLecture, "%i", &matrice[i][j].valeurG);
			if(!(matrice[i][j].valeurG >= 0 && matrice[i][j].valeurG <= *p_maxval))
			{
				status = ERREUR_FORMAT;
				return(status);
			}
			fscanf(fpLecture, "%i", &matrice[i][j].valeurB);
			if(!(matrice[i][j].valeurB >= 0 && matrice[i][j].valeurB <= *p_maxval))
			{
				status = ERREUR_FORMAT;
				return(status);
			}
			printf("R:%i, G:%i, B:%i ", matrice[i][j].valeurR, matrice[i][j].valeurG, matrice[i][j].valeurB);
		}
		printf("\n");
	}
	//SAVE DONNÉES FIN
	fclose(fpLecture); //fin de lecture
	return (status);
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
