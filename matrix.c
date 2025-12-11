//
// Created by alilo on 22/11/2025.
//
#include "part1.h"
#include "part2.h"
#include "matrix.h"


//crée une matrice nxn remplie avec la valeur 0
  t_matrix create_empty_matrix(int n){
    t_matrix matrix;
    matrix.nb_lignes = n;
    matrix.nb_colonnes = n;
    for(int i = 0; i < matrix.nb_lignes; i++){
      for(int j = 0; j < matrix.nb_colonnes; j++){
        matrix.donnees[i][j] = 0.0;
      }
    }
    return matrix;
  }

//crée une matrice nxn avec les probabilités de passage entre états à partir d’une liste d’adjacence (graphe)
t_matrix create_matrix(t_list_adj* graph){
     int nb_etats= graph->taille;
     t_matrix matrix;
     matrix.nb_lignes = nb_etats;
     matrix.nb_colonnes = nb_etats;
     matrix= create_empty_matrix(nb_etats); //On initialise la matrice a 0

      for(int i = 0; i < matrix.nb_lignes; i++){
        t_list* list = graph->tab[i]; //liste du sommet i (tous les passages à partir de ce sommet)
        t_cell* current = list->head;

        while (current != NULL){
          int j = current->node - 1; //Ici, j représente le sommet d'arrivée
          //On soustrait 1 car les sommets sont numérotés à partir de 1 dans les exemples
          float proba = current->proba; //la proba que le sommet à l'indice i arrive au sommet indince j

          matrix.donnees[i][j] = proba;

          current = current->next;
        }
      }
    return matrix;
 }


  void copy_matrix(t_matrix M1, t_matrix M2){
    for(int i = 0; i < M1.nb_lignes; i++){
      for(int j = 0; j < M1.nb_colonnes; j++){
        M1.donnees[i][j] = M2.donnees[i][j]; //On copie les valeurs de la matrice M1 dans la matrice M2
      }
    }
  }

  //multiplication de deux matrices n x n
  t_matrix produit_matrix(t_matrix M1, t_matrix M2){
    t_matrix M3; //M3 sera le produit des matrices M1 et M2
    //M3.nb_lignes = M1.nb_lignes;
    //M3.nb_colonnes = M1.nb_colonnes;
    M3=create_empty_matrix(M1.nb_lignes);

    for(int i = 0; i < M3.nb_lignes; i++){
      for(int j = 0; j < M3.nb_colonnes; j++){
        M3.donnees[i][j] = 0;
       	for(int k = 0; k < M3.nb_lignes; k++){
          M3.donnees[i][j] += M1.donnees[i][k] * M2.donnees[k][j]; // Produit matriciel
       	}
      }
    }
    return M3;
  }

  //Calcule la différence entre 2 matrices M et N
  float difference(t_matrix M, t_matrix N){
    float val=0; //val va contenir la différence entre 2 coeffiecients des matrices
    float somme=0; // somme contiendra la S des val abs des différeces entre les coeff des matrices
    for(int i = 0; i < M.nb_lignes; i++){
      for(int j = 0; j < M.nb_colonnes; j++){
        val = M.donnees[i][j] - N.donnees[i][j];
        if(val < 0){
          val=-val; //valeur absolue
      	}
        somme+=val;
      }
    }
    return somme;
  }

  //affichage d'une matrice
  void affichage_matrix(t_matrix M){
    for(int i = 0; i < M.nb_lignes; i++){
      for(int j = 0; j < M.nb_colonnes; j++){
        printf("%.2f\t",M.donnees[i][j]);
      }
      printf("\n");
    }
  }

