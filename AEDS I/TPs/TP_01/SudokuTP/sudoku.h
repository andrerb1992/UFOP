/* 
 * File:   sudoku.h
 * Author: Andréa Iabrudi Tavares
 *
 * Created on 15 de Dezembro de 2012, 10:19
 */

#ifndef SUDOKU_H
#define	SUDOKU_H

/*!
 * Tipo lógico, imita C++
 */
typedef char bool;
#define true  1
#define false 0

///////////////////////////////// TAD Tabuleiro

/*
 * Implementa o TAD Tabuleiro para Sudoku
 * Independente do tamanho, pode basta alterar valores de REGIAO_MAX
 */
#define REGIAO_MAX    3
#define TABULEIRO_MAX REGIAO_MAX * REGIAO_MAX

/* 
 * Tipo Celula 
 * l,c: guarda linha e coluna (0..TABULEIRO_MAX-1)
 */
typedef struct {
  short l;
  short c;
} Celula;

/* 
 * Tipo ElementoInvalido
 * conflitos: Invalidos num elemento (linha/coluna/regiao)
 *             Numeração na região é pela linhas e colunas
 */
typedef struct {
    int   numero;
    bool  conflitos[TABULEIRO_MAX];
} ElementoInvalido;

/*
 *  TAD Tabuleiro
 *  val: guarda os valores no tabuleiro
 *  linhas, colunas, regioes: conflitos
 */
typedef struct {
    char                val[TABULEIRO_MAX][TABULEIRO_MAX];
    ElementoInvalido    linhas[TABULEIRO_MAX];
    ElementoInvalido    colunas[TABULEIRO_MAX];
    ElementoInvalido    regioes[TABULEIRO_MAX];
} Tabuleiro;

/*!
 * Operações do TAD Tabuleiro
 */
#define SUCESSO 0
#define ERRO_ARQUIVO_INEXISTENTE         1
#define ERRO_ARQUIVO_FORMATO_INVALIDO    2
int Tabuleiro_inicializa(char*, Tabuleiro*);

int Tabuleiro_defineVazias(Tabuleiro*,Celula*);

bool Tabuleiro_eValido(Tabuleiro*);

int Tabuleiro_valoresValidos(Tabuleiro*, Celula*, char*);

void Tabuleiro_imprimeConflitos(char*, ElementoInvalido*);
#endif	/* SUDOKU_H */

