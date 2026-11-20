// grafo_lista_ponderado.c
#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista_ponderado.h"

GrafoListaPonderado* criar_grafo_lista_ponderado(int n) {
    GrafoListaPonderado *g = malloc(sizeof(GrafoListaPonderado));
    g->n = n;
    g->adj = malloc(n * sizeof(NoPonderado*));
    for (int i = 0; i < n; i++) g->adj[i] = NULL;
    return g;
}

void inserir_aresta_ponderada(GrafoListaPonderado *g, int u, int v, int peso) {
    NoPonderado *novo = malloc(sizeof(NoPonderado));
    novo->destino = v;
    novo->peso = peso;
    novo->prox = g->adj[u];
    g->adj[u] = novo;
}

void liberar_grafo_lista_ponderado(GrafoListaPonderado *g) {
    for (int i = 0; i < g->n; i++) {
        NoPonderado *atual = g->adj[i];
        while (atual != NULL) {
            NoPonderado *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

void exibir_lista_ponderada(GrafoListaPonderado *g) {
    for (int i = 0; i < g->n; i++) {
        printf("%d:", i);
        for (NoPonderado *atual = g->adj[i]; atual != NULL; atual = atual->prox)
            printf(" -> %d(%d)", atual->destino, atual->peso);
        printf("\n");
    }
}