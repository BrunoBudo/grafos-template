#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "dag.h"

int main() {
    // Criando um grafo com 6 vértices (0 a 5)
    int n = 6;
    GrafoLista *g = criar_grafo_lista(n);

    // Adicionando arestas para formar um DAG (ex: tarefas com dependências)
    // 5 -> 2, 5 -> 0
    // 4 -> 0, 4 -> 1
    // 2 -> 3
    // 3 -> 1
    inserir_aresta_lista(g, 5, 2);
    inserir_aresta_lista(g, 5, 0);
    inserir_aresta_lista(g, 4, 0);
    inserir_aresta_lista(g, 4, 1);
    inserir_aresta_lista(g, 2, 3);
    inserir_aresta_lista(g, 3, 1);

    printf("--- Estrutura do Grafo (Lista de Adjacencia) ---\n");
    exibir_lista(g);
    printf("\n");

    // Testando se é DAG
    if (eh_dag(g)) {
        printf("O grafo e um DAG (Directed Acyclic Graph).\n\n");
    } else {
        printf("O grafo NAO e um DAG (contem ciclo).\n\n");
    }

    int tamanho = 0;

    // Testando Ordenação Topológica por Kahn
    int *ordem_kahn = ordenacao_topologica_kahn(g, &tamanho);
    if (ordem_kahn != NULL) {
        printf("Ordenacao Topologica (Kahn): ");
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", ordem_kahn[i]);
        }
        printf("\n");
        free(ordem_kahn);
    } else {
        printf("Ordenacao Topologica (Kahn): Falha (Ciclo detectado)\n");
    }

    // Testando Ordenação Topológica por DFS
    int *ordem_dfs = ordenacao_topologica_dfs(g, &tamanho);
    if (ordem_dfs != NULL) {
        printf("Ordenacao Topologica (DFS):  ");
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", ordem_dfs[i]);
        }
        printf("\n");
        free(ordem_dfs);
    } else {
        printf("Ordenacao Topologica (DFS):  Falha (Ciclo detectado)\n");
    }

    // Liberando memória do grafo
    liberar_grafo_lista(g);

    return 0;
}