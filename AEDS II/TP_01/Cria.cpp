#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
#include "Geral.h"

// criando os arquivos binarios
// função para criar o arquivo ordenado ascendentemente, ou seja, em ordem

int arquivoOrdenadoAscendentemente(FILE *arq1, int TAM) {
    Registro r;
    int i;

    if ((arq1 = fopen("arquivo1.bin", "wb")) == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 0;
    }
    // inserio os dados abaixo nos arquivos binarios
    r.dado1 = 50000;
    strcpy(r.dado2, "abcdefgh ijkmnopq hihgffdu");
    for (i = 0; i < TAM; i++) {
        r.chave = i;
        fwrite(&r, sizeof (Registro), 1, arq1);
    }
    fclose(arq1);

}
// função para criar o arquivo ordenado descendentemente, ou seja, em pos ordem

int arquivoOrdenadoDescendentemente(FILE *arq1, int TAM) {
    Registro r;
    int i, j;

    if ((arq1 = fopen("arquivodescendentemente.bin", "wb")) == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 0;
    }

    r.dado1 = 50000;
    strcpy(r.dado2, "abcdefghijkmnopq");

    j = TAM;

    for (i = 0; i < TAM; i++, j--) {
        r.chave = j;
        fwrite(&r, sizeof (Registro), 1, arq1);
    }
    fclose(arq1);

}

// função para criar o arquivo desordenado aleatoriamente, ou seja, em aleatorio

int arquivoDesordenadoAleatoriamente(FILE *arq1, int TAM) {
    Registro r;
    int i;
    srand(time(NULL));
    long int cont = 0;
    long int v = 0;

    if ((arq1 = fopen("arquivoaleatoriamente.bin", "wb")) == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 0;
    }
    r.dado1 = 1000;
    strcpy(r.dado2, "abcdefghijkmnopq");

     int *vetor;

    vetor = (int*) calloc(TAM, sizeof (int));

    while (cont < TAM) {
        v = (rand() % TAM + 1);
        if (vetor[v] != 1) {
            r.chave = v;
            fwrite(&r, sizeof (Registro), 1, arq1);
            cont++;
          //  printf("%ld ",cont);
             
        }
        vetor[v] = 1;
    }
    free(vetor);
   fclose(arq1);

}

