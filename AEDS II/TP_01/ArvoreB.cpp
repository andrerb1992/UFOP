#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include"ArvoreB.h"
#include "Geral.h"
#include "AcessoSequencialIndexado.h"

int numero_transf = 0;
int comparacao_total = 0;

// essa função e a mesma função do slides que esta no main
// foi utilizada no .cpp para que haja mais clareza e etc

void Arvore_B(FILE* arq, int chave) {
    TipoApontador Arvore_B = NULL;
    Registro aux[TAMP];
    tipoitem reg, reg2;
    int qtd = 0;
    fseek(arq, 0, SEEK_END); //altera o endereço do ponteiro de um arquivo binário, ou seja, aponta para o final do arquivo
    qtd = (ftell(arq) / sizeof (Registro)) % TAMP; // qtd recebe  a posição
    fseek(arq, 0, SEEK_SET); //altera o endereço do ponteiro de um arquivo binário, ou seja, aponta para o final do arquivo
    int i = 1;
    while (fread(&aux, sizeof (Registro), TAMP, arq) == TAMP) { // ira ler o arquivo binario
        for (int j = 0; j < TAMP; j++) {
            reg.chave = aux[j].chave;
            reg.pos = i;
            insere(reg, &Arvore_B); // chamo a função insere
        }
        i++;
        numero_transf++;
    }
    if (qtd != 0) {
        fread(&aux, sizeof (Registro), qtd, arq); //  enquanto meu arquivo tiver posição diferente de 0 leio meu arquivo binario
        for (int j = 0; j < qtd; j++) {
            reg.chave = aux[j].chave;
            reg.pos = i;
            insere(reg, &Arvore_B); // chamo a função insere
        }
        numero_transf++;
    }//busco meu arquivo
    Registro aux2;
    int desloca = 0;
    reg2.chave = chave;
    reg2.pos = reg.pos;
    aux2.chave = reg2.chave;



    if (pesquisa(&reg2, Arvore_B)) { // chamo a função pesquisa
        if (reg.pos != i || qtd == 0) {
            qtd = TAMP;
        }
        desloca = (reg2.pos - 1) * TAMP * sizeof (Registro);
        fseek(arq, desloca, SEEK_SET);
        fread(&aux, sizeof (Registro), qtd, arq);
        numero_transf++; // conta numero de tranferencias....
        if (pesquisaSequencialB(aux, &aux2, qtd)) {
            printf("Numero de transferencia: %d\n", numero_transf); // imprimo número de transferências (leitura) de itens da memória externa para a memória interna;
            printf("Numero de comparacao entre chaves: %d\n", comparacao_total); // imprimo número de comparações entre chaves de pesquisa;
        }

    } else { // caso nao acha a chave no arquivo
        printf("A chave nao esta presente no arquivo\n");
    }
    fclose(arq);
    delete(Arvore_B); // libera memoria
}

void insere(tipoitem indice, TipoApontador* item) { // insercao dos dados 
    short aux;
    tipoitem retorno;
    TipoPagina *retorno_t, *temp;
    ins(indice, *item, &aux, &retorno, &retorno_t);
    if (aux) {
        temp = (TipoPagina*) calloc(1, sizeof (TipoPagina));
        temp->n = 1;
        temp->r[0] = retorno;
        temp->p[1] = retorno_t;
        temp->p[0] = *item;
        *item = temp;
    }
}

void insereNaPagina(TipoApontador Ap, tipoitem Reg, TipoApontador ApDir) { // Procedimento auxiliar

    short NaoAchouPosicao;
    int k;

    k = Ap->n;
    NaoAchouPosicao = (k > 0);

    while (NaoAchouPosicao) {
        if (Reg.chave >= Ap->r[k - 1].chave) {
            comparacao_total++;
            NaoAchouPosicao = false;
            break;
        }

        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k];
        k--;

        if (k < 1) {
            NaoAchouPosicao = false;
        }
    }

    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

void ins(tipoitem Reg, TipoApontador Ap, short *cresceu, tipoitem* RegRetorno, TipoApontador* ApRetorno) { // Refinamento Final
    long i;
    long j;
    i = 1;
    TipoApontador ApTemp;

    if (Ap == NULL) {
        *cresceu = true;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }
    while (i < Ap->n && Reg.chave > Ap->r[i - 1].chave) {
        comparacao_total++;
        i++;
    }
    if (Reg.chave == Ap->r[i - 1].chave) {
        printf("Erro\n");
        *cresceu = false;
        comparacao_total++;
        return;
    }
    if (Reg.chave < Ap->r[i - 1].chave) {
        i--;
        comparacao_total++;
    }
    ins(Reg, Ap->p[i], cresceu, RegRetorno, ApRetorno);
    if (!*cresceu) {
        return;
    }
    if (Ap->n < 2 * M) {
        insereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *cresceu = false;
        return;
    }
    ApTemp = (TipoApontador) calloc(1, sizeof (TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    if (i < M + 1) {
        insereNaPagina(ApTemp, Ap->r[2 * M - 1], Ap->p[2 * M]);
        Ap->n--;
        insereNaPagina(Ap, *RegRetorno, *ApRetorno);
    } else {
        insereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
    }
    for (j = M + 2; j < 2 * M; j++) {
        insereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j]);
    }
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M + 1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

int pesquisa(tipoitem* item, TipoApontador Ap) {
    long i = 1;
    if (Ap == NULL) {
        printf("ERRO\n ");
        return 0;
    }
    while (i < Ap->n && item->chave > Ap->r[i - 1].chave) { // pesquisa sequencial para encontra a chave desejada
        i++;
        comparacao_total++;
    }
    if (item->chave == Ap->r[i - 1].chave) { // verifica se a chave foi localizada
        item->pos = Ap->r[i - 1].pos;
        comparacao_total++;
        return 1;
    }
    if (item->chave < Ap->r[i - 1].chave) { // ativa recursivamente a função recursiva para os filhos da direita ou esquerda
        comparacao_total++;
        pesquisa(item, Ap->p[i - 1]);
    } else {
        pesquisa(item, Ap->p[i]);
    }
    return 1;
}

int pesquisaSequencialB(Registro* pagina, Registro* reg, int tamanho) { // utilizo essa função para pesquisar elemento por elemento no vetor
    for (int i = 0; i < tamanho; i++) {
        comparacao_total++;
        if (pagina[i].chave == reg->chave) {
            reg->chave = pagina[i].chave;
            reg->dado1 = pagina[i].dado1;
            strcpy(reg->dado2, pagina[i].dado2);
            return 1;
        }
    }
    return 0;
}


