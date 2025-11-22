//
// Created by alilo on 10/11/2025.
//
#include "part1.h"
#include "part2.h"
#include <stdio.h>

//initialise tab vertex avec n -1 -1 0
tab_all_vertex tab_all_vertex_create(t_list_adj graph){
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

t_tarjan_vertex* pop(t_pile* pile)
{
    if (pile->taille == 0) return NULL;
    pile->taille--;
    return pile->tab[pile->taille];
}

// Fonction min pour calculer le minimum entre deux entiers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Fonction parcours selon l'algorithme de Tarjan
void parcours(t_list_adj* graph, tab_all_vertex* all_vertex, t_pile* pile,
              int* p_num, t_list_class* partition, int sommet_id)
{
    // Récupérer le vertex correspondant (sommet_id est en base 1, tableau en base 0)
    t_tarjan_vertex* vertex = &(all_vertex->vertex[sommet_id - 1]);

    // Initialiser num et num_tmp avec le numéro d'ordre
    vertex->num_vertex = *p_num;
    vertex->num_tmp = *p_num;
    (*p_num)++;

    // Empiler le sommet
    push(pile, vertex);
    vertex->booleen = 1; // Marquer comme étant dans la pile

    // Parcourir tous les successeurs du sommet
    t_cell* current = graph->tab[sommet_id - 1]->head;
    while (current != NULL) {
        int succ_id = current->node;
        t_tarjan_vertex* succ = &(all_vertex->vertex[succ_id - 1]);

        if (succ->num_vertex == -1) {
            // Successeur non encore visité
            parcours(graph, all_vertex, pile, p_num, partition, succ_id);
            vertex->num_tmp = min(vertex->num_tmp, succ->num_tmp);
        }
        else if (succ->booleen == 1) {
            // Successeur dans la pile (arc retour)
            vertex->num_tmp = min(vertex->num_tmp, succ->num_vertex);
        }

        current = current->next;
    }

    // Si c'est une racine de composante fortement connexe
    if (vertex->num_tmp == vertex->num_vertex) {
        // Créer une nouvelle classe
        t_class* new_class = (t_class*)malloc(sizeof(t_class));

        // Compter les sommets de la classe
        int count = 0;
        for (int i = pile->taille - 1; i >= 0; i--) {
            count++;
            if (pile->tab[i]->id == sommet_id) break;
        }

        // Allouer l'espace pour les sommets de la classe
        new_class->nb_vertex = (t_tarjan_vertex*)malloc(sizeof(t_tarjan_vertex) * count);
        new_class->size = count;

        // Nom de la classe
        new_class->nom_class = (char*)malloc(20 * sizeof(char));
        sprintf(new_class->nom_class, "C%d", partition->taille + 1);

        // Dépiler jusqu'à trouver le sommet racine
        int idx = 0;
        t_tarjan_vertex* w;
        do {
            w = pop(pile);
            w->booleen = 0; // Retirer de la pile
            new_class->nb_vertex[idx] = *w;
            idx++;
        } while (w->id != sommet_id);

        // Ajouter la classe à la partition
        partition->tab = (t_class**)realloc(partition->tab,
                                            (partition->taille + 1) * sizeof(t_class*));
        partition->tab[partition->taille] = new_class;
        partition->taille++;
    }
}

// Fonction principale de Tarjan
t_list_class* tarjan(t_list_adj* graph)
{
    // Initialiser la partition vide
    t_list_class* partition = (t_list_class*)malloc(sizeof(t_list_class));
    partition->taille = 0;
    partition->tab = NULL;

    // Initialiser tous les vertices
    tab_all_vertex all_vertex = tab_all_vertex_create(*graph);

    // Initialiser la pile vide
    t_pile pile;
    pile.taille = 0;
    pile.tab = (t_tarjan_vertex**)malloc(graph->taille * sizeof(t_tarjan_vertex*));

    // Compteur pour la numérotation
    int num = 0;

    // Parcourir tous les sommets
    for (int i = 0; i < graph->taille; i++) {
        if (all_vertex.vertex[i].num_vertex == -1) {
            parcours(graph, &all_vertex, &pile, &num, partition, i + 1);
        }
    }

    // Libérer la pile
    free(pile.tab);
    free(all_vertex.vertex);

    return partition;
}

// Fonction pour afficher les composantes fortement connexes
void display_partition(t_list_class* partition)
{
    printf("\nComposantes fortement connexes trouvées : %d\n", partition->taille);
    for (int i = 0; i < partition->taille; i++) {
        printf("Composante %s: {", partition->tab[i]->nom_class);
        for (int j = 0; j < partition->tab[i]->size; j++) {
            printf("%d", partition->tab[i]->nb_vertex[j].id);
            if (j < partition->tab[i]->size - 1) {
                printf(",");
            }
        }
        printf("}\n");
    }
}

// Fonction pour libérer la partition
void free_partition(t_list_class* partition)
{
    if (partition == NULL) return;

    for (int i = 0; i < partition->taille; i++) {
        free(partition->tab[i]->nom_class);
        free(partition->tab[i]->nb_vertex);
        free(partition->tab[i]);
    }
    free(partition->tab);
    free(partition);
}