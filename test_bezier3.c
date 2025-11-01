#include <stdio.h>
#include <time.h>
#include "approx_bezier3.h"
#include "contours.h"




int main(int argc, char const *argv[])
{
    
    
    
    if (argc != 4 ){
        printf("\nUsage : ./test_simplification_segment <fichier.pbm> <fichier.eps> <d>\n\n");
        exit(1);
    }

    FILE *f = fopen(argv[2],"w");
    Image I = lire_fichier_image(argv[1]);
    Image M = creer_image_masque(I);
    

    double d;
    sscanf(argv[3], "%lf", &d);
    if (d < 0)
    {
        printf("\nMerci de rentrer une distance seuil d positive\n\n");
        exit(1);
    }
    

    int H = hauteur_image(I);
    int L = largeur_image(I);

    int nb_contours = 0;
    // int nb_points = 0;
    // int nb_segments = 0;
    int nb_courbes = 0;
    int somme_courbes = 0;
    

    int le_fameux_compte_heure = 0;
    Point P_debut = set_point(1,1);
    Point P;

    fprintf(f,"%%!PS−Adobe −3.0 EPSF−3.0\n");
    fprintf(f,"%%%%BoundingBox: 0 0 %d %d\n",L ,H);

    
    Point debut_sympa = set_point(1,1);
    while (parcourir_image_masque(M,debut_sympa).x != -1 && parcourir_image_masque(M,debut_sympa).y != -1) {
        if (le_fameux_compte_heure == 0)
        {
            P = trouver_pixel_depart(M, P_debut);
            le_fameux_compte_heure++;
            //debut_sympa = parcourir_image_masque(M, debut_sympa);
        }
        else
        {   
            
            P = trouver_pixel_depart(M, P);
            
        }
        

        Point position_initiale = {P.x - 1, P.y - 1};
        Point robot = position_initiale;
        Orientation orientation = EST;
        bool FLAG = true;

        liste_points liste;
        liste.taille = 0;
        liste.tete = NULL;
        liste.queue = NULL;


        while (FLAG) {
            memoriser_position(robot, &liste);
            if (orientation == EST) {
                set_pixel_image(M, robot.x + 1, robot.y + 1, BLANC);

            }
            avancer(orientation, &robot);
            
            

            orientation = nouvelle_orientation(orientation, I, robot);

            if ((distance_point(robot, position_initiale) == 0) && (orientation == EST)) {
                FLAG = false;
            }
        }
        debut_sympa = parcourir_image_masque(M, debut_sympa);
        
        memoriser_position(robot, &liste);
        nb_contours++;
        tableau_points tableau;
        tableau = convertir_liste_en_tableau(&liste);
        liste_points liste_bezier3;
        int taille_liste_bezier3 = taille_liste(liste);
        //afficher_liste_points(&liste);
        liste_bezier3 = simplification_douglas_peucker_bezier3(&tableau, 0, taille_liste_bezier3, d);
        //printf("Contour simplifié n°%d : \n\n", nb_contours);
        //afficher_liste_points(&liste_bezier3);
        nb_courbes = ecrire_bezier3(&liste_bezier3,f,I);
        somme_courbes+=nb_courbes;
        
        
    }
    

    // rewind(f);
    //printf("%d\n", nb_contours);
    somme_courbes-=nb_contours;
    printf("\n\n%d courbes\n",somme_courbes);
    fprintf(f,"fill\n");
    fprintf(f,"showpage");
    fclose(f);
    

    
    return 0;
}