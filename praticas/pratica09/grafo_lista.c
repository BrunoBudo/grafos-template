#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista* criar_grafo_lista(int n) {
    GrafoLista *g = malloc(sizeof(GrafoLista));
    g->n = n;
    g->adj = malloc(n * sizeof(No*));
    for (int i = 0; i < n; i++) g->adj[i] = NULL;
    return g;
}

void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    No *novo = malloc(sizeof(No));
    novo->destino = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;
}

void remover_aresta_lista(GrafoLista *g, int u, int v) {
    No *atual = g->adj[u], *anterior = NULL;
    while (atual != NULL) {
        if (atual->destino == v) {
            if (anterior == NULL) g->adj[u] = atual->prox;
            else anterior->prox = atual->prox;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

int grau_lista(GrafoLista *g, int u) {
    int grau = 0;
    for (No *atual = g->adj[u]; atual != NULL; atual = atual->prox) grau++;
    return grau;
}

int sao_adjacentes_lista(GrafoLista *g, int u, int v) {
    for (No *atual = g->adj[u]; atual != NULL; atual = atual->prox)
        if (atual->destino == v) return 1;
    return 0;
}

void liberar_grafo_lista(GrafoLista *g) {
    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];
        while (atual != NULL) {
            No *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

void exibir_lista(GrafoLista *g) {
    for (int i = 0; i < g->n; i++) {
        printf("%d:", i);
        for (No *atual = g->adj[i]; atual != NULL; atual = atual->prox)
            printf(" -> %d", atual->destino);
        printf("\n");
    }
}