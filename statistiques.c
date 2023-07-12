/**
 * @file statistiques.c
 * @author Gabriel Siles
 * @brief Ce fichier contient les définitions des fonctions pour gérer les statistiques du jeu de bataille navale.
 *
 * Il inclut des fonctions pour créer une nouvelle instance de statistiques, libérer la mémoire allouée pour les statistiques,
 * écrire les statistiques dans un fichier, incrémenter les différents types de coups dans les statistiques,
 * et définir le nom du dernier navire coulé et le nombre de lettres uniques dans le nom du premier navire touché.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "statistiques.h"
#include "commun.h"

Statistiques* stats = NULL;

/**
 * Crée une nouvelle instance de Statistiques et initialise ses champs.
 * @return Un pointeur vers la nouvelle instance de Statistiques.
 */
Statistiques* creer_statistiques() {
   Statistiques* stats = malloc(sizeof(Statistiques));
   if (stats == NULL) {
       printf("Erreur d'allocation de mémoire pour les statistiques.\n");
       return NULL;
   }
   stats->total_coups = 0;
   stats->lettres_premier_navire = 0;
   stats->total_a_l_eau = 0;
   stats->total_deja_joue = 0;
   stats->total_touche = 0;
   stats->dernier_navire_coule = NULL;
   return stats;
}

/**
 * Écrit les statistiques dans un fichier.
 * @param stats Un pointeur vers l'instance de Statistiques à écrire.
 * @param nom_fichier Le nom du fichier dans lequel écrire les statistiques.
 */
void liberer_statistiques(Statistiques* stats) {
    if (stats->dernier_navire_coule != NULL) {
       free(stats->dernier_navire_coule);
   }
   free(stats);
}

/**
 * Écrit les statistiques dans un fichier.
 * @param stats Un pointeur vers l'instance de Statistiques à écrire.
 * @param nom_fichier Le nom du fichier dans lequel écrire les statistiques.
 */
void ecrire_statistiques(Statistiques* stats, char* nom_fichier) {
   FILE* fichier = fopen(nom_fichier, "w");
   if (fichier == NULL) {
       printf("Erreur d'ouverture du fichier %s\n", nom_fichier);
       return;
   }
   fprintf(fichier, "Total coups: %d\n", stats->total_coups);
   fprintf(fichier, "Nombre de lettres sans doublon du premier navire: %d\n", stats->lettres_premier_navire);
   fprintf(fichier, "Total à l'eau: %d\n", stats->total_a_l_eau);
   fprintf(fichier, "Total déjà joué: %d\n", stats->total_deja_joue);
   fprintf(fichier, "Total touché: %d\n", stats->total_touche);
   if (stats->dernier_navire_coule != NULL) {
       fprintf(fichier, "Dernier navire coulé: %s\n", stats->dernier_navire_coule);
   }
   fclose(fichier);
}
/**
 * Incrémente le nombre total de coups dans les statistiques.
 * @param stats Un pointeur vers l'instance de Statistiques à mettre à jour.
 */
void incrementer_total_coups(Statistiques* stats) {
   stats->total_coups++;
}

/**
 * Incrémente le nombre total de coups à l'eau dans les statistiques.
 * @param stats Un pointeur vers l'instance de Statistiques à mettre à jour.
 */
void incrementer_total_a_l_eau(Statistiques* stats) {
   stats->total_a_l_eau++;
}

/**
 * Incrémente le nombre total de coups déjà joués dans les statistiques.
 * @param stats Un pointeur vers l'instance de Statistiques à mettre à jour.
 */
void incrementer_total_deja_joue(Statistiques* stats) {
   stats->total_deja_joue++;
}

/**
 * Incrémente le nombre total de coups touchés dans les statistiques.
 * @param stats Un pointeur vers l'instance de Statistiques à mettre à jour.
 */
void incrementer_total_touche(Statistiques* stats) {
   stats->total_touche++;
}


/**
 * Définit le nom du dernier navire coulé dans les statistiques.
 * @param stats Un pointeur vers l'instance de Statistiques à mettre à jour.
 * @param nom_navire Le nom du dernier navire coulé.
 */
void set_dernier_navire_coule(Statistiques* stats, char* nom_navire) {
   if (stats->dernier_navire_coule != NULL) {
       free(stats->dernier_navire_coule);
   }
   stats->dernier_navire_coule = strdup(nom_navire);
}

/**
 * Définit le nombre de lettres uniques dans le nom du premier navire touché dans les statistiques.
 * @param stats Un pointeur vers l'instance de Statistiques à mettre à jour.
 * @param nom_navire Le nom du premier navire touché.
 */
void set_lettres_premier_navire(Statistiques* stats, char* nom_navire) {
   if (stats->lettres_premier_navire == 0) {
       // Le premier navire touché
       bool letters[26] = {false};
       for (int i = 0; nom_navire[i] != '\0'; i++) {
           if (nom_navire[i] >= 'a' && nom_navire[i] <= 'z') {
               letters[nom_navire[i] - 'a'] = true;
           } else if (nom_navire[i] >= 'A' && nom_navire[i] <= 'Z') {
               letters[nom_navire[i] - 'A'] = true;
           }
       }
       int lettres_uniques = 0;
       for (int i = 0; i < 26; i++) {
           if (letters[i]) {
               lettres_uniques++;
           }
       }
       stats->lettres_premier_navire = lettres_uniques;
   }

}

