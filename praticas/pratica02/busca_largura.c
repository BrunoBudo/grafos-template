#include <stdio.h>
#include <stdlib.h>

#include "busca_largura.h"


GrafoLista *criar_grafo(int num_vertices)
{
    GrafoLista *g;
    int i;

    g = (GrafoLista *)malloc(sizeof(GrafoLista));

    if (g == NULL) {
        printf("Erro ao alocar o grafo.\n");
        exit(1);
    }

    g->num_vertices = num_vertices;

    g->lista = (No **)malloc(num_vertices * sizeof(No *));

    if (g->lista == NULL) {
        printf("Erro ao alocar as listas de adjacencia.\n");
        free(g);
        exit(1);
    }

    for (i = 0; i < num_vertices; i++) {
        g->lista[i] = NULL;
    }

    return g;
}



void adicionar_aresta(GrafoLista *g, int origem, int destino)
{
    No *novo;

    if (g == NULL) {
        return;
    }

    if (origem < 0 || origem >= g->num_vertices ||
        destino < 0 || destino >= g->num_vertices) {

        printf("Vertice invalido.\n");
        return;
    }

    
    novo = (No *)malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar aresta.\n");
        exit(1);
    }

    novo->destino = destino;
    novo->prox = g->lista[origem];
    g->lista[origem] = novo;


    
    novo = (No *)malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro ao alocar aresta.\n");
        exit(1);
    }

    novo->destino = origem;
    novo->prox = g->lista[destino];
    g->lista[destino] = novo;
}


void liberar_grafo(GrafoLista *g)
{
    int i;
    No *atual;
    No *temp;

    if (g == NULL) {
        return;
    }

    for (i = 0; i < g->num_vertices; i++) {

        atual = g->lista[i];

        while (atual != NULL) {
            temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(g->lista);
    free(g);
}


void mostrar_grafo(GrafoLista *g)
{
    int i;
    No *atual;

    printf("\n===== LISTA DE ADJACENCIA =====\n");

    for (i = 0; i < g->num_vertices; i++) {

        printf("%d: ", i);

        atual = g->lista[i];

        while (atual != NULL) {
            printf("%d -> ", atual->destino);
            atual = atual->prox;
        }

        printf("NULL\n");
    }

    printf("===============================\n");
}



void inicializar_fila(Fila *f, int capacidade)
{
    f->dados = (int *)malloc(capacidade * sizeof(int));

    if (f->dados == NULL) {
        printf("Erro ao alocar fila.\n");
        exit(1);
    }

    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}


void enfileirar(Fila *f, int valor)
{
    if (f->tamanho == f->capacidade) {
        printf("Erro: fila cheia.\n");
        return;
    }

    f->dados[f->fim] = valor;

    f->fim = (f->fim + 1) % f->capacidade;

    f->tamanho++;
}


int desenfileirar(Fila *f)
{
    int valor;

    if (f->tamanho == 0) {
        return -1;
    }

    valor = f->dados[f->inicio];

    f->inicio = (f->inicio + 1) % f->capacidade;

    f->tamanho--;

    return valor;
}


int fila_vazia(Fila *f)
{
    return f->tamanho == 0;
}


void liberar_fila(Fila *f)
{
    free(f->dados);

    f->dados = NULL;
    f->capacidade = 0;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}




void bfs(GrafoLista *g, int origem, int *dist, int *pred)
{
    int i;
    int u;
    int v;

    No *atual;

    Fila fila;


    
    for (i = 0; i < g->num_vertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }


    
    inicializar_fila(&fila, g->num_vertices);


    
    dist[origem] = 0;

    enfileirar(&fila, origem);


    
    while (!fila_vazia(&fila)) {

        u = desenfileirar(&fila);

        
        atual = g->lista[u];

        while (atual != NULL) {

            v = atual->destino;

            
            if (dist[v] == -1) {

                dist[v] = dist[u] + 1;

                pred[v] = u;

                enfileirar(&fila, v);
            }

            atual = atual->prox;
        }
    }


    liberar_fila(&fila);
}