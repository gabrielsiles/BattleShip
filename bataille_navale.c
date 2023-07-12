
/**
 * @file bataille_navale.c
 * @author Gabriel Siles
 * @brief Ce fichier contient les définitions des fonctions pour gérer le jeu de bataille navale.
 *
 * Il inclut des fonctions pour initialiser le générateur de nombres aléatoires, créer le plateau de jeu et la grille de jeu,
 * créer et placer les navires, vérifier si une position est valide, afficher le plateau et la grille de jeu,
 * gérer les coups du joueur, et mettre à jour la grille de jeu après chaque coup.
 */
#include "bataille_navale.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "commun.h"
#include "statistiques.h"


char* noms_navires[] = {"", "Porte-avions", "Croiseur", "Contre-torpilleur 1", "Contre-torpilleur 2", "Torpilleur"};
int tailles_navires[] = {0, 5, 4, 3, 3, 2};

/**
 * Initialise le générateur de nombres aléatoires.
 *
 * @param max La valeur maximale que peut prendre le nombre aléatoire.
 */
void init_nb_aleatoire() {
  srandom(time(NULL));
}

/**
 * Retourne un nombre aléatoire entre 0 et max (exclusivement).
 *
 * @param max La valeur maximale que peut prendre le nombre aléatoire.
 * @return Un nombre aléatoire entre 0 et max (exclusivement).
 */
int nb_aleatoire(int max) {
   return (random()%max);
}


/**
 * C'est la représentation interne du jeu dans le programme.
 * Il est utilisé pour suivre l'emplacement des navires et
 * pour déterminer si une case a été touchée ou non.
 * Chaque case du plateau peut être soit vide ('.'),
 * soit contenir une partie d'un navire ('x').
 *
 * @param taille_plateau La taille du plateau de jeu.
 * @return Un pointeur vers le plateau de jeu créé.
 */
int** creer_plateau(int taille_plateau) {
   int** plateau = malloc(taille_plateau * sizeof(int*));
   for (int i = 0; i < taille_plateau; i++) {
       plateau[i] = malloc(taille_plateau * sizeof(int));
       for (int j = 0; j < taille_plateau; j++) {
           plateau[i][j] = 0;  // Initialiser toutes les cases à 0
       }
   }
   return plateau;
}


/**
 * C'est la représentation du jeu qui est affichée à l'utilisateur.
 * La grille est un tableau 2D de caractères, où chaque case est initialement définie comme '.'.
 * Chaque case de la grille peut être soit non jouée ('.'),
 * soit touchée sans navire ('o'), soit touchée avec un navire ('x').
 *
 * @param taille_plateau La taille de la grille de jeu.
 * @return Un pointeur vers la grille de jeu créée.
 */
char** creer_grille(int taille_plateau) {
   char** grille = malloc(taille_plateau * sizeof(char*));
   for (int i = 0; i < taille_plateau; i++) {
       grille[i] = malloc(taille_plateau * sizeof(char));
       for (int j = 0; j < taille_plateau; j++) {
           grille[i][j] = '.';  // Initialiser toutes les cases à '.'
       }
   }
   return grille;
}
//allo
/**
 * Crée un nouveau navire avec une taille et une position aléatoires.
 *
 * @param taille La taille du navire à créer.
 * @param taille_plateau La taille du plateau de jeu.
 * @return Le navire créé.
 */
Navire creer_navire(int taille, int taille_plateau) {
   Navire nav;
   nav.taille = taille;
   nav.sens = nb_aleatoire(4);  // Générer une direction aléatoire
   nav.premiere_case.x = nb_aleatoire(taille_plateau);
   nav.premiere_case.y = nb_aleatoire(taille_plateau);
   return nav;
}

/**
 * Détermine si un navire est entièrement sur le plateau de jeu.
 *
 * @param taille_plateau La taille du plateau de jeu.
 * @param nav Le navire à vérifier.
 * @return 1 si le navire est entièrement sur le plateau de jeu, 0 sinon.
 */
