# 🖼️ Vector is à l’heure

## 📖 Description

Projet réalisé en **C** avec un script d’exécution en **shell (sh)**.  
L’objectif : créer un **vectoriseur d’images PBM noir et blanc**, capable de convertir une image bitmap (PBM) en tracés vectoriels (EPS) à l’aide d’**approximations de Bézier** (ordre 2 ou 3) ou de simplifications de segments.

Le script d’exécution propose une **interface interactive en ligne de commande**, permettant de :
- Sélectionner un fichier `.pbm`
- Choisir le mode de vectorisation (`bezier2`, `bezier3` ou `simplification segment`)
- Choisir un seuil d
- Visualiser le résultat automatiquement dans un visualiseur EPS (`gv`)

---

## ✨ Fonctionnalités principales

- 🧩 Lecture et analyse d’images PBM noir et blanc  
- 📈 Conversion en tracés vectoriels Bézier (2e ou 3e ordre)  
- 🧮 Paramétrage du seuil `d` pour la précision de la simplification  
- 🗂️ Gestion automatique des fichiers de sortie dans `dossier_eps/`  
- 💬 Interface shell simple et interactive  
- 🎨 Visualisation directe avec `gv`  

---

## ⚙️ Installation

### 🔧 Dépendances

Assure-toi d’avoir les outils suivants installés sur ton système :

| Outil | Rôle | Commande d’installation |
|--------|------|--------------------------|
| `gcc` | Compilation du code C | `sudo apt install build-essential` |
| `make` | Automatisation de la compilation | *(inclus avec build-essential)* |
| `gv` | Visualiseur d’images EPS | `sudo apt install gv` |
| `bash` / `sh` | Exécution du script | *(installé par défaut sur Linux/macOS)* |

---

## 🚀 Utilisation

### 1️⃣ Compilation
Le script `exec.sh` s’en charge, mais tu peux aussi compiler manuellement :

make

(Pour utiliser exec.sh faites la commande, chmod 700 exec.sh, cela vous donnera les droits d'executions)

2️⃣ Lancement du programme

Exécute le script interactif :
./exec.sh

###########################################
#                                         #
#  Bienvenue dans le vector is a l'heure  #
#                                         #
#        Donnez moi un fichier pbm        #
#                                         #
###########################################


3️⃣ Sélection du fichier PBM

Place tes fichiers .pbm dans dossier_pbm/

Entre le nom du fichier (ex: chat.pbm)

4️⃣ Choix du mode de vectorisation

Saisis :

bezier2 → courbes de Bézier d’ordre 2

bezier3 → courbes de Bézier d’ordre 3

simplification segment → simplification linéaire

Le programme génère un fichier .eps dans dossier_eps/ et l’ouvre automatiquement avec gv

---

###Version test performance
Vous pouvez consulter les performances selon les fichiers grace a l'executable, test.sh, il faut faire :
chmod 700 test.sh
./test.sh

---

🧑‍💻 Auteur

Projet développé en C par Sabon Marcus et Stien Emilio

Version originale : 2023

Mise à jour et publication GitHub : 2025






