#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "coloracao.h"

int main() {
    // Criando um grafo de teste com 4 vértices (ciclo C4: 0-1-2-3-0)
    int n = 4;
    GrafoLista *g = criar_grafo_lista(n);

    // Inserindo arestas bidirecionais
    int arestas[][2] = {
        {0, 1}, {1, 0},
        {1, 2}, {2, 1},
        {2, 3}, {3, 2},
        {3, 0}, {0, 3}
    };

    int num_arestas = sizeof(arestas) / sizeof(arestas[0]);
    for (int i = 0; i < num_arestas; i++) {
        inserir_aresta_lista(g, arestas[i][0], arestas[i][1]);
    }

    printf("--- Estrutura do Grafo (C4) ---\n");
    exibir_lista(g);
    printf("\n");

    // Testando Verificação de Bipartição
    if (eh_bipartido(g)) {
        printf("O grafo e bipartido.\n");
    } else {
        printf("O grafo NAO e bipartido.\n");
    }

    // Testando Coloração Gulosa
    int num_cores_gulosa = 0;
    int *cores_gulosa = coloracao_gulosa(g, &num_cores_gulosa);
    printf("\nColoracao Gulosa (Total de cores: %d):\n", num_cores_gulosa);
    for (int i = 0; i < n; i++) {
        printf("  Vertice %d -> Cor %d\n", i, cores_gulosa[i]);
    }
    free(cores_gulosa);

    // Testando Coloração de Welsh-Powell
    int num_cores_wp = 0;
    int *cores_wp = coloracao_welsh_powell(g, &num_cores_wp);
    printf("\nColoracao Welsh-Powell (Total de cores: %d):\n", num_cores_wp);
    for (int i = 0; i < n; i++) {
        printf("  Vertice %d -> Cor %d\n", i, cores_wp[i]);
    }
    free(cores_wp);

    // Liberando memória
    liberar_grafo_lista(g);

    return 0;
}