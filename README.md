# TP2 : Bataille navale - inf3135-ete2023-tp2

# Auteur
Gabriel Siles (SILG09109901)

## Description

Ce programme est une implémentation du jeu de la Bataille Navale en C. Il permet à un joueur de jouer contre l'ordinateur.

## Compilation

Pour compiler le programme, utilisez la commande `make` dans le répertoire du projet :

`make`

Cela va créer un exécutable nommé `bataille_navale`.

## Exécution

Pour exécuter le programme, utilisez la commande suivante :

`./bataille_navale` ou `make run`


## Options

Le programme accepte une option `-S` suivie du nom d'un fichier. Si cette option est utilisée, le programme enregistrera les statistiques de la partie dans le fichier spécifié. Par exemple :

`./bataille_navale -S stats.txt` ou `make stats`


## Fonctionnement du jeu

Au début du jeu, le joueur doit entrer la taille du plateau de jeu. Ensuite, le jeu se déroule en tours. À chaque tour, le joueur doit entrer les coordonnées d'une case à attaquer. Le jeu continue jusqu'à ce que tous les navires soient coulés.
L'utilisateur a l'option a tout moment durant la partie de sauvegarder ou charger la carte.

## Statistiques

Le programme enregistre plusieurs statistiques pendant le jeu, notamment le nombre total de coups, le nombre de coups qui ont touché un navire, le nombre de coups qui ont été joués sur une case déjà jouée, et le nombre de coups qui ont été joués dans l'eau. Si l'option `-S` est utilisée, ces statistiques seront enregistrées dans le fichier spécifié à la fin du jeu.

## Tests
Pour les tests CUNIT et Bats on peux faire la commande `make test` sinon `./test_cunit`.

## Nettoyages
Pour enlever les fichiers pas importants créés après la compiliation. 
Il faut faire la commande `make clean`

## Dépendances
* CUnit : version 2.1-3
* BATS

## État du projet


* [x] L'utilisateur `dogny_g` a accès au projet en mode *Developer*.
* [x] Les correcteurs ont accès au projet en mode *Developer* (`id`à venir).
* [x] Le dépôt GitLab est un *fork* de [ce dépôt](https://gitlab.info.uqam.ca/inf3135-sdo/motdedyck).
* [x] Le dépôt GitLab est privé.
* [x] Le dépôt contient au moins un fichier `.gitignore`.
* [x] Le fichier `Makefile` permet de compiler le projet lorsqu'on entre `make`. Il supporte les cibles `html`, `test` et `clean`.
* [x] Le nombre de tests qui réussissent/échouent avec la `make test` est indiqué dans la section "Tests".
* [x] Les sections incomplètes de ce fichier (`README.md`) ont été complétées.
* [x] L'en-tête du fichier est documentée.
* [x] L'en-tête des déclarations des fonctions est documentée (*docstring*).
* [x] Le programme ne contient pas de valeurs magiques.

























