//
// Created by alilo on 10/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "part1.h"
#include "part2.h"
#include "hasse.h"


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
    // Récupérer le vertex correspondant au sommet
    t_tarjan_vertex* vertex = &(all_vertex->vertex[sommet_id - 1]);

    // Initialiser num et num_tmp avec le numéro d'ordre
    vertex->num_vertex = *p_num;
    vertex->num_tmp = *p_num;
    (*p_num)++;

    // Empiler le sommet
    push(pile, vertex);
    vertex->booleen = 1; // Marquer comme étant dans pile

    // Parcourir tous les successeurs du sommet : "pour chaque w successeur de v"
    t_cell* current = graph->tab[sommet_id - 1]->head;
    while (current != NULL) { //tant que current n'est pas dernier élém de liste chaînée "tab" de liste adjacence
        int succ_id = current->node; //récup id successeur
        t_tarjan_vertex* succ = &(all_vertex->vertex[succ_id - 1]); // pointeur succ récup adresse vertex

        if (succ->num_vertex == -1) {
            // Successeur non encore visité
            parcours(graph, all_vertex, pile, p_num, partition, succ_id);
            vertex->num_tmp = min(vertex->num_tmp, succ->num_tmp); //num_tmp représente plus petit numéro de sommet que je peux atteindre depuis ma position
        }
        else if (succ->booleen == 1) {
            // Successeur dans la pile (arc retour)
            vertex->num_tmp = min(vertex->num_tmp, succ->num_vertex);
        }

        current = current->next;
    }

    // Si c'est une racine de composante fortement connexe
    if (vertex->num_tmp == vertex->num_vertex) { //retour sur lui même possible
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
            w->booleen = 0; // Retirer de pile
            new_class->nb_vertex[idx] = *w;
            idx++;
        } while (w->id != sommet_id);

        // Ajouter la classe à la partition (liste de classe)
        partition->tab = (t_class**)realloc(partition->tab, (partition->taille + 1) * sizeof(t_class*)); //realloc pour agrandir
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

    // Parcourir tous les sommets + ajouter classes dans partition
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
    printf("\nComposantes fortement connexes trouvees : %d\n", partition->taille);
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



// Etape 2

/* Retourne un tableau d'entiers (taille n_vertices) : v2c[i] = index de classe (0..C-1) */
int *vertex_to_class(t_list_class *partition, int n_vertices)
{
    /* Allocation du tableau résultat : un entier par sommet */
    int *v2c = malloc(sizeof(int) * n_vertices);
    if(!v2c){ perror("malloc"); exit(EXIT_FAILURE); }

    /* Initialisation à -1 : aucun sommet n’est encore associé à une classe */
    for(int i=0;i<n_vertices;i++) v2c[i] = -1;

    /* Parcourt toutes les classes trouvées par Tarjan */
    for(int c = 0; c < partition->taille; ++c){
        t_class *cl = partition->tab[c];

        /* Parcourt tous les sommets appartenant à cette classe */
        for(int j=0;j<cl->size;++j){

            /* Récupère l’ID réel du sommet (numérotation 1..n) */
            int vid = cl->nb_vertex[j].id; /* 1-based */

            /* Vérification de sécurité : l'ID doit être dans [1, n_vertices] */
            if(vid < 1 || vid > n_vertices){
                fprintf(stderr,
                        "vertex_to_class: vertex id out of range %d\n", vid);
                continue;
            }

            /* Association :
               comme vid est en base 1, on le met en (vid - 1)
               et on stocke l’indice de classe c (base 0). */
            v2c[vid - 1] = c; /* store 0-based class index */
        }
    }

    /* Vérifie si tous les sommets ont bien été placés dans une classe */
    for(int i=0;i<n_vertices;++i){
        if(v2c[i] == -1){
            /* Cela ne devrait JAMAIS arriver après Tarjan.
               Si oui : sommet ignoré ou partition incohérente. */
            fprintf(stderr,"Warning: vertex %d has no class assigned\n", i+1);
        }
    }

    return v2c;
}

// build hasse links
// Construit les liens entre classes (graphe des classes) avant réduction de Hasse.
// Chaque lien représente l'existence d'au moins UNE arête allant d'une classe SCC vers une autre.
// La fonction retourne une structure t_hasse_link_array contenant ces liens.
// L'appelant devra ensuite appeler removeTransitiveLinks() pour obtenir le diagramme de Hasse réduit.

