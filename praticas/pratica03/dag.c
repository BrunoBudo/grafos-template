#include <stdlib.h>
#include "dag.h"

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int *grau_entrada = calloc(g->n, sizeof(int));
    
    // TODO 1: percorra todas as listas de adjacência e calcule o grau de entrada
    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];
        while (atual != NULL) {
            int v = atual->destino;
            grau_entrada[v]++;
            atual = atual->prox;
        }
    }

    int *fila = malloc(g->n * sizeof(int));
    int inicio_fila = 0, fim_fila = 0;
    
    // TODO 2: coloque na fila todo vértice com grau_entrada == 0
    for (int i = 0; i < g->n; i++) {
        if (grau_entrada[i] == 0) {
            fila[fim_fila++] = i;
        }
    }

    int *resultado = malloc(g->n * sizeof(int));
    int count = 0;
    
    // TODO 3: enquanto a fila não estiver vazia, tire um vértice, coloque
    // em 'resultado', e para cada vizinho dele diminua grau_entrada;
    // se chegar a 0, coloque esse vizinho na fila
    while (inicio_fila < fim_fila) {
        int u = fila[inicio_fila++];
        resultado[count++] = u;

        No *atual = g->adj[u];
        while (atual != NULL) {
            int v = atual->destino;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) {
                fila[fim_fila++] = v;
            }
            atual = atual->prox;
        }
    }

    free(grau_entrada);
    free(fila);

    if (count < g->n) {
        // TODO 4: tem ciclo -> libere 'resultado' e retorne NULL, *tamanho = 0
        free(resultado);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = count;
    return resultado;
}

// Função auxiliar recursiva para o DFS (0 = Branco, 1 = Cinza, 2 = Preto)
static int dfs_visita(GrafoLista *g, int u, int *estado, int *pilha, int *topo) {
    estado[u] = 1; // Marcado como visitando (Cinza)

    No *atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->destino;
        if (estado[v] == 1) {
            return 0; // Ciclo detectado (encontrou um vértice Cinza)
        }
        if (estado[v] == 0) {
            if (!dfs_visita(g, v, estado, pilha, topo)) {
                return 0;
            }
        }
        atual = atual->prox;
    }

    estado[u] = 2; // Marcado como concluído (Preto)
    pilha[(*topo)++] = u; // Empilha o vértice ao terminar
    return 1;
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    // TODO: implemente com os 3 estados (branco/cinza/preto)
    int *estado = calloc(g->n, sizeof(int)); // 0 por padrão (Branco)
    int *pilha = malloc(g->n * sizeof(int));
    int topo = 0;

    for (int i = 0; i < g->n; i++) {
        if (estado[i] == 0) {
            if (!dfs_visita(g, i, estado, pilha, &topo)) {
                free(estado);
                free(pilha);
                *tamanho = 0;
                return NULL; // Ciclo detectado
            }
        }
    }

    int *resultado = malloc(g->n * sizeof(int));
    // Inverte a ordem da pilha para obter a ordenação topológica correta
    for (int i = 0; i < g->n; i++) {
        resultado[i] = pilha[topo - 1 - i];
    }

    *tamanho = g->n;
    free(estado);
    free(pilha);
    return resultado;
}

int eh_dag(GrafoLista *g) {
    int tamanho;
    int *resultado = ordenacao_topologica_kahn(g, &tamanho);
    int resposta = (resultado != NULL);
    free(resultado);
    return resposta;
}