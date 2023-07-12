/**
* @file sauvegarder_partie.c
* @author Gabriel Siles
*
* Ce fichier sert a sauvegarder ou charger une partie de bataille navale en cours,
* a tout moment durant la partie. La partie est enregistree dans un fichier .txt.
*/

#include <stdio.h>
#include <string.h>


/**
* Sauvegarder le statut de la partie, c'est-a-dire l'etat de la matrice,
* les statistiques, etc. dans un fichier .txt.(ecris les valeurs)
*/
void sauvegarder_partie(int** plateau, char** grille, int** prop, int nb_touche, int nb_joue, int* nb_touche_nav, int taille_plateau) {
   char nom_fichier[50];
   printf("Entrez le nom du fichier de sauvegarde : ");
   scanf("%s", nom_fichier);

   FILE* fichier = fopen(nom_fichier, "w");
   if (fichier == NULL) {
       printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
       return;
   }

   // Écrire les données dans le fichier
   fprintf(fichier, "%d\n", nb_touche);
   fprintf(fichier, "%d\n", nb_joue);
   for (int i = 0; i < 5; i++) {
       fprintf(fichier, "%d ", nb_touche_nav[i]);
   }
   fprintf(fichier, "\n");
   fprintf(fichier, "%d\n", taille_plateau);
   for (int i = 0; i < taille_plateau; i++) {
       for (int j = 0; j < taille_plateau; j++) {
           fprintf(fichier, "%d ", plateau[i][j]);
       }
       fprintf(fichier, "\n");
   }
   for (int i = 0; i < taille_plateau; i++) {
       for (int j = 0; j < taille_plateau; j++) {
           fprintf(fichier, "%c ", grille[i][j]);
       }
       fprintf(fichier, "\n");
   }
   for (int i = 0; i < taille_plateau; i++) {
       for (int j = 0; j < taille_plateau; j++) {
           fprintf(fichier, "%d ", prop[i][j]);
       }
       fprintf(fichier, "\n");
   }

   fclose(fichier);

   printf("Partie sauvegardée avec succès dans le fichier %s.\n", nom_fichier);
}

/**
* Charge dand le terminal la partie la ou elle a etait sauvegardee.
* Lis les valeurs du fichier text.
*/

void charger_partie(int** plateau, char** grille, int** prop, int* nb_touche, int* nb_joue, int* nb_touche_nav, int* taille_plateau) {
   char nom_fichier[50];
   printf("Entrez le nom du fichier de chargement : ");
   scanf("%s", nom_fichier);

   FILE* fichier = fopen(nom_fichier, "r");
   if (fichier == NULL) {
       printf("Erreur lors de l'ouverture du fichier de chargement.\n");
       return;
   }

   fscanf(fichier, "%d", nb_touche);
   fscanf(fichier, "%d", nb_joue);
   for (int i = 0; i < 5; i++) {
       fscanf(fichier, "%d", &nb_touche_nav[i]);
   }
   fscanf(fichier, "%d", taille_plateau);

   for (int i = 0; i < *taille_plateau; i++) {
       for (int j = 0; j < *taille_plateau; j++) {
           fscanf(fichier, "%d", &plateau[i][j]);
       }
   }

   for (int i = 0; i < *taille_plateau; i++) {
       for (int j = 0; j < *taille_plateau; j++) {
           fscanf(fichier, " %c", &grille[i][j]);
       }
   }

   for (int i = 0; i < *taille_plateau; i++) {
       for (int j = 0; j < *taille_plateau; j++) {
           fscanf(fichier, "%d", &prop[i][j]);
       }
   }

   fclose(fichier);

   printf("Partie chargée avec succès à partir du fichier %s.\n", nom_fichier);
}
