#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

typedef struct grafo Grafo;
typedef struct vertice Vertice;
typedef struct aresta Aresta;

Grafo *cria_grafo(int n_vertice);
int insere_vertice(Grafo *g, int v);
int insere_aresta(Grafo *g,int v1,int v2);
// int remove_aresta(Grafo *g,int v1,int v2);
int verifica_aresta(Grafo *g,int v1,int v2);
int conferirExiste(Grafo *g,int v1,int v2);
void libera_grafo(Grafo *g);
void mostrar_adjacente(Grafo *g,int v);
void mostrar_grafo(Grafo *g);

// Getters e setters
int get_numverts(Grafo *g);
int get_numarestas(Grafo *g);
int get_grau(Grafo *g, int vertice);
int get_vert(Grafo *g, int pos);
int get_excentricidade(Grafo *g, int vert);
void set_excentricidade(Grafo *g, int vert, int valor);

// Utils
int indice(Grafo *g, int vertice);
void busca_largura(Grafo* G,int v, int *visita);
int contem_vertice(Grafo *g, int vertice);
void bubble_sort(Grafo *G,int *v);
int num_cromatico(Grafo *G,int *v,int *cor);
float agrupamento(Grafo* G, int vert);
int caminho(Grafo* G, int vert_i, int vert_f);
int caminhoRecursao(Grafo* G, int vert_f, int *caminhos, int total);
int caminhoMenor(Grafo *G, int vert_i, int vert_f);
int caminhoMenorRecursao(Grafo* G, int vert_f, int *caminhos, int total);

#endif // GRAFO_H_INCLUDED
