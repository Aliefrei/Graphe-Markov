//
// Created by alilo on 20/10/2025.
//
// #include <stdio.h>
// #include <stdlib.h>
// #include "part1.h"
// #include "part2.h"
// #include "hasse.h"
// #include "matrix.h"
// #define MAX_ITERATIONS 1000

// int main() {

  //   int choix;
  //   printf("1. Partie 1\n2. Partie 2\n3. Partie 3\nVotre choix : ");
  //   scanf("%d",&choix);


  //   if (choix == 1) {
  //       printf("\n========== PARTIE 1 ==========\n");
  //       t_list_adj* graphe = readGraph("exemple_valid_step3.txt");

  //       display_list_adj(graphe);
  //       is_markov(graphe);
  //       draw_graph(graphe);
  //       free(graphe);
  //   }

  //   else if (choix == 2) {
  //       printf("\n========== PARTIE 2 ==========\n");
  //       t_list_adj* graphe = readGraph("exemple_valid_step3.txt");


  //       t_list_class* partition_test = tarjan(graphe);
  //       display_partition(partition_test);


  //       /* construire les liens (sans redondance initiale) */
  //       t_hasse_link_array links = build_hasse_links(graphe, partition_test);

  //       /* supprimer transitive links (réduction de Hasse)  */
  //       removeTransitiveLinks(&links);

  //       /* afficher Mermaid et caractéristiques */
  //       print_hasse_mermaid(partition_test, &links);
  //       print_class_characteristics(partition_test, &links);

  //       //Libérer mémoire
  //       free_partition(partition_test);
  //       free(graphe);
  //       free_hasse_links(&links);
  //   }
  //   else if (choix == 3) {
  //       printf("\n========== PARTIE 3 - ETAPE 1 ==========\n");
  //       //Affichage de la matrice
  //       t_list_adj* graphe = readGraph("matrice27projet.txt");
  //       t_matrix matrix;
  //       matrix = create_matrix(graphe);
  //       printf ("Matrice M : \n");
  //       affichage_matrix(matrix);
  //       //Calcul de M^2

  //       printf("\n\n---------------------------\n\n\n");
  //       printf("La matrice M^2 :\n");
  //       t_matrix M2;
  //       M2 = matrix;
  //       for(int i = 0; i < 1; i++) {
  //           M2= produit_matrix(M2, matrix);
  //       }
  //       affichage_matrix(M2);
  //       printf("\n\n---------------------------\n\n\n");
  //       printf("La matrice M^10 :\n");
  //       t_matrix M3;
  //       M3 = matrix;
  //       for(int i = 0; i < 9; i++) {
  //           M3= produit_matrix(M3, matrix);
  //       }
  //       affichage_matrix(M3);
  //       printf("\n\n---------------------------\n\n\n");
  //       //Calcul de M^50
  //       printf("La matrice M^50\n");
  //       t_matrix M7;
  //       M7 = matrix;
  //       for(int j = 0; j < 49 ;j++) {
  //           M7= produit_matrix(M7, matrix);
  //       }
  //       affichage_matrix(M7);
  //       printf("\n\n---------------------------\n\n\n");


  //       printf("Calcul de M^n pour laquelle diff(M^n,M^n-1) inferieure a 0.01 :\n Matrice initiale :\n");
  //       //Calcul de M^n pour laquelle diff(M^n,M^n-1) inférieure à 0.01
  //       t_list_adj* graphe2 = readGraph("matrice27projet.txt");
  //       t_matrix M;
  //       M = create_matrix(graphe2);

  //       affichage_matrix(M);
  //       t_matrix M_previous;
  //       t_matrix M_initiale= create_matrix(graphe2);
  //       int n=1;


  //       do {
  //           M_previous= M; //On sauvegarde M^(n-1)
  //           M=produit_matrix(M_previous, M_initiale); // M^n = M^(n-1) * M
  //           n++;
  //           if (n>MAX_ITERATIONS) {
  //               break; //Pas de convergence
  //           }
  //       } while (difference(M, M_previous)>=0.01);

  //       if (n<MAX_ITERATIONS) {
  //           printf("Convergence atteinte a M^%d :\n", n);
  //           affichage_matrix(M);
  //       }
  //       else {
  //           printf("\nCe grave ne converge pas\n");
  //       }
  //       //Cela fonctionne ne fonctionne pas pour exemple3

  //       free(graphe);
  //   }
  //   else {
  //       printf("\nChoix invalide !\n");
  //   }

  // return 0; 


// }

// exp_q6_q7.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "part1.h"
#include "part2.h"
#include "matrix.h"

#define N_STATES 27
#define MAX_ITER 1000
#define CONV_THRESH 0.01f

/* --- Fonctions utilitaires --- */

/* multiplie vecteur ligne (size N_STATES) par matrice M (N_STATES x N_STATES)
   res = vect * M
*/
void mult_vect_matrix(float* res, const float* vect, t_matrix M){
    for(int j = 0; j < M.nb_colonnes; j++){
        float s = 0.0f;
        for(int i = 0; i < M.nb_lignes; i++){
            s += vect[i] * M.donnees[i][j];
        }
        res[j] = s;
    }
}

/* affiche un vecteur de taille n (avec indices 1..n) */
void affichage_vect(const float* v, int n){
    for(int i = 0; i < n; i++){
        printf("%.6f", v[i]);
        if(i < n-1) printf(" ");
    }
    printf("\n");
}

/* calcule la norme L1 (somme des valeurs absolues) entre deux vecteurs */
float norme_L1(const float* a, const float* b, int n){
    float s = 0.0f;
    for(int i = 0; i < n; i++){
        s += fabsf(a[i] - b[i]);
    }
    return s;
}

