// hamiltoniano.c
#include <stdlib.h>
#include "hamiltoniano.h"

static int bt_hamiltoniano(GrafoLista *g, int *caminho, int *visitado, int pos) {
    int n = g->n;
    if (pos == n) return 1;

    int ultimo = caminho[pos - 1];
    for (int v = 0; v < n; v++) {
        if (!visitado[v] && sao_adjacentes_lista(g, ultimo, v)) {
            visitado[v] = 1;
            caminho[pos] = v;
            if (bt_hamiltoniano(g, caminho, visitado, pos + 1)) return 1;
            visitado[v] = 0;
        }
    }
    return 0;
}

int* encontrar_caminho_hamiltoniano_bt(GrafoLista *g, int *tamanho) {
    int n = g->n;
    int *caminho = malloc(n * sizeof(int));
    int *visitado = calloc(n, sizeof(int));
    int achou = 0;

    for (int inicio = 0; inicio < n && !achou; inicio++) {
        for (int i = 0; i < n; i++) visitado[i] = 0;
        visitado[inicio] = 1;
        caminho[0] = inicio;
        if (bt_hamiltoniano(g, caminho, visitado, 1)) achou = 1;
    }

    free(visitado);
    if (achou) {
        *tamanho = n;
        return caminho;
    }
    free(caminho);
    *tamanho = 0;
    return NULL;
}