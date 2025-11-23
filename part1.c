#include "part1.h"
#include <stdio.h>
#include <stdlib.h>

// fonction pour créer une « cellule »
t_cell* create_cell(int node, float proba) {
    t_cell *new = (t_cell*)malloc(sizeof(t_cell));
    new->node = node;
    new->proba = proba;
    new->next = NULL;
    return new;
}
// libère l'espace alloué à une cellule et celles qui la suivent dans la liste
void free_cells(t_cell *head) {
    t_cell *tmp;
    while (head != NULL) {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}



// fonction pour créer une « liste » vide
t_list* create_empty_list() {
    t_list *newliste = (t_list*)malloc(sizeof(t_list));
    newliste->head = NULL;
    return newliste;
}
// libère l'espace alloué à une liste
void free_list(t_list *list) {
    if (list == NULL)
        return;
    free_cells(list->head);
    free(list);
}



// fonction pour ajouter une cellule à une liste
void add_cell(t_list* p_list, int node, float proba) {
    t_cell *new = create_cell(node, proba);
    new->next = p_list->head;
    p_list->head = new;
}


// fonction pour afficher une liste
void display_list(t_list* L) {
    t_cell *current = L->head;
    while (current != NULL) {
        printf("%d %.2f  ", current->node, current->proba);
        current = current->next;
    }
    printf("\n");
}


// fonction pour créer une liste d’adjacence ‘vide’ à partir d’une taille donnée en paramètre
t_list_adj* create_list_adj(int taille) {
    t_list_adj *l_adj = (t_list_adj*)malloc(sizeof(t_list_adj));
    l_adj->taille = taille;
    l_adj->tab = (t_list**)malloc(taille * sizeof(t_list*));

    for (int i = 0; i < taille; i++) {
        l_adj->tab[i] = create_empty_list();
    }
    return l_adj;
}
// libère l'espace alloué à une liste d'adjacence
void free_list_adj(t_list_adj *list) {
    if (list == NULL)
        return;
    // Libérer chaque liste
    for (int i = 0; i < list->taille; i++) {
        free_list(list->tab[i]);
    }
    // Libére le tableau de listes
    free(list->tab);
    // Libére la structure principale
    free(list);
}



// fonction pour afficher une liste d’adjacence
void display_list_adj(t_list_adj* L) {
    printf("Liste d'adjacence (%d sommets) :\n", L->taille);
    for (int i = 0; i < L->taille; i++) {
        printf("Sommet %d : ", i + 1);
        display_list(L->tab[i]);
    }
}


// Permet d'importer un graph depuis un fichier texte
t_list_adj* readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt");
    int nbvert, depart, arrivee;
    float proba;

    if (file == NULL) {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }

    if (fscanf(file, "%d", &nbvert) != 1) {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }

    t_list_adj *my_list_adj = create_list_adj(nbvert);

    while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3) {
        add_cell(my_list_adj->tab[depart - 1], arrivee, proba);
    }

    fclose(file);
    return my_list_adj;
}



void is_markov(t_list_adj* list) {
    // parcourt les éléments de la liste d'adjacence
    for (int i = 0; i < list->taille; i++) {
        float sum = 0;
        t_cell * current = list->tab[i]->head;
        // parcourt les données des arrêtes
        while (current != NULL) {
            sum += current->proba; // somme des probabilités du sommet
            current = current->next;
        }
        if ((sum<0.99)||(sum>1)) {
            printf("Le graphe n'est pas un graphe de Markov\nLa somme des probabilites du sommet %d est %.2f\n", list->tab[i]->head->node, sum);
            return;
        }
    }
    printf("Le graphe est un graphe de Markov\n");
    return;
}


// Renvoie une série de lettres correspondant à l'entier entré en paramètre (1->A, 26->Z, 27->AA...) | (Fonction fournie).
static char *getID(int i) {
    // translate from 1,2,3, .. ,500+ to A,B,C,..,Z,AA,AB,...
    static char buffer[10];
    char temp[10];
    int index = 0;
    i--; // Adjust to 0-based index
    while (i >= 0)
    {
        temp[index++] = 'A' + (i % 26);
        i = (i / 26) - 1;
    }
    // Reverse the string to get the correct order
    for (int j = 0; j < index; j++)
    {
        buffer[j] = temp[index - j - 1];
    }
    buffer[index] = '\0';
    return buffer;
}


// Écrit dans dessin_graph.txt les données nécessaires au dessin du graph de Markov via Mermaid
void draw_graph(t_list_adj* list) {
    FILE *p_texte;
    p_texte = fopen("dessin_graph.txt", "w");   // ouverture en mode écriture
    fprintf(p_texte, "---\nconfig:\n   layout: elk\n   theme: neo\n   look: neo\n---\n\nflowchart LR\n");

    // parcourt les éléments de la liste d'adjacence
    for (int i = 0; i < list->taille; i++) {
        fprintf(p_texte, "%s((%d))\n", getID(i+1), i+1);
    }

    //parcourt les éléments de la liste d'adjacence ET les arêtes
    for (int i = 0; i < list->taille; i++) {
        t_cell *current = list->tab[i]->head;
        while (current != NULL) {
            fprintf(p_texte, "\n%s -->|%0.2f|%c", getID(i+1), current->proba, *getID(current->node));
            current = current->next;
        }
    }
}


