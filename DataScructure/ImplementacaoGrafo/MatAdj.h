#ifndef MATADJ_H_INCLUDED
#define MATADJ_H_INCLUDED

typedef struct grafoAdj GrafoAdj;

GrafoAdj *cria_grafoAdj(int nro_vert);
int insereArestaDirAdj(GrafoAdj* G,int vert_che, int vert_sai, int peso);
int removeArestaDirAdj(GrafoAdj* G, int vert_che, int vert_sai);
int insereArestaAdj(GrafoAdj* G,int v1, int v2, int p);
int removeArestaDirAdj(GrafoAdj* G, int v1, int v2);
void liberaGrafoAdj(GrafoAdj* G);
int consultaArestaAdj(GrafoAdj* G, int vert_che, int vert_sai);
void mostraAdjAdj(GrafoAdj* G, int v);
void grauVertAdj(GrafoAdj* G, int v);
void imprimeGrafoAdj(GrafoAdj* G);

#endif // MATADJ_H_INCLUDED
