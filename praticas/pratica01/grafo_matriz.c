#include <stdio.h>
#include <string.h>
#include "grafo_matriz.h"

void inicializar(GrafoMatriz *grafo, int numero) {
    grafo->num_vertices = numero;
    for (int i = 0; i < numero; i++) {
        for (int j = 0; j < numero; j++) {
            grafo->adjacencia[i][j] = 0;
        }
    }
}

void inserir_aresta(GrafoMatriz *grafo, int u, int v) {
    if (u >= 0 && u < grafo->num_vertices && v >= 0 && v < grafo->num_vertices) {
        grafo->adjacencia[u][v] = 1;
        grafo->adjacencia[v][u] = 1; // Descomentado para grafos não-orientados
    }
}

void inserir_arco(GrafoMatriz *grafo, int u, int v) {
    if (u >= 0 && u < grafo->num_vertices && v >= 0 && v < grafo->num_vertices) {
        grafo->adjacencia[u][v] = 1; // Para grafos orientados (arcos)
    }
}

void exibir_matriz(GrafoMatriz *grafo) {
    for (int i = 0; i < grafo->num_vertices; i++) {
        for (int j = 0; j < grafo->num_vertices; j++) {
            printf("%3d", grafo->adjacencia[i][j]);
        }
        printf("\n");
    }
}