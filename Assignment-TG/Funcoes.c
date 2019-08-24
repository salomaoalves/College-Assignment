#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"
#include "Grafo.h"

#ifdef __unix__
    #define OS                0
    #define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#elif defined(_WIN32) || defined(WIN32)
    #define OS                1
    #include <windows.h>
    void  gotoxy(int x, int y) {
      COORD coord;
      coord.X = x;
      coord.Y = y;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
#endif


int cromatico(Grafo* G){
    if(G == NULL)
        return -1;
    int n_crom, i, cor[get_numverts(G)], v[get_numverts(G)];
    for(i=0; i<get_numverts(G); i++){
        cor[i] = -1;
        v[i] = i;
    }
    bubble_sort(G,v);
    n_crom = num_cromatico(G,v,cor);
    return n_crom;
}

int componentesConexos(Grafo* G){
    if(G == NULL)
        return -1;
    int i, conexo = 0,visita[get_numverts(G)];
    for(i=0;i<get_numverts(G);i++)visita[i]=0;
    for(i=0;i<get_numverts(G);i++){
        if(visita[i]==0){
            busca_largura(G,i,visita);
            conexo++;
        }
    }
    return conexo;
}

float grauMedio(Grafo* G){
    int i, soma = 0;
    float media;
    if(G == NULL)
        return -1;
    for(i=0;i<get_numverts(G);i++){
        soma += get_grau(G, get_vert(G, i));
    }
    media = soma/get_numverts(G);
    return media;
}

float densidade(Grafo* G){
    if(G == NULL)
        return -1;
    return ((double)(2*get_numarestas(G))/(get_numverts(G)*(get_numverts(G)-1)));
}

float agrupamentoMedio(Grafo* G){
    int i, soma = 0;
    if(G == NULL)
        return -1;
    for(i=0;i<get_numverts(G);i++)
        soma += agrupamento(G,i);
    return ((double) soma/get_numverts(G));
}

// Recebe o índice do vértice
int excentricidade(Grafo* G, int vert){
    if(get_excentricidade(G, vert) != -1)
        return get_excentricidade(G, vert);
    int i,var,maior;
    if(G == NULL)
        return -1;

    maior = caminho(G,vert,0);
    for(i=1;i<get_numverts(G);i++){
        if(i!=vert)
            var = caminho(G,vert,i);
        if(var>maior)
            maior = var;
    }
    set_excentricidade(G, vert, maior);
    return maior;
}

float excentricidadeMedia(Grafo* G){
    int i;
    float soma = 0;
    if(G == NULL)
        return -1;
    for(i=0;i<get_numverts(G);i++)
        soma += excentricidade(G,i);
    return soma/get_numverts(G);
}

int diametroEfetivo(Grafo* G){
    int i,var,maior;
    if(G == NULL)
        return -1;
    maior = excentricidade(G,0);
    for(i=1;i<get_numverts(G);i++){
        var = excentricidade(G,i);
        if(var>maior)
            maior = var;
    }
    return maior;
}

int raioEfetivo(Grafo* G){
    int i,var,menor;
    if(G == NULL)
        return -1;
    menor = excentricidade(G,0);
    for(i=1;i<get_numverts(G);i++){
        var = excentricidade(G,i);
        if(var<menor)
            menor = var;
    }
    return menor;
}

float centralidade(Grafo* G, int vert){
    if(G == NULL)
        return -1;
    int i, soma = 0;
    for(i=0;i<get_numverts(G);i++){
        if(i!=vert) soma += caminhoMenor(G,vert,i);
    }
    return 1.0 * (get_numverts(G) - 1) / (1.0 * soma);
}

float centralidadeMedia(Grafo* G){
    int i;
    float soma = 0,media;
    if(G == NULL)
        return -1;
    for(i=0;i<get_numverts(G);i++){
        soma += centralidade(G,i);
    }
    media = soma/get_numverts(G);
    return media;
}

int vertCentral(Grafo* G, int vert){
    int raio;
    if(G == NULL)
        return -1;
    raio = raioEfetivo(G);
    if(excentricidade(G,vert) == raio)
        return 1;
    else
        return 0;
}

float porceVertCentral(Grafo* G){
    int i,cont = 0;
    if(G == NULL)
        return -1;
    for(i=1;i<get_numverts(G);i++){
        if(vertCentral(G,i))
            cont += 1;
    }
    return (cont*1.0)/(get_numverts(G)*1.0);
}

float porcetagemExtremos(Grafo* G){
    int i,cont = 0;
    if(G == NULL)
        return -1;
    for(i=0;i<get_numverts(G);i++){
        if(get_grau(G,get_vert(G,i)) == 1)
            cont += 1;
    }
    return (cont*1.0)/(get_numverts(G)*1.0);
}
