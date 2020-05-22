#include <stdio.h>
#include <assert.h>
#include "sudoku.h"



/*! \brief Le a configuracao inicial do tabuleiro de um arquivo
 *  \param nomeArquivo string com o nome do arquivo
 *  \param tab preenchido com os valores do arquivo 
 *  \return sucesso ou fracasso na leitura
 */
int Tabuleiro_inicializa(char* nomeArquivo, Tabuleiro* tab){
    assert(nomeArquivo && tab); // apontadores não nulos
    
    FILE* arq = fopen(nomeArquivo,"rt");
    if (arq == NULL) {
        return ERRO_ARQUIVO_INEXISTENTE;
    }
    // Le as linhas e colunas do arquivo
    int l,c;
    for (l=0; l < TABULEIRO_MAX; l++){
        for (c=0; c < TABULEIRO_MAX; c++){
            if (feof(arq)) {
                fclose(arq);
                return ERRO_ARQUIVO_FORMATO_INVALIDO;
            }
            fscanf(arq,"%d",&(tab->val[l][c]));
            if ((tab->val[l][c] < 0) || (tab->val[l][c] >9)) {
                fclose(arq);
                return ERRO_ARQUIVO_FORMATO_INVALIDO;
            }
        }
    }    
    fclose(arq);
    
    // Inicializa conflitos com falso
    int i, j;
    for(i=0;i<TABULEIRO_MAX;i++){
        tab->colunas[i].numero = 0;
        tab->linhas[i].numero = 0;
        tab->regioes[i].numero = 0;
        for(j=0;j<TABULEIRO_MAX;j++){
            tab->colunas[i].conflitos[j] = false;
            tab->linhas[i].conflitos[j] = false;
            tab->regioes[i].conflitos[j] = false;
        }
    }
    
    return SUCESSO;
}

/*! \brief Identifica células vazias de um tabuleiro de Sudoku.
 *         Elas conterão posição 0.
 *  \param tab endereço da variável de tabuleiro
 *  \param tab vetor de células vazias identificadas 
 *         (deve estar pré-alocado com TABULEIRO_MAX * TABULEIRO_MAX posições)   
 *  \return número de células vazias
 */
int Tabuleiro_defineVazias(Tabuleiro* tab, Celula* vazias) {
    assert(tab && vazias); // verifica apontadores não nulos
    
    int nVazias = 0;
    int l,c;
    for (l=0; l < TABULEIRO_MAX; l++) {
       for (c=0; c < TABULEIRO_MAX; c++) {
           if (tab->val[l][c] == 0){
               vazias[nVazias].l = l;
               vazias[nVazias].c = c;
               nVazias++;
           }
       }
    }
    return nVazias;
}

#define DIM_LINHA  0
#define DIM_COLUNA 1
#define DIM_REGIAO 2
////////////////////// Funções auxiliares de manipulação de regiao
// Regiao      0          1         2
//          0  1  2    3  4  5   6  7  8  
//          9 10 11   12 13 14  15 16 17
//         18 19 20   21 22 23  24 25 26 
//             3          4         5
//         27 28 29   30 31 32  33 34 35 
//         ...
/////////////////////////////////////////////////////////
short regiaoCelula(Celula* cel) {
    return cel->c/TABULEIRO_MAX + cel->l/TABULEIRO_MAX;
}

short linhaRegiao(short r) {
    return (r/REGIAO_MAX) * REGIAO_MAX;
}

short colunaRegiao(short r) {
    return (r%REGIAO_MAX) * REGIAO_MAX;
}

// Verifica se não há conflitos em uma linha, coluna ou região
// em tempo linear, contando quantas vezes cada valor aparece.
// Os valores são aramazenados no vetor vezes, que deve sempre
// conter 0 ou 1. Valores maiores definem conflitos.
// qual: LINHA, COLUNA ou REGIAO
// fixo: número do elemento fixo
// tab: endereco do tabuleiro
// invalido: conflitos do elemento
bool checaTodos(int qual, int fixo, Tabuleiro* tab, ElementoInvalido* invalido)  {
    assert(tab);
    // contador de vezes que um valor aparece
    int vezes[TABULEIRO_MAX+1];
    // indice de onde aparece o valor pela primeira vez
    int primeiro[TABULEIRO_MAX+1];   
    int v;
    for(v=0; v<TABULEIRO_MAX+1; v++) {
        vezes[v] = 0;
    }
    
    // percorre todo o elemento
    // se LINHA, c percorre colunas
    // se COLUNA, c percorre linhas
    // se REGIAO, c percorre posições da mesma 0 1 2/ 3 4 5/ 6 7 8
    int c;
    bool resultado = true;
    for(c=0; c<TABULEIRO_MAX; c++) {
        char valor;                 // valor da célu antual
        switch (qual) {
            case DIM_LINHA: 
                valor = tab->val[fixo][c];
                break;
            case DIM_COLUNA: 
                valor = tab->val[c][fixo];
                break;
            case DIM_REGIAO: 
                // indice no tabuleiro correspondente à c-ésima posição da 
                // região número fixo
                valor = tab->val[linhaRegiao(fixo)+(c/REGIAO_MAX)][colunaRegiao(fixo)+(c%REGIAO_MAX)];
                break;
            default:
                assert(0);
        }
        // Só faz computação de conflito para células ocupadas
        if (valor != 0) {
            vezes[valor]++;
            // conflito identificado
            if (vezes[valor]>1) {
                resultado = false;
                invalido->numero++;
                invalido->conflitos[primeiro[valor]] = true;
                // essa linha pode ser executada mais de uma vez, mas não há
                //problemas
                invalido->conflitos[c] = true;
            } else {
                primeiro[valor] = c;
            }
        }
    }
    return resultado;
}

bool checaLinha(int linha, Tabuleiro* tab){
    return checaTodos(DIM_LINHA, linha, tab, tab->linhas+linha);
}

bool checaColuna(int coluna, Tabuleiro* tab){
    return checaTodos(DIM_COLUNA, coluna, tab, tab->colunas+coluna);
}

bool checaRegiao(int regiao, Tabuleiro* tab){
    return checaTodos(DIM_REGIAO, regiao, tab, tab->regioes+regiao);
}

/*! \brief Verifica um tabuleiro definindo se ele é válido.
 *         Checa e armazena TODOS conflitos em linhas, colunas e regiões.
 *  \param tab endereço da variável de tabuleiro  
 *  \return se o tabuleiro é válido (sem conflitos) ou não.
 */
bool Tabuleiro_eValido(Tabuleiro* tab) {
    assert(tab); // verifica endereço não nulo
    
    // Armazena inconsistencias
    // Checa linhas
    bool resultado = true;
    int l;
    for (l=0; l<TABULEIRO_MAX; l++){
        if (!checaLinha(l,tab)) 
            resultado = false;
    }
    // Checa colunas
    int c;
    for(c=0; c<TABULEIRO_MAX; c++) {
        if (!checaColuna(c,tab))
            resultado = false;
    }
    // Checa regioes
    int r;
    for(r=0; r<TABULEIRO_MAX; r++){
        if (!checaRegiao(r,tab))
            resultado = false;
    }
    return resultado;
}

/*! \brief Define valores válidos para uma determinada célula, retornando
 *         no vetor valido.
 *  \param tab endereço da variável de tabuleiro 
 *  \param cel endereco da célula 
 *  \param validos vetor de TABULEIRO_MAX posições, para os valores válidos
 *  \return número de valores válidos
 */
int Tabuleiro_valoresValidos(Tabuleiro* tab, Celula* cel, char* validos)  {
    int nValidos = 0;
    bool ehValido[TABULEIRO_MAX+1]; // Marca valores validos
    char v;
    for(v = 0;v<=TABULEIRO_MAX;v++)
        ehValido[v] = true;
    
    // Invalidade valores da linha
    int l,c,r;
    for(l=0;l<TABULEIRO_MAX;l++) {
        ehValido[tab->val[l][cel->c]] = false;
    }
    //Invalida valores da coluna
    for(c=0;c<TABULEIRO_MAX;c++){
        ehValido[tab->val[cel->l][c]] = false;
    }
    //Invalida valores da regiao
    r = regiaoCelula(cel);
    for(l=linhaRegiao(r);l<linhaRegiao(r)+REGIAO_MAX;l++){
        for(c=colunaRegiao(r);c<colunaRegiao(c)+REGIAO_MAX;c++){
            ehValido[tab->val[l][c]] = false;
        }
    }
    // Coloca valores válidos restantes no vetor de retorno
    for(v=1;v<=TABULEIRO_MAX;v++) {
        if (ehValido[v]) {
            validos[nValidos++] = v;
        }
    }
    return nValidos;
}

void Tabuleiro_imprimeConflitos(char* onde, ElementoInvalido* invalido) {
    int l;
    for (l = 0; l < TABULEIRO_MAX; l++) {
        if (invalido[l].numero > 0) {
            printf("%s %d: ", onde, l + 1);
            int c;
            for (c = 0; c < TABULEIRO_MAX; c++) {
                if (invalido[l].conflitos[c])
                    printf("(%d,%d) ", l + 1, c + 1);
            }
            printf("\n");
        }
    }
}
int Tabuleiro_imprime(Tabuleiro* tab) {
    int l,c;
    for (l=0; l < TABULEIRO_MAX; l++){
       for (c=0; c < TABULEIRO_MAX; c++){
           if (tab->val[l][c] == 0) {
               printf("  ");
           } else {
               printf("%d ",tab->val[l][c]);
           }
       }
       printf("\n");
    }
}