int est_position_libre(int **plateau, Navire *nav) {
   for (int i = 0; i < nav->taille; i++) {
       int x, y;
       obtenir_case(&x, &y, nav, i);
       if (plateau[x][y] != 0) {
           return 0;
       }
   }
   return 1;
}

/**
 * Génère une nouvelle position et direction pour le navire jusqu'à ce qu'un placement valide soit trouvé.
 *
 * @param plateau Le plateau de jeu.
 * @param taille_plateau La taille du plateau de jeu.
 * @param nav Le navire à placer.
 */
void generer_position_navire(int **plateau, int taille_plateau, Navire *nav) {
   int valide;
   do {
       nav->sens = nb_aleatoire(4);
       switch (nav->sens) {
           case 0:  // Haut
           case 2:  // Bas
               nav->premiere_case.x = nb_aleatoire(taille_plateau - nav->taille + 1);
               nav->premiere_case.y = nb_aleatoire(taille_plateau);
               break;
           case 1:  // Droite
           case 3:  // Gauche
               nav->premiere_case.x = nb_aleatoire(taille_plateau);
               nav->premiere_case.y = nb_aleatoire(taille_plateau - nav->taille + 1);
               break;
       }
       //  Genere une nouvelle position et direction pour le bateau
       valide = est_valide(plateau, taille_plateau, nav) && est_position_libre(plateau, nav);
   } while (!valide);
}


/**
 * Place un navire sur le plateau de jeu.
 *
 * @param plateau Le plateau de jeu.
 * @param nav Le navire à placer.
 */
void placer_navire(int **plateau, Navire *nav, int index) {
   for (int i = 0; i < nav->taille; i++) {
       switch (nav->sens) {
           case 0:  // Haut
               plateau[nav->premiere_case.x - i][nav->premiere_case.y] = index ; break;
           case 1:  // Droite
               plateau[nav->premiere_case.x][nav->premiere_case.y + i] = index ; break;
           case 2:  // Bas
               plateau[nav->premiere_case.x + i][nav->premiere_case.y] = index ; break;
           case 3:  // Gauche
               plateau[nav->premiere_case.x][nav->premiere_case.y - i] = index ; break;
       }
   }
}


/**
    Cette fonction vérifie si un point (x, y) est à l'intérieur des limites d'un plateau de jeu de taille taille_plateau.
    Elle retourne vrai si le point est dans les limites et faux sinon.
    @param x La coordonnée x du point.
    @param y La coordonnée y du point.
    @param taille_plateau La taille du plateau de jeu.
**/
int est_dans_limites(int x, int y, int taille_plateau) {
   return x >= 0 && x < taille_plateau && y >= 0 && y < taille_plateau;
}


/**
  Elle vérifie si la case spécifiée par les paramètres x et y est occupée ou non,
  en comparant le contenu de cette case avec la valeur 1.
  Si le contenu de la case est égal à 1, alors elle renvoie true, sinon elle renvoie false.
    * @param plateau Le plateau de jeu.
    * @param x La coordonnée x de la case.
    * @param y La coordonnée y de la case.
    * @return Vrai si la case est occupée, faux sinon.
**/
int est_occupee(int **plateau, int x, int y) {
   return plateau[x][y] == 1;
}

/**
 * Cette fonction permet de trouver les coordonnées d'une case à partir des coordonnées du navire
 * et de la direction dans laquelle il se dirige. Elle prend en paramètre un pointeur vers un entier
 * x et un entier y, ainsi qu'un pointeur vers un objet Navire et un entier i.
 * En fonction de la direction du navire (0 pour haut, 1 pour droite, 2 pour bas et 3 pour gauche),
 * elle modifie les valeurs des entiers x et y en conséquence.
 * @param x Un pointeur vers un entier qui contiendra la coordonnée x de la case.
 * @param y Un pointeur vers un entier qui contiendra la coordonnée y de la case.
 * @param nav Un pointeur vers un objet Navire.
 * @param i Un entier qui représente le décalage par rapport à la première case du navire.
**/
void obtenir_case(int *x, int *y, Navire *nav, int i) {
   switch (nav->sens) {
       case 0:  // Haut
           *x = nav->premiere_case.x - i;
           *y = nav->premiere_case.y;
           break;
       case 1:  // Droite
           *x = nav->premiere_case.x;
           *y = nav->premiere_case.y + i;
           break;
       case 2:  // Bas
           *x = nav->premiere_case.x + i;
           *y = nav->premiere_case.y;
           break;
       case 3:  // Gauche
           *x = nav->premiere_case.x;
           *y = nav->premiere_case.y - i;
           break;
   }
}

