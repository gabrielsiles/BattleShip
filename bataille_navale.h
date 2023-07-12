#ifndef BATAILLE_NAVALE_H
#define BATAILLE_NAVALE_H
#include "statistiques.h"


/* STRUCTURES DE DONNEES*/
typedef struct une_case {
   int x; /* position de la case en x*/
   int y; /* position de la case en y*/
} Case;

typedef struct navire {
   int sens; /* 0 haut 1 droite 2 bas 3 gauche */
   Case premiere_case;
   int taille;
} Navire;




/* PROTOTYPES */
int nb_aleatoire(int max);
void init_nb_aleatoire();
int** creer_plateau(int taille_plateau);
char** creer_grille(int taille_plateau);

Navire creer_navire(int taille, int taille_plateau);
void generer_position_navire(int **plateau, int taille_plateau, struct navire  *nav);
void placer_navire(int **plateau, Navire *nav,int index);

int est_valide(int **plateau, int taille_plateau, struct navire  *nav);
int est_dans_limites(int x, int y, int taille_plateau);
int est_occupee(int **plateau, int x, int y);
void obtenir_case(int *x, int *y, Navire *nav, int i);
void initialisation_plateau(int **plateau, int taille_plateau);

//void initialisation_plateau(int **plateau, int taille_plateau);
void proposition_joueur(int **plateau, char **grille, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau);
void affichage_plateau(int **plateau, int taille_plateau);
void affichage_grille(char **grille, int taille_plateau);

#endif /* BATAILLE_NAVALE_H */
