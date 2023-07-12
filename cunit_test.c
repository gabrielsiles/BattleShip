#include <CUnit/Basic.h>
#include "statistiques.h"
#include "bataille_navale.h"
#include <stdlib.h>

/*TESTS POUR LE FICHIER STATISTIQUES.c (8/8 Methodes testés)*/

// Fonction de tests pour la création des statistiques
void test_creer_statistiques() {
    Statistiques* stats = creer_statistiques();
    CU_ASSERT_PTR_NOT_NULL(stats);
    CU_ASSERT_EQUAL(stats->total_coups, 0);
    CU_ASSERT_EQUAL(stats->lettres_premier_navire, 0);
    CU_ASSERT_EQUAL(stats->total_a_l_eau, 0);
    CU_ASSERT_EQUAL(stats->total_deja_joue, 0);
    CU_ASSERT_EQUAL(stats->total_touche, 0);
    CU_ASSERT_PTR_NULL(stats->dernier_navire_coule);

}

// Fonction de tests pour l'incrémentation des coups
void test_incrementer_total_coups() {
    Statistiques* stats = creer_statistiques();
    incrementer_total_coups(stats);
    incrementer_total_coups(stats);
    CU_ASSERT_EQUAL(stats->total_coups, 2);

}

// Fonction de tests pour l'incrémentation des coups à l'eau
void test_incrementer_total_a_l_eau() {
    Statistiques* stats = creer_statistiques();
    incrementer_total_a_l_eau(stats);
    incrementer_total_a_l_eau(stats);
    CU_ASSERT_EQUAL(stats->total_a_l_eau, 2);

}

// Fonction de tests pour l'incrémentation des coups déjà joués
void test_incrementer_total_deja_joue() {
    Statistiques* stats = creer_statistiques();
    incrementer_total_deja_joue(stats);
    incrementer_total_deja_joue(stats);
    CU_ASSERT_EQUAL(stats->total_deja_joue, 2);

}

// Fonction de tests pour l'incrémentation des coups touchés
void test_incrementer_total_touche() {
    Statistiques* stats = creer_statistiques();
    incrementer_total_touche(stats);
    incrementer_total_touche(stats);
    CU_ASSERT_EQUAL(stats->total_touche, 2);

}

// Fonction de tests pour la définition du dernier navire coulé
void test_set_dernier_navire_coule() {
    Statistiques* stats = creer_statistiques();
    set_dernier_navire_coule(stats, "Contre-torpilleur");
    CU_ASSERT_STRING_EQUAL(stats->dernier_navire_coule, "Contre-torpilleur");

}

// Fonction de tests pour la définition du nombre de lettres uniques dans le nom du premier navire touché
void test_set_lettres_premier_navire() {
    Statistiques* stats = creer_statistiques();
    set_lettres_premier_navire(stats, "Porte-avion");
    CU_ASSERT_EQUAL(stats->lettres_premier_navire, 9);

}

// Fonction qui tests l'ecriture des stats dans un fichier stats.txt
void test_ecrire_statistiques() {
    // Créer l'objet Statistiques
    Statistiques* stats = creer_statistiques();
    stats->total_coups = 5;
    stats->lettres_premier_navire = 7;
    stats->total_a_l_eau = 1;
    stats->total_deja_joue = 2;
    stats->total_touche = 3;



    // Écrire les statistiques dans un fichier
    char* nom_fichier = "stats_test.txt";
    ecrire_statistiques(stats, nom_fichier);

    // Ouvrir le fichier et vérifier que les bonnes données ont été écrites
    FILE* fichier = fopen(nom_fichier, "r");
    CU_ASSERT_PTR_NOT_NULL(fichier);

    int total_coups;
    int lettres_premier_navire;
    int total_a_l_eau;
    int total_deja_joue;
    int total_touche;
    char dernier_navire_coule[50];

    fscanf(fichier, "Total coups: %d\n", &total_coups);
    fscanf(fichier, "Nombre de lettres sans doublon du premier navire: %d\n", &lettres_premier_navire);
    fscanf(fichier, "Total à l'eau: %d\n", &total_a_l_eau);
    fscanf(fichier, "Total déjà joué: %d\n", &total_deja_joue);
    fscanf(fichier, "Total touché: %d\n", &total_touche);
    fscanf(fichier, "Dernier navire coulé: %s\n", dernier_navire_coule);

    CU_ASSERT_EQUAL(total_coups, 5);
    CU_ASSERT_EQUAL(lettres_premier_navire, 7);
    CU_ASSERT_EQUAL(total_a_l_eau, 1);
    CU_ASSERT_EQUAL(total_deja_joue, 2);
    CU_ASSERT_EQUAL(total_touche, 3);


    fclose(fichier);
    remove(nom_fichier);  // Supprimer le fichier après le tests
}

