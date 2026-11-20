#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

// ---------- MinHeap (infraestrutura pronta) ----------

static void heap_trocar(MinHeap *h, int i, int j) {
    NoHeap tmp = h->dados[i]; h->dados[i] = h->dados[j]; h->dados[j] = tmp;
    h->posicao[h->dados[i].vertice] = i;
    h->posicao[h->dados[j].vertice] = j;
}

static void heap_sift_down(MinHeap *h, int i) {
    int menor = i, esq = 2*i+1, dir = 2*i+2;
    if (esq < h->tamanho && h->dados[esq].distancia < h->dados[menor].distancia) menor = esq;
    if (dir < h->tamanho && h->dados[dir].distancia < h->dados[menor].distancia) menor = dir;
    if (menor != i) { heap_trocar(h, i, menor); heap_sift_down(h, menor); }
}

static void heap_sift_up(MinHeap *h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (h->dados[pai].distancia <= h->dados[i].distancia) break;
        heap_trocar(h, i, pai);
        i = pai;
    }
}

MinHeap* criar_min_heap(int capacidade) {
    MinHeap *h = malloc(sizeof(MinHeap));
    h->dados = malloc(capacidade * sizeof(NoHeap));
    h->posicao = malloc(capacidade * sizeof(int));
    h->capacidade = capacidade;
    h->tamanho = 0;
    return h;
}

NoHeap extrair_minimo(MinHeap *h) {
    NoHeap min = h->dados[0];
    h->posicao[min.vertice] = -1;
    h->tamanho--;
    if (h->tamanho > 0) {
        h->dados[0] = h->dados[h->tamanho];
        h->posicao[h->dados[0].vertice] = 0;
        heap_sift_down(h, 0);
    }
    return min;
}

void diminuir_chave(MinHeap *h, int vertice, int nova_distancia) {
    int pos = h->posicao[vertice];
    if (pos == -1 || h->dados[pos].distancia <= nova_distancia) return;
    h->dados[pos].distancia = nova_distancia;
    heap_sift_up(h, pos);
}

void liberar_min_heap(MinHeap *h) {
    free(h->dados);
    free(h->posicao);
    free(h);
}

// ---------- Algoritmo (sua parte) ----------

int dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int n = g->n;

    // TODO 1: inicialize dist[i] = INFINITO_DIJKSTRA e pred[i] = -1 para todo i
    // dist[origem] = 0

    MinHeap *h = criar_min_heap(n);
    // TODO 2: coloque todos os n vértices em h->dados[] (vertice=i, distancia=dist[i]),
    // preencha h->posicao[i] = i, defina h->tamanho = n, e rode heap_sift_down
    // de trás pra frente (igual fizemos no Prim) para transformar em heap válido

    while (h->tamanho > 0) {
        NoHeap min = extrair_minimo(h);
        int u = min.vertice;

        // TODO 3: para cada vizinho v de u (percorrendo g->adj[u]):
        //   se dist[u] + peso < dist[v]:
        //     atualize dist[v], pred[v] = u
        //     chame diminuir_chave(h, v, dist[v])
    }

    liberar_min_heap(h);
    return 1;
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    // TODO 4: a partir de 'destino', siga pred[] pra trás guardando cada vértice
    // num array/pilha, até chegar em 'origem' (ou em -1, se não houver caminho).
    // Depois imprima na ordem correta: origem -> ... -> destino
    (void)origem; (void)destino; (void)pred;
}