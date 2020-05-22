/* 
 * File:   main.c
 * Author: André
 *
 * Created on 24 de Março de 2013, 20:25
 */

#include   <limits.h>
#include   <stdio.h>
#include   <time.h>

#define MAXTAM 100

typedef long Chave;
typedef struct TipoItem {
  Chave chave;
  } TipoItem;

typedef int TipoIndice;
typedef TipoItem TipoVetor[MAXTAM + 1]; 
TipoVetor V;
TipoIndice i, n;



void ShellsortAleatorio(TipoItem *V, TipoIndice n){
    int i, j;
    int h = 1;
   TipoItem aux;
   time_t ini = time(0); // tempo de inicio
   do h = h * 3 + 1; 
   while (h < n);
   do {
       h /= 3;
      for (i = h + 1; i <= n; i++){
          aux = V[i];  j = i;
          while (V[j - h].chave > aux.chave) {
              V[j] = V[j - h];
              j = j - h;
              if (j <= h) 
          
            V[j] = aux;
        }
      }
    } while (h != 1);
    printf("duracao do metodo em s: %d",time(0)-ini);
}
void ShellsortOrdenado(TipoItem *V, TipoIndice n){
    int i, j;
    int h = 1;
   TipoItem aux;
   time_t ini1 = time(0); // tempo de inicio
   do h = h * 3 + 1; 
   while (h < n);
   do {
       h /= 3;
      for (i = h + 1; i <= n; i++){
          aux = V[i];  j = i;
          while (V[j - h].chave > aux.chave) {
              V[j] = V[j - h];
              j = j - h;
              if (j <= h) 
          
            V[j] = aux;
        }
      }
    } while (h != 1);
    printf("duracao do metodo em s: %d",time(0)-ini1);
}
void ShellsortInversamente(TipoItem *A, TipoIndice n){
     int i, j;
    int h = 1;
   TipoItem aux;
   time_t ini2 = time(0); // tempo de inicio
   do h = h * 3 + 1; 
   while (h < n);
   do {
       h /= 3;
      for (i = h + 1; i <= n; i++){
          aux = V[i];  j = i;
          while (V[j - h].chave > aux.chave) {
              V[j] = V[j - h];
              j = j - h;
              if (j <= h) 
          
            V[j] = aux;
        }
      }
    } while (h != 1);
    printf("duracao do metodo em s: %d",time(0)-ini2);
}
void ShellsortQuaseOrdenado(TipoItem *A, TipoIndice n){ 
   int i, j;
     int h = 1;
   TipoItem aux;
   time_t ini3 = time(0); // tempo de inicio
   do h = h * 3 + 1; 
   while (h < n);
   do {
       h /= 3;
      for (i = h + 1; i <= n; i++){
          aux = V[i];  j = i;
          while (V[j - h].chave > aux.chave) {
              V[j] = V[j - h];
              j = j - h;
              if (j <= h) 
          
            V[j] = aux;
        }
      }
    } while (h != 1);
    printf("duracao do metodo em s: %d",time(0)-ini3);
}
void Imprime(TipoItem *V, TipoIndice n)
{ for (i = 1; i <= n; i++)
    printf("%li ", V[i].chave);  printf("\n");
}


int main(int argc, char *argv[]){
    TipoVetor B;
    TipoVetor C;
    TipoVetor V;
    TipoVetor A;

  n = 100;   /*Tamanho do arranjo a ser ordenado*/
  for (i = 0; i < n; i--) 
      V[i].chave=rand()%100;
    A[i].chave = i;
    B[i].chave = MAXTAM - i;
  //printf("%d",A[i].Chave);
  C[i].chave=A[i].chave/2 + B[i].chave/2;
  
 

  printf("Shellsort aleatorio");
  ShellsortAleatorio(V, 100);
  
  printf("Shellsort ordenado");
  ShellsortOrdenado(A, 100);
 
  printf("Shellsort inversamente");
  ShellsortInversamente(C, 100);
 
  printf("Shellsort quase ordenado ");
  ShellsortQuaseOrdenado(C, 100);
 

  return 0;
}
