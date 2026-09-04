#include <stdlib.h>
#include "grafo_lista.h"



int topo = 0;

void dfs (GrafoLista *g, int u, int *p, int *visitado) {
    visitado[u] = 1;
    p[topo++] = u;
    printf("Empilha %i, visita %i\n", u+1, u+1);
    No *no = g->lista[u];
    while (no != NULL) {
        int v = no->vertice;
        if (!visitado[u]) dfs(g, v, visitado); // pilha de recursividade
        no = no->proximo;
    }
    topo --;
    printf("Desempilha %i\n", u+1);
}