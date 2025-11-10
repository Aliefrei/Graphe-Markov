//
// Created by alilo on 10/11/2025.
//
#include "part1.h"
#include "part2.h"

tab_all_vertex load_tab(t_list_adj graph){
    tab_all_vertex mytab_vertex;
    mytab_vertex.taille = graph.taille;
    mytab_vertex.vertex = malloc(sizeof(t_tarjan_vertex) * mytab_vertex.taille);
    for(int i = 0; i < mytab_vertex.taille; i++){
      mytab_vertex.vertex[i].id=i+1;
      mytab_vertex.vertex[i].num_tmp=-1;
      mytab_vertex.vertex[i].num_vertex=-1;
      mytab_vertex.vertex[i].booleen=0;
    }
    return mytab_vertex;
   } 

   void push(t_pile* pile, t_tarjan_vertex* vertex)
    {
         pile->tab[pile->taille] = vertex;
         pile->taille++;
    }
    