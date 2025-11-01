#include <stdio.h>

#include "approx_bezier2.h"



Bezier2 approx_bezier2(tableau_points *tableau, int j1, int j2){

    Bezier2 B;
    int n = j2 - j1;
    Point Pj1 = tableau->tab[j1];
    Point Pj2 = tableau->tab[j2];

    B.C0 = Pj1;
    B.C2 = Pj2;

    if (n==1)
    {
        B.C1 = multi_point(add_point(Pj1,Pj2),0.5);
    }

    else if (n >= 2)
    {
        double alpha = (3*(double)n)/(carre((double)n)-1);
        double beta = (1-2*(double)n)/(2*((double)n+1));

        Point Pi_sum = set_point(0,0);
        for (int i = 1; i <= n-1; i++)
        {
            Point Pi =  tableau->tab[j1+i];
            Pi_sum = add_point(Pi_sum,Pi);
        }   
        
        B.C1 = add_point(multi_point(Pi_sum, alpha), multi_point(add_point(Pj1, Pj2), beta));
    }
    
    
    return B;
}

liste_points simplification_douglas_peucker_bezier2(tableau_points *tableau, int j1, int j2, double d){

    int n = j2 - j1;
    Bezier2 B = approx_bezier2(tableau,j1,j2);
    double dmax = 0;
    int k = j1;
    double ti;
    double i;

    double dj;
    liste_points L;
    L.taille = 0;
    L.tete = NULL;
    L.queue = NULL;

    for (int j = j1 + 1 ; j < j2; j++)
    {
        Point Pj = tableau->tab[j];
        i = j - j1;
        ti = i/n;
        dj = distance_point_bezier2(Pj, B, ti);

        if (dmax < dj)
        {
            dmax = dj;
            k = j;
        }
    }  
    if (dmax <= d)
    {
        memoriser_position(B.C0,&L);
        memoriser_position(B.C1,&L);
        memoriser_position(B.C2,&L);
    }
    else
    {
        liste_points L1 = simplification_douglas_peucker_bezier2(tableau,j1,k,d);
        liste_points L2 = simplification_douglas_peucker_bezier2(tableau,k,j2,d);
        L = concatenation(L1,L2);
    }
        
    return L;
}

void ecrire_bezier2(liste_points *liste, FILE *f, Image I) {
    tableau_points tableau = convertir_liste_en_tableau(liste);
    int nb_points = taille_liste(*liste);
    
    Point premier_point_contour = tableau.tab[0];
    fprintf(f, "%.1f %.1f moveto\n", premier_point_contour.x, hauteur_image(I) - premier_point_contour.y);
    
    for (int i = 0; i < nb_points-3; i+=3) {
        Point C0 = tableau.tab[i];
        Point C1 = tableau.tab[i+1];
        Point C2 = tableau.tab[i+2];
        double C0_y = hauteur_image(I)-C0.y;
        double C1_y = hauteur_image(I)-C1.y;
        double C2_y = hauteur_image(I)-C2.y;

        fprintf(f, "%.1lf %.1lf %.1lf %.1lf %.1lf %.1lf curveto\n", C0.x, C0_y, C1.x, C1_y, C2.x, C2_y);
    }

    
    fprintf(f,"\n");
    
}