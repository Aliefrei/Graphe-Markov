//
// Created by alilo on 20/10/2025.
//
#include "part1.h"
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

t_list* create_empty_list()
{
    t_list* newliste= (t_list*)malloc(sizeof(t_list));
    newliste->head = NULL;
    return newliste;
}

void add_cell(t_list* p_list, int node, float proba){
    t_cell *new = create_cell(node, proba);
    new->next = p_list->head;
    p_list->head = new;
    return;
}


void display_list(t_list* L){
    t_cell *current = L->head;
    while (current != NULL){
        printf("%d %.2f\n", current->node, current->proba);
        current = current->next;
    }
}
t_list_adj* create_list_adj(int taille){
    t_list_adj *l_adj= (t_list_adj*)malloc(sizeof(t_list_adj));
    l_adj->taille = taille;
    l_adj->tab = (t_list**)malloc(taille*sizeof(t_list*));

    for (int i = 0; i < taille; i++){
      t_list *L = create_empty_list();
      l_adj->tab[i] = create_empty_list();
    }
    return l_adj;
}

void display_list_adj(t_list_adj* L){
    printf("Liste d'adjacence (%d sommets) :\n", L->taille);
    for (int i = 0; i < L->taille; i++){
        printf("Sommet %d : ", i + 1);
        display_list(L->tab[i]);
    }
}



t_list_adj* readGraph(const char *filename) {
 FILE *file = fopen(filename, "rt"); // read-only, text
 int nbvert, depart, arrivee;
 float proba;
 t_list_adj my_list_adj;
 if (file==NULL)
 {
 perror("Could not open file for reading");
 exit(EXIT_FAILURE);
 }
 // first line contains number of vertices
 if (fscanf(file, "%d", &nbvert) != 1)
 {
 perror("Could not read number of vertices");
 exit(EXIT_FAILURE);
 }
 my_list_adj = create_list_adj(nbvert);
 while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3)
 {
 // on obtient, pour chaque ligne du fichier les valeurs
 // depart, arrivee, et proba
 t_cell *new = create_cell(arrivee, proba);
 add_cell(my_list_adj->tab[depart - 1], arrivee, proba);

 }
 fclose(file);
 return my_list_adj;
}






