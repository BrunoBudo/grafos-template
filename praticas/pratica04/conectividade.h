#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H
#include "grafo_lista.h"

int* dfs_articulacoes(GrafoLista *g, int *num_articulacoes);
// Retorna array de pares (u,v) em sequência: [u1,v1,u2,v2,...]
int* detectar_pontes(GrafoLista *g, int *num_pontes);

#endif