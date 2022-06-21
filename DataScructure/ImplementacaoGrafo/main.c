#include <stdio.h>
#include <stdlib.h>
#include "MatAdj.h"
#include "MatInc.h"

int main(){
    int choice;
    printf("Qual metodo voce deseja usar:\n");
    printf("\t1 - Matriz Adjacencia:\n");
    printf("\t2 - Matriz Incidencia:\n");
    scanf("%d",&choice);
    if(choice == 1)
        matAdj();
    else
        matInc();
}

void matAdj(){
    GrafoAdj* G;
    int continua = 1,type,choice,correto;
    printf("Seu grafo sera direcionado?\n");
    printf("1 para nao e 2 para sim: ");
    scanf("%d",&type);
    while(continua){
        printf("\n\n-----------------------MENU---------------------\n\n");
        printf("1 - Cria grafo\n");
        printf("2 - Insere Aresta\n");
        printf("3 - Remove Aresta\n");
        printf("4 - Mostra vertices adjacentes\n");
        printf("5 - Consultar aresta\n");
        printf("6 - Imprimir a Matriz de Adjacencia do Grafo\n");
        printf("7 - Grau do Vertice\n");
        printf("8 - Sair\n");
        printf("Opcao: ");
        scanf("%d",&choice);
        printf("\n");
        switch(choice){
        case 1://cria grafo
            printf("Qual a quantidade de vertices do seu grafo: ");
            int qtd_vert;
            scanf("%d",&qtd_vert);
            G = cria_grafoAdj(qtd_vert);
            break;
        case 2://insere aresta
            if (type == 1){
                int v1,v2,peso;
                printf("Quais sao vertices: ");
                scanf("%d %d",&v1,&v2);
                printf("Qual o peso da aresta: ");
                scanf("%d",&peso);
                correto = insereArestaAdj(G,v1,v2,peso);
                if(correto)
                    printf("Aresta inserida. \n");
                else
                    printf("Aresta nao foi inserida. \n");
            }else{
                int vert_che, vert_sai,peso;
                printf("Qual o vertice de saida: ");
                scanf("%d",&vert_sai);
                printf("Qual o vertice de chegada: ");
                scanf("%d",&vert_che);
                printf("Qual o peso da aresta: ");
                scanf("%d",&peso);
                correto = insereArestaDirAdj(G,vert_che,vert_sai,peso);
                if(correto)
                    printf("Aresta inserida. \n");
                else
                    printf("Aresta nao foi inserida. \n");
            }
            break;
        case 3://remove aresta
            if (type == 1){
                int v1,v2;
                printf("Quais sao vertices: ");
                scanf("%d %d",&v1,&v2);
                correto = removeArestaAdj(G,v1,v2);
                if(correto)
                    printf("Aresta removida. \n");
                else
                    printf("Aresta nao foi removida. \n");
            }else{
                int vert_che, vert_sai;
                printf("Qual o vertice de saida: ");
                scanf("%d",&vert_sai);
                printf("Qual o vertice de chegada: ");
                scanf("%d",&vert_che);
                correto = removeArestaDirAdj(G,vert_che,vert_sai);
                if(correto)
                    printf("Aresta removida. \n");
                else
                    printf("Aresta nao foi removida. \n");
            }
            break;
        case 4://mostra adj
            printf("Qual vertice: ");
            int v;
            scanf("%d",&v);
            mostraAdjAdj(G,v);
            break;
        case 5://consulta aresta
            printf("Qual o vertice de saida: ");
            int vert_che, vert_sai,are;
            scanf("%d",&vert_sai);
            printf("Qual o vertice de chegada: ");
            scanf("%d",&vert_che);
            are = consultaArestaAdj(G,vert_che,vert_sai);
            if(are == 0)
                printf("A aresta entre os vertices %d e %d nao existe.\n",vert_sai,vert_che);
            else
                printf("A aresta entre os vertices %d e %d existe e tem peso %d.\n",vert_sai,vert_che,are);
            break;
        case 6://imprime grafo
            imprimeGrafoAdj(G);
            break;
        case 7:
            printf("Qual o vertice: ");
            int vert;
            scanf("%d",&vert);
            grauVertAdj(G,vert);
        case 8://sair
            liberaGrafoAdj(G);
            continua = 0;
            break;
        }
    }
}

