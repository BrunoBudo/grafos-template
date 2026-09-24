#include <stdlib.h>
#include "conectividade.h"

// Função auxiliar para encontrar o menor valor entre dois inteiros
static int min(int a, int b) {
    return (a < b) ? a : b;
}

static void tarjan_dfs(GrafoLista *g, int u, int *visitado, int *descoberta,
                        int *low, int *pai, int *tempo) {
    visitado[u] = 1;
    descoberta[u] = low[u] = (*tempo)++;

    No *atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->destino;

        if (!visitado[v]) {
            pai[v] = u;
            // TODO 1: chame tarjan_dfs recursivamente para v
            tarjan_dfs(g, v, visitado, descoberta, low, pai, tempo);
            // TODO 2: depois da chamada, atualize low[u] = min(low[u], low[v])
            low[u] = min(low[u], low[v]);
        } else if (v != pai[u]) {
            // TODO 3: aresta de retorno -> low[u] = min(low[u], descoberta[v])
            low[u] = min(low[u], descoberta[v]);
        }
        atual = atual->prox;
    }
}

static void executar_tarjan(GrafoLista *g, int *descoberta, int *low, int *pai) {
    int *visitado = calloc(g->n, sizeof(int));
    int tempo = 0;
    for (int i = 0; i < g->n; i++) pai[i] = -1;

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) tarjan_dfs(g, i, visitado, descoberta, low, pai, &tempo);
    }
    free(visitado);
}

int* dfs_articulacoes(GrafoLista *g, int *num_articulacoes) {
    int *descoberta = malloc(g->n * sizeof(int));
    int *low = malloc(g->n * sizeof(int));
    int *pai = malloc(g->n * sizeof(int));
    executar_tarjan(g, descoberta, low, pai);

    int *marcado = calloc(g->n, sizeof(int));
    int *filhos_raiz = calloc(g->n, sizeof(int));

    // TODO 4: para cada vértice v de 0 a g->n-1 com pai[v] != -1:
    //   seja u = pai[v]
    //   se pai[u] == -1 (u é raiz da sua árvore): filhos_raiz[u]++
    //   senão: se low[v] >= descoberta[u] -> marcado[u] = 1
    // Depois do loop, para cada raiz com filhos_raiz[i] > 1 -> marcado[i] = 1
    for (int v = 0; v < g->n; v++) {
        if (pai[v] != -1) {
            int u = pai[v];
            if (pai[u] == -1) {
                filhos_raiz[u]++;
            } else {
                if (low[v] >= descoberta[u]) {
                    marcado[u] = 1;
                }
            }
        }
    }

    for (int i = 0; i < g->n; i++) {
        if (pai[i] == -1 && filhos_raiz[i] > 1) {
            marcado[i] = 1;
        }
    }

    int count = 0;
    for (int i = 0; i < g->n; i++) if (marcado[i]) count++;
    int *resultado = malloc(count * sizeof(int));
    int idx = 0;
    for (int i = 0; i < g->n; i++) if (marcado[i]) resultado[idx++] = i;

    *num_articulacoes = count;
    free(descoberta); free(low); free(pai);
    free(marcado); free(filhos_raiz);
    return resultado;
}

int* detectar_pontes(GrafoLista *g, int *num_pontes) {
    int *descoberta = malloc(g->n * sizeof(int));
    int *low = malloc(g->n * sizeof(int));
    int *pai = malloc(g->n * sizeof(int));
    executar_tarjan(g, descoberta, low, pai);

    int *pontes = malloc(2 * g->n * sizeof(int)); // no máximo n-1 pontes
    int count = 0;

    // TODO 5: para cada vértice v de 0 a g->n-1 com pai[v] != -1:
    //   seja u = pai[v]
    //   se low[v] > descoberta[u]: (u,v) é ponte
    //     -> pontes[count*2] = u; pontes[count*2+1] = v; count++
    for (int v = 0; v < g->n; v++) {
        if (pai[v] != -1) {
            int u = pai[v];
            if (low[v] > descoberta[u]) {
                pontes[count * 2] = u;
                pontes[count * 2 + 1] = v;
                count++;
            }
        }
    }

    *num_pontes = count;
    free(descoberta); free(low); free(pai);
    return pontes;
}