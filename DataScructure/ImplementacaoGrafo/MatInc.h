#ifndef MATINC_H_INCLUDED
#define MATINC_H_INCLUDED

typedef struct grafoInc GrafoInc;

GrafoInc *cria_grafoInc(int nro_vert, int nro_are);
int insereArestaDirInc(GrafoInc* G,int vert_che, int vert_sai, int nro_are, int p);
int removeArestaDirInc(GrafoInc* G, int vert_che, int vert_sai, int nro_are);
void consultaArestaDirInc(GrafoInc* G, int nro_are);
int insereArestaInc(GrafoInc* G,int v1, int v2, int nro_are, int p);
int removeArestaInc(GrafoInc* G, int v1, int v2, int nro_are);
void consultaArestaInc(GrafoInc* G, int nro_are);
void grauVertInc(GrafoInc* G,int v);
void liberaGrafoInc(GrafoInc* G);
void mostraAdjInc(GrafoInc* G, int v);
void imprimeGrafoInc(GrafoInc* G);

#endif // MATINC_H_INCLUDED
