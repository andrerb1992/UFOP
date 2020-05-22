/* 
 * File:   ordenacao.h
 * Author: André
 *
 * Created on 19 de Março de 2013, 14:17
 */

#ifndef ORDENACAO_H
#define	ORDENACAO_H

typedef long Chave;
typedef struct {
    Chave chave;
}Registro;


void Heap_Refaz(Registro* V, int , int );
void Heap_Constroi(Registro* V, int n);
void Heap_Aleatorio(Registro* V, int n);
void Heap_Ordenado(Registro* V, int n);
void Heap_Inversamente(Registro* V, int n);
void Heap_QuaseOrdenado(Registro* V, int n);

void QuickSortAleatorio(Registro* V, int n);
void QuickSortOrdenado(Registro* V, int n);
void QuickSortInversamente(Registro* V, int n);
void QuickSortQuaseOrdenado(Registro* V, int n);
void QuickSort_ordena(Registro* V, int esq, int dir);
void QuickSort_particao(Registro* V, int esq, int dir, int *i, int *j);
void Insercao (Registro* V, int n);
void imprimir(Registro* V, int n);
    
#endif	/* ORDENACAO_H */

