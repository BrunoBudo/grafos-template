#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "grafo_lista_ponderado.h"

#define INFINITO_DIJKSTRA 999999

typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

MinHeap* criar_min_heap(int capacidade);
NoHeap extrair_minimo(MinHeap *h);
void diminuir_chave(MinHeap *h, int vertice, int nova_distancia);
void liberar_min_heap(MinHeap *h);

int dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif