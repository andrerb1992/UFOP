/* 
 * File:   ArvoreBinaria.h
 * Author: USER
 *
 * Created on 12 de Maio de 2014, 16:43
 */

#ifndef ARVOREBINARIA_H
#define	ARVOREBINARIA_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include<string.h>
#include<ctype.h>

#include "Geral.h"


#define TAMP 4
#define TAMANHO_ARQ 100

typedef struct {
    int chave;
    int pag;
} TItem;
//
//typedef struct{
//    int chave;
//    double dado1;
//    long int dado2;
//    char dado3[500];
//}Registro;

typedef struct TNo {
    struct TNo* pEsq;
    struct TNo* pDir;
    TItem valor;
} TNo;

typedef struct {
    TNo* pRaiz;
} ArvoreBinaria;


void Arvore_Binaria(ArvoreBinaria* pAB, FILE* arq, int TAMANHO_ARQUIVO, int chave);
int desalocaSubarvore(TNo* pN);
void libera(ArvoreBinaria* pAB);
int insere_binaria(ArvoreBinaria * pAB, TItem *it);
int pesquisa(ArvoreBinaria* pAB, int chave, TItem* item);
int pesquisarecursia(TNo* ppRaiz, int chave, TItem* item);
int pesquisaSequencialBinaria(Registro * pPagina, Registro* r, int tamanho);





#endif	/* ARVOREBINARIA_H */

