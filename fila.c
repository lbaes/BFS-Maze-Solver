/*
    Lucas Franchini Baes - 31849202
    Mauricio Lucianelli  - 31818587
*/
#include "fila.h"
#include <stdlib.h>

fila_t *fila_criar(int Tmax)
{
    fila_t *f = malloc(sizeof(fila_t));
    if (f)
    {
        f->Tmax = Tmax;
        f->Tatual = 0;
        f->prim = 0;
        f->ult = 0;
        f->elems = malloc(sizeof(int) * Tmax);
        if (!(f->elems))
        {
            free(f);
            f = NULL;
        }
    }

    return f;
}

fila_t *fila_deletar(fila_t *f)
{
    free(f->elems);
    free(f);
    return NULL;
}

int fila_cheia(fila_t *f)
{
    return f->Tatual == f->Tmax;
}

int fila_vazia(fila_t *f)
{
    return f->Tatual == 0;
}

void enfileirar(fila_t *f, int e)
{
    if (!fila_cheia(f)){
        f->elems[f->ult] = e;
        f->ult = (f->ult + 1) % f->Tmax;
        f->Tatual++;
    }
}

int desenfileirar(fila_t *f)
{
    int ret = -1;
    if (!fila_vazia(f)){
        ret = f->elems[f->prim];
        f->prim = (f->prim + 1) % f->Tmax;
        f->Tatual--;
    }
    return ret;
}
