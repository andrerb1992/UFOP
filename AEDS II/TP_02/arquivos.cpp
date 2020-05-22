/* 
 * File:   main.cpp
 * Author: Leonardo Isaac
 *
 * Created on 16 de Janeiro de 2014, 20:31
 */

#include <cstdlib>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <limits.h>

using namespace std;

typedef struct { // estrutura que repesenta um dado manipulado no arquivo
    long insc;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
} TipoDados;

int print(FILE *arquivo, int tam, char *nome) { // imprime arquivo de acordo com o nome e tamanho
    TipoDados dado;
    if ((arquivo = fopen(nome, "rb")) == NULL) { //abre arquivo binário de acordo com o nome recebido na função
        cout << "erro ao abrir arquivo" << endl;
        return 0;
    }
    for (int i = 0; i < tam; i++) { // Lê o arquivo de acordo com o tamanho passado como argumento
        fread(&dado, sizeof (TipoDados), 1, arquivo);
        cout << dado.insc << " " << dado.nota << " " << dado.estado << " " << dado.cidade << dado.curso << endl; // imprime um dado lido
    }
    fclose(arquivo); // fecha arquivo
    return 1;
}
int txt_para_binario() { // converte o arquivo PROVAO.TXT para PROVAOBIN.bin
    FILE *entrada, *saida;
    long insc;
    double nota;
    char estado[3];
    char cidade[53];
    char curso[31];
    TipoDados dado;

    if ((entrada = fopen("PROVAO.txt", "r")) == NULL) { // abre PROVAO.TXT para leitura 
        cout << "erro ao abrir arquivo PROVAO.txt" << endl;
        return 0;
    }
    if ((saida = fopen("PROVAOBIN.bin", "wb")) == NULL) { // abre PROVAOBIN.bin para escrita 
        cout << "erro ao abrir arquivo PROVAOBIN.bin" << endl;
        return 0;
    }

    while (!feof(entrada)) { // lê dados do arquivo de entrada
        fscanf(entrada, "%ld", &insc);
        fscanf(entrada, "%lf", &nota);
        fscanf(entrada, "%s", estado);
        fscanf(entrada, "%50[A-Z ]s%*c", cidade);
        fscanf(entrada, "%30[A-Z ]s%*c", curso);
        int i;
        dado.insc = insc; // atribui dados à estrutura 
        dado.nota = nota;
        for (i = 0; i < 2; i++)
            dado.estado[i] = estado[i];
        dado.estado[i] = '\0'; //'\0' inserido para sinalizar o final da cadeia
        for (i = 0; i < 50; i++)
            dado.cidade[i] = cidade[i];
        dado.cidade[i] = '\0'; //'\0' inserido para sinalizar o final da cadeia
        for (i = 0; i < 30; i++)
            dado.curso[i] = curso[i];
        dado.curso[i] = '\0'; //'\0' inserido para sinalizar o final da cadeia 
        fwrite(&dado, sizeof (TipoDados), 1, saida); // grava estrututra no arquivo de saída 
    }
    fclose(entrada); //fecha arquivos
    fclose(saida);
    // imprime arquivo gerado  
    //        cout << "erro ao abrir arquivo" << endl;
    //        return 0;
    //    }
    //    while (!feof(saida)) {
    //        fread(&dado, sizeof (TipoDados), 1, saida);
    //        cout << dado.insc << " " << dado.nota << " " << dado.estado << " " << dado.cidade << " " << dado.curso << endl;
    //    }
    //    fclose(saida);

    return 1;
}


// QuickSort externo

#define TamAREA 100 // Tamnaho da area de memória principal para ordenação dos dados
#define TRUE 1
#define FALSE 0

// contadores para análise do algoritmo

long numero_transferencia_leitura = 0;
long numero_transferencia_escrita = 0;
long numero_comparacao = 0;
float tempo_execucao = 0;

typedef int TApontador;

typedef struct TCelula { // celula que contem um item e apontadores para o anterior e próximo
    TipoDados Item;
    TApontador pProx, Ant;
} TCelula;

typedef struct TipoArea { //area de memoria interna para ordenação do arquivo
    TCelula Itens[TamAREA];
    TApontador CelulasDisp, Primeiro, Ultimo;
    int NumCelOcupadas;
} TipoArea;

void FAVazia(TipoArea *Area) { // inicializa area de memória interna para ordenação de dados  
    int i;
    Area->NumCelOcupadas = 0;
    Area->Primeiro = -1;
    Area->Ultimo = -1;
    Area->CelulasDisp = 0;
    for (i = 0; i < TamAREA; i++) {
        Area->Itens[i].Ant = -1;
        Area->Itens[i].pProx = i + 1;
    }
}

int ObterNumCelOcupadas(TipoArea *Area) { // obten numeo de areas ocupadas 
    return (Area->NumCelOcupadas);
}

