// tsp.c
#include <stdlib.h>
#include "tsp.h"

static int peso_aresta(GrafoListaPonderado *g, int u, int v) {
    for (NoPonderado *atual = g->adj[u]; atual != NULL; atual = atual->prox)
        if (atual->destino == v) return atual->peso;
    return 999999;
}

static void permutar(int *vertices, int inicio, int fim, GrafoListaPonderado *g,
                      int origem, int *melhor_custo, int *melhor_ordem) {
    if (inicio == fim) {
        int custo = peso_aresta(g, origem, vertices[0]);
        for (int i = 0; i < fim; i++) custo += peso_aresta(g, vertices[i], vertices[i+1]);
        custo += peso_aresta(g, vertices[fim], origem);

        if (custo < *melhor_custo) {
            *melhor_custo = custo;
            for (int i = 0; i <= fim; i++) melhor_ordem[i] = vertices[i];
        }
        return;
    }
    for (int i = inicio; i <= fim; i++) {
        int tmp = vertices[inicio]; vertices[inicio] = vertices[i]; vertices[i] = tmp;
        permutar(vertices, inicio + 1, fim, g, origem, melhor_custo, melhor_ordem);
        tmp = vertices[inicio]; vertices[inicio] = vertices[i]; vertices[i] = tmp;
    }
}

int* tsp_forca_bruta(GrafoListaPonderado *g, int origem, int *custo_total) {
    int n = g->n;
    int *vertices = malloc((n - 1) * sizeof(int));
    int idx = 0;
    for (int i = 0; i < n; i++) if (i != origem) vertices[idx++] = i;

    int *melhor_ordem = malloc((n - 1) * sizeof(int));
    *custo_total = 999999;

    permutar(vertices, 0, n - 2, g, origem, custo_total, melhor_ordem);

    free(vertices);
    return melhor_ordem;
}

int* tsp_vizinho_mais_proximo(GrafoListaPonderado *g, int origem, int *custo_total) {
    int n = g->n;
    int *visitado = calloc(n, sizeof(int));
    int *ordem = malloc(n * sizeof(int));
    *custo_total = 0;

    ordem[0] = origem;
    visitado[origem] = 1;
    int atual = origem;

    for (int passo = 1; passo < n; passo++) {
        int melhor_v = -1, melhor_peso = 999999;
        for (int v = 0; v < n; v++) {
            if (!visitado[v]) {
                int peso = peso_aresta(g, atual, v);
                if (peso < melhor_peso) { melhor_peso = peso; melhor_v = v; }
            }
        }
        ordem[passo] = melhor_v;
        visitado[melhor_v] = 1;
        *custo_total += melhor_peso;
        atual = melhor_v;
    }
    *custo_total += peso_aresta(g, atual, origem);

    free(visitado);
    return ordem;
}

int* tsp_insercao(GrafoListaPonderado *g, int *custo_total) {
    int n = g->n;
    int *na_rota = calloc(n, sizeof(int));
    int *rota = malloc(n * sizeof(int));
    int tamanho_rota = 2;

    rota[0] = 0; rota[1] = 1;
    na_rota[0] = 1; na_rota[1] = 1;

    while (tamanho_rota < n) {
        int melhor_v = -1, melhor_dist = 999999;
        for (int v = 0; v < n; v++) {
            if (na_rota[v]) continue;
            for (int i = 0; i < tamanho_rota; i++) {
                int peso = peso_aresta(g, rota[i], v);
                if (peso < melhor_dist) { melhor_dist = peso; melhor_v = v; }
            }
        }

        int melhor_pos = 0, melhor_aumento = 999999;
        for (int i = 0; i < tamanho_rota; i++) {
            int prox = (i + 1) % tamanho_rota;
            int aumento = peso_aresta(g, rota[i], melhor_v)
                        + peso_aresta(g, melhor_v, rota[prox])
                        - peso_aresta(g, rota[i], rota[prox]);
            if (aumento < melhor_aumento) { melhor_aumento = aumento; melhor_pos = i + 1; }
        }

        for (int i = tamanho_rota; i > melhor_pos; i--) rota[i] = rota[i - 1];
        rota[melhor_pos] = melhor_v;
        na_rota[melhor_v] = 1;
        tamanho_rota++;
    }

    *custo_total = 0;
    for (int i = 0; i < n; i++) {
        int prox = (i + 1) % n;
        *custo_total += peso_aresta(g, rota[i], rota[prox]);
    }

    free(na_rota);
    return rota;
}

GrafoListaPonderado* grafo_para_tsp(GrafoLista *g) {
    int n = g->n;
    GrafoListaPonderado *gp = criar_grafo_lista_ponderado(n);

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u == v) continue;
            int peso = sao_adjacentes_lista(g, u, v) ? 1 : 2;
            inserir_aresta_ponderada(gp, u, v, peso);
        }
    }
    return gp;
}