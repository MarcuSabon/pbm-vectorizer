#include "geom2.h"
#include "listes.h"
#include "image.h"
#include "contours.h"

Bezier2 approx_bezier2(tableau_points *CONT, int j1, int j2);

liste_points simplification_douglas_peucker_bezier2(tableau_points *tableau, int j1, int j2, double d);

void ecrire_bezier2(liste_points *liste, FILE *f, Image I);