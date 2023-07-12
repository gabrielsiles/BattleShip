#ifndef STATISTIQUES_H
#define STATISTIQUES_H


/* STRUCTURES DE DONNEES*/
typedef struct {
   int total_coups;
   int lettres_premier_navire;
   int total_a_l_eau;
   int total_deja_joue;
   int total_touche;
   char* dernier_navire_coule;
} Statistiques;

/* PROTOTYPES */
Statistiques* creer_statistiques();
void liberer_statistiques(Statistiques* stats);
void ecrire_statistiques(Statistiques* stats, char* nom_fichier);
void incrementer_total_coups(Statistiques* stats);
void incrementer_total_a_l_eau(Statistiques* stats);
void incrementer_total_deja_joue(Statistiques* stats);
void incrementer_total_touche(Statistiques* stats) ;
void set_dernier_navire_coule(Statistiques* stats, char* nom_navire) ;
void set_lettres_premier_navire(Statistiques* stats, char* nom_navire);

// variable globale
extern Statistiques* stats; 
#endif /* STATISTIQUES_H */
