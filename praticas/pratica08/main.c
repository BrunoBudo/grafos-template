// main.c
#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista_ponderado.h"
#include "agm.h"

int main() {
    int n = 5;

    // --- Kruskal: trabalha direto com array de arestas ---
    Aresta arestas[] = {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5}, {2,4,7}, {3,4,9}
    };
    int num_arestas = sizeof(arestas) / sizeof(arestas[0]);

    int num_sel_k, peso_k;
    Aresta *mst_kruskal = kruskal(arestas, num_arestas, n, &num_sel_k, &peso_k);
    printf("--- Kruskal ---\nPeso total: %d\n", peso_k); // Esperado: 16
    for (int i = 0; i < num_sel_k; i++)
        printf("(%d, %d) peso %d\n", mst_kruskal[i].u, mst_kruskal[i].v, mst_kruskal[i].peso);
    free(mst_kruskal);

    // --- Prim: trabalha com GrafoListaPonderado (precisa das duas direções) ---
    GrafoListaPonderado *g = criar_grafo_lista_ponderado(n);
    inserir_aresta_ponderada(g, 0, 1, 2); inserir_aresta_ponderada(g, 1, 0, 2);
    inserir_aresta_ponderada(g, 0, 3, 6); inserir_aresta_ponderada(g, 3, 0, 6);
    inserir_aresta_ponderada(g, 1, 2, 3); inserir_aresta_ponderada(g, 2, 1, 3);
    inserir_aresta_ponderada(g, 1, 3, 8); inserir_aresta_ponderada(g, 3, 1, 8);
    inserir_aresta_ponderada(g, 1, 4, 5); inserir_aresta_ponderada(g, 4, 1, 5);
    inserir_aresta_ponderada(g, 2, 4, 7); inserir_aresta_ponderada(g, 4, 2, 7);
    inserir_aresta_ponderada(g, 3, 4, 9); inserir_aresta_ponderada(g, 4, 3, 9);

    int num_sel_p, peso_p;
    Aresta *mst_prim = prim(g, 0, &num_sel_p, &peso_p);
    printf("\n--- Prim ---\nPeso total: %d\n", peso_p); // Esperado: 16 (mesma MST)
    for (int i = 0; i < num_sel_p; i++)
        printf("(%d, %d) peso %d\n", mst_prim[i].u, mst_prim[i].v, mst_prim[i].peso);
    free(mst_prim);

    liberar_grafo_lista_ponderado(g);
    return 0;
}