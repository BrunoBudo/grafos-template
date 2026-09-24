#include <stdlib.h>
#include "coloracao.h"

static int* colorir_na_ordem(GrafoLista *g, int *ordem, int *num_cores) {
    int n = g->n;
    int *cor = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) cor[i] = -1;

    int *usada = malloc(n * sizeof(int));

    for (int idx = 0; idx < n; idx++) {
        int v = ordem[idx];

        // TODO 1: zere 'usada[]' (todas as cores como "não usada" nesse passo)
        for (int i = 0; i < n; i++) usada[i] = 0;

        // TODO 2: para cada vizinho de v que já tem cor atribuída,
        // marque usada[cor_do_vizinho] = 1
        No *atual = g->adj[v];
        while (atual != NULL) {
            int viz = atual->destino;
            if (cor[viz] != -1) {
                usada[cor[viz]] = 1;
            }
            atual = atual->prox;
        }

        // TODO 3: escolha a menor cor c tal que usada[c] == 0, e faça cor[v] = c
        int c = 0;
        while (usada[c]) {
            c++;
        }
        cor[v] = c;
    }

    free(usada);

    // TODO 4: calcule *num_cores como (maior valor em cor[]) + 1
    int max_cor = -1;
    for (int i = 0; i < n; i++) {
        if (cor[i] > max_cor) {
            max_cor = cor[i];
        }
    }
    *num_cores = (n > 0 && max_cor != -1) ? max_cor + 1 : 0;

    return cor;
}

int* coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int n = g->n;
    int *ordem = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) ordem[i] = i; // ordem arbitrária = natural

    int *resultado = colorir_na_ordem(g, ordem, num_cores);
    free(ordem);
    return resultado;
}

int* coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int n = g->n;
    int *ordem = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) ordem[i] = i;

    // TODO 5: ordene 'ordem[]' do MAIOR grau pro MENOR grau
    // (compare grau_lista(g, ordem[i]) com grau_lista(g, ordem[j]);
    // um bubble sort simples é suficiente aqui)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (grau_lista(g, ordem[j]) < grau_lista(g, ordem[j + 1])) {
                int temp = ordem[j];
                ordem[j] = ordem[j + 1];
                ordem[j + 1] = temp;
            }
        }
    }

    int *resultado = colorir_na_ordem(g, ordem, num_cores);
    free(ordem);
    return resultado;
}

int eh_bipartido(GrafoLista *g) {
    int n = g->n;
    int *cor = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) cor[i] = -1;
    int *fila = malloc(n * sizeof(int));

    for (int inicio = 0; inicio < n; inicio++) {
        if (cor[inicio] != -1) continue;

        int ini_fila = 0, fim_fila = 0;
        cor[inicio] = 0;
        fila[fim_fila++] = inicio;

        // TODO 6: BFS -- enquanto a fila não estiver vazia, tire um vértice u;
        // para cada vizinho v de u:
        //   se cor[v] == -1: dê a cor oposta de cor[u] (1 - cor[u]) e coloque na fila
        //   se cor[v] == cor[u]: encontrou conflito -> libere cor/fila e retorne 0
        while (ini_fila < fim_fila) {
            int u = fila[ini_fila++];
            No *atual = g->adj[u];
            while (atual != NULL) {
                int v = atual->destino;
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    fila[fim_fila++] = v;
                } else if (cor[v] == cor[u]) {
                    free(cor);
                    free(fila);
                    return 0;
                }
                atual = atual->prox;
            }
        }
    }

    free(cor);
    free(fila);
    return 1;
}