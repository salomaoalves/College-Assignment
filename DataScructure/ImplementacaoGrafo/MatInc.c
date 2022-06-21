#include <stdio.h>
#include <stdlib.h>
#include "MatInc.h"
struct grafoInc{
    int qtd_vert, qtd_arestas;
    int *grau/*vetor dos graus dos vert*/, **arestas/*matriz de adj*/;
};

GrafoInc *cria_grafoInc(int nro_vert, int nro_are){
    int i,j,k;
    if (nro_vert <= 0 || nro_are <= 0)
        return NULL;

    GrafoInc* G = (GrafoInc*) malloc(sizeof(GrafoInc));
    if(G == NULL)
        return NULL;

    G->qtd_vert = nro_vert;
    G->qtd_arestas = nro_are;

    G->grau = (int*) calloc(nro_vert,sizeof(int));
    if(G->grau == NULL){
        free(G);
        return NULL;
    }

    G->arestas = (int**) calloc(nro_are,sizeof(int*));//as arestas sao as colunas
    if(G->arestas == NULL){
        free(G->grau);
        free(G);
        return NULL;
    }
    for(i=0;i<nro_vert;i++){
        G->arestas[i] = (int*) calloc(nro_vert,sizeof(int));//os vertices sao as linhas
        if(G->arestas[i] == NULL)
            for(k=0;k<i;k++){
                free(G->arestas);
                free(G->grau);
                return NULL;
            }
    }

    for(i=0;i<nro_vert;i++){//anda pelas linhas
        for(j=0;j<nro_are;j++){//anda pelas colunas
            G->arestas[i][j] = 0;
        }
    }

    return G;
}

/*FUNCOES PARA GRAFOS DIRECIONADOS*/
int insereArestaDirInc(GrafoInc* G,int vert_che, int vert_sai, int nro_are, int p){
    if(G == NULL || vert_che < 0 || vert_sai < 0 || nro_are < 0)
        return -1;

    if(G->arestas[vert_che][nro_are] != 0 && G->arestas[vert_sai][nro_are] != 0)
        return -1;

    G->arestas[vert_sai][nro_are] = p;
    G->arestas[vert_che][nro_are] = -1*p;
    G->grau[vert_che]++;
    G->grau[vert_sai]++;

    return 1;
}

int removeArestaDirInc(GrafoInc* G, int vert_che, int vert_sai, int nro_are){
    if(G == NULL || vert_che < 0 || vert_sai < 0 || nro_are < 0)
        return -1;

    if(G->arestas[vert_che][nro_are] == 0 && G->arestas[vert_sai][nro_are] == 0)
        return -1;

    G->arestas[vert_che][nro_are] = 0;
    G->arestas[vert_sai][nro_are] = 0;
    G->grau[vert_che]--;
    G->grau[vert_sai]--;

    return 1;
}

void consultaArestaDirInc(GrafoInc* G, int nro_are){
    if(G == NULL || nro_are < 0)
        return;

    int i,vert_sai,vert_che,existe;
    for(i=0;i<G->qtd_vert;i++){
        if(G->arestas[i][nro_are] != 0){
            existe=1;
            if(G->arestas[i][nro_are] <= 0)
                vert_che = i;
            else
                vert_sai = i;
        }
    }
    if(existe == 1)
        printf("A aresta %d sai do vertice %d e chega no vertice %d e tem peso %d\n",nro_are,vert_sai,vert_che,G->arestas[vert_sai][nro_are]);
    else
        printf("Nao existe aresta %d\n",nro_are);
}

/*FUNCOES PARA GRAFOS NAO DIRECIONADOS*/
int insereArestaInc(GrafoInc* G,int v1, int v2, int nro_are, int p){
    if(G == NULL || v1 < 0 || v2 < 0 || nro_are < 0)
        return -1;

    if(G->arestas[v1][nro_are] != 0 && G->arestas[v2][nro_are] != 0)
        return -1;

    G->arestas[v1][nro_are] = p;
    G->arestas[v2][nro_are] = p;
    G->grau[v1]++;
    G->grau[v2]++;

    return 1;
}

int removeArestaInc(GrafoInc* G, int v1, int v2, int nro_are){
    if(G == NULL || v1 < 0 || v2 < 0 || nro_are < 0)
        return -1;

    if(G->arestas[v1][nro_are] == 0 && G->arestas[v2][nro_are] == 0)
        return -1;

    G->arestas[v1][nro_are] = 0;
    G->arestas[v2][nro_are] = 0;
    G->grau[v1]--;
    G->grau[v2]--;

    return 1;
}

void consultaArestaInc(GrafoInc* G, int nro_are){
    if(G == NULL || nro_are < 0)
        return;

    int i,vert[2],k=0;
    for(i=0;i<G->qtd_vert;i++){
        if(G->arestas[i][nro_are] != 0){
            vert[k] = i;
            k++;
        }
    }
    if(k==0)
        printf("Nao existe aresta %d\n",nro_are);
    else
        printf("A aresta %d liga os vertices %d e %d e tem peso %d\n",nro_are,vert[0],vert[1],G->arestas[vert[0]][nro_are]);
}

/*FUNCOES QUE VALEM PARA GRAFOS DIRECIONADOS E NAO DIRECIONADOS*/

void liberaGrafoInc(GrafoInc* G){
    if(G == NULL)
        return NULL;

    int i;
    for(i=0;i<G->qtd_arestas;i++)
        free(G->arestas[i]);

    free(G->arestas);
    free(G->grau);
    free(G);
}

void mostraAdjInc(GrafoInc* G, int v){
    if(G == NULL)
        return;

    printf("Sao adjacentes de %d: ",v);

    int c,l;
    for(c=0;c<G->qtd_arestas;c++){/*decobre qual aresta*/
        if(G->arestas[v][c] > 0){ /*liga o vert ao seu adj*/
            for(l=0;l<G->qtd_vert;l++){
                if(v != l && G->arestas[l][c] < 0){     /*descobre os*/
                    printf("%d com a aresta %d\n",l,c); /*vert adj e printa*/
                }
            }
        }
    }
    printf("\n");
}

void grauVertInc(GrafoInc* G,int v){
    if(G == NULL)
        return;

    printf("O vertice %d tem grau %d",v,G->grau[v]);
}

void imprimeGrafoInc(GrafoInc* G){
    if(G == NULL)
        return NULL;

    int i,j,k;
    for(i=-1;i<G->qtd_vert;i++){
        for(j=-1;j<G->qtd_arestas;j++){
            if(i == -1 && j == -1)
                printf("       ");
            if(i == -1 && j != -1)
                printf("  A%d ",j);
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