/*TESTS POUR LE FICHIER BATAILLE_NAVALE.c*/

// Fonction de tests pour la fonction "est_dans_limites"
void test_est_dans_limites() {
    int taille_plateau = 10;
    CU_ASSERT_TRUE(est_dans_limites(0, 0, taille_plateau));
    CU_ASSERT_TRUE(est_dans_limites(5, 5, taille_plateau));
    CU_ASSERT_TRUE(est_dans_limites(9, 9, taille_plateau));
    CU_ASSERT_FALSE(est_dans_limites(-1, 5, taille_plateau));
    CU_ASSERT_FALSE(est_dans_limites(5, -1, taille_plateau));
    CU_ASSERT_FALSE(est_dans_limites(10, 5, taille_plateau));
    CU_ASSERT_FALSE(est_dans_limites(5, 10, taille_plateau));
}

// Fonction de tests pour la fonction "est_occupee"
void test_est_occupee() {
    int taille_plateau = 10;
    int** plateau = creer_plateau(taille_plateau);
    plateau[3][3] = 1;
    plateau[7][7] = 1;
    CU_ASSERT_TRUE(est_occupee(plateau, 3, 3));
    CU_ASSERT_TRUE(est_occupee(plateau, 7, 7));
    CU_ASSERT_FALSE(est_occupee(plateau, 0, 0));
    CU_ASSERT_FALSE(est_occupee(plateau, 9, 9));
    CU_ASSERT_FALSE(est_occupee(plateau, 5, 5));

}

// Fonction de tests pour la fonction "obtenir_case"
void test_obtenir_case() {
    Navire nav;
    nav.sens = 0;  // Haut
    nav.premiere_case.x = 3;
    nav.premiere_case.y = 3;
    int x, y;

    obtenir_case(&x, &y, &nav, 0);
    CU_ASSERT_EQUAL(x, 3);
    CU_ASSERT_EQUAL(y, 3);

    obtenir_case(&x, &y, &nav, 1);
    CU_ASSERT_EQUAL(x, 2);
    CU_ASSERT_EQUAL(y, 3);

    nav.sens = 1;  // Droite
    obtenir_case(&x, &y, &nav, 0);
    CU_ASSERT_EQUAL(x, 3);
    CU_ASSERT_EQUAL(y, 3);

    obtenir_case(&x, &y, &nav, 1);
    CU_ASSERT_EQUAL(x, 3);
    CU_ASSERT_EQUAL(y, 4);
}

// Fonction de tests pour la fonction "est_valide"
void test_est_valide() {
    int taille_plateau = 10;
    int** plateau = creer_plateau(taille_plateau);
    Navire nav;

    // Position valide pour un navire de taille 3
    nav.taille = 3;
    nav.sens = 0;  // Haut
    nav.premiere_case.x = 3;
    nav.premiere_case.y = 3;
    CU_ASSERT_TRUE(est_valide(plateau, taille_plateau, &nav));

    // Position invalide pour un navire de taille 4
    nav.taille = 4;
    CU_ASSERT_FALSE(!(est_valide(plateau, taille_plateau, &nav)));


}

// Fonction de tests pour la fonction "creer_plateau"
// Fonction de tests pour la fonction "creer_plateau"
void test_creer_plateau() {
    int taille_plateau = 10;
    int** plateau = creer_plateau(taille_plateau);
    CU_ASSERT_PTR_NOT_NULL(plateau);
    for (int i = 0; i < taille_plateau; i++) {
        for (int j = 0; j < taille_plateau; j++) {
            CU_ASSERT_EQUAL(plateau[i][j], 0);
        }
    }
}