/* calcule P^n (retourne t_matrix par valeur; attention copies fréquentes) */
t_matrix puissance_matrice(t_matrix P, int n){
    if(n <= 1) return P;
    t_matrix R = P;
    for(int k = 1; k < n; k++){
        R = produit_matrix(R, P);
    }
    return R;
}

void run_scenario(const char* title, const float* Pi0, t_matrix P){
    int ns[] = {1,2,10,50};
    int n_count = 4;

    printf("\n--- SCENARIO: %s ---\n", title);

    for(int idx = 0; idx < n_count; idx++){
        int n = ns[idx];
        t_matrix Pn = puissance_matrice(P, n);
        float Pin[27];
        mult_vect_matrix(Pin, Pi0, Pn);

        printf("Pi(%d) = ", n);
        affichage_vect(Pin, 27);
    }
}

/* initialise Pi0 à zéro */
void zero_pi(float* Pi){
    for(int i = 0; i < N_STATES; i++) Pi[i] = 0.0f;
}

int main(void){
    // lire la matrice depuis le fichier (utilise ton readGraph/create_matrix)
    t_list_adj* graphe = readGraph("matrice27projet.txt");
    if(graphe == NULL){
        fprintf(stderr, "Erreur: impossible de lire matrice27projet.txt\n");
        return 1;
    }
    t_matrix P = create_matrix(graphe);

    // //scenario Q3:
    // float Pi0[N_STATES];
    // zero_pi(Pi0);
    // for(int trial = 1; trial <= 3; trial++){
    //     float a = (float)rand() / (float)RAND_MAX;
    //     float b = (float)rand() / (float)RAND_MAX;
    //     float c = (float)rand() / (float)RAND_MAX;
    //     float d = (float)rand() / (float)RAND_MAX;
    //     float e = (float)rand() / (float)RAND_MAX;
        
    //     float s = a + b + c+d + e;
    //     zero_pi(Pi0);
    //     Pi0[1]  = a / s;
    //     Pi0[4] = b / s;
    //     Pi0[11] = c / s;
    //     Pi0[20]  = d / s;
    //     Pi0[24]  = e / s;
    //     char title[80];
    //     snprintf(title, sizeof(title), "Q3: aleatoire #%d sur {2,,5, 12,21,25} (a=%.3f,b=%.3f,c=%.3f, d=%.3f, e=%.3f)", trial, Pi0[1], Pi0[4], Pi0[11],Pi0[20], Pi0[24]);
    //     run_scenario(title, Pi0, P);
    // }


    // SCENARIOS Q6
    float Pi0[N_STATES];

    // 4.1: depart dans l'etat 8 
    zero_pi(Pi0);
    Pi0[7] = 1.0f;
    run_scenario("Q4.1: depart dans l'etat 8 (e8)", Pi0, P);

    // 6.2: depart uniforme sur {6,17,20} (indices 5,16,19)
    zero_pi(Pi0);
    Pi0[7]  = 1.0f/3.0f;
    Pi0[8] = 1.0f/3.0f;
    Pi0[15] = 1.0f/3.0f;
    run_scenario("Q4.2: depart uniforme sur {8,9,16}", Pi0, P);

    // 6.3: trois tirages aleatoires sur {6,17,20}
    for(int trial = 1; trial <= 3; trial++){
        float a = (float)rand() / (float)RAND_MAX;
        float b = (float)rand() / (float)RAND_MAX;
        float c = (float)rand() / (float)RAND_MAX;
        float s = a + b + c;
        zero_pi(Pi0);
        Pi0[7]  = a / s;
        Pi0[8] = b / s;
        Pi0[15] = c / s;
        char title[80];
        snprintf(title, sizeof(title), "Q4.3: aleatoire #%d sur {8,9,16} (a=%.3f,b=%.3f,c=%.3f)", trial, Pi0[7], Pi0[8], Pi0[15]);
        run_scenario(title, Pi0, P);
    }

    // SCENARIOS Q5 (facultatif: tu peux commenter si tu veux lancer seulement Q6)
    // 5.1: depart dans l'etat 3 (index 2)
    zero_pi(Pi0);
    Pi0[13] = 1.0f;
    run_scenario("Q5.1: depart dans l'etat 14 (e14)", Pi0, P);

    // 5.2: depart uniforme sur {3,7,23} (indices 2,6,22)
    zero_pi(Pi0);
    Pi0[9] = 1.0f/5.0f;
    Pi0[13] = 1.0f/5.0f;
    Pi0[18]= 1.0f/5.0f;
    Pi0[21]= 1.0f/5.0f;
    Pi0[23]= 1.0f/5.0f;

    run_scenario("Q5.2: depart uniforme sur {10,14,19,22,24}", Pi0, P);

    // 5.3: trois tirages aleatoires sur {3,7,23}
 
    zero_pi(Pi0);
    for(int trial = 1; trial <= 3; trial++){
        float a = (float)rand() / (float)RAND_MAX;
        float b = (float)rand() / (float)RAND_MAX;
        float c = (float)rand() / (float)RAND_MAX;
        float d = (float)rand() / (float)RAND_MAX;
        float e = (float)rand() / (float)RAND_MAX;
        
        float s = a + b + c+d + e;
        zero_pi(Pi0);
        Pi0[9]  = a / s;
        Pi0[13] = b / s;
        Pi0[18] = c / s;
        Pi0[21]  = d / s;
        Pi0[23]  = e / s;
        char title[80];
        snprintf(title, sizeof(title), "Q5: aleatoire #%d sur {10,14,19,22,24} (a=%.3f,b=%.3f,c=%.3f, d=%.3f, e=%.3f)", trial, Pi0[9], Pi0[13], Pi0[18],Pi0[21], Pi0[23]);
        run_scenario(title, Pi0, P);
    }

    // liberer
    free(graphe);
    return 0;
}
