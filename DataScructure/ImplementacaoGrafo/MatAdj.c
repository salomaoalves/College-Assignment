#include <stdio.h>
#include <stdlib.h>
#include "MatAdj.h"
struct grafoAdj{
    int qtd_vert, qtd_arestas;
    int *grau/*vetor dos graus dos vert*/, **arestas/*matriz de adj*/;
};

GrafoAdj *cria_grafoAdj(int nro_vert){
    int i,j,k;
    if (nro_vert <= 0)
        return NULL;

    GrafoAdj* G = (GrafoAdj*) malloc(sizeof(GrafoAdj));
    if(G == NULL)
        return NULL;

    G->qtd_vert = nro_vert;
    G->qtd_arestas = 0;

    G->grau = (int*) calloc(nro_vert,sizeof(int));
    if(G->grau == NULL){
        free(G);
        return NULL;
    }

    G->arestas = (int**) calloc(nro_vert,sizeof(int*));
    if(G->arestas == NULL){
        free(G->grau);
        free(G);
        return NULL;
    }
    for(i=0;i<nro_vert;i++){
        G->arestas[i] = (int*) calloc(nro_vert,sizeof(int));
        if(G->arestas[i] == NULL)
            for(k=0;k<i;k++){
                free(G->arestas);
                free(G->grau);
                return NULL;
            }
    }

    for(i=0;i<nro_vert;i++){
        for(j=0;j<nro_vert;j++){
            G->arestas[i][j] = 0;
        }
    }

    return G;
}

/*FUNCOES PARA GRAFOS DIRECIONADOS*/
int insereArestaDirAdj(GrafoAdj* G,int vert_che, int vert_sai, int p){
    if(G == NULL || vert_che < 0 || vert_sai < 0)
        return -1;

    if(G->arestas[vert_sai][vert_che] != 0)
        return -1;

    G->arestas[vert_sai][vert_che] = p;
    G->qtd_arestas++;
    G->grau[vert_che]++;
    G->grau[vert_sai]++;

    return 1;
}

int removeArestaDirAdj(GrafoAdj* G, int vert_che, int vert_sai){
    if(G == NULL || vert_che < 0 || vert_sai < 0)
        return -1;

    if(G->arestas[vert_sai][vert_che] == 0)
        return -1;

    G->arestas[vert_sai][vert_che] = 0;
    G->qtd_arestas--;
    G->grau[vert_che]--;
    G->grau[vert_sai]--;

    return 1;
}

/*FUNCOES PARA GRAFOS NAO DIRECIONADOS*/
int insereArestaAdj(GrafoAdj* G,int v1, int v2, int p){
    if(G == NULL || v1 < 0 || v2 < 0)
        return -1;

    if(G->arestas[v1][v2] != 0 && G->arestas[v2][v1] != 0)
        return -1;

    G->arestas[v1][v2] = p;
    G->arestas[v2][v1] = p;
    G->qtd_arestas++;
    G->grau[v1]++;
    G->grau[v2]++;

    return 1;
}

int removeArestaAdj(GrafoAdj* G, int v1, int v2){
    if(G == NULL || v1 < 0 || v2 < 0)
        return -1;

    if(G->arestas[v1][v2] == 0 && G->arestas[v2][v1] == 0)
        return -1;

    G->arestas[v1][v2] = 0;
    G->arestas[v2][v1] = 0;
    G->qtd_arestas--;
    G->grau[v1]--;
    G->grau[v2]--;

    return 1;
}

/*FUNCOES QUE VALEM PARA GRAFOS DIRECIONADOS E NAO DIRECIONADOS*/

void liberaGrafoAdj(GrafoAdj* G){
    if(G == NULL)
        return;

    int i;
    for(i=0;i<G->qtd_vert;i++)
        free(G->arestas[i]);

    free(G->arestas);
    free(G->grau);
    free(G);
}

int consultaArestaAdj(GrafoAdj* G, int vert_che, int vert_sai){
    if(G == NULL || vert_che < 0 || vert_sai < 0)
        return -1;

    if(G->arestas[vert_sai][vert_che] == 0)
        return 0;

    return G->arestas[vert_sai][vert_che];
}

void mostraAdjAdj(GrafoAdj* G, int v){
    if(G == NULL)
        return NULL;

    int i,existe=0;
    printf("Sao adjacentes de %d: ",v);
    for(i=0;i<G->qtd_vert;i++){
        if(G->arestas[v][i] != 0){
            printf("%d ",i);
            existe=1;
        }
    }
    if(existe == 0)
        printf("None");
    printf("\n");
}

void grauVertAdj(GrafoAdj* G, int v){
    if(G == NULL)
        return;
    printf("O vertice %d tem grau %d",v,G->grau[v]);
}

void imprimeGrafoAdj(GrafoAdj* G){
    if(G == NULL)
        return NULL;

    int i,j,k;
    for(i=-1;i<G->qtd_vert;i++){
        for(j=-1;j<G->qtd_vert;j++){
            if(i == -1 && j == -1)
                printf("       ");
            if(i == -1 && j != -1)
                printf("  V%d ",j);
            if(i!=-1){
                if(j==-1)
                    printf("  | V%d |",i);
                else
                    printf("| %d |",G->arestas[i][j]);
            }
        }
        printf("\n");
    }
}
