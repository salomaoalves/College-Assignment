//LISTA DE ADJACENCIA
/*bom quando tem poucas aresta e mts vertices*/

struct grafo{
    int eh_ponderado;//determina se eh ponderado
    int nro_vert;
    int grau_max;//max de aresta por vert
    int **arestas;//essa e a debaixo sao array de listas
    float **pesos//para grafos ponderados
    int *grau;//array dos grau de cada vert
};

Grafo *cria_grafo(int nro_vert, int grau_max, int eh_ponderado){
    Grafo *g = (Grafo*) malloc(sizeof(struct grafo));
    if(g != NULL){
        int i;
        g->nro_vert = nro_vert;//define a qtd de vert
        g->grau_max = grau_max;//define o tamanho da lista dos elementos de arestas e pesos
        g->eh_ponderado = (eh_ponderado != 0)?1:0;//define sera ou n ponderado
        g->grau = (int*) calloc(nro_vert,sizeof(int));//aloca espaço para o vetor dos graus
        g->arestas = (int**) malloc(nro_vert*sizeof(int*));     /*aloca espaço para um*/
        for(i=0 ; i<nro_vert ; i++)                             /*array, onde cada elementos*/
            g->aresta[i] = (int*) malloc(grau_max*sizeof(int)); /*seu é uma lista*/
        if(g->eh_ponderado){//caso seja ponderado
            g->pesos = (float**) malloc(nro_vert*sizeof(float*));      /*faz a msm*/
            for(i=0 ; i<nro_vert ; i++)                                /*coisa q o*/
                g->pesos[i] = (float*) malloc(grau_max*sizeof(float)); /*g->arestas*/
        }    /*o grau_max define o tamanho da lista de cada elemento*/
    }
    return g;
}

void libera_grafo(Grafo *g){
    if(g != NULL){
        int i;
        for(i=0 ; i<g->nro_vert ; i++)//liberas a matriz arestas
            free(g->arestas[i]);
        free(g->arestas);
        if(g->eh_ponderado){
            for(i=0 ; i<g->nro_vert ; i++)//libera a matriz pesos
                free(g->pesos[i]);
            free(g->pesos);
        }
        free(g->grau);
        free(g);
    }
}

int insere_aresta(Grafo *g, int orig, int dest, int eh_digrafo, float peso){
    if(g == NULL)
        return 0;
    if(orig <0 || orig >= g->nro_vert)
        return 0;
    if(dest < 0 || dest >= g->nro_vert)
        return 0;
    //o "g->grau[orig]" define em qual elemento da lista q vai por a aresta/peso
    //insere smp no final da linha
    g->arestas[orig][g->grau[orig]] = dest;
    if(g->eh_ponderado)
        g->pesos[orig][g->grau[orig]] = peso;
    g->grau[orig]++;

    if(eh_digrafo == 0)//insere outra aresta se n for digrafo(orientado)
        insere_aresta(g,dest,orig,1,peso);
    return 1;
}

int remove_aresta(Grafo *g, int orig, int dest, int eh_digrafo){
    if(g == NULL)
        return 0;
    if(orig <0 || orig >= g->nro_vert)
        return 0;
    if(dest < 0 || dest >= g->nro_vert)
        return 0;

    int i=0;
    while(i<g->grau[orig] && g->arestas[orig][i] != dest)//acha a pos da aresta na fila
        i++;
    if(i == g->grau[orig])//pos do vert no elemento orig n encontrado
        return 0;
    g->grau[orig]--;//diminui o grau do vert
    g->arestas[orig][i] = g->arestas[orig][g->grau[orig]];/*remove a aresta*/
    if(g->eh_ponderado)//se for ponderado                 /*desejada e no lugar*/
        f->pesos[orig][i] = g->pesos[orig][g->grau[orig]];/*dela, poe a ultima aresta*/
    if(eh_digrafo == 0)//se n for digrafo, remove a outra aresta
        remove_aresta(g,dest,orig,1);
    return 1;
}

int verifica_aresta(Grafo *g, int v1, int v2){
    if(g == NULL)
        return 0;
    if(v1 <0 || v1 >= g->nro_vert)
        return 0;
    if(v2 < 0 || v2 >= g->nro_vert)
        return 0;

    for(i=0 ; i<g->grau[v1] ; i++){
        if(g->aresta[v1][i] == v2)
            return 1;
    }
    return 0;
}
