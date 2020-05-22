#include "ArvoreBinaria.h"
#include <assert.h>
#include <time.h>

//#define TAMANHO_ARQUIVO 500
//#define TAM_PAGINA 15

int numero_transferencia = 0;
int comp2T = 0;

// essa função e a mesma função do slides que esta no main
// foi utilizada no .cpp para que haja mais clareza e adaptação a memoria externa

void Arvore_Binaria(ArvoreBinaria* pAB, FILE* arq, int TAMANHO_ARQUIVO, int chave) {
    assert(pAB);

    pAB->pRaiz = NULL;
    Registro aux[TAMP];
    TItem it[TAMP];
    int qtd;
    fseek(arq, 0, SEEK_END); // altera o endereço do ponteiro de um arquivo binário, ou seja, aponta para o final do arquivo
    qtd = (ftell(arq) / sizeof (Registro)) % TAMP;
    fseek(arq, 0, SEEK_SET);

    int j = 0;


    while (fread(&aux, sizeof (Registro), TAMP, arq) == TAMP) {
        for (int i = 0; i < TAMP; i++) {
            it[i].chave = aux[i].chave;
            it[i].pag = j;
            insere_binaria(pAB, &it[i]);
        }

        j++;
        numero_transferencia++;
    }

    rewind(arq);

    if (qtd != 0) {
        fread(&aux, sizeof (Registro), qtd, arq);
        for (int i = 0; i < qtd + 2; i++) {
            it[i].chave = aux[i].chave;
            it[i].pag = j;
            pAB->pRaiz->pDir = NULL;
            pAB->pRaiz->pEsq = NULL;
            insere_binaria(pAB, &it[i]);
        }
        numero_transferencia++;

    } else
        qtd = TAMP;

    TItem res;
    if (pesquisa(pAB, chave, &res)) {
        long desloca;
        desloca = sizeof (Registro) * TAMP * (res.pag);
        fseek(arq, desloca, SEEK_SET);
        fread(&aux, sizeof (Registro), qtd, arq);
        numero_transferencia++;

        Registro reg;
        reg.chave = res.chave;
        //   printf("%d\n",res.chave);


        if (res.pag == TAMANHO_ARQUIVO / TAMP) {
            if (pesquisaSequencialBinaria(aux, &reg, qtd)) {
                printf("Numero de transferencia: %d\n", numero_transferencia); // imprimo número de transferências (leitura) de itens da memória externa para a memória interna
                printf("Numero de comparacao entre chaves: %d\n", comp2T); // imprimo número de comparações entre chaves de pesquisa
                return;
            }
        } else {
            if (pesquisaSequencialBinaria(aux, &reg, TAMP)) {
                printf("\nNumero de transferencia: %d\n", numero_transferencia);
                printf("\nNumero de comparacao entre chaves: %d\n", comp2T);
                return;
            }
        }
    } else {
        printf("A chave nao se encontra no arquivo.\n");
        return;
    }

}

// função utilizada para liberar espaço na memoria 

int desaloca(TNo* ppRaiz) {
    if (ppRaiz == NULL) {
        return 0;
    } else {
        desaloca(ppRaiz->pEsq);
        desaloca(ppRaiz->pDir);
        free(ppRaiz);
    }
}

void libera(ArvoreBinaria* ppRaiz) {
    assert(ppRaiz);
    desaloca(ppRaiz->pRaiz);

}
// inserção 

int insere_binaria(ArvoreBinaria * pAB, TItem *it) {

    if (pAB->pRaiz == NULL) {
        pAB->pRaiz = (TNo *) calloc(1, sizeof (TNo));
        pAB->pRaiz->valor.chave = it->chave;
        pAB->pRaiz->valor.pag = it->pag;
        pAB->pRaiz->pDir = NULL;
        pAB->pRaiz->pEsq = NULL;

    }

    TNo* pPai = pAB->pRaiz;
    int achou = 0;
    while (!achou) {
        if (pPai->valor.chave < it->chave) {
            if (pPai->pEsq == NULL)
                achou = 1;
            else
                pPai = pPai->pEsq;
            comp2T++;
        } else if (pPai->valor.chave > it->chave) {
            if (pPai->pDir == NULL)
                achou = 1;
            else
                pPai = pPai->pDir;
            comp2T++;
        } else
            return 0;
    }

    if (pPai->valor.chave < it->chave) {
        pPai->pEsq = (TNo *) calloc(1, sizeof (TNo));
        pPai->pEsq->valor.chave = it->chave;
        pPai->pEsq->valor.pag = it->pag;
        comp2T++;
    } else {
        pPai->pDir = (TNo *) calloc(1, sizeof (TNo));
        pPai->pDir->valor.chave = it->chave;
        pPai->pDir->valor.pag = it->pag;
    }

    return 1;
}

int pesquisa(ArvoreBinaria* pAB, int chave, TItem* item) {
    return pesquisarecursia(pAB->pRaiz, chave, item);
}

int pesquisarecursia(TNo* ppRaiz, int c, TItem* item) {
    if (ppRaiz == NULL)
        return 0;
    if (ppRaiz->valor.chave < c) {

        comp2T++;
        return pesquisarecursia(ppRaiz->pEsq, c, item);
    } else if (ppRaiz->valor.chave > c) {

        comp2T++;
        return pesquisarecursia(ppRaiz->pDir, c, item);
    } else {
        item->chave = ppRaiz->valor.chave;
        item->pag = ppRaiz->valor.pag;
        return 1;
    }
}

int pesquisaSequencialBinaria(Registro * pPagina, Registro* r, int tamanho) {

    for (int i = 0; i < tamanho; i++) {
        comp2T++;
        if (pPagina[i].chave == r->chave) {
            r->chave = pPagina[i].chave;
            r->dado1 = pPagina[i].dado1;
            strcpy(r->dado2, pPagina[i].dado2);
            return 1;
        }
    }
    return 0;
}


