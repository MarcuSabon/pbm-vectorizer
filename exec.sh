#!/bin/sh

make
sleep 1
while true; do
    clear
    echo "###########################################"
    echo "#                                         #"
    echo "#  Bienvenue dans le vector is a l'heure  #"
    echo "#                                         #"
    echo "#        Donnez moi un ficher pbm         #"
    echo "#                                         #"
    echo "###########################################"
    echo
    ls dossier_pbm

    echo
    echo "###########################################"
    echo
    # Initialisation de la variable de contrôle pour la boucle
    saisie_invalide=true

    # Boucle pour gérer les erreurs de saisie de l'utilisateur
    while [ "$saisie_invalide" = true ]; do
        read -p "Veuillez saisir le nom du fichier PBM : " fichier_pbm
        echo

        if [ -f "dossier_pbm/$fichier_pbm" ] && [ "${fichier_pbm##*.}" = "pbm" ]; then
            fichier_pbm_sans_extension=$(basename "$fichier_pbm" .pbm)
            saisie_invalide=false
        else
            tput setaf 1 # Texte rouge pour l'erreur
            echo "Le fichier '$fichier_pbm' n'existe pas, ou n'est pas un .pbm. Veuillez recommencer."
            tput sgr0 # Réinitialiser les couleurs
            sleep 1
            for i in $(seq 1 4); do
                tput cuu1
                tput el
            done
        fi
    done

    # Demande à l'utilisateur de saisir la valeur de d
    saisie_invalide=true
    while [ "$saisie_invalide" = true ]; do
        read -p "Veuillez saisir la valeur de d : " d

        if [ "$(echo "$d" | grep -E '^[0-9]+([.][0-9]+)?$')" ]; then
            saisie_invalide=false
        else
            tput setaf 1
            echo "La valeur saisie pour d n'est pas un double valide. Veuillez réessayer."
            tput sgr0
        fi
    done

    echo
    #chef fait fonction while qui boucle sur choisir bezier3 ou bezier2
    while true; do
        read -p "Veuillez choisir 'bezier3', 'bezier2' ou 'simplification segment': " choix_bezier
        case "$choix_bezier" in
            simplification\ segment|ss|simp\ seg)
                break;;
            bezier3|3)
                mkdir -p dossier_eps
                ./test_bezier3 "dossier_pbm/$fichier_pbm_sans_extension.pbm" "dossier_eps/$fichier_pbm_sans_extension.eps" "$d"
                break ;;
            bezier2|2)
                mkdir -p dossier_eps
                ./test_bezier2 "dossier_pbm/$fichier_pbm_sans_extension.pbm" "dossier_eps/$fichier_pbm_sans_extension.eps" "$d"
                break ;;
            *)
                tput setaf 1
                echo "Choix invalide. Veuillez choisir 'bezier3' ou 'bezier2'." 
                tput sgr0
                sleep 2
                for i in $(seq 1 2); do
                    tput cuu1
                    tput el
                done
                ;;
        esac
    done

    gv -presentation "dossier_eps/$fichier_pbm_sans_extension.eps"
    
    for i in $(seq 1 6); do
        tput cuu1
        tput el
    done
    echo
    read -p "Voulez-vous quitter ? (tapez q) : " reponse

    if [ "$reponse" = "q" ]; then
        echo
        echo "Vector is plus l'heure."
        echo
        echo "###########################################"
        break
    fi

    echo "Continuation du programme..."
    echo
    sleep 1
    echo "###########################################"
done
