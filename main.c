//
// Created by alilo on 20/10/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "part1.h"

int main() {
  t_list_adj* graphe = readGraph("exemple1.txt");

  display_list_adj(graphe);

  return 0;
}