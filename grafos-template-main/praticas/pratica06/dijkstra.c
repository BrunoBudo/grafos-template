#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

GrafoListaPonderado *criar_grafo(int n) {
    GrafoListaPonderado *g = malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = n;
    g->adj = calloc(n, sizeof(Aresta *));
    resturn g;
}

static void inserir(GrafoListaPonderado *g, int u, int v, int peso) {
    Aresta *a = malloc(sizeof(Aresta));
    a->destino = v;
    a->peso = peso;
    a->prox = g->adj[u];
    g->adj[u] = a;
}

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso) {
    inserir(g, u, v, peso);
    inserir(g, v, u, peso);
}

void liberar_grafo(GrafoListaPonderado *g) {
    for (int i=0; i < g-> num_vertices; i++) {
        Aresta *a = g->adj[i];
        while (a) {
            Aresta *prox = a->prox;
            free(a);
            a = prox;
        }
    }
    free(g->adj);
    free(g);
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int n = g->num_vertices;
    int *visitado = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[origem] = 0;

    for (int iter = 0; iter < n; iter++) {
        /* escolhe o vértice não visitado com menor distância */
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!visitado[i] && dist[i] != INF && (u == -1 || dist[i] < dist[u]))
                u = i;
        }
        if (u == -1) break; /* restantes inalcançáveis */
        visitado[u] = 1;

        /* relaxamento das arestas de u */
        for (Aresta *a = g->adj[u]; a; a = a->prox) {
            if (!visitado[a->destino] && dist[u] + a->peso < dist[a->destino]) {
                dist[a->destino] = dist[u] + a->peso;
                pred[a->destino] = u;
            }
        }
    }
    free(visitado);
}

static void imprimir_rec(int origem, int v, int *pred) {
    if (v == origem) {
        printf("%c", 'A' + v);
        return;
    }
    if (pred[v] == -1) {
        printf("(sem caminho)");
        return;
    }
    imprimir_rec(origem, pred[v], pred);
    printf(" -> %c", 'A' + v);
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    imprimir_rec(origem, destino, pred);
}