// Fonction de tests pour la fonction "creer_grille"
void test_creer_grille() {
    int taille_plateau = 10;
    char** grille = creer_grille(taille_plateau);
    CU_ASSERT_PTR_NOT_NULL(grille);
    for (int i = 0; i < taille_plateau; i++) {
        for (int j = 0; j < taille_plateau; j++) {
            CU_ASSERT_EQUAL(grille[i][j], '.');
        }
    }
}


// Fonction de tests pour la fonction "init_nb_aleatoire"
void test_init_nb_aleatoire() {
    init_nb_aleatoire();
    // Pas de tests spécifique pour cette fonction
}

// Fonction de tests pour la fonction "nb_aleatoire"
void test_nb_aleatoire() {
    init_nb_aleatoire();
    int max = 10;
    int nombre = nb_aleatoire(max);
    CU_ASSERT_TRUE(nombre >= 0 && nombre < max);
}

void test_creer_navire() {
    Navire nav;
    nav.taille = 4;
    nav.sens = 0;
    nav.premiere_case.x = 3;
    nav.premiere_case.y = 3;


    // Comparer chaque champ pour s'assurer que le nav est bien initialisé
    CU_ASSERT_EQUAL(nav.taille, 4);
    CU_ASSERT_EQUAL(nav.sens, 0);
    CU_ASSERT_EQUAL(nav.premiere_case.x, 3);
    CU_ASSERT_EQUAL(nav.premiere_case.y, 3);
}




// Test pour la fonction "generer_position_navire"
void test_generer_position_navire() {
    int taille_plateau = 10;
    int** plateau = creer_plateau(taille_plateau);
    Navire nav = creer_navire(3, taille_plateau);
    generer_position_navire(plateau, taille_plateau, &nav);
}

// Test pour la fonction "placer_navire"
void test_placer_navire() {
    int taille_plateau = 10;
    int** plateau = creer_plateau(taille_plateau);
    Navire nav = creer_navire(3, taille_plateau);
    placer_navire(plateau, &nav, 1);
    CU_ASSERT_EQUAL(plateau[3][3], 1);
    CU_ASSERT_EQUAL(plateau[2][3], 1);
    CU_ASSERT_EQUAL(plateau[1][3], 1);
}





// De même, pour afficher_coup, verifier_toucher, proposition_joueur...

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Statistiques", NULL, NULL);
    CU_add_test(suite, "Test de création des statistiques", test_creer_statistiques);
    CU_add_test(suite, "Test d'incrémentation des coups", test_incrementer_total_coups);
    CU_add_test(suite, "Test d'incrémentation des coups à l'eau", test_incrementer_total_a_l_eau);
    CU_add_test(suite, "Test d'incrémentation des coups déjà joués", test_incrementer_total_deja_joue);
    CU_add_test(suite, "Test d'incrémentation des coups touchés", test_incrementer_total_touche);
    CU_add_test(suite, "Test de la définition du dernier navire coulé", test_set_dernier_navire_coule);
    CU_add_test(suite, "Test de la définition du nombre de lettres uniques dans le nom du premier navire touché", test_set_lettres_premier_navire);
    CU_add_test(suite, "Test d'écriture des statistiques", test_ecrire_statistiques);

    // Suite pour les tests de bataille_navale
    CU_pSuite suiteBatailleNavale = CU_add_suite("BatailleNavale", NULL, NULL);
    CU_add_test(suiteBatailleNavale, "Test de init_nb_aleatoire", test_init_nb_aleatoire);
    CU_add_test(suiteBatailleNavale, "Test de nb_aleatoire", test_nb_aleatoire);
    CU_add_test(suiteBatailleNavale, "Test de creer_plateau", test_creer_plateau);
    CU_add_test(suiteBatailleNavale, "Test de creer_grille", test_creer_grille);
    CU_add_test(suiteBatailleNavale, "Test de creer_navire",test_creer_navire);
    CU_add_test(suiteBatailleNavale, "Test de generer_position_navire",test_generer_position_navire);
    CU_add_test(suiteBatailleNavale, "Test de est_dans_limites", test_est_dans_limites);
    CU_add_test(suiteBatailleNavale, "Test de est_occupee", test_est_occupee);
    CU_add_test(suiteBatailleNavale, "Test de obtenir_case", test_obtenir_case);
    CU_add_test(suiteBatailleNavale, "Test de est_valide", test_est_valide);


    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
