//
// Created by alilo on 20/10/2025.
//

#ifndef PART1_H
#define PART1_H
#include <stdio.h>
#include <stdlib.h>


// Structures
typedef struct s_cell {
    int node; //sommet d'arrivée
    float proba;
    struct s_cell *next;
} t_cell;


typedef struct s_list {
    t_cell *head;
} t_list;

typedef struct list_adj {
    int taille; // taille représente le nombre de sommets
    t_list** tab ; // tableau dynamique
    }t_list_adj;


// Prototype des fonctions

// fonction pour créer une « cellule »
t_cell* create_cell(int node, float proba);

// fonction pour créer une « liste » vide
t_list* create_empty_list();

// fonction pour ajouter une cellule à une liste
void add_cell(t_list* list, int node, float proba);
// fonction pour afficher une liste

void display_list(t_list* L);

// fonction pour créer une liste d’adjacence ‘vide’ à partir d’une taille donnée
t_list_adj* create_list_adj(int taille);

// fonction pour aƯicher une liste d’adjacence
void display_list_adj(t_list_adj* L);


t_list_adj* readGraph(const char *filename);

// Détermine si un graphe est un graphe de Markov et écrit le résultat
void is_markov(t_list_adj* list);

// Écrit dans dessin_graph.txt les données nécessaires au dessin du graph de Markov
void draw_graph(t_list_adj* list);

#endif //PART1_H
