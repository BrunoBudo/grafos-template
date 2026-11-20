// cobertura.h
#ifndef COBERTURA_H
#define COBERTURA_H
#include "grafo_lista.h"

int eh_cobertura(GrafoLista *g, int *conjunto, int tamanho_conjunto);
int* cobertura_minima_bt(GrafoLista *g, int *tamanho_cobertura);
int* cobertura_gulosa(GrafoLista *g, int *tamanho_cobertura);

#endif