#include "planaridade.h"

int eh_planar_euler(GrafoLista *g) {
    if (g->n < 3) return 1; // fórmula só vale a partir de n=3

    int m = 0;
    // TODO 6: conte o total de arestas do grafo (some grau_lista(g,i) para
    // todo vértice i, e cuidado: se você guarda aresta em dobro para grafo
    // não-dirigido, terá que dividir por 2 no final)
    for (int i = 0; i < g->n; i++) {
        m += grau_lista(g, i);
    }
    m = m / 2; // Considerando grafo não-dirigido (arestas armazenadas em dobro)

    return m <= 3 * g->n - 6;
}

static int testa_k5(GrafoLista *g, int a, int b, int c, int d, int e) {
    int v[5] = {a, b, c, d, e};
    // TODO 7: retorne 1 se TODOS os pares dentro de v[] são adjacentes entre si
    // (use sao_adjacentes_lista, lembrando de checar os dois sentidos u->v e v->u)
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (!sao_adjacentes_lista(g, v[i], v[j]) && !sao_adjacentes_lista(g, v[j], v[i])) {
                return 0;
            }
        }
    }
    return 1;
}

static int testa_k33(GrafoLista *g, int a1, int a2, int a3, int b1, int b2, int b3) {
    int A[3] = {a1, a2, a3}, B[3] = {b1, b2, b3};
    // TODO 8: retorne 1 se TODO vértice de A é adjacente a TODO vértice de B
    // (não precisa checar arestas dentro do próprio A ou dentro do próprio B)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int u = A[i];
            int v = B[j];
            if (!sao_adjacentes_lista(g, u, v) && !sao_adjacentes_lista(g, v, u)) {
                return 0;
            }
        }
    }
    return 1;
}

int tem_k5_ou_k33(GrafoLista *g) {
    int n = g->n;

    // Testa todos os subconjuntos de 5 vértices (K5)
    for (int a = 0; a < n; a++)
        for (int b = a + 1; b < n; b++)
            for (int c = b + 1; c < n; c++)
                for (int d = c + 1; d < n; d++)
                    for (int e = d + 1; e < n; e++)
                        if (testa_k5(g, a, b, c, d, e)) return 1;

    // Testa todos os subconjuntos disjuntos de 3+3 vértices (K3,3)
    for (int a1 = 0; a1 < n; a1++)
        for (int a2 = a1 + 1; a2 < n; a2++)
            for (int a3 = a2 + 1; a3 < n; a3++)
                for (int b1 = 0; b1 < n; b1++) {
                    if (b1 == a1 || b1 == a2 || b1 == a3) continue;
                    for (int b2 = b1 + 1; b2 < n; b2++) {
                        if (b2 == a1 || b2 == a2 || b2 == a3) continue;
                        for (int b3 = b2 + 1; b3 < n; b3++) {
                            if (b3 == a1 || b3 == a2 || b3 == a3) continue;
                            if (testa_k33(g, a1, a2, a3, b1, b2, b3)) return 1;
                        }
                    }
                }

    return 0;
}