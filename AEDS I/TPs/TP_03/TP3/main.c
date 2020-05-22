/* 
 * File:   main.c
 * Author: André
 *
 * Created on 19 de Março de 2013, 14:16
 */

#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"
#include <time.h>
#define TAM 10

/*
 * 
 */
int main(int argc, char** argv) {
    
    Registro V[100];
    Registro aux[100];
    Registro aux1[100];
    Registro aux3[100];
    int i;
    
    srand(time(NULL));
    for(i=0; i<TAM;i++){
        V[i].chave=rand()%100;
        
   }
    for(i=0;i<TAM;i++){
        aux[i].chave = i;
        aux3[i].chave = (V[i].chave + aux[i].chave)/2;
    }  
    for(i=TAM; i > 0;i--){
        aux1[i].chave=i;
    }
  
    
    printf("Aleatorio\n");
    Heap_Aleatorio(V ,10);
    printf("\n");
    printf("Ordenado\n");
    Heap_Ordenado(aux ,10);
    printf("\n");
    printf("Inversamente\n");
    Heap_Inversamente(aux1 ,10);
    printf("\n");
    printf("Quase Ordenado\n");
    Heap_QuaseOrdenado(aux3 ,10);
    printf("\n");
    
    
    
    printf("Aleatorio do quicksort\n"); 
    QuickSortAleatorio(V ,100);
    printf("\n");
    printf("Quase Ordenado do quicksort\n");
    QuickSortOrdenado(aux ,100);
    printf("\n");
    printf("Inversamente Ordenado do quicksort\n");
    QuickSortInversamente(aux1 ,100);
    printf("\n");
    printf("Quase Ordenado do quicksort\n");
    QuickSortQuaseOrdenado(aux3 ,100);
    imprimir(V , 10);

    return (EXIT_SUCCESS);
}



