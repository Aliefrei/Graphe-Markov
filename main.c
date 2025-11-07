//
// Created by alilo on 20/10/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "part1.h"

int main() {
  t_list_adj* graphe = readGraph("C:/Users/tsunt/Desktop/Graphe-Markov/exemple1.txt");

  display_list_adj(graphe);

  is_markov(graphe);

  draw_graph(graphe);

  return 0;
}