//
// Created by alilo on 20/10/2025.
//

#ifndef PART1_H
#define PART1_H
#include <stdio.h>
#include <stdlib.h>


//STRUCTURES
typedef struct s_cell {
    int node; //sommet d'arrivée
    int proba;
    struct s_cell *next;
} t_cell;


typedef struct s_list {
  t_cell *head;
}t_list;

typedef struct list_adj {
  int taille; // taille représente le nombre de sommets
  t_list* tab ; // tableau dynamique
  }t_list_adj;


//PROTOTYPE DES FONCTIONS
    t_cell* create_cell(int node, int proba);
    t_list* create_empty_list();
    void add_cell(t_list* list, int node, int proba);
    void display_list(t_list* L);
    list_adj* create_list_adj(int taille);
    void display_list_adj(list_adj L);









#endif //PART1_H
