//
// Created by alilo on 22/11/2025.
//

#ifndef MATRIX_H
#define MATRIX_H
#include "part1.h"
#include "part2.h"
#define T_MAX 50


typedef struct {
  int nb_lignes;
  int nb_colonnes;
  float donnees[T_MAX][T_MAX]; //contenant les probabilités de passage entre états
} t_matrix;



t_matrix create_matrix(t_list_adj* graph);

t_matrix create_empty_matrix(int n);

void copy_matrix(t_matrix M1, t_matrix M2);

t_matrix produit_matrix(t_matrix M1, t_matrix M2);

float difference(t_matrix M, t_matrix N);

void affichage_matrix(t_matrix M);





t_matrix subMatrix(t_matrix matrix, t_list_class* partition, int compo_index);

#endif //MATRIX_H
