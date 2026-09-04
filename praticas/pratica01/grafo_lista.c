#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

No* criar_no(int destino) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo) {
        novo->destino = destino;
        novo->prox = NULL;
    }
    return novo;
}

GrafoLista* criar_grafo_lista(int n) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    if (!g) return NULL;
    
    g->n = n;
    g->adj = (No**) malloc(n * sizeof(No*));
    
    for (int i = 0; i < n; i++) {
        g->adj[i] = NULL;
    }
    
    return g;
}


void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    if (!g || u < 0 || u >= g->n || v < 0 || v >= g->n) return;

    
    No *novo_v = criar_no(v);
    if (g->adj[u] == NULL) {
        g->adj[u] = novo_v;
    } else {
        No *atual = g->adj[u];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_v;
    }

    
    No *novo_u = criar_no(u);
    if (g->adj[v] == NULL) {
        g->adj[v] = novo_u;
    } else {
        No *atual = g->adj[v];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo_u;
    }
}

void remover_aresta_lista(GrafoLista *g, int u, int v) {
    if (!g || u < 0 || u >= g->n || v < 0 || v >= g->n) return;

    
    No *atual = g->adj[u];
    No *anterior = NULL;
    while (atual != NULL && atual->destino != v) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual != NULL) {
        if (anterior == NULL) g->adj[u] = atual->prox;
        else anterior->prox = atual->prox;
        free(atual);
    }

    
    atual = g->adj[v];
    anterior = NULL;
    while (atual != NULL && atual->destino != u) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual != NULL) {
        if (anterior == NULL) g->adj[v] = atual->prox;
        else anterior->prox = atual->prox;
        free(atual);
    }
}

int grau_lista(GrafoLista *g, int u) {
    if (!g || u < 0 || u >= g->n) return -1;
    
    int grau = 0;
    No *atual = g->adj[u];
    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }
    return grau;
}

int sao_adjacentes_lista(GrafoLista *g, int u, int v) {
    if (!g || u < 0 || u >= g->n || v < 0 || v >= g->n) return 0;
    
    No *atual = g->adj[u];
    while (atual != NULL) {
        if (atual->destino == v) return 1;
        atual = atual->prox;
    }
    return 0;
}

void liberar_grafo_lista(GrafoLista *g) {
    if (!g) return;
    
    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}

// Imprime a lista exatamente no formato do exemplo da imagem
void exibir_lista(GrafoLista *g) {
    if (!g) return;
    for (int i = 0; i < g->n; i++) {
        // Exibe i + 1 para mostrar os vértices como 1, 2, 3, 4
        printf("%d: ", i + 1);
        No *atual = g->adj[i];
        while (atual != NULL) {
            // Exibe atual->destino + 1 para mostrar o destino na base 1
            printf("-> %d ", atual->destino + 1);
            atual = atual->prox;
        }
        printf("-> NULL\n");
    }
}