t_hasse_link_array build_hasse_links(t_list_adj *graph, t_list_class *partition)
{
    int n = graph->taille;          // Nombre total de sommets du graphe.
    int C = partition->taille;      // Nombre total de classes (SCC).
    
    t_hasse_link_array h;           // Structure résultat.
    h.links = NULL;
    h.log_size = 0;

    // Si aucune classe, rien à faire.
    if(C == 0){
        return h;
    }

    // v2c[i] = numéro de classe du sommet i (0-based).
    // Permet de passer d’un sommet → classe en O(1)
    int *v2c = vertex_to_class(partition, n);

    // Matrice C×C pour empêcher les doublons (mat[i*C + j] = 1 si lien déjà enregistré)
    char *mat = calloc(C * C, 1);
    if(!mat){ perror("calloc"); exit(EXIT_FAILURE); }

    // Tableau dynamique temporaire pour accumuler les liens (avant copie vers h.links).
    // On part sur une capacité initiale de 16 et on double si besoin.
    int cap = 16;
    t_link *temp = malloc(sizeof(t_link) * cap);
    if(!temp){ perror("malloc"); exit(EXIT_FAILURE); }

    int cnt = 0; // Nombre de liens réellement trouvés

    // Parcours des sommets du graphe
    for(int i=0;i<n;++i){
        int ci = v2c[i];        // classe du sommet i
        if(ci < 0) continue;    // sommet sans classe (ne devrait pas arriver)

        // Parcours des successeurs du sommet i+1 (car graph->tab est 0-based)
        t_cell *cur = graph->tab[i]->head;
        while(cur){
            int j = cur->node;  // identifiant du successeur (1-based)

            // Vérification sécurité (j doit être un sommet valide)  
            if(j >= 1 && j <= n){
                int cj = v2c[j - 1];  // classe du successeur

                // On ne crée un lien qu’entre classes différentes
                if(cj >= 0 && ci != cj){

                    int idx = ci * C + cj; // position dans la matrice C×C

                    // Si le lien n’a pas encore été enregistré
                    if(!mat[idx]){
                        mat[idx] = 1; // marquer qu’on l’a déjà ajouté

                        // Si le tableau temporaire est plein, on le redimensionne
                        if(cnt >= cap){
                            cap *= 2;
                            temp = realloc(temp, sizeof(t_link) * cap);
                            if(!temp){ perror("realloc"); exit(EXIT_FAILURE); }
                        }

                        // Ajouter le lien (classe ci → classe cj)
                        temp[cnt].from = ci;
                        temp[cnt].to   = cj;
                        cnt++;
                    }
                }
            }
            cur = cur->next; // passer au successeur suivant
        }
    }

    // Finalisation de la structure t_hasse_link_array
    if(cnt > 0){
        // Allocation pile-poil à la bonne taille
        h.links = malloc(sizeof(t_link) * cnt);
        if(!h.links){ perror("malloc"); exit(EXIT_FAILURE); }

        // Copie des liens trouvés
        memcpy(h.links, temp, sizeof(t_link) * cnt);
        h.log_size = cnt;
    } else {
        h.links = NULL;
        h.log_size = 0;
    }

    // Libérations
    free(temp);
    free(mat);
    free(v2c);

    return h;
}

/* ---------------------- print Mermaid ---------------------- */
void print_hasse_mermaid(t_list_class *partition, t_hasse_link_array *links)
{
    printf("\n```mermaid\n");
    printf("graph TD\n");
    /* nodes */
    for(int c = 0; c < partition->taille; ++c){
        t_class *cl = partition->tab[c];
        printf("  C%d[\"{", c+1);
        for(int j=0;j<cl->size;++j){
            printf("%d", cl->nb_vertex[j].id);
            if(j+1 < cl->size) printf(",");
        }
        printf("}\"]\n");
    }
    /* edges */
    for(int e = 0; links && e < links->log_size; ++e){
        printf("  C%d --> C%d\n", links->links[e].from + 1, links->links[e].to + 1);
    }
    printf("```\n");
}

//ETAPE 3

void print_class_characteristics(t_list_class *partition, t_hasse_link_array *links)
{
    int C = partition->taille;
    int *outdeg = calloc(C, sizeof(int));
    if(links){
        for(int e=0;e<links->log_size;++e){
            int u = links->links[e].from;
            if(u>=0 && u<C) outdeg[u]++;
        }
    }

    int persistent_count = 0;
    for(int c=0;c<C;++c){
        if(outdeg[c] == 0){
            printf("Classe %s (C%d) : persistante (pas de fleche sortante)\n",
                   partition->tab[c]->nom_class ? partition->tab[c]->nom_class : "", c+1);
            persistent_count++;
            if(partition->tab[c]->size == 1){
                printf("  -> etat %d est absorbant (classe de taille 1).\n", partition->tab[c]->nb_vertex[0].id);
            }
        } else {
            printf("Classe %s (C%d) : transitoire (outdeg=%d)\n",
                   partition->tab[c]->nom_class ? partition->tab[c]->nom_class : "", c+1, outdeg[c]);
        }
    }
    if(C == 1) printf("Graphe irreductible (une seule classe)\n");
    else printf("Graphe non irreductible\n");

    free(outdeg);
}

/* ---------------------- free helper ---------------------- */
void free_hasse_links(t_hasse_link_array *links)
{
    if(!links) return;
    if(links->links) free(links->links);
    links->links = NULL;
    links->log_size = 0;
}