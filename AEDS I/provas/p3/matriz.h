

#ifndef MATRIZ_H
#define	MATRIZ_H


#define MATRIZ_SUCESSO            1 
#define MATRIZ_ERRO_SOMA          2
#define MATRIZ_ERRO_MULTIPLICACAO 3
#define MATRIZ_ERRO_CRIACAO       4
#define MATRIZ_ERRO_GRAVACAO      5
#define MATRIZ_ERRO_MEMORIA       6


typedef int Inteiro;

typedef struct {
    int nLinhas;
    int nColunas;
    Inteiro** val; 
} Matriz;

int Matriz_aloca(Matriz* matrizRet, int linhas, int colunas);

int Matriz_cria(char* arquivoEntrada, Matriz* matrizRet);

int Matriz_soma(Matriz* matrizA, Matriz* matrizB, Matriz* matrizResp);

void Matriz_destroi(Matriz* matriz);

int Matriz_multiplica(Matriz* matrizA, Matriz* matrizB, Matriz* matrizResp);


int Matriz_transposta(Matriz* matriz, Matriz* matrizResp);




void Matriz_mostra(Matriz* matriz);

int Matriz_grava(Matriz* matriz, char* arquivoSaida);

#endif	/* MATRIZ_H */

