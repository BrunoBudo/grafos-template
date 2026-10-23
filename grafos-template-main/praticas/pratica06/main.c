#include <stdio.h>
#include "dijkstra.h"

enum { A, B, C, D, E, F, N };

int main(void) {
    GrafoListaPonderado *g = criar_grafo(N);

    adicionar_aresta(g, A, B, 4);
    adicionar_aresta(g, A, C, 2);
    adicionar_aresta(g, B, C, 1);
    adicionar_aresta(g, B, D, 5);
    adicionar_aresta(g, B, E, 8);
    adicionar_aresta(g, C, D, 4);
    adicionar_aresta(g, C, E, 10);
    adicionar_aresta(g, D, E, 2);
    adicionar_aresta(g, D, F, 1);
    adicionar_aresta(g, E, F, 3);

    int dist[N], pred[N];
    int origem = A;
    dijkstra(g, origem, dist, pred);

    printf("Distancias a partir de %c:\n", 'A' + origem);
    for (int i = 0; i < N; i++) {
        printf("  %c: ", 'A' + i);
        if (dist[i] == INF) printf("INF\n");
        else printf("%d\n", dist[i]);
    }

    printf("\nCaminhos minimos:\n");
    for (int i = 0; i < N; i++) {
        printf("  %c -> %c (custo %d): ", 'A' + origem, 'A' + i, dist[i]);
        reconstruir_caminho(origem, i, pred);
        printf("\n");
    }

    liberar_grafo(g);
    return 0;
}