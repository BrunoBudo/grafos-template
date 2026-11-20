// bellman_ford.h
#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H
#include "grafo_lista_ponderado.h"

#define INFINITO 999999

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *pred, int n, int inicio);

#endif