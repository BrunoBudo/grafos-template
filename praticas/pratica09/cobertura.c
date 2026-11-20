// cobertura.c
#include <stdlib.h>
#include "cobertura.h"

int eh_cobertura(GrafoLista *g, int *conjunto, int tamanho_conjunto) {
    int *incluido = calloc(g->n, sizeof(int));
    for (int i = 0; i < tamanho_conjunto; i++) incluido[conjunto[i]] = 1;
    int cobre_tudo = 1;
    for (int u = 0; u < g->n && cobre_tudo; u++) {
        for (No *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
            int v = atual->destino;
            if (!incluido[u] && !incluido[v]) { cobre_tudo = 0; break; }
        }
    }
    free(incluido);
    return cobre_tudo;
}

static int encontrar_aresta_nao_coberta(GrafoLista *g, int *incluido, int *u_out, int *v_out) {
    for (int u = 0; u < g->n; u++) {
        if (incluido[u]) continue;
        for (No *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
            int v = atual->destino;
            if (!incluido[v]) { *u_out = u; *v_out = v; return 1; }
        }
    }
    return 0;
}

static void bt_cobertura(GrafoLista *g, int *incluido, int *conjunto_atual,
                          int tamanho_atual, int *melhor, int *melhor_tamanho) {
    if (tamanho_atual >= *melhor_tamanho) return;
    int u, v;
    if (!encontrar_aresta_nao_coberta(g, incluido, &u, &v)) {
        *melhor_tamanho = tamanho_atual;
        for (int i = 0; i < tamanho_atual; i++) melhor[i] = conjunto_atual[i];
        return;
    }
    incluido[u] = 1;
    conjunto_atual[tamanho_atual] = u;
    bt_cobertura(g, incluido, conjunto_atual, tamanho_atual + 1, melhor, melhor_tamanho);
    incluido[u] = 0;

    incluido[v] = 1;
    conjunto_atual[tamanho_atual] = v;
    bt_cobertura(g, incluido, conjunto_atual, tamanho_atual + 1, melhor, melhor_tamanho);
    incluido[v] = 0;
}

int* cobertura_minima_bt(GrafoLista *g, int *tamanho_cobertura) {
    int n = g->n;
    int *melhor = malloc(n * sizeof(int));
    int melhor_tamanho = n + 1;
    int *atual = malloc(n * sizeof(int));
    int *incluido = calloc(n, sizeof(int));
    bt_cobertura(g, incluido, atual, 0, melhor, &melhor_tamanho);
    free(atual); free(incluido);
    int *resultado = malloc(melhor_tamanho * sizeof(int));
    for (int i = 0; i < melhor_tamanho; i++) resultado[i] = melhor[i];
    free(melhor);
    *tamanho_cobertura = melhor_tamanho;
    return resultado;
}

int* cobertura_gulosa(GrafoLista *g, int *tamanho_cobertura) {
    int n = g->n;
    int *incluido = calloc(n, sizeof(int));
    int *resultado = malloc(n * sizeof(int));
    int count = 0;
    while (!eh_cobertura(g, resultado, count)) {
        int melhor_v = -1, melhor_grau = -1;
        for (int u = 0; u < n; u++) {
            if (incluido[u]) continue;
            int grau_restante = 0;
            for (No *atual = g->adj[u]; atual != NULL; atual = atual->prox)
                if (!incluido[atual->destino]) grau_restante++;
            if (grau_restante > melhor_grau) { melhor_grau = grau_restante; melhor_v = u; }
        }
        incluido[melhor_v] = 1;
        resultado[count++] = melhor_v;
    }
    free(incluido);
    *tamanho_cobertura = count;
    return resultado;
}