void InsereItem(TipoDados Item, TipoArea *Area) { // insere o item na area de forma ordenada 
    int Pos, Disp, IndiceInsercao;
    if (Area->NumCelOcupadas == TamAREA) {
        printf("Tentativa de insercao em lista cheia.\n");
        return;
    }
    Disp = Area->CelulasDisp;
    Area->CelulasDisp = Area->Itens[Area->CelulasDisp].pProx;
    Area->Itens[Disp].Item = Item;
    Area->NumCelOcupadas++;
    numero_comparacao++;
    if (Area->NumCelOcupadas == 1) { /* Insercao do primeiro item */
        Area->Primeiro = Disp;
        Area->Ultimo = Area->Primeiro;
        Area->Itens[Area->Primeiro].pProx = -1;
        Area->Itens[Area->Primeiro].Ant = -1;
        return;
    }
    Pos = Area->Primeiro;
    numero_comparacao++;
    if (Item.nota < Area->Itens[Pos].Item.nota) { /* Insercao realizada na primeira posicao */
        Area->Itens[Disp].Ant = -1;
        Area->Itens[Disp].pProx = Pos;
        Area->Itens[Pos].Ant = Disp;
        Area->Primeiro = Disp;
        return;
    }
    IndiceInsercao = Area->Itens[Pos].pProx;
    numero_comparacao++;
    while (IndiceInsercao != -1 && Area->Itens[IndiceInsercao].Item.nota < Item.nota) {
        numero_comparacao++;
        Pos = IndiceInsercao;
        IndiceInsercao = Area->Itens[Pos].pProx;
    }
    numero_comparacao++;
    if (IndiceInsercao == -1) { /*Insercao realizada na ultima posicao*/
        Area->Itens[Disp].Ant = Pos;
        Area->Itens[Disp].pProx = -1;
        Area->Itens[Pos].pProx = Disp;
        Area->Ultimo = Disp;
        return;
    }
    Area->Itens[Disp].Ant = Pos;
    Area->Itens[Disp].pProx = Area->Itens[Pos].pProx;
    Area->Itens[Pos].pProx = Disp;
    Pos = Area->Itens[Disp].pProx;
    Area->Itens[Pos].Ant = Disp;
    /* Insercao realizada no meio de Area */
}

void RetiraPrimeiro(TipoArea *Area, TipoDados *Item) { // retira o primeiro item da area de memória interna 
    TApontador ProxTmp;
    if (Area->NumCelOcupadas == 0) { /* Area vazia */
        printf("ERRO Lista Vazia\n");
        return;
    }
    *Item = Area->Itens[Area->Primeiro].Item;
    ProxTmp = Area->Itens[Area->Primeiro].pProx;
    Area->Itens[Area->Primeiro].pProx = Area->CelulasDisp;
    Area->CelulasDisp = Area->Primeiro;
    Area->Primeiro = ProxTmp;
    numero_comparacao++;
    if ((unsigned int) Area->Primeiro < TamAREA)
        Area->Itens[Area->Primeiro].Ant = -1;
    Area->NumCelOcupadas--;
}

void RetiraUltimo(TipoArea *Area, TipoDados *Item) { // retira o ultimo item da area de memória interna 
    TApontador AntTmp;
    if (Area->NumCelOcupadas == 0) { /* Area vazia */
        printf("ERRO Lista Vazia\n");
        return;
    }
    *Item = Area->Itens[Area->Ultimo].Item;
    AntTmp = Area->Itens[Area->Ultimo].Ant;
    Area->Itens[Area->Ultimo].pProx = Area->CelulasDisp;
    Area->CelulasDisp = Area->Ultimo;
    Area->Ultimo = AntTmp;
    if ((unsigned int) Area->Ultimo < TamAREA)
        Area->Itens[Area->Ultimo].pProx = -1;
    Area->NumCelOcupadas--;
}

// Procedimentos utilizados pelo função Particao do quicksort externo 

void LeSup(FILE **ArqLEs, TipoDados *UltLido, int *Ls, short *OndeLer) { // lê dados do limite superior (fim do arquivo)
    fseek(*ArqLEs, (*Ls - 1) * sizeof (TipoDados), SEEK_SET);
    fread(UltLido, sizeof (TipoDados), 1, *ArqLEs);
    numero_transferencia_leitura++;
    (*Ls)--;
    *OndeLer = FALSE;
}

void LeInf(FILE **ArqLi, TipoDados *UltLido, int *Li, short *OndeLer) { // lê dados do limite inferio (inicio do arquivo)
    fread(UltLido, sizeof (TipoDados), 1, *ArqLi);
    numero_transferencia_leitura++;
    (*Li)++;
    *OndeLer = TRUE;
}

