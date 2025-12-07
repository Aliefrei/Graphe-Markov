//
// Created by alilo on 20/10/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "part1.h"
#include "part2.h"
#include "hasse.h"
#include "matrix.h"
#define MAX_ITERATIONS 1000

int main() {
  t_list_adj* graphe = readGraph("C:/Users/tsunt/Desktop/Graphe-Markov/exemple_valid_step3.txt");

  display_list_adj(graphe);
  is_markov(graphe);
  draw_graph(graphe);


  t_list_class* partition_test = tarjan(graphe);
  display_partition(partition_test);


  /* construire les liens (sans redondance initiale) */
  t_hasse_link_array links = build_hasse_links(graphe, partition_test);

  /* supprimer transitive links (réduction de Hasse)  */
  removeTransitiveLinks(&links); 

  /* afficher Mermaid et caractéristiques */
  print_hasse_mermaid(partition_test, &links);
  print_class_characteristics(partition_test, &links);

  //Libérer mémoire
  free_partition(partition_test);
  free(graphe);
  free_hasse_links(&links);

  /*
  //main de partie 3 etape 1, a voir comment on fera pour tout rassembler sur le meme main
  int main() {
  //Affichage de la matrice
  t_list_adj* graphe = readGraph("exemple_meteo.txt");
  t_matrix matrix;
  matrix = create_matrix(graphe);
  affichage_matrix(matrix);
  //Calcul de M^3

  printf("La matrice M^3 :\n");
  t_matrix M3;
  M3 = matrix;
  for(int i = 0; i < 2; i++) {
  M3= produit_matrix(M3, matrix);
  }
  affichage_matrix(M3);

  //Calcul de M^7
  printf("La matrice M^7\n");
  t_matrix M7;
  M7 = matrix;
  for(int j = 0; j < 6 ;j++) {
  M7= produit_matrix(M7, matrix);
  }
  affichage_matrix(M7);
  printf("\n\n---------------------------\n\n\n");


  printf("Calcul de M^n pour laquelle diff(M^n,M^n-1) inferieure a 0.01 :\n Matrice initiale :\n");
  //Calcul de M^n pour laquelle diff(M^n,M^n-1) inférieure à 0.01
  t_list_adj* graphe2 = readGraph("exemple3.txt");
  t_matrix M;
  M = create_matrix(graphe2);

  affichage_matrix(M);
  t_matrix M_previous;
  t_matrix M_initiale= create_matrix(graphe2);
  int n=1;


  do {
  M_previous= M; //On sauvegarde M^(n-1)
  M=produit_matrix(M_previous, M_initiale); // M^n = M^(n-1) * M
  n++;
  if (n>MAX_ITERATIONS) {
  break; //Pas de convergence
  }
  } while (difference(M, M_previous)>=0.01);

  if (n<MAX_ITERATIONS) {
  printf("Convergence atteinte a M^%d :\n", n);
  affichage_matrix(M);
  }
  else {
  printf("\nCe grave ne converge pas\n");
  }
  //Cela fonctionne ne fonctionne pas pour exemple3

  free(graphe);


  return 0;
  }
  */
  return 0;
}
