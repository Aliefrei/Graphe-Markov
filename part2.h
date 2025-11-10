//
// Created by alilo on 10/11/2025.
//

#ifndef PART2_H
#define PART2_H

typedef struct s_tarjan_vertex{
  int id;
  int num_tmp;
  int num_vertex;
  int booleen;
  } t_tarjan_vertex;

typedef struct {
  t_tarjan_vertex *vertex;
}tab_all_vertex;

typedef struct s_class{
  char *nom_class;
  t_tarjan_vertex *nb_vertex;
}t_class;


//FONCTIONS
tab_all_vertex load_tab(t_list_adj);














#endif //PART2_H
