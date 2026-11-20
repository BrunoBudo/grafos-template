// main.c
#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "grafo_lista_ponderado.h"
#include "hamiltoniano.h"
#include "tsp.h"

int main() {
    // --- Teste 1: Caminho Hamiltoniano ---
    int n1 = 5;
    GrafoLista *g1 = criar_grafo_lista(n1);
    int arestas1[][2] = {{0,1},{1,0},{1,2},{2,1},{2,3},{3,2},{3,4},{4,3},{4,0},{0,4},{0,2},{2,0}};
    int num1 = sizeof(arestas1)/sizeof(arestas1[0]);
    for (int i = 0; i < num1; i++) inserir_aresta_lista(g1, arestas1[i][0], arestas1[i][1]);

    int tam_h;
    int *caminho = encontrar_caminho_hamiltoniano_bt(g1, &tam_h);
    printf("--- Caminho Hamiltoniano ---\n");
    if (caminho != NULL) {
        printf("Caminho encontrado: ");
        for (int i = 0; i < tam_h; i++) printf("%d ", caminho[i]);
        printf("\n");
        free(caminho);
    } else {
        printf("Nao existe caminho hamiltoniano\n");
    }

    // --- Teste 2: TSP ---
    int n2 = 5;
    GrafoListaPonderado *g2 = criar_grafo_lista_ponderado(n2);
    int pesos[5][5] = {
        {0, 2, 9, 10, 7},
        {2, 0, 6, 4, 3},
        {9, 6, 0, 8, 5},
        {10,4, 8, 0, 6},
        {7, 3, 5, 6, 0}
    };
    for (int u = 0; u < n2; u++)
        for (int v = 0; v < n2; v++)
            if (u != v) inserir_aresta_ponderada(g2, u, v, pesos[u][v]);

    int custo_bf, custo_vmp, custo_ins;

    int *ordem_bf = tsp_forca_bruta(g2, 0, &custo_bf);
    printf("\n--- TSP Forca Bruta ---\nCusto: %d\n", custo_bf);
    free(ordem_bf);

    int *ordem_vmp = tsp_vizinho_mais_proximo(g2, 0, &custo_vmp);
    printf("\n--- TSP Vizinho Mais Proximo ---\nCusto: %d\n", custo_vmp);
    free(ordem_vmp);

    int *ordem_ins = tsp_insercao(g2, &custo_ins);
    printf("\n--- TSP Insercao ---\nCusto: %d\n", custo_ins);
    free(ordem_ins);

    liberar_grafo_lista_ponderado(g2);

    // --- Teste 3: Reducao Hamiltoniano -> TSP (usando o mesmo g1) ---
    GrafoListaPonderado *g3_tsp = grafo_para_tsp(g1);
    int custo_reducao;
    int *ordem_reducao = tsp_forca_bruta(g3_tsp, 0, &custo_reducao);
    printf("\n--- Reducao Hamiltoniano -> TSP ---\n");
    printf("Custo do TSP reduzido: %d (n = %d)\n", custo_reducao, n1);
    printf("=> %s\n", (custo_reducao == n1) ? "Existe ciclo hamiltoniano!" : "Nao existe ciclo hamiltoniano.");
    free(ordem_reducao);

    liberar_grafo_lista(g1);
    liberar_grafo_lista_ponderado(g3_tsp);

    return 0;
}