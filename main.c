/*
    Lucas Franchini Baes - 31849202
    Mauricio Lucianelli  - 31818587
*/

#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#define ENTRADA "labirinto.txt"

// labirinto
typedef struct labirinto
{
    int N, M;
    int *grid;
} labirinto_t;

// auxilia na indexacao da matriz do labirinto
int labIndex(labirinto_t *lab, int i, int j)
{
    return i * lab->M + j;
}

// aloca memoria e inicializa o labirinto
labirinto_t *labirinto_criar(int N, int M)
{
    labirinto_t *lab = malloc(sizeof(labirinto_t));
    if (lab)
    {
        lab->N = N;
        lab->M = M;
        lab->grid = malloc(sizeof(int) * N * M);
        if (!lab->grid)
        {
            free(lab);
            lab = NULL;
        }
    }
    return lab;
}

// libera memoria do labirinto
labirinto_t *labirinto_deletar(labirinto_t *lab)
{
    free(lab->grid);
    free(lab);
    return NULL;
}

// le o labirinto de um arquivo de texto
labirinto_t *ler_entrada(const char *entrada)
{
    int N, M;
    FILE *fp;
    labirinto_t *lab;

    fp = fopen(entrada, "r");
    fscanf(fp, "%d", &N);
    fscanf(fp, "%d", &M);
    printf("N=%d\nM=%d\n", N, M);

    lab = labirinto_criar(N, M);
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            fscanf(fp, "%d", &lab->grid[labIndex(lab, i, j)]);
        }
    }

    return lab;
}

// imprime a matriz representando o labirinto
void labirinto_print(labirinto_t *lab)
{
    int N = lab->N;
    int M = lab->M;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            printf("%3d ", lab->grid[labIndex(lab, i, j)]);
        }
        printf("\n");
    }
}

// enfileira os vizihos na fila viz quando sao validos, altera o valor do grid dependendo do valor do parametro flag;
void enfileirar_vizinhos(labirinto_t * lab, fila_t * viz, int i, int j, int flag){
    int temp = 1;
    if (flag)
        temp = lab->grid[labIndex(lab, i, j)] + 1;
    if (j + 1 < lab->M && lab->grid[labIndex(lab, i, j + 1)] == 0)
    {
        lab->grid[labIndex(lab, i, j + 1)] = temp;
        enfileirar(viz, i);
        enfileirar(viz, j + 1);
    }
    if (j - 1 >= 0 && lab->grid[labIndex(lab, i, j - 1)] == 0)
    {
        lab->grid[labIndex(lab, i, j - 1)] = temp;
        enfileirar(viz, i);
        enfileirar(viz, j - 1);
    }
    if (i + 1 < lab->N && lab->grid[labIndex(lab, i + 1, j)] == 0)
    {
        lab->grid[labIndex(lab, i + 1, j)] = temp;
        enfileirar(viz, i + 1);
        enfileirar(viz, j);
    }
    if (i - 1 >= 0 && lab->grid[labIndex(lab, i - 1, j)] == 0)
    {
        lab->grid[labIndex(lab, i - 1, j)] = temp;
        enfileirar(viz, i - 1);
        enfileirar(viz, j);
    }

}

// printa o caminho entre o ponto de entrada e o ponto de saida.
void labirinto_caminho(labirinto_t * lab, int ie, int je, int i, int j);

// preenche a matriz grid com as distancias a partir do ponto (ie, je);
void labirinto_distancia(labirinto_t *lab, int ie, int je, int is, int js)
{
    fila_t *vizinhos;
    vizinhos = fila_criar(100);

    // 1. Numerar todos os vizinhos do ponto inicial com 1.
    // 2. Colocar os vizinhos em uma fila.
    enfileirar_vizinhos(lab, vizinhos, ie, je, 0);

    int achou = 0;
    // 3. Enquanto a fila não estiver vazia:
    while (!fila_vazia(vizinhos))
    {
        int pi, pj;

        // (a) Retirar um ponto da fila;
        pi = desenfileirar(vizinhos);
        pj = desenfileirar(vizinhos);
        if (pi == is && pj == js)
            achou = 1;
        
        // (b) Numerar os seus vizinhos livres com o número do ponto acrescido de 1; 
        // (c) Colocar os novos pontos (vizinhos livres) na fila.
        enfileirar_vizinhos(lab, vizinhos, pi, pj, 1);
    }
    // 4. Se a fila estiver vazia e não se tiver atingido o ponto de destino, não existe percurso. Caso contrário, imprimir o percurso.
    if (!achou)
    {
        printf("Caminho nao encontrado...\n");
    }
    else
    {
        lab->grid[labIndex(lab, ie, je)] = 0;
        printf("Caminho encontrado...\n");
        printf("Menor distancia de a ate b: %d\n", lab->grid[labIndex(lab, is, js)]);
        printf("Caminho de a ate b: \n");
        labirinto_caminho(lab, ie, je, is, js);
    }

    fila_deletar(vizinhos);
}

// printa o caminho entre o ponto de entrada (ie, je) até o ponto de saida (i, j).
void labirinto_caminho(labirinto_t * lab, int ie, int je, int i, int j){
    // Cheguei na entrada. retorne
    if (i == ie && j == je){
        printf("[%2d, %2d]\n", i, j);
        return;
    }
    int vatual = lab->grid[labIndex(lab, i, j)];

    // procure o vizinho com valor = lab->grid[i][j] -1
    if (j + 1 < lab->M && lab->grid[labIndex(lab, i, j + 1)] == vatual -1)
    {
        labirinto_caminho(lab, ie, je, i, j+1);
    }
    else if (j - 1 >= 0 && lab->grid[labIndex(lab, i, j - 1)] == vatual -1)
    {
        labirinto_caminho(lab, ie, je, i, j-1);
    }
    else if (i + 1 < lab->N && lab->grid[labIndex(lab, i + 1, j)] == vatual -1)
    {
        labirinto_caminho(lab, ie, je, i+1, j);
    }
    else if (i - 1 >= 0 && lab->grid[labIndex(lab, i - 1, j)] == vatual -1)
    {
        labirinto_caminho(lab, ie, je, i-1, j);
    }
    printf("[%2d, %2d]\n", i, j);

}

int main(int argc, char const *argv[])
{
    int ai, aj, bi, bj;
    labirinto_t *lab = ler_entrada(ENTRADA);
    printf("As coordenadas digitadas nao devem ser paredes e devem estar dentro do labirinto\n");
    printf("As coordenadas devem ser digitadas separadas por espaco\nExemplo: Se quiser selecionar o ponto [0][0] insira 0 0\n");
    printf("Digite a cooordenada do ponto A: ");
    scanf("%d %d", &ai, &aj);

    printf("Digite a cooordenada do ponto B: ");
    scanf("%d %d", &bi, &bj);
    printf("\n\n");

    labirinto_distancia(lab, ai, aj, bi, bj);
    printf("\nGrid:\n");
    labirinto_print(lab);
    lab = labirinto_deletar(lab);

    return 0;
}
