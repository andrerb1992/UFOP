
#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include "AcessoSequencialIndexado.h"
#include "Cria.h"
#include "ArvoreB.h"
#include "Geral.h"
#include"ArvoreBinaria.h"
#include <string.h>
#include <time.h>

using namespace std;

int main(int argc, char** argv) {

    if (argc != 6 && argc != 7) {// posição 0 caminho do arquivo (projeto)
        printf("Erro!!! Formato de entrada invalido\n\n");
        return 0;
    }
    // pesquisa(1) <método>(2) <quantidade>(3) <situação>(4) <chave>(5) [-P](6)
    FILE * arq;
    ArvoreBinaria pRaiz;

    switch (atoi(argv[2])) {
        case 1:
            if (atoi(argv[4]) == 1) {
                printf("Acesso sequencial indexado\n");
                arquivoOrdenadoAscendentemente(arq, atoi(argv[3]));
                clock_t end, start;
                start = clock();
                AcessoSequencialIndexado(atoi(argv[5]), arq, atoi(argv[3]));
                end = clock();
                printf("Tempo gasto: %4.0f ms\n\n", 1000 * (double) (end - start) / (double) (CLOCKS_PER_SEC));

            } else {
                printf("\nEsse arquivo necessita de estar ordenado para executar esse metodo.\n\n");
            }

            break;

        case 2:
            printf("ArvoreBinaria\n");
            if (atoi(argv[4]) == 1) {
                arquivoOrdenadoAscendentemente(arq, atoi(argv[3]));
                if ((arq = fopen("arquivo1.bin", "rb")) == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    return 0;
                }
                
                clock_t end, start;
                start = clock();                
                Arvore_Binaria(&pRaiz, arq, atoi(argv[3]), atoi(argv[5]));
                end = clock();
                printf("Tempo gasto: %4.0f ms\n\n", 1000 * (double) (end - start) / (double) (CLOCKS_PER_SEC));
            } else if (atoi(argv[4]) == 2) {
                arquivoOrdenadoDescendentemente(arq, atoi(argv[3]));
                if ((arq = fopen("arquivodescendentemente.bin", "rb")) == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    return 0;
                }
                clock_t end, start;
                start = clock();                
                Arvore_Binaria(&pRaiz, arq, atoi(argv[3]), atoi(argv[5]));
                end = clock();
                printf("Tempo gasto: %4.0f ms\n\n", 1000 * (double) (end - start) / (double) (CLOCKS_PER_SEC));
            } else if (atoi(argv[4]) == 3) {
                arquivoDesordenadoAleatoriamente(arq, atoi(argv[3]));
                if ((arq = fopen("arquivoaleatoriamente.bin", "rb")) == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    return 0;
                }
                clock_t end, start;
                start = clock();                
                Arvore_Binaria(&pRaiz, arq, atoi(argv[3]), atoi(argv[5]));
                end = clock();
                printf("Tempo gasto: %4.0f ms\n\n", 1000 * (double) (end - start) / (double) (CLOCKS_PER_SEC));
            }
            else {
                printf("Erro ao abrir o arquivo \n");
            }
           // Arvore_Binaria(&pRaiz, arq, atoi(argv[3]), atoi(argv[5]));
            libera(&pRaiz);
            fclose(arq);
            break;

        case 3:
            printf("ArvoreB\n");
            if (atoi(argv[4]) == 1) {
                arquivoOrdenadoAscendentemente(arq, atoi(argv[3]));
                if ((arq = fopen("arquivo1.bin", "rb")) == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    return 0;
                }
                clock_t end, start;
                start = clock();
                Arvore_B(arq, atoi(argv[5]));
                end = clock();
                printf("Tempo gasto: %4.0f ms\n\n", 1000 * (double) (end - start) / (double) (CLOCKS_PER_SEC));
            } else if (atoi(argv[4]) == 2) {
                arquivoOrdenadoDescendentemente(arq, atoi(argv[3]));
                if ((arq = fopen("arquivodescendentemente.bin", "rb")) == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    return 0;
                }
                clock_t end, start;
                start = clock();
                Arvore_B(arq, atoi(argv[5]));
                end = clock();
                printf("Tempo gasto: %4.0f ms\n\n", 1000 * (double) (end - start) / (double) (CLOCKS_PER_SEC));
            } else if (atoi(argv[4]) == 3) {

                arquivoDesordenadoAleatoriamente(arq, atoi(argv[3]));
                printf("1223\n\n");
                if ((arq = fopen("arquivoaleatoriamente.bin", "rb")) == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    return 0;
                }
                clock_t end, start;
                start = clock();
                Arvore_B(arq, atoi(argv[5]));
                end = clock();
                printf("Tempo gasto: %4.0f ms\n\n", 1000 * (double) (end - start) / (double) (CLOCKS_PER_SEC));
            } else {
                printf("Erro ao abrir o arquivo \n");
            }
            fclose(arq);


    }


    return 0;
}

