#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista_ponderado.h"
#include "dijkstra.h"

int main() {
    // TODO 1: escolha o número de vértices do seu grafo de teste
    // (sugestão: 5 ou 6 vértices, com pesos variados e positivos)
    int n = 5;
    GrafoListaPonderado *g = criar_grafo_lista_ponderado(n);

    inserir_aresta_ponderada(g, 0, 1, 4); inserir_aresta_ponderada(g, 1, 0, 4);
    inserir_aresta_ponderada(g, 0, 2, 1); inserir_aresta_ponderada(g, 2, 0, 1);
    inserir_aresta_ponderada(g, 2, 1, 2); inserir_aresta_ponderada(g, 1, 2, 2);
    inserir_aresta_ponderada(g, 1, 3, 1); inserir_aresta_ponderada(g, 3, 1, 1);
    inserir_aresta_ponderada(g, 2, 3, 5); inserir_aresta_ponderada(g, 3, 2, 5);
    inserir_aresta_ponderada(g, 3, 4, 3); inserir_aresta_ponderada(g, 4, 3, 3);

    int origem = 0;
    int *dist = malloc(n * sizeof(int));
    int *pred = malloc(n * sizeof(int));

    dijkstra(g, origem, dist, pred);

     for (int i = 0; i < n; i++) {
        printf("dist[%d] = %d\n", i, dist[i]);
    }

    printf("\n");
    int destino = 2;
    reconstruir_caminho(origem, destino, pred);

    free(dist);
    free(pred);
    liberar_grafo_lista_ponderado(g);
    return 0;
}