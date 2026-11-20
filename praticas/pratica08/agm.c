// agm.c
#include <stdlib.h>
#include "agm.h"

// ---------- DSU (Union-Find) ----------

void dsu_criar(DSU *d, int n) {
    d->n = n;
    d->pai = malloc(n * sizeof(int));
    d->rank = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) d->pai[i] = i;
}

int find(DSU *d, int x) {
    if (d->pai[x] != x) d->pai[x] = find(d, d->pai[x]); // compressão de caminho
    return d->pai[x];
}

void unir(DSU *d, int x, int y) {
    int rx = find(d, x), ry = find(d, y);
    if (rx == ry) return;
    if (d->rank[rx] < d->rank[ry]) d->pai[rx] = ry;
    else if (d->rank[rx] > d->rank[ry]) d->pai[ry] = rx;
    else { d->pai[ry] = rx; d->rank[rx]++; }
}

void dsu_liberar(DSU *d) {
    free(d->pai);
    free(d->rank);
}

// ---------- Kruskal ----------

static int comparar_arestas(const void *a, const void *b) {
    return ((Aresta*)a)->peso - ((Aresta*)b)->peso;
}

Aresta* kruskal(Aresta *arestas, int num_arestas, int n, int *num_selecionadas, int *peso_total) {
    qsort(arestas, num_arestas, sizeof(Aresta), comparar_arestas);

    DSU d;
    dsu_criar(&d, n);

    Aresta *resultado = malloc((n - 1) * sizeof(Aresta));
    int count = 0;
    *peso_total = 0;

    for (int i = 0; i < num_arestas && count < n - 1; i++) {
        int u = arestas[i].u, v = arestas[i].v;
        if (find(&d, u) != find(&d, v)) {
            unir(&d, u, v);
            resultado[count++] = arestas[i];
            *peso_total += arestas[i].peso;
        }
    }

    dsu_liberar(&d);
    *num_selecionadas = count;
    return resultado;
}

// ---------- Prim (com Min-Heap + decrease-key) ----------

typedef struct { int vertice, chave; } HeapItem;
typedef struct { HeapItem *itens; int *posicao; int tamanho; } MinHeap;

static void heap_trocar(MinHeap *h, int i, int j) {
    HeapItem tmp = h->itens[i]; h->itens[i] = h->itens[j]; h->itens[j] = tmp;
    h->posicao[h->itens[i].vertice] = i;
    h->posicao[h->itens[j].vertice] = j;
}

static void heap_sift_down(MinHeap *h, int i) {
    int menor = i, esq = 2*i+1, dir = 2*i+2;
    if (esq < h->tamanho && h->itens[esq].chave < h->itens[menor].chave) menor = esq;
    if (dir < h->tamanho && h->itens[dir].chave < h->itens[menor].chave) menor = dir;
    if (menor != i) { heap_trocar(h, i, menor); heap_sift_down(h, menor); }
}

static void heap_sift_up(MinHeap *h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (h->itens[pai].chave <= h->itens[i].chave) break;
        heap_trocar(h, i, pai);
        i = pai;
    }
}

static HeapItem heap_extrair_min(MinHeap *h) {
    HeapItem min = h->itens[0];
    h->posicao[min.vertice] = -1;
    h->tamanho--;
    if (h->tamanho > 0) {
        h->itens[0] = h->itens[h->tamanho];
        h->posicao[h->itens[0].vertice] = 0;
        heap_sift_down(h, 0);
    }
    return min;
}

static void heap_diminuir_chave(MinHeap *h, int vertice, int nova_chave) {
    int pos = h->posicao[vertice];
    if (pos == -1 || h->itens[pos].chave <= nova_chave) return;
    h->itens[pos].chave = nova_chave;
    heap_sift_up(h, pos);
}

Aresta* prim(GrafoListaPonderado *g, int origem, int *num_selecionadas, int *peso_total) {
    int n = g->n;
    int *chave = malloc(n * sizeof(int));
    int *pai = malloc(n * sizeof(int));
    int *na_arvore = calloc(n, sizeof(int));

    MinHeap h;
    h.itens = malloc(n * sizeof(HeapItem));
    h.posicao = malloc(n * sizeof(int));
    h.tamanho = n;

    for (int i = 0; i < n; i++) {
        chave[i] = (i == origem) ? 0 : INFINITO_PRIM;
        pai[i] = -1;
        h.itens[i] = (HeapItem){i, chave[i]};
        h.posicao[i] = i;
    }
    for (int i = n/2 - 1; i >= 0; i--) heap_sift_down(&h, i);

    Aresta *resultado = malloc((n - 1) * sizeof(Aresta));
    int count = 0;
    *peso_total = 0;

    while (h.tamanho > 0) {
        HeapItem min = heap_extrair_min(&h);
        int u = min.vertice;
        na_arvore[u] = 1;

        if (pai[u] != -1) {
            resultado[count] = (Aresta){pai[u], u, chave[u]};
            *peso_total += chave[u];
            count++;
        }

        for (NoPonderado *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
            int v = atual->destino, peso = atual->peso;
            if (!na_arvore[v] && peso < chave[v]) {
                chave[v] = peso;
                pai[v] = u;
                heap_diminuir_chave(&h, v, peso);
            }
        }
    }

    free(chave); free(pai); free(na_arvore);
    free(h.itens); free(h.posicao);

    *num_selecionadas = count;
    return resultado;
}