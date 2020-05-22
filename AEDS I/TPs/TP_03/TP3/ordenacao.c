#include <stdio.h>
#include <stdlib.h>
#include "ordenacao.h"
#include <time.h>
//#define TAM 100;



void Heap_Refaz(Registro* V, int esq, int dir ){
    int i = esq;
    int j= (i * 2) + 1;
    Registro aux;
    aux = V[i];
    while (j <= dir) {
        if ((j < dir) && (V[j].chave < V[j+1].chave)) 
            j++; // j recebe o outro filho de i
        if(aux.chave >= V[j].chave)

            break; // heap foi refeito corretamente
         V[i] = V[j];
         i = j; 
         j = i*2 + 1; // j = primeiro filho de i
     }
     V[i] = aux;
 }
void Heap_Constroi(Registro* V, int n) { 
    int esq;
    esq = (n/2) - 1;
    
    while (esq >= 0) { 
        Heap_Refaz(V,esq,n - 1);
        esq--;
       
 }
}
void Heap_Aleatorio(Registro* V, int n){
    Registro ax;
   clock_t ini1, time; // tempo de inicio
   ini1=clock();
   //printf("HeaP aleatorio\n");
    Heap_Constroi(V, n);
    while (n > 1) {
        ax = V[n-1];
        V[n-1]= V[0];
        V[0] = ax;
        n--;
        Heap_Refaz(V, 0, n-1); // refaz o heap
        printf("\n");
         
        imprimir(V, n);
        
 }
    printf("duracao do metodo aleatorio e: %f milisegundo",((double)( time - ini1 ) / ((double)CLOCKS_PER_SEC )));;
    
    }
   
   

void Heap_Ordenado(Registro* V, int n) {
    Registro aux6;
    clock_t ini2, time2; // tempo de inicio
    ini2=clock();
    Heap_Constroi(V, n);
    while (n > 1) {
        aux6 = V[n-1];
        V[n-1] = V[0];
        V[0] = aux6;
        n--;
        Heap_Refaz(V, 0, n-1);// refaz o heap
        imprimir(V, n);       
 }   
     printf("duracao do metodo ordenado e: %f",((double)( time2 - ini2 ) / ((double)CLOCKS_PER_SEC )));
}
void Heap_Inversamente(Registro* V, int n){
    Registro aux1;
    clock_t ini3, time3; // tempo de inicio
    
    ini3=clock();    
    Heap_Constroi(V, n);
    while (n < 1) {
        aux1 = V[0];
        V[0] = V[n-1];
        V[n-1] = aux1;
        n++;
        Heap_Refaz(V, 0, n-1); // refaz o heap
    imprimir(V, n);  
 }
    
    printf("duracao do metodo inversamente e: %f",((double)( time3 - ini3 ) / ((double)CLOCKS_PER_SEC )));
    
    
}

void Heap_QuaseOrdenado(Registro* V , int n){
    Registro aux;
    clock_t ini4, time4; // tempo de inicio
    
    ini4=clock();    
    Heap_Constroi(V, n);
    while (n > 1) {
        aux = V[n-1];
        V[n-1] = V[0];
        V[0] = aux;
        n--;
        Heap_Refaz(V, 0, n-1); // refaz o heap
        imprimir(V, n);
        
 }

  
    printf("duracao do metodo quase ordenado e: %f",((double)( time4 - ini4 ) / ((double)CLOCKS_PER_SEC )));
   // printf("\n\n");
   
}
 


void QuickSortAleatorio(Registro *V, int n) {
   clock_t ini5, time5; // tempo de inicio
   ini5=clock();    
   QuickSort_ordena(V, 0, n-1); 
   imprimir( V, n);
   printf("duracao do metodo quase ordenado e: %f",((double)( time5 - ini5 ) / ((double)CLOCKS_PER_SEC )));
}


void QuickSortOrdenado(Registro *V, int n){
    clock_t ini6, time6; // tempo de inicio
    ini6=clock(); 
    QuickSort_ordena(V, 0, n-1);
    imprimir(V,  n);
    printf("duracao do metodo quase ordenado e: %f",((double)( time6 - ini6 ) / ((double)CLOCKS_PER_SEC )));
}
void QuickSortInversamente(Registro *V, int n){
    clock_t ini7, time7; // tempo de inicio
    ini7=clock(); 
    QuickSort_ordena(V, n-1, 0);
    imprimir(V, n);
    printf("duracao do metodo quase ordenado e: %f",((double)( time7 - ini7 ) / ((double)CLOCKS_PER_SEC )));
}

void QuickSortQuaseOrdenado(Registro *V, int n){
    clock_t ini8, time8; // tempo de inicio
    ini8=clock(); 
    QuickSort_ordena(V, 0, n-1);
    imprimir( V, n);
    printf("duracao do metodo quase ordenado e: %f",((double)( time8 - ini8 ) / ((double)CLOCKS_PER_SEC )));
}

    
void QuickSort_ordena(Registro* V, int esq, int dir) { 
  int i, j, n;
  if(dir - esq < 10)
     Insercao (V, n); 
    QuickSort_particao(V, esq, dir, &i, &j);
      if (esq < j)
          QuickSort_ordena(V, esq, j);
      if (i < dir)
          QuickSort_ordena(V, i, dir);
    }

void QuickSort_particao(Registro *v, int esq, int dir, int *i, int *j) { 
    Registro pivo;
    Registro aux;
     *i = esq; *j = dir;
    pivo = v[(*i + *j)/2]; /* obtem o pivo x */
    do { 
    while (pivo.chave > v[*i].chave) (*i)++;
    while (pivo.chave < v[*j].chave) (*j)--;
    if (*i <= *j) { 
     aux = v[*i]; 
     v[*i] = v[*j]; 
     v[*j] = aux;
     (*i)++; (*j)--;
     }
     } 
    while (*i <= *j);
}

void Insercao (Registro* V, int n) {
    int i,j;
    for (i = 0; i <50; i++) {
        V[n] = V[i];
        j = i + 1;
        while (V[n].chave > V[j].chave) {
            V[j - 1] = V[j];
            j++;
            }
        V[j - 1] = V[n];
        }
}


void imprimir(Registro *V, int n){
     int i;
     for (i = 0; i < n; i++){
         printf("%2d ",V[i].chave);         
     }
     printf("\n");
 }
