//
// Created by alilo on 10/11/2025.
//

#ifndef PART2_H
#define PART2_H
#include <stdio.h>
#include <stdlib.h>
#include "part1.h"
#include "hasse.h"

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
  int size;
}t_class;

typedef struct s_list_class{
  int taille;
  t_class** tab;

}t_list_class;


typedef struct s_pile{
  int taille;
  t_tarjan_vertex** tab;
}t_pile;

//Etape2 
typedef struct {
  t_link *a;
  int size, cap;
} t_link_array;




//FONCTIONS


tab_all_vertex tab_all_vertex_create(t_list_adj list);

void push(t_pile* pile, t_tarjan_vertex* vertex);

t_tarjan_vertex* pop(t_pile* pile);

void parcours(t_list_adj* graph, tab_all_vertex* all_vertex, t_pile* pile,
              int* p_num, t_list_class* partition, int sommet_id);

t_list_class* tarjan(t_list_adj* graph);

void display_partition(t_list_class* partition);

void free_partition(t_list_class* partition);

//etape 2

int *vertex_to_class(t_list_class *partition, int n_vertices);

/* construit t_link_array (compatible hasse.c) ;
   l'appelleur est responsable d'appeler removeTransitiveLinks(&h) s'il veut réduire */
t_hasse_link_array build_hasse_links(t_list_adj *graph, t_list_class *partition);

/* affichages et utilitaires */
void print_hasse_mermaid(t_list_class *partition, t_hasse_link_array *links);
//ETAPE 3
void print_class_characteristics(t_list_class *partition, t_hasse_link_array *links);
void free_hasse_links(t_hasse_link_array *links);

#endif //PART2_H