/**
 * Vérifie si un navire peut être placé sur le plateau de jeu.
 *
 * @param plateau Le plateau de jeu.
 * @param taille_plateau La taille du plateau de jeu.
 * @param nav Le navire à placer.
 * @return 1 si le navire peut être placé, 0 sinon.
 */
int est_valide(int **plateau, int taille_plateau, Navire *nav) {
   for (int i = 0; i < nav->taille; i++) {
       int x, y;
       obtenir_case(&x, &y, nav, i);
       if (!est_dans_limites(x, y, taille_plateau) || est_occupee(plateau, x, y)) {
           return 0;
       }
   }
   return 1;
}




void initialisation_plateau(int **plateau, int taille_plateau) {
   // Créer les navires
   Navire porte_avions = creer_navire(5, taille_plateau);
   Navire croiseur = creer_navire(4, taille_plateau);
   Navire contre_torpilleur1 = creer_navire(3, taille_plateau);
   Navire contre_torpilleur2 = creer_navire(3, taille_plateau);
   Navire torpilleur = creer_navire(2, taille_plateau);

   // Placer les navires sur le plateau
   Navire navires[] = {porte_avions, croiseur, contre_torpilleur1, contre_torpilleur2, torpilleur};
   for (int i = 0; i < 5; i++) {
       generer_position_navire(plateau, taille_plateau, &navires[i]);
       placer_navire(plateau, &navires[i],i+1);
   }
}
/**
 * Affiche le plateau de jeu.
 *
 * @param plateau Le plateau de jeu.
 * @param taille_plateau La taille du plateau de jeu.
 */
/**
 * Affiche le plateau de jeu.
 *
 * @param plateau Le plateau de jeu.
 * @param taille_plateau La taille du plateau de jeu.
 */
void affichage_plateau(int **plateau, int taille_plateau) {
   for (int i = 0; i < taille_plateau; i++) {
       for (int j = 0; j < taille_plateau; j++) {
           printf("%d ", *(*(plateau + i) + j));
       }
       printf("\n");
   }
}

/**
 * Affiche la grille de jeu.
 *
 * @param grille La grille de jeu à afficher.
 * @param taille_plateau La taille de la grille de jeu.
 */
void affichage_grille(char **grille, int taille_plateau) {
   for (int i = 0; i < taille_plateau; i++) {
       for (int j = 0; j < taille_plateau; j++) {
           printf("%c ", grille[i][j]);
       }
       printf("\n");
   }
}

/**
 * Met à jour la grille de jeu après chaque coup.
 *
 * @param grille La grille de jeu à mettre à jour.
 * @param plateau Le plateau de jeu.
 * @param x La coordonnée x du coup.
 * @param y La coordonnée y du coup.
 * @param taille_plateau La taille de la grille de jeu.
 */
void mise_a_jour_grille(char **grille, int **plateau, int x, int y, int taille_plateau) {
   if (plateau[x][y] > 0) {
       grille[x][y] = 'x';  // Un navire a été touché
   } else {
       grille[x][y] = 'o';  // Aucun navire n'a été touché
   }
   // Afficher la grille
   affichage_grille(grille, taille_plateau);
}

/**
 * Demande au joueur de choisir une position sur la grille.
 *
 * @param taille_plateau La taille de la grille de jeu.
 * @return La position choisie par le joueur.
 */
