// main.c
#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "cobertura.h"

int main() {
    int n = 5;
    GrafoLista *g = criar_grafo_lista(n);
    int arestas[][2] = {{0,1},{1,0},{1,2},{2,1},{2,3},{3,2},{3,4},{4,3},{4,0},{0,4}};
    int num_arestas = sizeof(arestas) / sizeof(arestas[0]);
    for (int i = 0; i < num_arestas; i++)
        inserir_aresta_lista(g, arestas[i][0], arestas[i][1]);

    int tam_bt;
    int *cob_bt = cobertura_minima_bt(g, &tam_bt);
    printf("Cobertura minima (backtracking), tamanho %d: ", tam_bt);
    for (int i = 0; i < tam_bt; i++) printf("%d ", cob_bt[i]);
    printf("\n");

    int tam_g;
    int *cob_g = cobertura_gulosa(g, &tam_g);
    printf("Cobertura gulosa, tamanho %d: ", tam_g);
    for (int i = 0; i < tam_g; i++) printf("%d ", cob_g[i]);
    printf("\n");

    free(cob_bt); free(cob_g);
    liberar_grafo_lista(g);
    return 0;
}