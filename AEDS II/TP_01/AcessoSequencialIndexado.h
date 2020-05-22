/* 
 * File:   AcessoSequencialIndexado.h
 * Author: USER
 *
 * Created on 12 de Maio de 2014, 16:38
 */

#ifndef ACESSOSEQUENCIALINDEXADO_H
#define	ACESSOSEQUENCIALINDEXADO_H

#include "Geral.h"



void AcessoSequencialIndexado(int chave, FILE* arq1, int TAM);
int pesquisaS(tipoindice tab[], int tamanho, Registro* r, FILE *arq1) ;


#endif	/* ACESSOSEQUENCIALINDEXADO_H */

