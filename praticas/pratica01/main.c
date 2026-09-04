#include <stdio.h>
#include "grafo_lista.h"

int main() {
    int n = 4; // Vértices 1, 2, 3, 4
    
    GrafoLista *g = criar_grafo_lista(n);

    // Conjunto E = {{1, 2}, {1, 3}, {2, 3}, {3, 4}}
    // Passamos com -1 porque no código a indexação começa em 0:
    inserir_aresta_lista(g, 1 - 1, 2 - 1); // {1, 2}
    inserir_aresta_lista(g, 1 - 1, 3 - 1); // {1, 3}
    inserir_aresta_lista(g, 2 - 1, 3 - 1); // {2, 3}
    inserir_aresta_lista(g, 3 - 1, 4 - 1); // {3, 4}

    // Exibe a lista formatada conforme o slide
    exibir_lista(g);

    // Liberando a memória alocada
    liberar_grafo_lista(g);

    return 0;
}