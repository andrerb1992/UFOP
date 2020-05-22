#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#include "AcessoSequencialIndexado.h"
#include "Geral.h"
#include "Cria.h"

 int ntransferencias = 0;
 int comparacao = 0;

// essa função e a mesma função do slides que esta no main
// foi utilizada no .cpp para que haja mais clareza e adaptação a memoria externa
void AcessoSequencialIndexado(int chave, FILE* arq1, int TAM) {
    if ((arq1 = fopen("arquivo1.bin", "rb")) == NULL) {
        printf("Erro na abertura do arquivo1\n");
        return ;
    }
    tipoindice tab[TAM / TAMP + 1];
    Registro r, r1;

    int p = 0;
    int qtd = 0;

    fseek(arq1, 0, SEEK_END); // altera o endereço do ponteiro de um arquivo binário, ou seja, aponta para o final do arquivo
    qtd = (ftell(arq1) / sizeof (Registro)) % TAMP;
    int cont=0;
    fseek(arq1, 0, SEEK_SET);
    while (fread(&r, sizeof (Registro), 1, arq1) == 1) {
        cont++;
        if(cont % TAMP == 1){
        tab[p].chave = r.chave; // pegando primera chave da pagina
        //printf("teste 2 :%d\n", tab[p].chave);
        tab[p].posicao = p + 1; // posiçao da tabela de paginas
        p++;
        ntransferencias++;
    }
    }
    if (qtd != 0) {
        fread(&r, sizeof (Registro), qtd, arq1);
        tab[p].chave = r.chave; 
        tab[p].posicao = p + 1; 
        ntransferencias++;
    }
    r1.chave = chave;
 //   printf("%d\n",r1.chave);
    if (pesquisaS(tab, p, &r1, arq1)) {
//        printf("\n%ld\n%s\n\n", r1.dado1, r1.dado2);// imprimo o conteudo do arquivo binario
        printf("\nNumero de transferencia: %d\n", ntransferencias);// imprimo número de transferências (leitura) de itens da memória externa para a memória interna
        printf("\nNumero de comparacao entre chaves: %d\n", comparacao);// imprimo número de comparações entre chaves de pesquisa;
        } else
        printf("A chave nao se encontra no arquivo.\n");
    fclose(arq1);// fecha o arquivo
}
        
int pesquisaS(tipoindice tab[], int tamanho, Registro* r, FILE *arq1) {
    Registro pagina[TAMP];
    int i, quantitens;
    long desloc;
    // procura pela pagina onde o item pode se encontrar
    i = 0;
    while (i < tamanho && tab[i].chave <= r->chave) {
        i++;
        comparacao++;
    }
    // caso a chave desejada seja menor que a 1 chave, o item nao existe no arquivo
    if (i == 0)
        return 0;
    else{        
     if (i < tamanho)  // a ultima pode nao estar completa 
        quantitens = TAMP;
    
    else {
        fseek(arq1, 0, SEEK_END);
        quantitens = (ftell(arq1) / sizeof (Registro)) % TAMP;
        comparacao++;
    }
    // le  a pagina desejada do arquivo
    desloc = (tab[i - 1].posicao - 1) * TAMP * sizeof (Registro);
    fseek(arq1, desloc, SEEK_SET);
    fread(&pagina, sizeof (Registro), quantitens, arq1);
    ntransferencias++;
   comparacao++;
    for (i = 0; i < quantitens; i++)
        if (pagina[i].chave == r->chave) {
            *r = pagina[i];
            ntransferencias++;
            comparacao++;
            return 1;
      }
   comparacao++;
   return 0;
}
}


