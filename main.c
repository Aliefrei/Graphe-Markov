//
// Created by alilo on 20/10/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "part1.h"
#include "part2.h"

int main() {
  t_list_adj* graphe = readGraph("exemple_valid_step3.txt");

  display_list_adj(graphe);
  is_markov(graphe);
  draw_graph(graphe);


  t_list_class* partition_test = tarjan(graphe);
  display_partition(partition_test);

  free_partition(partition_test);
  free(graphe);

  return 0;
}
