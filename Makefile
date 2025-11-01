#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = gcc

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES =  test_calc_bezier3 test_bezier3


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules


contours.o : contours.c contours.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contours"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

image.o : image.c image.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

geom2.o : geom2.c geom2.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

listes.o : listes.c listes.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module listes"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

approx_bezier3.o : approx_bezier3.c approx_bezier3.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module approx_bezier3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_contours.o : test_contours.c contours.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contours"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_calc_dist_PS.o : test_calc_dist_PS.c geom2.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_calc_dist_PS"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_calc_bezier3.o : test_calc_bezier3.c geom2.h approx_bezier3.h listes.h contours.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_bezier3.o : test_bezier3.c approx_bezier3.h contours.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de creation des executables

test_contours : test_contours.o contours.o geom2.o image.o contours.o listes.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_calc_dist_PS : test_calc_dist_PS.o geom2.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_calc_bezier3 : test_calc_bezier3.o geom2.o image.o contours.o listes.o approx_bezier3.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_bezier3 : test_bezier3.o geom2.o image.o contours.o listes.o approx_bezier3.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
