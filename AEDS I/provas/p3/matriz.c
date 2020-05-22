
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matriz.h"

int Matriz_aloca(Matriz* matriz, int linhas, int colunas) {
    assert(matriz);
    
    
    matriz->val = (Inteiro**) malloc(linhas * sizeof (Inteiro*)); 

    if (matriz == NULL) {
        return MATRIZ_ERRO_MEMORIA;
    }

    int i;
    for (i = 0; i < linhas; i++) {
        matriz->val[i] = (Inteiro*) malloc(colunas * sizeof (Inteiro));
        if (matriz->val[i] == NULL) {
            return MATRIZ_ERRO_MEMORIA;
        }
    }
    matriz->nLinhas = linhas;
    matriz->nColunas = colunas;
    return MATRIZ_SUCESSO;
}

int Matriz_cria(char* arquivoEntrada, Matriz* matriz) {
    assert(arquivoEntrada && matriz);
    
    FILE* fp;
 
    if ((fp = fopen(arquivoEntrada, "r")) == NULL) {
        return MATRIZ_ERRO_CRIACAO;
    }
    int linhas, colunas;
    fscanf(fp, "%d %d", &linhas, &colunas);
    
    int resAloca = Matriz_aloca(matriz, linhas, colunas);
    if (resAloca != MATRIZ_SUCESSO)
        return resAloca;
    
    int i, j;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
    
            if (feof(fp)) return MATRIZ_ERRO_CRIACAO;
            fscanf(fp, "%d", &matriz->val[i][j]);
        }
    }
    fclose(fp);
    return MATRIZ_SUCESSO;
}


int Matriz_soma(Matriz* matrizA, Matriz* matrizB, Matriz* matrizResp) {
    assert(matrizA && matrizB && matrizResp);
    

    if ((matrizA->nLinhas == matrizB->nLinhas) && 
        (matrizA->nColunas == matrizB->nColunas)) {
        int resAloca = Matriz_aloca(matrizResp, matrizA->nLinhas, matrizA->nColunas);
        if (resAloca != MATRIZ_SUCESSO) return resAloca;
        
        int i, j;
        for (i = 0; i < matrizA->nLinhas; i++) {
            for (j = 0; j < matrizB->nColunas; j++) {
                matrizResp->val[i][j] = matrizA->val[i][j] + matrizB->val[i][j];
            }
        }
        return MATRIZ_SUCESSO;
    } else {
        return MATRIZ_ERRO_SOMA;
    }
}

void Matriz_destroi(Matriz* matriz) {
    assert(matriz);
    int i; 
    for (i = 0; i < matriz->nLinhas; i++)
        free(matriz->val[i]); 
    free(matriz->val); 
}


int Matriz_multiplica(Matriz* matrizA, Matriz* matrizB, Matriz* matrizResp) {
    assert(matrizA && matrizB && matrizResp);
    
 
    if (matrizA->nColunas == matrizB->nLinhas) {
        int resAloca = Matriz_aloca(matrizResp, matrizA->nLinhas, matrizB->nColunas);
        if (resAloca != MATRIZ_SUCESSO) return resAloca;
        
        int i, j, k;
        int soma;
        for (i = 0; i < matrizA->nLinhas; i++) {
            for (j = 0; j < matrizB->nColunas; j++) {
                soma = 0;
                for (k = 0; k < matrizA->nColunas; k++) {
                    soma += matrizA->val[i][k] * matrizB->val[k][j];
                }
                matrizResp->val[i][j] = soma;
            }
        }
        return MATRIZ_SUCESSO;
    } else {
        return MATRIZ_ERRO_MULTIPLICACAO;
    }

}

int Matriz_transposta(Matriz* matriz, Matriz* matrizResp) {
    assert(matriz &&  matrizResp);
    

    int resAloca = Matriz_aloca(matrizResp, matriz->nColunas, matriz->nLinhas);
    if (resAloca != MATRIZ_SUCESSO) return resAloca;
    int i, j;
    for (i = 0; i < matriz->nLinhas; i++) {
        for (j = 0; j < matriz->nColunas; j++) {
            matrizResp->val[j][i] = matriz->val[i][j];
        }
    }
}

int Matriz_grava(Matriz* matriz, char* arquivoSaida) {
    FILE* fp;
    if ((fp = fopen(arquivoSaida, "w")) == NULL) {
        return MATRIZ_ERRO_GRAVACAO;
    }
    fprintf(fp, "%d %d\n", matriz->nLinhas, matriz->nColunas);
    int i, j;
    for (i = 0; i < matriz->nLinhas; i++) {
        for (j = 0; j < matriz->nColunas; j++) {
            fprintf(fp, "%-3d", matriz->val[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return MATRIZ_SUCESSO;
}

void Matriz_mostra(Matriz* matriz) {
    int i, j;
    for (i = 0; i < matriz->nLinhas; i++) {
        for (j = 0; j < matriz->nColunas; j++) {
            printf("%4d", matriz->val[i][j]);
        }
        printf("\n");
    }
}




