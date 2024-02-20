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