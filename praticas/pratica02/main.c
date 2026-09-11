#include <stdio.h>
#include <stdlib.h>

#include "busca_largura.h"
#include "busca_profundidade.h"


int main(void)
{
    GrafoLista *g;

    int *dist;
    int *pred;
    int *visitado;

    int componentes;
    int i;


    g = criar_grafo(6);


    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 0, 2);
    adicionar_aresta(g, 1, 3);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 3, 4);
    adicionar_aresta(g, 4, 5);


    
    mostrar_grafo(g);


    

    dist = (int *)malloc(g->num_vertices * sizeof(int));
    pred = (int *)malloc(g->num_vertices * sizeof(int));


    if (dist == NULL || pred == NULL) {

        printf("Erro ao alocar vetores da BFS.\n");

        liberar_grafo(g);

        free(dist);
        free(pred);

        return 1;
    }


    printf("\n===== BFS =====\n");

    bfs(g, 0, dist, pred);


    printf("Origem: 0\n\n");

    for (i = 0; i < g->num_vertices; i++) {

        printf(
            "Vertice %d | distancia = %d | predecessor = %d\n",
            i,
            dist[i],
            pred[i]
        );
    }


    

    visitado = (int *)calloc(
        g->num_vertices,
        sizeof(int)
    );


    if (visitado == NULL) {

        printf("Erro ao alocar vetor da DFS.\n");

        free(dist);
        free(pred);
        liberar_grafo(g);

        return 1;
    }


    printf("\n===== DFS RECURSIVA =====\n");

    dfs_recursiva(g, 0, visitado);

    printf("\n");


    

    printf("\n===== COMPONENTES CONEXOS =====\n");

    componentes = contar_componentes(g);

    printf(
        "\nQuantidade de componentes: %d\n",
        componentes
    );


   

    printf("\n===== BIPARTICAO =====\n");

    if (eh_bipartido(g)) {

        printf("O grafo e bipartido.\n");

    } else {

        printf("O grafo nao e bipartido.\n");
    }


    

    printf("\n===== CICLO =====\n");

    if (tem_ciclo(g)) {

        printf("O grafo possui ciclo.\n");

    } else {

        printf("O grafo nao possui ciclo.\n");
    }


    

    free(dist);
    free(pred);
    free(visitado);

    liberar_grafo(g);


    return 0;
}