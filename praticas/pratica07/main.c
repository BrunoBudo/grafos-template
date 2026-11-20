// main.c
#include <stdio.h>
#include "grafo_lista_ponderado.h"
#include "bellman_ford.h"

int main() {
    // Teste 1: grafo clássico sem ciclo negativo (CLRS)
    int n1 = 5;
    GrafoListaPonderado *g1 = criar_grafo_lista_ponderado(n1);
    inserir_aresta_ponderada(g1, 0, 1, 6);
    inserir_aresta_ponderada(g1, 0, 3, 7);
    inserir_aresta_ponderada(g1, 1, 2, 5);
    inserir_aresta_ponderada(g1, 1, 3, 8);
    inserir_aresta_ponderada(g1, 1, 4, -4);
    inserir_aresta_ponderada(g1, 2, 1, -2);
    inserir_aresta_ponderada(g1, 3, 2, -3);
    inserir_aresta_ponderada(g1, 3, 4, 9);
    inserir_aresta_ponderada(g1, 4, 0, 2);
    inserir_aresta_ponderada(g1, 4, 2, 7);

    int dist1[5], pred1[5];
    printf("--- Teste 1: sem ciclo negativo ---\n");
    if (bellman_ford(g1, 0, dist1, pred1)) {
        for (int i = 0; i < n1; i++) printf("dist[%d] = %d\n", i, dist1[i]);
        // Esperado: 0, 2, 4, 7, -2
    }
    liberar_grafo_lista_ponderado(g1);

    // Teste 2: ciclo negativo simples (0->1->2->0, soma = -1)
    int n2 = 3;
    GrafoListaPonderado *g2 = criar_grafo_lista_ponderado(n2);
    inserir_aresta_ponderada(g2, 0, 1, 1);
    inserir_aresta_ponderada(g2, 1, 2, -1);
    inserir_aresta_ponderada(g2, 2, 0, -1);

    int dist2[3], pred2[3];
    printf("\n--- Teste 2: com ciclo negativo ---\n");
    if (!bellman_ford(g2, 0, dist2, pred2)) {
        printf("(detectado corretamente acima)\n");
    }
    liberar_grafo_lista_ponderado(g2);

    return 0;
}