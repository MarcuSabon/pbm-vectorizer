#include <stdio.h>
#include <stdlib.h>

#include "math.h"
#include "geom2.h"
#include "approx_bezier2.h"
#include "approx_bezier3.h"

/* creer un point */
Point set_point(double x, double y){
    Point P = {x,y};
    return P;
}

Vecteur set_vecteur(double x, double y){
    Vecteur V = {x,y};
    return V;
}

/* ajouter deux points entre eux */
Point add_point(Point P1, Point P2){
    return set_point(P1.x+P2.x, P1.y+P2.y);
}

Point sub_point(Point P1, Point P2){
    return set_point(P1.x-P2.x, P1.y-P2.y);
}

/* ajouter deux vecteurs entre eux */
Vecteur add_vect(Vecteur V1, Vecteur V2){
    Vecteur V = {V1.x+V2.x, V1.y+V2.y};
    return V;
}


/* creation d'un vecteur a partir de deux vecteurs */
Vecteur vect_bipoint(Point A, Point B){
    Vecteur V = {B.x-A.x,B.y-A.y};
    return V;
}


/* multiplier un point par un scalaire */
Point multi_point(Point P, double x){
    return set_point(x*P.x, x*P.y);
}

Point div_point(Point P, double x){
    return set_point(P.x/x,P.y/x);
}


/* Multiplier un vecteur par un scalaire */
Vecteur multi_vect(Vecteur V, double x){
    Vecteur V1 = {x*V.x, x*V.y};
    return V1;
}

/* Calcule le produit scalaire de deux vecteurs */
double produit_scalaire(Vecteur V1, Vecteur V2){
    return (V1.x*V2.x + V1.y*V2.y);

}

/* Calcule la norme d'un vecteur */
double norme_vect(Vecteur V){
    return (sqrt((V.x*V.x)+(V.y*V.y)));
}

/* calcule la distance entre deux points*/
double distance_point(Point P1, Point P2){
    return (sqrt((P1.x-P2.x) * (P1.x-P2.x) + (P1.y-P2.y) * (P1.y-P2.y)));
}

/* Affiche les points */
void affiche_point(Point P){
    printf("(%lf,%lf)\n", P.x, P.y);
}


/* Affiche les vecteurs*/
void affiche_vecteur(Vecteur V){
    printf("(%lf,%lf)\n", V.x, V.y);
}

Segment creer_segment(Point A, Point B){
    Segment AB;
    AB.A = A;
    AB.B = B;
    return AB;
}

Bezier2 creer_Bezier2(Point C0, Point C1, Point C2){
    Bezier2 C;
    C.C0 = C0;
    C.C1 = C1;
    C.C2 = C2;
    return C;
}

double distance_point_segment(Point P, Segment S){
    //double Calcule = distance_point(A,B);
    Point Q = set_point(0,0);  // initialise le point Q a (0.0 0.0)
    Vecteur AP = vect_bipoint(S.A,P);
    Vecteur BP = vect_bipoint(S.B,P);;
    Vecteur AB = vect_bipoint(S.A,S.B);;
    double L;
    L= produit_scalaire(AP,AB)/produit_scalaire(AB,AB);
    printf("\nλ = %f\n",L);
    if (distance_point(S.A,S.B)==0)
    {
        return norme_vect(AP);
    }
    else
    {
        if (L<0)
        {
            return norme_vect(AP);
        }
        else if (L >= 0 && L <= 1)
        {

            Q = add_point(S.A, multi_point(sub_point(S.B,S.A),L));
            Vecteur QP = vect_bipoint(Q,P);
            return norme_vect(QP);
        }
        else
        {
            return norme_vect(BP);
        }
    }
}

double carre(double n){
    return n*n;
}

double cube(double n){
    return n*n*n;
}

double pquatre(double n){
    return n*n*n*n;
}


Point calcul_C_t_Bez2(Bezier2 B, double t){
    return add_point(add_point( multi_point(B.C0, carre(1-t)), multi_point(B.C1, 2*t*(1-t))), multi_point(B.C2, carre(t)));
}

Point calcul_C_t_Bez3(Bezier3 B, double t){
    return add_point(add_point(add_point(multi_point(B.C0,cube(1-t)),multi_point(B.C1,3*t*carre(1-t))),multi_point(B.C2,3*carre(t)*(1-t))),multi_point(B.C3,cube(t)));
}

double distance_point_bezier2(Point P, Bezier2 B, double ti){
    Point C_ti = calcul_C_t_Bez2(B,ti);
    double distance = distance_point(P,C_ti);
    return distance;
}

double distance_point_bezier3(Point P, Bezier3 B, double ti){
    Point C_ti = calcul_C_t_Bez3(B,ti);
    double distance = distance_point(P,C_ti);
    return distance;
}