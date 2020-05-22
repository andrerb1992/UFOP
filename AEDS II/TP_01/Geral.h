/* 
 * File:   Geral.h
 * Author: USER
 *
 * Created on 12 de Maio de 2014, 16:38
 */

#ifndef GERAL_H
#define	GERAL_H

#define TAMP 4
#define M 100

// definição de uma entrada da tabela de índice das páginas
typedef struct{
    int chave;
    int pos;
 }tipoitem;
// definição de um item do arquivo de dados
typedef struct{
    int chave;
    long int dado1;
    char dado2[1000];        
}Registro;

typedef struct{
    int posicao;
    int chave;
}tipoindice;



#endif	/* GERAL_H */

