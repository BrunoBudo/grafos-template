// agm.h
#ifndef AGM_H
#define AGM_H
#include "grafo_lista_ponderado.h"

#define INFINITO_PRIM 999999

typedef struct {
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

void dsu_criar(DSU *d, int n);
int find(DSU *d, int x);
void unir(DSU *d, int x, int y);
void dsu_liberar(DSU *d);

Aresta* kruskal(Aresta *arestas, int num_arestas, int n, int *num_selecionadas, int *peso_total);
Aresta* prim(GrafoListaPonderado *g, int origem, int *num_selecionadas, int *peso_total);

#endif