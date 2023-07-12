/**
 * @file main.c
 * @author Gabriel Siles (SILG09109901)
 * @brief Fichier principal pour le jeu de la bataille navale.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bataille_navale.h"
#include "statistiques.h"
#include "sauvegarder_partie.h"
#include "commun.h"



int main(int argc, char *argv[]) {
   // Déclaration de toutes les variables au début de la fonction
   //int taille_plateau;
   int **plateau;
   int **prop;
   char **grille;
   int nb_touche = 0;
   int nb_joue = 0;
   int *nb_touche_nav;
   int total_cases_navires;

   // Créez une instance des statistiques
   stats = creer_statistiques();

   // Initialise le générateur de nombres aléatoires avec l'heure actuelle
   init_nb_aleatoire();

    char buffer[256];
    printf("Veuillez entrer la taille de la carte (minimum 6, maximum 100) : ");
    fgets(buffer, sizeof(buffer), stdin);

    char *end;
    int taille_plateau = strtol(buffer, &end, 10);

    while (end == buffer || taille_plateau < 6 || taille_plateau > 100) {
        printf("Taille de carte invalide. Veuillez entrer une taille entre 6 et 100.\n");
        printf("Veuillez entrer la taille de la carte (minimum 6, maximum 100) : ");
        fgets(buffer, sizeof(buffer), stdin);
        taille_plateau = strtol(buffer, &end, 10); //si le user rentre une lettre
    }

   // Créer le plateau de jeu
   plateau = creer_plateau(taille_plateau);
   prop = creer_plateau(taille_plateau);  // Supposons que prop est un autre plateau
   grille = creer_grille(taille_plateau);  // Créer la grille de jeu
   nb_touche_nav = malloc(5 * sizeof(int));  // Supposons qu'il y a 5 navires

   // Initialiser le plateau avec les navires
   initialisation_plateau(plateau, taille_plateau);

   // Calculer le nombre total de cases occupées par les navires
   total_cases_navires = 5 + 4 + 3 + 3 + 2;  // Supposons que vous avez un porte-avions (5 cases), un croiseur (4 cases), deux contre-torpilleurs (3 cases chacun) et un torpilleur (2 cases)

   // Boucle principale du jeu
   while (nb_touche < total_cases_navires) {
       // Afficher le menu avec les options de jeu
       printf("Menu :\n");
       printf("1. Jouer un coup\n");
       printf("2. Sauvegarder la partie\n");
       printf("3. Charger une partie\n");
       printf("Choisissez une option : ");

       int choix;
       scanf("%d", &choix);

       switch (choix) {
           case 1:
               // Le joueur choisit de jouer un coup
               proposition_joueur(plateau, grille, prop, &nb_touche, &nb_joue, nb_touche_nav, taille_plateau);
               //affichage_grille(grille, taille_plateau);
               incrementer_total_coups(stats);
               break;
           case 2:
               // Le joueur choisit de sauvegarder la partie
               sauvegarder_partie(plateau, grille, prop, nb_touche, nb_joue, nb_touche_nav, taille_plateau);

               break;
           case 3:
               // Le joueur choisit de charger une partie
               charger_partie(plateau, grille, prop, &nb_touche, &nb_joue, nb_touche_nav, &taille_plateau);
               affichage_grille(grille, taille_plateau);
               break;
           default:
               printf("Option invalide. Veuillez choisir une option valide.\n");
               break;
       }
       incrementer_total_coups(stats);  // Incrémenter le nombre total de coups à chaque tour de boucle
       //affichage_plateau(plateau, taille_plateau); //POUR DEBUG
   }

   // Afficher le nombre de coups joués lorsque le joueur gagne
   printf("Bravo !! Vous avez gagné en %d coups.\n", nb_joue);

   // Gestion des arguments de la ligne de commande pour l'écriture des statistiques
   if(argc > 1 && strcmp(argv[1], "-S") == 0) {
       if (argc > 2) {
           char *nom_fichier_stats = argv[2];
           /**
            * @brief Écrit les statistiques du jeu dans un fichier.
            */
           ecrire_statistiques(stats, nom_fichier_stats);
       } else {
           printf("Erreur : option -S requiert un nom de fichier\n");
           return 1;
       }
   }

   //Liberer les statistiques
    liberer_statistiques(stats);
    // Liberer la memoire dynamiquement al
    for(int i = 0; i < taille_plateau; i++) {
        free(plateau[i]);
        free(prop[i]);
        free(grille[i]);
    }

    free(plateau);
    free(prop);
    free(grille);
    free(nb_touche_nav);

    plateau = NULL;
    prop = NULL;
    grille = NULL;
    nb_touche_nav = NULL;


    return 0;
}
