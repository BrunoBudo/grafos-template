#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H


typedef struct No {
    int destino;
    struct No *prox;
} No;


typedef struct {
    int num_vertices;
    No **lista;
} GrafoLista;



typedef struct {
    int *dados;
    int capacidade;
    int inicio;
    int fim;
    int tamanho;
} Fila;




GrafoLista *criar_grafo(int num_vertices);

void adicionar_aresta(GrafoLista *g, int origem, int destino);

void liberar_grafo(GrafoLista *g);

void mostrar_grafo(GrafoLista *g);




void inicializar_fila(Fila *f, int capacidade);

void enfileirar(Fila *f, int valor);

int desenfileirar(Fila *f);

int fila_vazia(Fila *f);

void liberar_fila(Fila *f);




void bfs(GrafoLista *g, int origem, int *dist, int *pred);

#endif