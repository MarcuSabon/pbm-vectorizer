#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include "contours.h"



void memoriser_position(Point P, liste_points *liste){
    cellule_liste_points *cel = malloc(sizeof(cellule_liste_points));
    if (cel == NULL){
        printf("Erreur allocation mémoire");
        exit(EXIT_FAILURE);
    }

    cel->value = P;
    cel->suiv = NULL;

    if (liste->tete == NULL)
    {
        liste->tete = cel;
        liste->queue = cel;
    }else{
        liste->queue->suiv = cel;
        liste->queue = cel;
    }
}



Point trouver_pixel_depart(Image I, Point coordonnee_retrouvee){

    double largeur = largeur_image(I);
    double hauteur = hauteur_image(I);
    Point P;
    Point onenvoie = set_point(-1,-1);

    for (P.y = coordonnee_retrouvee.y ; P.y <= hauteur ; P.y++){
        for (P.x = coordonnee_retrouvee.x ; P.x <= largeur ; P.x++){


            if (get_pixel_image(I, P.x , P.y) == NOIR){


                if (get_pixel_image(I, P.x,P.y-1)==BLANC){


                    onenvoie = set_point(P.x, P.y);
                    return onenvoie;
                }
            }
        }
    }
    return onenvoie;
}


Orientation nouvelle_orientation(Orientation orientation, Image I, Point P){
    Pixel pG = BLANC;
    Pixel pD = BLANC;
    switch(orientation){
        case EST:
            //printf("Orientation : EST\n\n");
            pG = get_pixel_image(I, P.x+1, P.y);
            pD = get_pixel_image(I, P.x+1, P.y+1);
            if (pG == BLANC && pD == BLANC)
            {
                return SUD;
            }
            else if((pG == NOIR && pD == BLANC) || (pG == NOIR && pD == NOIR))
            {
                return NORD;
            }
            else
            {
                return EST;
            }

            break;
        case NORD:
            //printf("Orientation : NORD\n\n");
            pG = get_pixel_image(I, P.x, P.y);
            pD = get_pixel_image(I, P.x+1, P.y);
            if (pG == BLANC && pD == BLANC)
            {
                return EST;
            }
            else if((pG == NOIR && pD == BLANC) || (pG == NOIR && pD == NOIR))
            {
                return OUEST;
            }
            else
            {
                return NORD;
            }
            break;
        case OUEST:
            //printf("Orientation : OUEST\n\n");
            pG = get_pixel_image(I, P.x, P.y+1);
            pD = get_pixel_image(I, P.x, P.y);
            if (pG == BLANC && pD == BLANC) 
            {
                return NORD;
            }
            else if((pG == NOIR && pD == BLANC) || (pG == NOIR && pD == NOIR))
            {
                return SUD;
            }
            else
            {
                return OUEST;
            }
            break;
        case SUD:
        //printf("Orientation : SUD\n\n");
            pG = get_pixel_image(I, P.x+1, P.y+1);
            pD = get_pixel_image(I, P.x, P.y+1);
            if (pG == BLANC && pD == BLANC) 
            {
                return OUEST;
            }
            else if((pG == NOIR && pD == BLANC) || (pG == NOIR && pD == NOIR))
            {
                return EST;
            }
            else
            {
                return SUD;
            }
            break;
    }
}




void avancer(Orientation orientation, Point *P)
{
    switch(orientation){
        case NORD:
            P->y--;
            break;
        case SUD:
            P->y++;
            break;
        case EST:
            P->x++;
            break;
        case OUEST:
            P->x--; 
            break;
    }
}


void ecrire_contour(liste_points *liste, FILE *f, Image I) {
    tableau_points tableau = convertir_liste_en_tableau(liste);
    int nb_points = taille_liste(*liste);
    
    Point premier_point_contour = tableau.tab[0];
    fprintf(f, "%.1f %.1f moveto\n", premier_point_contour.x, hauteur_image(I) - premier_point_contour.y);
    
    for (int i = 1; i < nb_points-1; i++) {
        Point P = tableau.tab[i];

        float Y = hauteur_image(I) - P.y;
        fprintf(f, "%.1lf %.1lf lineto\n", P.x, Y);
    }

    fprintf(f,"\n");
    
}




Image creer_image_masque(Image I)
{
    UINT largeur = largeur_image(I);
    UINT hauteur = hauteur_image(I);
    Image M = creer_image(largeur,hauteur);

    for (int i = 1; i <= hauteur; i++){
        for (int j = 1; j <= largeur; j++){
            if (get_pixel_image(I, j, i) == NOIR && get_pixel_image(I, j, i-1) == BLANC) {
                set_pixel_image(M, j, i, NOIR);
            }
        }
        
    }
    return M;
}





Point parcourir_image_masque(Image M, Point le_point_sympa){
    int largeur = largeur_image(M);
    int hauteur = hauteur_image(M);
    for (int i = le_point_sympa.y; i <= hauteur; i++) {        
        for (int j = le_point_sympa.x; j <= largeur; j++) {
            if (get_pixel_image(M, j, i) == NOIR) {
                return set_point(j,i); // Il y a un pixel noir dans l'image masque
            }
        }
    }
    return set_point(-1,-1); // Aucun pixel noir trouvé dans l'image masque
}

void set_pixel_blanc(Image I, Orientation orientation){
    Point P;
    switch(orientation){
        case EST:
            set_pixel_image(I, P.x+1, P.y+1,BLANC);
            break;
        case OUEST:
            set_pixel_image(I, P.x, P.y,BLANC);
            break;
        case NORD:
            set_pixel_image(I, P.x+1, P.y,BLANC);
            break;
        case SUD:
            set_pixel_image(I, P.x, P.y+1,BLANC);
            break;
    }
} 