void InserirArea(TipoArea *Area, TipoDados *UltLido, int *NRArea) {//Insere dados de forma ordenada na Area de memória interna
    InsereItem(*UltLido, Area);
    *NRArea = ObterNumCelOcupadas(Area);
}

void EscreveMax(FILE **ArqLEs, TipoDados R, int *Es) { // escreve o maior da area de memória principal no na posição do ponteiro ArqLEs arquivo lido
    fseek(*ArqLEs, (*Es - 1) * sizeof (TipoDados), SEEK_SET);
    fwrite(&R, sizeof (TipoDados), 1, *ArqLEs);
    (*Es)--;
    numero_transferencia_escrita++;
}

void EscreveMin(FILE **ArqEi, TipoDados R, int *Ei) { // escreve o menor da area de memória principal no na posição do ponteiro ArqEi arquivo lido
    fwrite(&R, sizeof (TipoDados), 1, *ArqEi);
    (*Ei)++;
    numero_transferencia_escrita++;
}

void RetiraMax(TipoArea *Area, TipoDados *R, int *NRArea) { // retira o maior valor da area e memória principal
    RetiraUltimo(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

void RetiraMin(TipoArea *Area, TipoDados *R, int *NRArea) { // retira o menor valor da area e memória principal
    RetiraPrimeiro(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j, int sit) { /* cria partições e realiza as comparações ,
    entre os dados e chama as funçõe de leitura e escrita no arquivo e de inserção e retirada da area de memória interna */
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0, Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = TRUE;
    TipoDados UltLido, R;
    fseek(*ArqLi, (Li - 1) * sizeof (TipoDados), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof (TipoDados), SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;
    while (Ls >= Li) { // enquanto os limites superior e inferior não forem iguais 
        if (NRArea < TamAREA - 1) {
            if (OndeLer)
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
            else LeInf(ArqLi, &UltLido, &Li, &OndeLer);
            InserirArea(&Area, &UltLido, &NRArea);
            continue;
        }
        numero_comparacao++;
        if (Ls == Es)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else if (Li == Ei)
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        else if (OndeLer)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        numero_comparacao++;
        if (sit == 1) { // Arquivo Ascendente
            if (UltLido.nota > Lsup) {
                *j = Es;
                EscreveMax(ArqLEs, UltLido, &Es);
                continue;
            }
            numero_comparacao++;
            if (UltLido.nota < Linf) {
                *i = Ei;
                EscreveMin(ArqEi, UltLido, &Ei);
                continue;
            }
            InserirArea(&Area, &UltLido, &NRArea);

            if (Ei - Esq < Dir - Es) {
                RetiraMin(&Area, &R, &NRArea);
                EscreveMin(ArqEi, R, &Ei);
                Linf = R.nota;
            } else {
                RetiraMax(&Area, &R, &NRArea);
                EscreveMax(ArqLEs, R, &Es);
                Lsup = R.nota;
            }
        }
        if (sit == 2) { // Arquivo descendente
            if (UltLido.nota < Linf) { // alterção para descendente > e Lsup
                *j = Es;
                EscreveMax(ArqLEs, UltLido, &Es);
                continue;
            }
            numero_comparacao++;
            if (UltLido.nota > Lsup) { // alterção para descendente < e Linf
                *i = Ei;
                EscreveMin(ArqEi, UltLido, &Ei);
                continue;
            }
            InserirArea(&Area, &UltLido, &NRArea);
            if (Ei - Esq < Dir - Es) {
                RetiraMax(&Area, &R, &NRArea); // alterção para descendene RetiraMin
                EscreveMin(ArqEi, R, &Ei);
                Lsup = R.nota;
            } else {
                RetiraMin(&Area, &R, &NRArea); // alterção para descendente RetiraMax
                EscreveMax(ArqLEs, R, &Es);
                Linf = R.nota;
            }
        }
    }
    if (sit == 1) { // Arquivo Ascendente
        while (Ei <= Es) {
            numero_comparacao++;
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei);
        }
    }
    if (sit == 2) {// Arquivo descendente 
        while (Ei <= Es) {
            numero_comparacao++;
            RetiraMax(&Area, &R, &NRArea); // alterção para descendente RetiraMin 
            EscreveMin(ArqEi, R, &Ei);
        }
    }
}

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir, int sit) {
    int i, j;
    TipoArea Area;
    if (Dir - Esq < 1)
        return;
    FAVazia(&Area);
    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j, sit);
    if (i - Esq < Dir - j) {
        //chamada recurssiva para ordenar primeiro o subarquivo menor
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, sit);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, sit);
    } else {
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, sit);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, sit);
    }
}

