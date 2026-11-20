// tsp.h
#ifndef TSP_H
#define TSP_H
#include "grafo_lista_ponderado.h"
#include "grafo_lista.h"

int* tsp_forca_bruta(GrafoListaPonderado *g, int origem, int *custo_total);
int* tsp_vizinho_mais_proximo(GrafoListaPonderado *g, int origem, int *custo_total);
int* tsp_insercao(GrafoListaPonderado *g, int *custo_total);
GrafoListaPonderado* grafo_para_tsp(GrafoLista *g);

#endif