#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "conectividade.h"
#include "planaridade.h"

int main() {
    // Criando um grafo com 5 vértices (0 a 4)
    int n = 5;
    GrafoLista *g = criar_grafo_lista(n);

    // Inserindo arestas bidirecionais (grafo não-dirigido)
    int arestas[][2] = {
        {0, 1}, {1, 0},
        {1, 2}, {2, 1},
        {2, 3}, {3, 2},
        {3, 4}, {4, 3},
        {4, 0}, {0, 4},
        {1, 3}, {3, 1}
    };

    int num_arestas = sizeof(arestas) / sizeof(arestas[0]);
    for (int i = 0; i < num_arestas; i++) {
        inserir_aresta_lista(g, arestas[i][0], arestas[i][1]);
    }

    printf("--- Estrutura do Grafo (Lista de Adjacencia) ---\n");
    exibir_lista(g);
    printf("\n");

    // 1. Testando Vértices de Articulação (Tarjan)
    int num_art = 0;
    int *articulacoes = dfs_articulacoes(g, &num_art);
    printf("Vertices de Articulacao (%d encontrados): ", num_art);
    for (int i = 0; i < num_art; i++) {
        printf("%d ", articulacoes[i]);
    }
    printf("\n");
    free(articulacoes);

    // 2. Testando Detecção de Pontes (Tarjan)
    int num_pontes = 0;
    int *pontes = detectar_pontes(g, &num_pontes);
    printf("Pontes do Grafo (%d encontradas):\n", num_pontes);
    for (int i = 0; i < num_pontes; i++) {
        printf("  Aresta ponte: (%d, %d)\n", pontes[i * 2], pontes[i * 2 + 1]);
    }
    free(pontes);

    // 3. Testando Planaridade por Euler (m <= 3n - 6)
    if (eh_planar_euler(g)) {
        printf("\n[Euler] O grafo e potencialmente planar (passou no teste de arestas).\n");
    } else {
        printf("\n[Euler] O grafo NAO e planar (excede o limite de arestas).\n");
    }

    // 4. Testando Presença de K5 ou K3,3 (Kuratowski)
    if (tem_k5_ou_k33(g)) {
        printf("[Kuratowski] O grafo contem subgrafo K5 ou K3,3.\n");
    } else {
        printf("[Kuratowski] Nenhum subgrafo K5 ou K3,3 encontrado.\n");
    }

    // Liberando a memória alocada para o grafo
    liberar_grafo_lista(g);

    return 0;
}