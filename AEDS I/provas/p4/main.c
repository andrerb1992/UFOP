

#include <stdio.h>
#include <stdlib.h>
#include "AmostraDados.h"

int main(int argc, char** argv) {

    int numeroAmostras;
    printf("Numero de amostras:");
    scanf("%d ", &numeroAmostras);
    int a;
    for (a = 0; a < numeroAmostras; a++) {
        AmostraDados amostra;
        if (AmostraDados_leitura(&amostra) == SUCESSO)  {
            printf("Media %.3lf Moda %d Mediana %d",
                    AmostraDados_mediaAritmetica(&amostra),
                    AmostraDados_moda(&amostra),
                    AmostraDados_mediana(&amostra));
            AmostraDados_destroi(&amostra);
        } else {
            printf("Erro de leitura\n");
        }
    }
    return (EXIT_SUCCESS);
}

