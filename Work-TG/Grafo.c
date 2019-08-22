#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

#ifdef __unix__
    #define OS                0
    #define gotoxy(x,y)       printf("\033[%d;%dH", (y), (x))
#elif defined(_WIN32) || defined(WIN32)
    #define OS                1
    #include <windows.h>
#endif


struct aresta{
    int vertice;
    struct aresta *prox;
};

struct vertice{
    int id;
    int excentricidade;
    int grau;
    struct aresta *arestas;
};

struct grafo{
    int n_vertice,n_aresta;
    struct vertice **vertices;
};

// Retorna um grafo com um vetor vazio de tamanho n_vertice
Grafo *cria_grafo(int n_vertice){
    if(n_vertice<1)
        return NULL;
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    if(g != NULL){
        g->n_vertice = n_vertice;
        g->n_aresta = 0;
        g->vertices = (Vertice**) calloc(n_vertice,sizeof(Vertice*));
    }
    return g;
}

int insere_vertice(Grafo *g, int v) {
    if(g == NULL)
        return -1;
    int i;
    Vertice *ve = (Vertice*) malloc(sizeof(Vertice));
    ve->id = v;
    ve->grau = 0;
    ve->excentricidade = -1;
    ve->arestas = NULL;
    for(i = 0; i < g->n_vertice; i++) {
        if(g->vertices[i] == NULL)
            break;
    }
    g->vertices[i] = ve;
    return 1;
}

int insere_aresta(Grafo *g,int v1,int v2){
    if(g == NULL || v1 == v2 || verifica_aresta(g, v1, v2))
        return -1;
    Aresta *aux = g->vertices[indice(g,v1)]->arestas;
    Aresta *a = (Aresta*) malloc(sizeof(Aresta));
    a->vertice = v2;
    a->prox = NULL;
    if(aux == NULL)
        g->vertices[indice(g,v1)]->arestas = a;
    else{
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = a;
    }
    (g->vertices[indice(g, v1)]->grau)++;
    if(!verifica_aresta(g, v2, v1)){
        g->n_aresta++;
        insere_aresta(g,v2,v1);
    }
    return 1;
}

// Verifica se a aresta pertence ao grafo
int verifica_aresta(Grafo *g,int v1,int v2){
    if(g == NULL)
        return -1;
    Aresta *aux;
    aux = g->vertices[indice(g, v1)]->arestas;
    while(aux != NULL && aux->vertice != v2){
        aux = aux->prox;
    }
    if(aux == NULL)
        return 0;
    return 1;
}

// int remove_aresta(Grafo *g,int v1,int v2){
//     if(g == NULL || v1<0 || v1>=(g->n_vertice) || v2<0 || v2>=(g->n_vertice))
//         return -1;
//     struct no *aux;
//     struct no *ant;
//     aux = g->aresta[v1];
//     ant = NULL;
//     while(aux != NULL && aux->vertice != v2){
//         ant = aux;
//         aux = aux->prox;
//     }
//     if(aux == NULL)
//         return 0;
//     if(ant == NULL)
//         g->aresta[v1] = aux->prox;
//     else
//         ant->prox = aux->prox;
//     free(aux);
//     g->n_aresta--;
//     g->grau[v1]--;
//     g->grau[v2]--;
//     return 1;
// }

void libera_grafo(Grafo *g){
    int i;
    Aresta *aux,*ant;
    for(i=0;i<g->n_vertice;i++){
        aux = g->vertices[i]->arestas;
        while(aux != NULL){
            ant = aux;
            aux = aux->prox;
            free(ant);
        }
        free(g->vertices[i]);
    }
    free(g->vertices);
    free(g);
}

void mostrar_adjacente(Grafo *g,int v){
    if(g == NULL){
        return;
    }
    Aresta *aux;
    aux = g->vertices[v]->arestas;
    while(aux != NULL){
        printf("|%d|-->",aux->vertice);
        aux = aux->prox;
    }
    printf("NULL\n");
}

void mostrar_grafo(Grafo *g){
    if(g == NULL)
        return;
    int i;
    printf("Grafo:\n");
    for(i=0;i<g->n_vertice;i++){
        if(g->vertices[i] == NULL)
            continue;
        printf("(Vertice %d)-->",g->vertices[i]->id);
        mostrar_adjacente(g, i);
    }
}

int conferirExiste(Grafo *g,int v1,int v2){
    Aresta *aux;
    aux = g->vertices[indice(g,v1)]->arestas;
    while(aux != NULL && aux->vertice != v2){
        aux = aux->prox;
    }
    if(aux == NULL)
        return 0;
    return 1;
}

int get_numverts(Grafo *g) {
    return g->n_vertice;
}

int get_numarestas(Grafo *g) {
    return g->n_aresta;
}

// Recebe o nome do vértice
int get_grau(Grafo *g, int vertice) {
     return g->vertices[indice(g, vertice)]->grau;
}


int get_vert(Grafo *g, int pos) {
    return g->vertices[pos]->id;
}

// Recebe o índice do vértice
int get_excentricidade(Grafo *g, int vert) {
    return g->vertices[vert]->excentricidade;
}

// Recebe o índice do vértice
void set_excentricidade(Grafo *g, int vert, int valor) {
    g->vertices[vert]->excentricidade = valor;
}

