#include "AmostraDados.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

int AmostraDados_leitura(AmostraDados* amostra) {
    assert(amostra);

    scanf("%d", &(amostra->tamanho));
    if (amostra->tamanho <= 0) {
        return ERRO_LEITURA;
    }
    amostra->dados = (int*)malloc(amostra->tamanho * sizeof(int));
    if (amostra->dados == NULL) {
        return ERRO_ALOCACAO;
    }
    int i;
    for(i = 0; i < amostra->tamanho; i++) {
        scanf("%d",amostra->dados+i);
        if ((amostra->dados[i] < VALOR_MIN) ||
             (amostra->dados[i] > VALOR_MAX))  {
            AmostraDados_destroi(amostra);
            return ERRO_LEITURA;
        }
    }
    return SUCESSO;
    
}

double AmostraDados_mediaAritmetica(AmostraDados* amostra) {
    assert(amostra);
    
    int soma = 0;
    int i;
    for(i = 0; i < amostra->tamanho; i++)
         soma += amostra->dados[i];
    return (double)soma/(double)amostra->tamanho;
    
}

double AmostraDados_desvioPadrao(AmostraDados* amostra) {
    assert(amostra);
    
    double media = AmostraDados_mediaAritmetica(amostra);
    double soma = 0;
    int i;
    for(i = 0; i < amostra->tamanho; i++)
         soma += (amostra->dados[i] - media)*(amostra->dados[i] - media);
    return sqrt(soma/(double)(amostra->tamanho - 1));
}


void histograma(AmostraDados* amostra, int* hist) {
    assert(amostra && hist);
  int i; 
  for (i = 0; i < VALOR_MAX-VALOR_MIN+1; i++)
        hist[i] = 0;
  for (i = 0; i < amostra->tamanho; i++)
        hist[amostra->dados[i]-VALOR_MIN]++;  
}


int AmostraDados_moda(AmostraDados* amostra) {
    assert(amostra);
    
    int hist[VALOR_MAX-VALOR_MIN+1];
    histograma(amostra, hist);

    // moda é o valor que mais aparece -- máximo do histograma
    int v;
    int moda = 0;
    for (v=1; v < VALOR_MAX-VALOR_MIN+1; v++)
        if (hist[v] > hist[moda])
            moda = v;
    return moda + VALOR_MIN;
}


int AmostraDados_mediana(AmostraDados* amostra) {
    assert(amostra);
    
    int hist[VALOR_MAX-VALOR_MIN+1];
    histograma(amostra, hist);
   
    int v;
    int soma = 0;
    for (v=0; (soma < (amostra->tamanho+1)/2); v++)
        soma += hist[v];
    
    int mediana = v-1+VALOR_MIN; 
    
   
    if (amostra->tamanho%2) {
        return mediana; 
    } else {
        
        if (soma  > (amostra->tamanho/2)) {
            return mediana;
        } else {
          
            for(; hist[v] == 0; v++);
            return (mediana+ (v + VALOR_MIN))/2;
        }
    }
}



void AmostraDados_destroi(AmostraDados* amostra) {
    free(amostra->dados);
}