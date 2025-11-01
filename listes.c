#include <stdio.h>
#include <stdlib.h>

#include "listes.h"


void afficher_liste_points(liste_points *liste) {
    if (liste == NULL || liste->tete == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    //printf("Liste de points:\n");

    cellule_liste_points *cel = liste->tete;

    while (cel != NULL) {
        printf("%.1f %.1f\n", cel->value.x, cel->value.y);
        cel = cel->suiv;
        liste->taille++;
    }
    // printf("\nNombre de points : %d\n", liste->taille);
    // printf("Nombre de segments : %d\n\n", liste->taille-1);
}



unsigned int taille_liste(liste_points liste) {
    unsigned int taille = 0;
    cellule_liste_points *courant = liste.tete; // Commencer à partir de la tête de la liste

    while (courant != NULL) {
        taille++; // Incrémenter la taille pour chaque élément trouvé
        courant = courant->suiv; // Passer à l'élément suivant
    }

    return taille;
}


tableau_points convertir_liste_en_tableau (liste_points *liste)
{
    tableau_points tableau;
    int nb_points = taille_liste(*liste);

    cellule_liste_points *cel = liste->tete;

    tableau.tab = malloc( (nb_points + 1) *sizeof(Point));

    
    for (int i = 0; i < nb_points; i++) {

        tableau.tab[i] = cel->value;
        cel = cel->suiv;
    }
    

    return tableau;
}



liste_points concatenation(liste_points L1, liste_points L2){

    if (L1.tete == NULL){ 
        return L2;
    }
    if (L2.tete == NULL){
        return L1;
    }

    cellule_liste_points *cel = L1.tete;
    while (cel->suiv != NULL)
    {
        cel = cel->suiv;
    }

    cel->suiv = L2.tete;
    L1.taille = L1.taille + L2.taille;


    return L1;

}

// //tableau_points list_to_tab(liste_points liste, )