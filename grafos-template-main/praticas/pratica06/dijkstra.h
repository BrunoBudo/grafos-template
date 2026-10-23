#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits.h>

#define INF INT_MAX 

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

typedef struct {
    int num_vertices;
    Aresta **adj;
} GrafoListaPonderado;

GrafoListaPonderado *criar_grafo(int n);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);
void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif