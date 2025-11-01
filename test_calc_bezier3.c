#include <stdio.h>
#include <stdlib.h>

#include "geom2.h"
#include "approx_bezier3.h"
#include "contours.h"
#include "listes.h"

int main(int argc, char * argv[])
{

    int n;
    printf("\nChoisir n :\n");
    scanf("%d", &n);

    if (n==1)
    {
        liste_points L;
        L.taille = 0;
        L.tete = NULL;
        L.queue = NULL;
        double P0_1_x, P0_1_y, P1_1_x, P1_1_y;

        printf("Point P0 :\n");
        scanf("%lf", &P0_1_x);
        scanf("%lf", &P0_1_y);
        printf("Point P1 :\n");
        scanf("%lf", &P1_1_x);
        scanf("%lf", &P1_1_y);

        Point P0_1 = set_point(P0_1_x,P0_1_y); 
        Point P1_1 = set_point(P1_1_x,P1_1_y);
        
        memoriser_position(P0_1, &L); 
        memoriser_position(P1_1, &L);

        tableau_points tableau = convertir_liste_en_tableau(&L);
        int taille_tab = taille_liste(L);
        Bezier3 B = approx_bezier3(&tableau, 0, taille_tab-1);
        printf("%lf %lf\n",B.C1.x, B.C1.y);
        
        printf("\n\n");
        printf("C0 = (%lf %lf)\n", B.C0.x, B.C0.y);
        printf("C1 = (%lf %lf)\n", B.C1.x, B.C1.y);
        printf("C2 = (%lf %lf)\n", B.C2.x, B.C2.y);
        printf("C3 = (%lf %lf)\n\n", B.C3.x, B.C3.y);
    }
    else if (n == 2)
    {
        liste_points L;
        L.taille = 0;
        L.tete = NULL;
        L.queue = NULL;
        double P0_x, P0_y, P1_x, P1_y, P2_x, P2_y;

        printf("Point P0 :\n");
        scanf("%lf", &P0_x);
        scanf("%lf", &P0_y);
        printf("Point P1 :\n");
        scanf("%lf", &P1_x);
        scanf("%lf", &P1_y);
        printf("Point P2 :\n");
        scanf("%lf", &P2_x);
        scanf("%lf", &P2_y);

        Point P0 = set_point(P0_x,P0_y); 
        Point P1 = set_point(P1_x,P1_y); 
        Point P2 = set_point(P2_x,P2_y);

        memoriser_position(P0, &L); 
        memoriser_position(P1, &L); 
        memoriser_position(P2, &L);

        tableau_points tableau = convertir_liste_en_tableau(&L);
        int taille_tab = taille_liste(L);

        Bezier3 B = approx_bezier3(&tableau, 0, taille_tab-1);
        printf("\n\n");
        printf("C0 = (%lf %lf)\n", B.C0.x, B.C0.y);
        printf("C1 = (%lf %lf)\n", B.C1.x, B.C1.y);
        printf("C2 = (%lf %lf)\n", B.C2.x, B.C2.y);
        printf("C3 = (%lf %lf)\n\n", B.C3.x, B.C3.y);


    }
    else
    {
        liste_points L;
        L.taille = 0;
        L.tete = NULL;
        L.queue = NULL;
        double Q0_x, Q0_y ,Q1_x ,Q1_y ,Q2_x ,Q2_y ,Q3_x ,Q3_y;

        printf("Point Q0 :\n");
        scanf("%lf", &Q0_x);
        scanf("%lf", &Q0_y);
        printf("Point Q1 :\n");
        scanf("%lf", &Q1_x);
        scanf("%lf", &Q1_y);
        printf("Point Q2 :\n");
        scanf("%lf", &Q2_x);
        scanf("%lf", &Q2_y);
        printf("Point Q3 :\n");
        scanf("%lf", &Q3_x);
        scanf("%lf", &Q3_y);

        Point Q0 = set_point(Q0_x,Q0_y);
        Point Q1 = set_point(Q1_x,Q1_y);
        Point Q2 = set_point(Q2_x,Q2_y);
        Point Q3 = set_point(Q3_x,Q3_y);

        memoriser_position(Q0, &L);
        memoriser_position(Q1, &L);
        memoriser_position(Q2, &L);
        memoriser_position(Q3, &L);

        tableau_points tableau = convertir_liste_en_tableau(&L);
        int taille_tab = taille_liste(L);

        Bezier3 B = approx_bezier3(&tableau,0,taille_tab-1);
        printf("\n\n");
        printf("C0 = (%lf %lf)\n", B.C0.x, B.C0.y);
        printf("C1 = (%lf %lf)\n", B.C1.x, B.C1.y);
        printf("C2 = (%lf %lf)\n", B.C2.x, B.C2.y);
        printf("C3 = (%lf %lf)\n\n", B.C3.x, B.C3.y);
    }
    

    return 0;
}
