#ifndef _LISTE_H_
#define _LISTE_H_

#include "geom2.h"


typedef struct cellule_liste_points{

    Point value;
    struct cellule_liste_points * suiv;

}cellule_liste_points;

typedef struct liste_points{

    unsigned int taille;
    cellule_liste_points *tete;
    cellule_liste_points *queue;

}liste_points;

typedef struct tableau_points{

    unsigned int taille;
    Point *tab;

}tableau_points; 

unsigned int taille_liste(liste_points liste);

tableau_points convertir_liste_en_tableau(liste_points *liste);
// typedef struct Tableau_Point_
// {
// 	unsigned int taille; /* nombre d'elements dans le tableau */
// 	Point *tab;			 /* (pointeur vers) le tableau des elements */
// } Tableau_Point;

// /*---- le type cellule de liste de point ----*/
// typedef struct Cellule_Liste_Point_
// {
// 	Point data;						   /* donnee de l'element de liste */
// 	struct Cellule_Liste_Point_ *suiv; /* pointeur sur l'element suivant */
// } Cellule_Liste_Point;

// /*---- le type liste de point ----*/
// typedef struct Liste_Point_
// {
// 	unsigned int taille;		/* nombre d'elements dans la liste */
// 	Cellule_Liste_Point *first; /* pointeur sur le premier element de la liste */
// 	Cellule_Liste_Point *last;	/* pointeur sur le dernier element de la liste */
// 								/* first = last = NULL et taille = 0 <=> liste vide */
// } Liste_Point;

// typedef Liste_Point Contour;


tableau_points sequence_points_liste_vers_tableau(liste_points *L);

void afficher_liste_points(liste_points *liste);

tableau_points sequence_liste_V_sequence_tab(liste_points liste);

liste_points concatenation(liste_points L1, liste_points L2);


#endif