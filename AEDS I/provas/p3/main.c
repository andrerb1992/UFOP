

#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"


int main(int argc, char** argv) {

    Matriz a;
    int resCria;
    if  ((resCria = Matriz_cria("mtr1.txt", &a)) == MATRIZ_SUCESSO) {
        printf("Matriz A:\n");
        Matriz_mostra(&a);
    } else {
        if (resCria == MATRIZ_ERRO_MEMORIA) {
            printf("Erro: memoria insuficiente\n");
            return(EXIT_FAILURE);
        } else {
            printf("Erro: arquivo mtr1.txt inexistente ou invalido\n");
        }
    }
    printf("\n");
    
    Matriz b;
    if ((resCria = Matriz_cria("mtr2.txt", &b)) == MATRIZ_SUCESSO) {
        printf("Matriz B:\n");
        Matriz_mostra(&b);
    } else {
        if (resCria == MATRIZ_ERRO_MEMORIA) {
            printf("Erro: memoria insuficiente\n");
            return (EXIT_FAILURE);
        } else {
            printf("Erro: arquivo mtr2.txt inexistente ou invalido\n");
        }
    }
    printf("\n");

    Matriz soma;
    if (Matriz_soma(&a, &b, &soma) == MATRIZ_SUCESSO) {
        printf("A + B:\n");
        Matriz_mostra(&soma);
        if (Matriz_grava(&soma, "soma.txt") == MATRIZ_SUCESSO) {
            printf("Arquivo gravado.\n");
        } else {
            printf("Erro na gravacao do aquivo.\n");
        }
        Matriz_destroi(&soma);
    } else {
        printf("Erro na operacao soma de matrizes: Dimensao de A diferente da dimensao de B\n");
    }
    printf("\n");

    Matriz produto;
    if (Matriz_multiplica(&b, &a, &produto) == MATRIZ_SUCESSO) {
        printf("B * A:\n");
        Matriz_mostra(&produto);
        if (Matriz_grava(&produto, "produto.txt") == MATRIZ_SUCESSO) {
            printf("Arquivo gravado.\n");
        } else {
            printf("Erro na gravacao do arquivo.\n");
        }
        Matriz_destroi(&produto);
    } else {
        printf("Erro na operacao de multiplicacao de matrizes: Dimensoes incimpativeis\n");
    }
    printf("\n");

    Matriz transposta;
    Matriz_transposta(&b, &transposta);
    printf("Matriz B Transposta:\n");
    Matriz_mostra(&transposta);
    if (Matriz_grava(&transposta, "transposta.txt") == MATRIZ_SUCESSO) {
        printf("Arquivo gravado.\n");
    } else {
        printf("Erro na gravacao do arquivo.\n");
    }
    printf("\n");
    Matriz_destroi(&transposta);
    
    Matriz_destroi(&a);
    Matriz_destroi(&b);
    return (EXIT_SUCCESS);
}

