//
// Created by alilo on 20/10/2025.
//
#include <part1.h>
#include <stdio.h>
#include <stdlib.h>


//DEFINITIONS DES FONCTIONS
t_cell* create_cell(int node, int proba){
    t_cell *new;
    new = (t_cell*)malloc(sizeof(t_cell));
    new->node = node;
    new->proba = proba;
    new->next = NULL;
    return new;
}

t_list* create_empty_list();
{
    t_list* newliste;
    newliste->head = NULL;
    return newliste;
}

void add_cell(t_list* p_list, int node, int proba){
    t_cell *new = create_cell(node, proba);
    new->next = p_list->head;
    p_list->head = new;
    return;
}


void display_list(t_list* L){
    t_cell *current = L->head;
    while (current != NULL){
        printf("%d %d\n", current->node, current->proba);
    }
}
list_adj* create_list_adj(int taille){
    list_adj *l_adj;
    l_adj->taille = taille;
    l_adj->tab= malloc(taille*sizeof(t_list));

    for (int i = 0; i < taille; i++){
      t_list *L = create_empty_list();
      l_adj[i] = L;
    }
    return l_adj;
}

void display_list_adj(list_adj L){
     printf("%d\n", L.taille);
     t_cell *current = L.tab->head;
     for (int i = 0; i < L.taille; i++){

       printf("%d %d %d\n", i+1, current.tab[i].node, current.tab[i].proba);

     }




  }