/*TEM BUGG ESSA POHA*/
void matInc(){
    GrafoInc* G;
    int continua = 1,type,choice,correto;
    printf("Seu grafo sera direcionado?\n");
    printf("1 para nao e 2 para sim: ");
    scanf("%d",&type);
    while(continua){
        printf("\n\n-----------------------MENU---------------------\n\n");
        printf("1 - Cria Grafo\n");
        printf("2 - Insere Aresta\n");
        printf("3 - Remove Aresta\n");
        printf("4 - Mostra Vertices Adjacentes\n");
        printf("5 - Consultar Aresta\n");
        printf("6 - Imprimir a Matriz de Adjacencia do Grafo\n");
        printf("7 - Grau do Vertice\n");
        printf("8 - Sair\n");
        printf("Opcao: ");
        scanf("%d",&choice);
        printf("\n");
        switch(choice){
        case 1://cria grafo
            printf("Qual a quantidade de vertices do seu grafo: ");
            int qtd_vert,qtd_are;
            scanf("%d",&qtd_vert);
            printf("Qual a quantidade de arestas do seu grafo: ");
            scanf("%d",&qtd_are);
            G = cria_grafoInc(qtd_vert,qtd_are);
            break;
        case 2://insere aresta
            if (type == 1){
                int v1,v2,peso,nro_are;
                printf("Quais sao vertices: ");
                scanf("%d %d",&v1,&v2);
                printf("Qual o numero da aresta: ");
                scanf("%d",&nro_are);
                printf("Qual o peso da aresta: ");
                scanf("%d",&peso);
                correto = insereArestaInc(G,v1,v2,nro_are,peso);
                if(correto)
                    printf("Aresta inserida. \n");
                else
                    printf("Aresta nao foi inserida. \n");
            }else{
                int vert_che, vert_sai,peso,nro_are;
                printf("Qual o vertice de saida: ");
                scanf("%d",&vert_sai);
                printf("Qual o vertice de chegada: ");
                scanf("%d",&vert_che);
                printf("Qual o numero da aresta: ");
                scanf("%d",&nro_are);
                printf("Qual o peso da aresta: ");
                scanf("%d",&peso);
                correto = insereArestaDirInc(G,vert_che,vert_sai,nro_are,peso);
                if(correto)
                    printf("Aresta inserida. \n");
                else
                    printf("Aresta nao foi inserida. \n");
            }
            break;
        case 3://remove aresta
            if (type == 1){
                int v1,v2,nro_are;
                printf("Quais sao vertices: ");
                scanf("%d %d",&v1,&v2);
                printf("Qual o numero da aresta: ");
                scanf("%d",&nro_are);
                correto = removeArestaInc(G,v1,v2,nro_are);
                if(correto)
                    printf("Aresta removida. \n");
                else
                    printf("Aresta nao foi removida. \n");
            }else{
                int vert_che, vert_sai,nro_are;
                printf("Qual o vertice de saida: ");
                scanf("%d",&vert_sai);
                printf("Qual o vertice de chegada: ");
                scanf("%d",&vert_che);
                printf("Qual o numero da aresta: ");
                scanf("%d",&nro_are);
                correto = removeArestaDirInc(G,vert_che,vert_sai,nro_are);
                if(correto)
                    printf("Aresta removida. \n");
                else
                    printf("Aresta nao foi removida. \n");
            }
            break;
        case 4://mostrar vert adj
            printf("Qual vertice: ");
            int v;
            scanf("%d",&v);
            mostraAdjInc(G,v);
            break;
        case 5://consulta aresta
            if(type==1){
                printf("Qual o numero da aresta: ");
                int nro_are;
                scanf("%d",&nro_are);
                consultaArestaInc(G,nro_are);
            }else{
                printf("Qual o numero da aresta: ");
                int nro_are;
                scanf("%d",&nro_are);
                consultaArestaDirInc(G,nro_are);
            }
            break;
        case 6://imprime
            imprimeGrafoInc(G);
            break;
        case 7:
            printf("Qual o vertice: ");
            int vert;
            scanf("%d",&vert);
            grauVertInc(G,vert);
            break;
        case 8://sair
            liberaGrafoInc(G);
            continua = 0;
            break;
        }
    }
}

