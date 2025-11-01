#include "geom2.h"
#include "listes.h"
#include "image.h"
#include "contours.h"

Bezier3 approx_bezier3(tableau_points *CONT, int j1, int j2);

liste_points simplification_douglas_peucker_bezier3(tableau_points *tableau, int j1, int j2, double d);

int ecrire_bezier3(liste_points *liste, FILE *f, Image I);