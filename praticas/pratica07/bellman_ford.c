// bellman_ford.c
#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int n = g->n;

    for (int i = 0; i < n; i++) {
        dist[i] = INFINITO;
        pred[i] = -1;
    }
    dist[origem] = 0;

    for (int iter = 0; iter < n - 1; iter++) {
        for (int u = 0; u < n; u++) {
            for (NoPonderado *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
                int v = atual->destino, peso = atual->peso;
                if (dist[u] != INFINITO && dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                }
            }
        }
    }

    // rodada extra: detecta ciclo negativo
    for (int u = 0; u < n; u++) {
        for (NoPonderado *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
            int v = atual->destino, peso = atual->peso;
            if (dist[u] != INFINITO && dist[u] + peso < dist[v]) {
                reconstruir_ciclo_negativo(g, pred, n, v);
                return 0;
            }
        }
    }

    return 1;
}

void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *pred, int n, int inicio) {
    (void)g;
    int v = inicio;
    for (int i = 0; i < n; i++) v = pred[v]; // garante cair dentro do ciclo

    int *ciclo = malloc((n + 1) * sizeof(int));
    int tamanho = 0;
    int atual = v;
    do {
        ciclo[tamanho++] = atual;
        atual = pred[atual];
    } while (atual != v);
    ciclo[tamanho++] = v;

    printf("Ciclo negativo: ");
    for (int i = tamanho - 1; i >= 0; i--) {
        printf("%d", ciclo[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");

    free(ciclo);
}