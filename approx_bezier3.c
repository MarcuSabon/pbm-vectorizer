#include <stdio.h>

#include "approx_bezier3.h"


double gamma(double k, double n){
    double gamma = 6*pquatre(k) - 8*n*cube(k) + 6*carre(k) - 4*n*k + pquatre(n) - carre(n);
    return gamma;
}



Bezier3 approx_bezier3(tableau_points *tableau, int j1, int j2){


    Bezier3 B;
    int n = j2 - j1;


    if (n==1)
    {
        Point P0 = tableau->tab[j1];
        Point P1 = tableau->tab[j2];
        B.C0 = P0;
        B.C1 = div_point(add_point(multi_point(P0,2),P1),3);
        B.C2 = div_point(add_point(P0, multi_point(P1,2)),3);
        B.C3 = P1;

    }
    else if (n==2)
    {
        Point P0 = tableau->tab[j1];
        Point P2 = tableau->tab[j2];
        Point P1 = multi_point(add_point(P0,P2),0.5);

        B.C0 = P0;
        B.C1 = div_point(sub_point(multi_point(P1,4),P2),3);
        B.C2 = div_point(sub_point(multi_point(P1,4),P0),3);
        B.C3 = P2;
    }

    else
    {
        Point Pj1 = tableau->tab[j1];
        Point Pj2 = tableau->tab[j2];

        double alpha = (-15*cube((double)n) + 5*carre((double)n) + 2*(double)n + 4) / (3 * ((double)n+2) * (3*carre((double)n)+1));
        double beta = ((10*cube((double)n)) - (15*carre((double)n)) + (double)n + 2)  /  ( 3*((double)n+2)*(3*carre((double)n)+1));
        double lambda = (70 * (double)n) / (3 * (carre((double)n)-1) * (carre((double)n)-4) * (3*carre((double)n) + 1));

        // Calcul de C0
        B.C0 = Pj1;

        // Calcul de C1
        Point Pi_sum_C1 = set_point(0,0);
        for (int i = 1; i <= n-1 ; i++)
        {
            Point Pi = multi_point(tableau->tab[j1+i],gamma((double)i,(double)n));
            Pi_sum_C1 = add_point(Pi_sum_C1,Pi);
        }
        B.C1 = add_point(add_point(multi_point(Pj1,alpha),multi_point(Pi_sum_C1,lambda)),multi_point(Pj2, beta));

        // Calcul de C2
        Point Pi_sum_C2 = set_point(0,0);
        for (int i = 1; i <= n-1; i++)
        {
            Point Pi = multi_point(tableau->tab[j1+i], gamma((double)n-i,(double)n));
            Pi_sum_C2 = add_point(Pi_sum_C2,Pi);
        }
        B.C2 = add_point(add_point(multi_point(Pj1,beta),multi_point(Pi_sum_C2,lambda)),multi_point(Pj2, alpha));
        
        // Calcul de C3
        B.C3 = Pj2;
    }
    
    
    return B;
}



liste_points simplification_douglas_peucker_bezier3(tableau_points *tableau, int j1, int j2, double d){

    int n = j2 - j1;
    Bezier3 B = approx_bezier3(tableau,j1,j2);
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
        dj = distance_point_bezier3(Pj, B, ti);

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
        memoriser_position(B.C3,&L);
    }
    else
    {
        liste_points L1 = simplification_douglas_peucker_bezier3(tableau,j1,k,d);
        liste_points L2 = simplification_douglas_peucker_bezier3(tableau,k,j2,d);
        L = concatenation(L1,L2);
    }
        
    return L;
}

int ecrire_bezier3(liste_points *liste, FILE *f, Image I) {
    tableau_points tableau = convertir_liste_en_tableau(liste);
    int nb_points = taille_liste(*liste);
    int nb_courbes = 1;
    Point premier_point_contour = tableau.tab[0];
    fprintf(f, "%.1f %.1f moveto\n", premier_point_contour.x, hauteur_image(I) - premier_point_contour.y);
    
    for (int i = 1; i < nb_points-3; i+=4) {
        Point C0 = tableau.tab[i];
        Point C1 = tableau.tab[i+1];
        Point C2 = tableau.tab[i+2];
        double C0_y = hauteur_image(I)-C0.y;
        double C1_y = hauteur_image(I)-C1.y;
        double C2_y = hauteur_image(I)-C2.y;
        nb_courbes++;
        fprintf(f, "%.1lf %.1lf %.1lf %.1lf %.1lf %.1lf curveto\n", C0.x, C0_y, C1.x, C1_y, C2.x, C2_y);
    }

    
    fprintf(f,"\n");
    return nb_courbes;
}