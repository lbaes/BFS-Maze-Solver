#include <stdlib.h>
/*
    Lucas Franchini Baes - 31849202
    Mauricio Lucianelli  - 31818587
*/

/// @param Tmax tamanho maximo da fila;
/// @param prim indice com elemento da entrada;
/// @param ult indice com o elemento de saida;
/// @param elems array de elementos na fila;
typedef struct fila
{
    int Tmax, Tatual, prim, ult, *elems;
} fila_t;

fila_t *fila_criar(int Tmax);
fila_t *fila_deletar(fila_t *f);
void enfileirar(fila_t *f, int e);
int desenfileirar(fila_t *f);
int fila_cheia(fila_t *f);
int fila_vazia(fila_t *f);
