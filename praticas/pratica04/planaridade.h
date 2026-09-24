#ifndef PLANARIDADE_H
#define PLANARIDADE_H
#include "grafo_lista.h"

int eh_planar_euler(GrafoLista *g);
int tem_k5_ou_k33(GrafoLista *g); // heurística de força bruta, use só para n <= 10

#endif