#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "busca_largura.h"


/*
 * ============================================================
 * PILHA (LIFO) PARA DFS
 * ============================================================
 */

typedef struct {
    int *dados;
    int topo;
    int capacidade;
} Pilha;


/*
 * ============================================================
 * FUNÇÕES DA PILHA
 * ============================================================
 */

void inicializar_pilha(Pilha *p, int capacidade);

void empilhar(Pilha *p, int valor);

int desempilhar(Pilha *p);

int pilha_vazia(Pilha *p);

void liberar_pilha(Pilha *p);


void dfs_recursiva(GrafoLista *g, int u, int *visitado);


int eh_bipartido(GrafoLista *g);

int contar_componentes(GrafoLista *g);

int tem_ciclo(GrafoLista *g);

#endif