#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED
#include "Grafo.h"

int cromatico(Grafo* G);
int componentesConexos(Grafo* G);
int caminho(Grafo* G, int vert_sai, int vert_che);
int excentricidade(Grafo* G, int vert);
int diametroEfetivo(Grafo* G);
int raioEfetivo(Grafo* G);
float centralidade(Grafo* G, int vert);
float centralidadeMedia(Grafo* G);
int vertCentral(Grafo* G, int vert);
float grauMedio(Grafo* G);
float densidade(Grafo* G);
float agrupamentoMedio(Grafo* G);
float excentricidadeMedia(Grafo* G);
float centralidadeMedia(Grafo* G);
float porceVertCentral(Grafo* G);
float porcetagemExtremos(Grafo* G);

#endif // FUNCOES_H_INCLUDED
