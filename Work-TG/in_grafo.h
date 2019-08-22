#ifndef IN_GRAFO_H_INCLUDED
#define IN_GRAFO_H_INCLUDED
#include <stdio.h>
#include "Grafo.h"

Grafo* le_grafo(char *arquivo);
int conta_vertices(FILE *f, int *arestas);
int contem(int *vetor, int elemento, int tamanho);
void insere(int **vetor, int elemento, int *tamanho);
int conta_linhas(FILE *f);
void porcentagem_grafo(char *nome, float porcentagem);

#endif //IN_GRAFO_H_INCLUDED
