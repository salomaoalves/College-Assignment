#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "in_grafo.h"
#include "Grafo.h"

#ifdef __unix__
    #define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
#endif


Grafo* le_grafo(char *arquivo) {
    char temp1[9], temp2[9];
    FILE *f;
    int vertices_ = 0, linhas_ = 0;
    if((f = fopen(arquivo, "r")) == NULL)
        return NULL;
    int linhas;
    int vertices = conta_vertices(f, &linhas);
    Grafo *g = cria_grafo(vertices);
    if(f == NULL || g == NULL)
        return NULL;
    while(fscanf(f, "%s", temp1) != EOF){
        fscanf(f, "%s", temp2);
        if(!contem_vertice(g, atoi(temp1))){
            insere_vertice(g, atoi(temp1));
            gotoxy(0, 2);
            printf("Inserindo vertices: %d/%d", ++vertices_, vertices);
        }
        if(!contem_vertice(g, atoi(temp2))){
            insere_vertice(g, atoi(temp2));
            gotoxy(0, 2);
            printf("Inserindo vertices: %d/%d", ++vertices_, vertices);
        }
        insere_aresta(g, atoi(temp1), atoi(temp2));
        gotoxy(0,3);
        printf("Processando linha: %d/%d\n", ++linhas_, linhas);
    }
    fclose(f);
    return g;
}

int conta_vertices(FILE *f, int *arestas) {
    int total = 0, *lidos, arestas_ = 0;
    lidos = (int*) malloc(sizeof(int));
    char temp[9];
    fpos_t ponteiro;
    fgetpos(f, &ponteiro); // Salva a posição do ponteiro do arquivo
    rewind(f); // Coloca o ponteiro do arquivo no início
    while(fscanf(f, "%s", temp) != EOF) {
        if(!contem(lidos, atoi(temp), total)){
            insere(&lidos, atoi(temp), &total);
            gotoxy(0, 2);
            printf("Contando vertices: 0/%d", total);
        }
        if(fscanf(f, "%s", temp) == EOF){
            printf("Erro(conta_vertices): esperado um segundo vertice na linha %d\n", total + 1);
            return -1;
        }
        if(!contem(lidos, atoi(temp), total)){
            insere(&lidos, atoi(temp), &total);
            gotoxy(0, 2);
            printf("Contando vertices: 0/%d", total);
        }
        gotoxy(0, 3);
        printf("Contando linhas: 0/%d", ++arestas_);
    }
    printf("\n");
    fsetpos(f, &ponteiro); // Retorna o ponteiro do arquivo à posição salva
    *arestas = arestas_;
    return total;
}

int contem(int *vetor, int elemento, int tamanho) {
    int i;
    for(i = 0; i < tamanho; i++) {
        if(elemento == vetor[i]) {
            return 1;
        }
    }
    return 0;
}

void insere(int **vetor, int elemento, int *tamanho) {
    int i = 0, *temp;
    temp = (int*) malloc((*tamanho + 1) * sizeof(int));
    for(i = 0; i < *tamanho; i++) {
        temp[i] = (*vetor)[i];
    }
    temp[i] = elemento;
    free((*vetor));
    (*vetor) = temp;
    (*tamanho)++;
}

// Cria um arquivo com uma porcentagem do grafo f, valores de 0-100
void porcentagem_grafo(char *nome, float porcentagem) {
    char temp[100];
    FILE *f = fopen(nome, "r");
    if(f == NULL) {
        return;
    }
    int p = (porcentagem/100.0) * conta_linhas(f), i;
    FILE *n = fopen(strcat(nome,".rdz"), "w+");
    printf("%d\n", p);
    for(i = 0; i < p; i++) {
        fgets(temp, 100, f);
        fprintf(n, "%s", temp);
    }
    printf("ok\n");
    fclose(n);
}

int conta_linhas(FILE *f) {
    int n = 0;
    fpos_t ponteiro;
    fgetpos(f, &ponteiro); // Salva a posição do ponteiro do arquivo
    rewind(f); // Coloca o ponteiro do arquivo no início
    while(!feof(f))
        if(fgetc(f) == '\n')
            n++;
    fsetpos(f, &ponteiro); // Retorna o ponteiro do arquivo à posição salva
    return n;
}
