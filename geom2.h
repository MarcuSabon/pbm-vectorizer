#ifndef _GEOM2_H_
#define _GEOM2_H_

typedef struct Vecteur{
    double x, y;
}Vecteur;

typedef struct Point{
    double x,y;
}Point;

typedef struct Segment{
    Point A, B;
}Segment;

typedef struct Bezier2{
    Point C0,C1,C2;
}Bezier2;

typedef struct Bezier3{
    Point C0,C1,C2,C3;
}Bezier3;

Point set_point(double x, double y);

Point add_point(Point P1, Point P2);

Point multi_point(Point P, double x);

Point div_point(Point P, double x);

Vecteur set_vecteur(double x, double y);

Vecteur add_vect(Vecteur V1, Vecteur V2);

Point sub_point(Point P1, Point P2);

Vecteur vect_bipoint(Point A, Point B);

Vecteur multi_vect(Vecteur V1, double x);

Segment creer_segment(Point A, Point B);

double produit_scalaire(Vecteur V1, Vecteur V2);

double norme_vect(Vecteur V);

double distance_point(Point P1, Point P2);

void affiche_point(Point P);

void affiche_vecteur(Vecteur V);

double distance_point_segment(Point P, Segment S);

double carre(double n);

double cube(double n);

double pquatre(double n);

Point calcul_C_t_Bez2(Bezier2 B, double t);

Point calcul_C_t_Bez3(Bezier3 B, double t);

double distance_point_bezier2(Point P, Bezier2 B, double ti);

double distance_point_bezier3(Point P, Bezier3 B, double ti);

#endif