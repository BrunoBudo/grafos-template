// grafo_lista_ponderado.h
#ifndef GRAFO_LISTA_PONDERADO_H
#define GRAFO_LISTA_PONDERADO_H

typedef struct NoPonderado {
    int destino;
    int peso;
    struct NoPonderado *prox;
} NoPonderado;

typedef struct {
    int n;
    NoPonderado **adj;
} GrafoListaPonderado;

GrafoListaPonderado* criar_grafo_lista_ponderado(int n);
void inserir_aresta_ponderada(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo_lista_ponderado(GrafoListaPonderado *g);
void exibir_lista_ponderada(GrafoListaPonderado *g);

#endif