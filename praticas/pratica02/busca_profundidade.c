#include <stdio.h>
#include <stdlib.h>

#include "busca_profundidade.h"


void inicializar_pilha(Pilha *p, int capacidade)
{
    p->dados = (int *)malloc(capacidade * sizeof(int));

    if (p->dados == NULL) {
        printf("Erro ao alocar pilha.\n");
        exit(1);
    }

    p->topo = -1;
    p->capacidade = capacidade;
}


void empilhar(Pilha *p, int valor)
{
    if (p->topo == p->capacidade - 1) {
        printf("Erro: pilha cheia.\n");
        return;
    }

    p->topo++;

    p->dados[p->topo] = valor;
}


int desempilhar(Pilha *p)
{
    if (p->topo == -1) {
        return -1;
    }

    return p->dados[p->topo--];
}


int pilha_vazia(Pilha *p)
{
    return p->topo == -1;
}


void liberar_pilha(Pilha *p)
{
    free(p->dados);

    p->dados = NULL;
    p->topo = -1;
    p->capacidade = 0;
}




void dfs_recursiva(GrafoLista *g, int u, int *visitado)
{
    No *atual;
    int v;


    /*
     * Marca u como visitado.
     */
    visitado[u] = 1;

    printf("%d ", u);


    /*
     * Percorre todos os vizinhos de u.
     */
    atual = g->lista[u];

    while (atual != NULL) {

        v = atual->destino;

        /*
         * Se o vizinho ainda nao foi visitado,
         * continua a DFS nele.
         */
        if (!visitado[v]) {
            dfs_recursiva(g, v, visitado);
        }

        atual = atual->prox;
    }
}




int eh_bipartido(GrafoLista *g)
{
    int *cor;
    Fila fila;

    int i;
    int u;
    int v;

    No *atual;


    cor = (int *)malloc(g->num_vertices * sizeof(int));

    if (cor == NULL) {
        printf("Erro ao alocar vetor de cores.\n");
        return 0;
    }


    
    for (i = 0; i < g->num_vertices; i++) {
        cor[i] = -1;
    }


    
    for (i = 0; i < g->num_vertices; i++) {

        if (cor[i] == -1) {

            
            cor[i] = 0;

            inicializar_fila(&fila, g->num_vertices);

            enfileirar(&fila, i);


            while (!fila_vazia(&fila)) {

                u = desenfileirar(&fila);

                atual = g->lista[u];

                while (atual != NULL) {

                    v = atual->destino;


                    
                    if (cor[v] == -1) {

                        
                        cor[v] = 1 - cor[u];

                        enfileirar(&fila, v);
                    }


                    
                    else if (cor[v] == cor[u]) {

                        liberar_fila(&fila);
                        free(cor);

                        return 0;
                    }

                    atual = atual->prox;
                }
            }

            liberar_fila(&fila);
        }
    }


    free(cor);

    return 1;
}




int contar_componentes(GrafoLista *g)
{
    int *visitado;
    int componentes;
    int i;


    visitado = (int *)calloc(
        g->num_vertices,
        sizeof(int)
    );

    if (visitado == NULL) {
        printf("Erro ao alocar vetor de visitados.\n");
        return -1;
    }


    componentes = 0;


    
    for (i = 0; i < g->num_vertices; i++) {

        if (!visitado[i]) {

            componentes++;

            dfs_recursiva(g, i, visitado);
        }
    }


    free(visitado);

    return componentes;
}




static int dfs_ciclo(
    GrafoLista *g,
    int u,
    int pai,
    int *visitado
)
{
    No *atual;
    int v;


    visitado[u] = 1;

    atual = g->lista[u];


    while (atual != NULL) {

        v = atual->destino;


        
        if (!visitado[v]) {

            if (dfs_ciclo(g, v, u, visitado)) {
                return 1;
            }
        }


        
        else if (v != pai) {

            return 1;
        }


        atual = atual->prox;
    }


    return 0;
}


int tem_ciclo(GrafoLista *g)
{
    int *visitado;
    int i;


    visitado = (int *)calloc(
        g->num_vertices,
        sizeof(int)
    );

    if (visitado == NULL) {
        printf("Erro ao alocar vetor de visitados.\n");
        return 0;
    }


    
    for (i = 0; i < g->num_vertices; i++) {

        if (!visitado[i]) {

            if (dfs_ciclo(g, i, -1, visitado)) {

                free(visitado);

                return 1;
            }
        }
    }


    free(visitado);

    return 0;
}