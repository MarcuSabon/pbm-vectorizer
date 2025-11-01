#ifndef _CONTOURS_H_
#define _CONTOURS_H_

#include "geom2.h"
#include "listes.h"
#include "types_macros.h"
#include "image.h"



typedef enum {NORD, EST, OUEST, SUD} Orientation;
  
void memoriser_position(Point P, liste_points *liste); 

Point trouver_pixel_depart(Image I, Point coordonnee_retrouvee);



Orientation nouvelle_orientation(Orientation orientation, Image I, Point P);

Orientation nouvelle_orientation2(Orientation orientation, Image I, Point P);

void set_pixel_blanc(Image I, Orientation orientation);

void avancer(Orientation orientation, Point *P);

void ecrire_contour(liste_points *liste, FILE *f, Image I);

void ecrire_contour_segments(liste_points liste, FILE *f,Image I);

Image creer_image_masque(Image I);

Point parcourir_image_masque(Image M, Point le_point_sympa);

liste_points simplification_douglas_peucker(tableau_points *tableau, int x, int y, double d);

#endif