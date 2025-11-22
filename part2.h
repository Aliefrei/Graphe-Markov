//
// Created by alilo on 10/11/2025.
//

#ifndef PART2_H
#define PART2_H
#include "part1.h"

typedef struct s_tarjan_vertex{
  int id;
  int num_tmp;
  int num_vertex;
  int booleen;
}t_tarjan_vertex;

typedef struct {
  int taille;
  t_tarjan_vertex* vertex;
}tab_all_vertex;

typedef struct s_class{
  char *nom_class;
  t_tarjan_vertex *nb_vertex;
}t_class;

typedef struct s_list_class{
  int taille;
  t_class** tab;
}t_list_class;

//FONCTIONS

tab_all_vertex tab_all_vertex_create(t_list_adj list);

typedef struct s_pile{
  int taille;
  t_tarjan_vertex** tab;
}t_pile;

void push(t_pile* pile, t_tarjan_vertex* vertex);


















#endif //PART2_H
