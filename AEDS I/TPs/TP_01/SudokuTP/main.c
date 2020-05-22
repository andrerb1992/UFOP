/* 
 * File:   main.c
 * Author: Andréa Iabrudi
 *
 * Created on 10 de Dezembro de 2012, 14:16
 */

#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

/*
 * 
 */
int main(int argc, char** argv) {

    
    if (argc < 2){
        printf("Uso: %s <arquivo_tabuleiro>\n", argv[0]);
        return (EXIT_FAILURE);
    }
    printf("%s\n", argv[1]);
    //Le arquivo com tabuleiro
    Tabuleiro sudoku;
    if (Tabuleiro_inicializa(argv[1], &sudoku) != SUCESSO) {
        printf("Arquivo de entrada %s com formato invalido.\n", argv[1]);
        return(EXIT_FAILURE);
    }
    Tabuleiro_imprime(&sudoku);
    
    // Recupera celulas vazias
    Celula vazias[TABULEIRO_MAX*TABULEIRO_MAX];
   
    int nVazias = Tabuleiro_defineVazias(&sudoku, vazias);
    printf("Numero de Celulas Vazias: %d\n", nVazias);
    
    //Verifica se tabuleiro é valido
    if (Tabuleiro_eValido(&sudoku)) {
        if (nVazias == 0) {
            printf("Jogo completo. Voce ganhou!\n");
        } else {
            printf("Voce esta no caminho certo. Sugestoes:\n");
            int c;
            char validos[9];
            for(c = 0; c < nVazias; c++){
                int nValidos = Tabuleiro_valoresValidos(&sudoku, vazias+c, validos);
                printf("(%d,%d): ",vazias[c].l, vazias[c].c);
                int v;
                for(v=0; v < nValidos; v++)
                    printf("%d ",validos[v]);
                printf("\n");
            }
        }
    } else {
        // Imprime conflitos
        printf("Alguma coisa deu errado... Invalidos:\n");
        Tabuleiro_imprimeConflitos("Linha", sudoku.linhas);
        Tabuleiro_imprimeConflitos("Coluna", sudoku.colunas);
        Tabuleiro_imprimeConflitos("Regiao", sudoku.regioes);
    }
    return (EXIT_SUCCESS);
   
}

