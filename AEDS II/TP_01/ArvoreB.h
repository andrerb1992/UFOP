/* 
 * File:   ArvoreB.h
 * Author: USER
 *
 * Created on 12 de Maio de 2014, 16:41
 */

#ifndef ARVOREB_H
#define	ARVOREB_H



#include "Geral.h"
   
typedef long TipoChave;

//typedef struct TipoRegistro {
//TipoChave Chave;
//} tipoitem;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina{
    
    short n;
    tipoitem r[2*M];
    TipoApontador p[2*M + 1];
    
}TipoPagina;

void Arvore_B(FILE* arq, int chave);
void insere(tipoitem indice, TipoApontador* item);
void insereNaPagina(TipoApontador Ap, tipoitem Reg, TipoApontador ApDir);
void ins(tipoitem Reg, TipoApontador Ap, short *cresceu, tipoitem* RegRetorno, TipoApontador* ApRetorno);
int pesquisa(tipoitem* item, TipoApontador Ap);
int pesquisaSequencialB(Registro* pagina, Registro* reg, int tamanho);
void emOrdem(TipoApontador Ap);



#endif	/* ARVOREB_H */