int indice(Grafo *g, int vertice) {
    int i;
    for(i = 0; i < g->n_vertice; i++) {
        if(g->vertices[i]->id == vertice){
            return i;
        }
    }
    return -1;
}

int contem_vertice(Grafo *g, int vertice) {
    int i;
    for(i = 0; i < g->n_vertice; i++){
        if(g->vertices[i] == NULL){
            continue;
        }
        if(g->vertices[i]->id == vertice)
            return 1;
    }
    return 0;
}

void busca_largura(Grafo* G,int v, int *visita){
    int vet,ini=0,fin=0,fila[get_numverts(G)];
    //printf("%d",G->vertices[0]->arestas->vertice);
    Aresta *aux;
    visita[v]=1;
    fila[fin] = v;fin++;
    while(ini != fin){
        vet = fila[ini];
        ini++;
        aux = G->vertices[vet]->arestas;
        while(aux != NULL){
            if(visita[indice(G,aux->vertice)] == 0){
                visita[indice(G,aux->vertice)]=1;
                fila[fin]=indice(G,aux->vertice);
                fin++;
            }
            aux = aux->prox;
        }
    }
}

void bubble_sort(Grafo *G,int *v){
    int aux,stop=1,i,j;
    for(i=0;i<get_numverts(G);i++){
        for(j=0;j<(get_numverts(G)-1);j++){
            if(G->vertices[v[j]]->grau < G->vertices[v[j+1]]->grau){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                stop=0;
            }
        }
        if(stop==1)break;
        stop=1;
    }
}

int num_cromatico(Grafo *G,int *v,int *cor){
    int i;
    int n_crom = 0, igual_adj = 0, fim = 0;
    Aresta *aux;
    while(fim == 0){
        fim = 1;
        n_crom++;
        for(i=0; i<get_numverts(G); i++){
            if(cor[v[i]] == -1){
                fim = 0;
                aux = G->vertices[v[i]]->arestas;
                while(aux != NULL){
                    if(cor[indice(G,aux->vertice)] == n_crom){
                        igual_adj = 1;
                        break;
                    }
                    aux = aux->prox;
                }
                if(igual_adj == 0){
                    cor[v[i]] = n_crom;
                }
                igual_adj = 0;
            }
        }
    }
    return n_crom - 1;
}

float agrupamento(Grafo* G, int vert){
    if(G == NULL)
        return -1;
    int i, j, e = 0, k = G->vertices[vert]->grau, adj[k];
    Aresta *aux;
    aux = G->vertices[vert]->arestas;
    for(i=0; i<k; i++){
        adj[i] = aux->vertice;
        aux = aux->prox;
    }
    for(i=0; i<(k-1); i++){
        for(j=(i+1); j<k; j++){
            if(verifica_aresta(G, adj[i], adj[j])==1)e++;
        }
    }
    if(e == 0)
        return 0;
    return (2.0*e)/(k*1.0*(k-1));
}

int caminho(Grafo* G, int vert_i, int vert_f){
    int tam, i, caminhos[get_numverts(G)];
    for(i=0; i<get_numverts(G); i++)caminhos[i] = -1;
    caminhos[0]=vert_i;
    tam = caminhoRecursao(G,vert_f,caminhos,0);
    if(tam == -1) return 0;//Se 'vert_i' n�o tem conectividade com 'vert_f' retorna 0
    return tam;
}

int caminhoRecursao(Grafo* G, int vert_f, int *caminhos, int total){
    int maior = -1, m, i, contido;
    if(caminhos[total] == vert_f)return total;
    Aresta *aux = G->vertices[caminhos[total]]->arestas;
    total++;

    while(aux != NULL){
        contido = 0;
        for(i=0; i<total-1;i++)
            if(caminhos[i]==indice(G,aux->vertice)) contido=1;

        if(contido == 0){
                caminhos[total] = indice(G,aux->vertice);
                m = caminhoRecursao(G,vert_f,caminhos,total);
                if(m > maior)maior = m;
        }
        aux = aux->prox;
    }
    return maior;
}

int caminhoMenor(Grafo *G, int vert_i, int vert_f){
    int i, tam, caminhos[get_numverts(G)];
    for(i=0; i<get_numverts(G); i++)caminhos[i] = -1;
    caminhos[0]=vert_i;
    tam = caminhoMenorRecursao(G,vert_f,caminhos,0);
    if(tam == get_numarestas(G)+1) return 0;//Se 'vert_i' n�o tem conectividade com 'vert_f' retorna 0
    return tam;
}

int caminhoMenorRecursao(Grafo* G, int vert_f, int *caminhos, int total){
    int menor = get_numarestas(G)+1, m, i, contido;
    if(caminhos[total] == vert_f)return total;
    Aresta *aux = G->vertices[caminhos[total]]->arestas;
    total++;

    while(aux != NULL){
        contido = 0;
        for(i=0; i<total-1;i++)
            if(caminhos[i]==indice(G,aux->vertice)) contido=1;

        if(contido == 0){
                caminhos[total] = indice(G,aux->vertice);
                m = caminhoMenorRecursao(G,vert_f,caminhos,total);
                if(m < menor)menor = m;
        }
        aux = aux->prox;
    }
    return menor;
}