int demander_position(int taille_plateau, char coordonnee) {
    char buffer[256];
    char *end;
    long position = -1;

    do {
        printf("Entrez une position pour %c: ", coordonnee);
        fgets(buffer, sizeof(buffer), stdin);
        position = strtol(buffer, &end, 10);

        if (end == buffer || position < 0 || position >= taille_plateau) {
            printf("Position invalide. Veuillez entrer une position entre 0 et %d.\n", taille_plateau-1);
        }
    } while (end == buffer || position < 0 || position >= taille_plateau);

    return position;
}



/**
 * Stocke la position choisie par le joueur.
 *
 * @param prop Le tableau des propositions du joueur.
 * @param x La coordonnée x de la position.
 * @param y La coordonnée y de la position.
 */
void stocker_position(int **prop, int x, int y) {
   prop[0][0] = x;
   prop[0][1] = y;
}


/**
 * Vérifie si le joueur a déjà joué à la position choisie.
 *
 * @param prop Le tableau des propositions du joueur.
 * @param x La coordonnée x de la position.
 * @param y La coordonnée y de la position.
 */
void verifier_deja_joue(char **grille, int x, int y) {
   if (grille[x][y] != '.') {
       printf("Déjà joué.\n");
       incrementer_total_deja_joue(stats);
   }
}



/**
 * Affiche le coup joué par le joueur.
 *
 * @param nb_joue Le nombre de coups joués.
 * @param x La coordonnée x du coup.
 * @param y La coordonnée y du coup.
 */
void afficher_coup(int *nb_joue, int x, int y) {
   (*nb_joue)++;
   printf("Coup %d : (%d, %d)\n", *nb_joue, x, y);
}

/**
 * Vérifie si le coup du joueur a touché un navire.
 *
 * @param plateau Le plateau de jeu.
 * @param prop Le tableau des propositions du joueur.
 * @param nb_touche Le nombre de coups qui ont touché un navire.
 * @param nb_touche_nav Le tableau du nombre de coups qui ont touché chaque navire.
 * @param x La coordonnée x du coup.
 * @param y La coordonnée y du coup.
 */
char* verifier_toucher(int **plateau, int **prop, int *nb_touche, int *nb_touche_nav, int x, int y) {
    if (plateau[x][y] > 0) {
        printf("Touché !\n");
        prop[x][y] = 1;
        (*nb_touche)++;
        incrementer_total_touche(stats);
        nb_touche_nav[plateau[x][y]-1]++;
        if (nb_touche_nav[plateau[x][y]-1] == tailles_navires[plateau[x][y]]) {
            printf("Navire %s de taille %d coulé !\n", noms_navires[plateau[x][y]], tailles_navires[plateau[x][y]]);
            set_dernier_navire_coule(stats, noms_navires[plateau[x][y]]);
            return noms_navires[plateau[x][y]];
        }
    } else {
        printf("À l'eau.\n");
        prop[x][y] = 0;
        incrementer_total_a_l_eau(stats);
    }
    return NULL;  // Return NULL si aucun bateau est toucher
}


/**
 * Gère la proposition de coup du joueur.
 *
 * @param plateau Le plateau de jeu.
 * @param prop Le tableau des propositions du joueur.
 * @param nb_touche Le nombre de coups qui ont touché un navire.
 * @param nb_joue Le nombre de coups joués.
 * @param nb_touche_nav Le tableau du nombre de coups qui ont touché chaque navire.
 * @param taille_plateau La taille de la grille de jeu.
 */
void proposition_joueur(int **plateau, char **grille, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau) {
    int x = demander_position(taille_plateau, 'X');
    int y = demander_position(taille_plateau, 'Y');

    stocker_position(prop, x, y);
    verifier_deja_joue(grille, x, y);

    afficher_coup(nb_joue, x, y);
    if (grille[x][y] == '.') {
        char* nom_navire = verifier_toucher(plateau, prop, nb_touche, nb_touche_nav, x, y);
        mise_a_jour_grille(grille, plateau, x, y, taille_plateau);

        // Si le bateau a couler et c'est le premier bateau a etre toucher set le nombre de lettres uniques
        if (nom_navire != NULL && stats->lettres_premier_navire == 0) {
            set_lettres_premier_navire(stats, nom_navire);
        }
    }
}