int main(int argc, char** argv) {
    TipoDados dado;
    int tam = 471705, Esq = 1, Dir = 471705, sit = 0;
    char nome[20];
    FILE *PROVAO_BIN_DES, *PROVAO_BIN_ASC, *entrada; // ponteiro para arquivos a serem ordenados
    FILE *ArqLEs, *ArqLi, *ArqEi;
    
    txt_para_binario(); // chamada da função que converte o arquivo PROVAO.TXT para PROVAOBIN.bin
    
    // abertura do arquivo PROVAO_BIN_DES.bin para a copia dos dados de PROVAOBIN.bin
    if ((PROVAO_BIN_DES = fopen("PROVAO_BIN_DES.bin", "wb")) == NULL) {
        cout << "erro ao abrir arquivo PROVAO_BIN_DES.bin" << endl;
        return 0;
    }
    // abertura do arquivo PROVAO_BIN_ASC.bin para a copia dos dados de PROVAOBIN.bin
    if ((PROVAO_BIN_ASC = fopen("PROVAO_BIN_ASC.bin", "wb")) == NULL) {
        cout << "erro ao abrir arquivo PROVAO_BIN_ASC" << endl;
        return 0;
    }

    if ((entrada = fopen("PROVAOBIN.bin", "rb")) == NULL) { // abertura do arquivo PROVAOBIN.bin para leitura
        cout << "erro ao abrir arquivo PROVAOBIN.bin" << endl;
        return 0;
    }
    
    while (!feof(entrada)) { //enquanto não for o final do arquivo entrada
        fread(&dado, sizeof (TipoDados), 1, entrada); // lê o dados de entrada 
        //imprime o dado lido 
        //cout << dado.insc << " " << dado.nota << " " << dado.estado << " " << dado.cidade << " " << dado.curso << endl;
        // escreve os dados nos arquivos de saida  
        fwrite(&dado, sizeof (TipoDados), 1, PROVAO_BIN_ASC);
        fwrite(&dado, sizeof (TipoDados), 1, PROVAO_BIN_DES);
    }
    //        testa arquivos  PROVAO_BIN_ASC e PROVAO_BIN_DES copiados para ordenação
    //    
    //        strcpy(nome, "PROVAO_BIN_DES.bin");
    //        print(PROVAO_BIN_DES, tam, nome);
    //        
    //        
    //        cout << "\n\n arquivo ascendente\n\n" << endl;
    //        strcpy(nome, "PROVAO_BIN_ASC.bin");
    //        print(PROVAO_BIN_ASC, tam, nome);
    // fecha arquivos após cópia 
    fclose(entrada);
    fclose(PROVAO_BIN_DES);
    fclose(PROVAO_BIN_ASC);
    //  cria arquivo ascendente
    cout << "\n\n criando arquivo ascendente...\n\n" << endl;

    if ((ArqLEs = fopen("PROVAO_BIN_ASC.bin", "r+b")) == NULL) {
        cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
        return 0;
    }
    if ((ArqLi = fopen("PROVAO_BIN_ASC.bin", "r+b")) == NULL) {
        cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
        return 0;
    }
    if ((ArqEi = fopen("PROVAO_BIN_ASC.bin", "r+b")) == NULL) {
        cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
        return 0;
    }
    sit = 1;
    QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, Esq, Dir, sit);
    fflush(ArqLi);
    fclose(ArqEi);
    fclose(ArqLEs);
    fseek(ArqLi, 0, SEEK_SET);
    strcpy(nome, "PROVAO_BIN_ASC.bin");
    print(ArqLi, tam, nome);
    fclose(ArqLi);
    cout << "\n\n arquivo descendente criado cm sucesso! \n\n" << endl;
    //cria arquivo descendente 
    cout << "\n\n arquivo descendente \n\n" << endl;
    if ((ArqLEs = fopen("PROVAO_BIN_DES.bin", "r+b")) == NULL) {
        cout << "erro ao abrir arquivo PROVAO_BIN_DES.bin" << endl;
        return 0;
    }
    if ((ArqLi = fopen("PROVAO_BIN_DES.bin", "r+b")) == NULL) {
        cout << "erro ao abrir arquivo PROVAO_BIN_DES.bin" << endl;
        return 0;
    }
    if ((ArqEi = fopen("PROVAO_BIN_DES.bin", "r+b")) == NULL) {
        cout << "erro ao abrir arquivo PROVAO_BIN_DES.bin" << endl;
        return 0;
    }
    sit=2;
    QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, Esq, Dir, sit);
    fflush(ArqLi);
    fclose(ArqEi);
    fclose(ArqLEs);
    fseek(ArqLi, 0, SEEK_SET);
    strcpy(nome, "PROVAO_BIN_DES.bin");
    print(ArqLi, tam, nome);
    fclose(ArqLi);
     cout << "\n\n arquivo descendente criado cm sucesso! \n\n" << endl;
    return 0;
}

