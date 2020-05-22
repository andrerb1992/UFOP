/* 
 * File:   main.cpp
 * Author: Leonardo Isaac
 *
 * Created on 8 de Dezembro de 2013, 22:20
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

typedef struct { // estrutura que representa um dado manipulado no arquivo
    long insc;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
} TipoDados;

int print(FILE *arquivo, int tam, char *nome) { // imprime arquivo de acordo com o nome e tamanho
    TipoDados dado;
    if ((arquivo = fopen(nome, "rb")) == NULL) { //abre arquivo binÃ¡rio de acordo com o nome recebido na funÃ§Ã£o
        cout << "erro ao abrir arquivo" << endl;
        return 0;
    }
    for (int i = 0; i < tam; i++) { // LÃª o arquivo de acordo com o tamanho passado como argumento
        fread(&dado, sizeof (TipoDados), 1, arquivo);
        cout << dado.insc << " " << dado.nota << " " << dado.estado << " " << dado.cidade << dado.curso << endl; // imprime um dado lido
    }
    fclose(arquivo); // fecha arquivo
    return 1;
}
// IBSS

#define MAXTAM 20
#define MEM 20

typedef float Tipochave;
typedef int TipoIndice;
typedef TipoDados TipoVetor[MAXTAM + 1];



// analise experimental de complexidade do metodo intercalação balanceada
long numeroTransferenciaLeitura =0;
long numeroTransferenciaEscrita= 0;
long comparacoes=0;
float tempo_execucao1=0;

// metodo de ordenaçao em memoria interna, que utiliza fila de prioridade
// compara o primeiro registro com o primeiro registro mais um
void refazHeap(TipoIndice Esq, TipoIndice Dir, TipoDados *A) {
    TipoIndice i = Esq;
    int j;
    TipoDados x;
    j = i * 2;
    x = A[i];
    while (j <= Dir) {
        if (j < Dir) {
            if (A[j].nota > A[j + 1].nota)
                j++;
        }
        if (x.nota <= A[j].nota)
            break;
        A[i] = A[j];
        i = j;
        j = i * 2;
    }
    A[i] = x;
}

void constroiHeap(TipoDados *A, TipoIndice *n) {
    TipoIndice Esq;
    Esq = *n / 2 + 1;
    while (Esq > 1) {
        Esq--;
        refazHeap(Esq, *n, A);
    }
}
//vetor usando para pegar o elemento do heap 
TipoDados ItemMarcado(TipoDados *A) {
    return (A[1]);
}
//função usada para remover o menor elemento do heap para ser inserida nas fitas
 TipoDados removeMenorElemento(TipoDados *A, TipoIndice *n) {
    TipoDados elemento;
    if (*n < 1)
        printf("Erro: heap vazio\n");
    else {
        elemento = A[1];
        A[1] = A[*n];
        (*n)--;
        refazHeap(1, *n, A);
    }
    return elemento;
}

void aumentaElementoHeap(TipoIndice i, Tipochave novoElemento, TipoDados *A) {
    TipoDados x;
    A[i].nota = novoElemento;
    while (i > 1 && A[i / 2].nota > A[i].nota) {
        x = A[i / 2];
        A[i / 2] = A[i];
        A[i] = x;
        i /= 2;

    }
}

// função para inserir as notas no heap sort
void insereHeap(TipoDados *x, TipoDados *A, TipoIndice *n) {
    (*n)++;
    A[*n] = *x;
    A[*n].nota = INT_MIN;
    aumentaElementoHeap(*n, x->nota, A);
}


// variaveis globais
int quantidadeFitas;
int qntItensIBSS = 0;

// função para intercalação

int intercalacaoIBSS(FILE **vetorFitas, int fitasEntrada, int fitasSaida, int *posRetorno) {
    for (int i = 0; i < quantidadeFitas; i++) {
        rewind(vetorFitas[i]);
    }
    int fitasEntradas = 0;

    //metodo usado para definir quantas fitas de entrada se utilizada.
    for (int i = fitasEntrada; i < fitasEntrada + (quantidadeFitas / 2); i++) {
        if (vetorFitas[i] && !feof(vetorFitas[i])) {
            fitasEntradas++;
        }
    }
    TipoDados memoria[MEM];
    int fitasIBSS = fitasSaida;
    int fitasPreenchidas = 0;
  // pega as 20 fitas
    int cont = 0;
    while (fitasPreenchidas < fitasEntradas) {
        fitasIBSS = (fitasIBSS % (quantidadeFitas / 2)) + fitasSaida;
        fitasPreenchidas = 0;
        
        // ler a primeira nota de cada fita contida no arquivo
        int j = 0;
        TipoDados tmp;
        tmp.nota = -1;
        cont = 0;
        for (int i = fitasEntrada; i < fitasEntrada + (quantidadeFitas / 2); i++) {
            if (cont < fitasEntradas) {
                numeroTransferenciaLeitura++;
                if (!fread(&memoria[j], sizeof (TipoDados), 1, vetorFitas[i])) {
                    memoria[j] = tmp;
                }
                j++;
                cont++;
            } else {
                memoria[j] = tmp;
                j++;
            }
        }
        //Intercalaçao dos blocos para as fitas de saida
        while (true) {
            int menor_pos = -1;
            TipoDados valor;
            valor.nota = INT_MAX;
            
            //Procurando a menor nota que seja diferente de -1
            for (int i = 0; i < MEM; i++) {
                comparacoes++;
                if ((memoria[i].nota != -1) &&(memoria[i].nota < valor.nota)) {
                    valor = memoria[i];
                    menor_pos = i;
                }
            }
               // compara a nota e escreve no arquivo
            if (valor.nota != INT_MAX) {
                numeroTransferenciaEscrita++;
                fwrite(&valor, sizeof (TipoDados), 1, vetorFitas[fitasIBSS]);
                TipoDados vet;
                numeroTransferenciaLeitura++;
                fread(&vet, sizeof (TipoDados), 1, vetorFitas[menor_pos + fitasEntrada]);
                memoria[menor_pos] = vet;
            }
            else {
                break;
            }
        }
       
        long posAtual = ftell(vetorFitas[fitasIBSS]);
        fseek(vetorFitas[fitasIBSS], 0, SEEK_END);
        int itens = ftell(vetorFitas[fitasIBSS]) / sizeof (TipoDados);
        fseek(vetorFitas[fitasIBSS], posAtual, SEEK_SET);
        long size = itens;
        if (size == qntItensIBSS) {
            *posRetorno = fitasIBSS;
            return 1;
        }
        
        for (int i = fitasEntrada; i < fitasEntrada + (quantidadeFitas / 2); i++) {
            if (vetorFitas[i] && feof(vetorFitas[i])) {
                fitasPreenchidas++;
            }
        }
       

        //Finaliza o bloco escrevendo -1
        numeroTransferenciaEscrita++;
        fwrite(&tmp, sizeof (TipoDados), 1, vetorFitas[fitasIBSS]);
        fitasIBSS++;
    }
    return -1;
}

void IBSS(FILE * file) {
    // verificação do arquivo
    if (file == NULL) {
        cout << "Erro no arquivo ." << endl;
        return;
    }
    quantidadeFitas = 40;
    rewind(file);
    
    //Criando as Fitas as 40 fitas  
    FILE * vetorFitas[quantidadeFitas];
    char nome[41][20] = {"fita1.bin", "fitas2.bin", "fitas3.bin", "fitas4.bin", "fitas5.bin", "fitas6.bin", "fitas7.bin",
        "fitas8.bin", "fitas9.bin", "fitas10.bin", "fitas11.bin", "fitas12.bin", "fitas13.bin", "fitas14.bin", "fitas15.bin",
        "fitas16.bin", "fitas17.bin", "fitas18.bin", "fitas19.bin", "fitas20.bin", "fitas21.bin", "fitas22.bin", "fitas23.bin",
        "fitas24.bin", "fitas25.bin", "fitas26.bin", "fitas27.bin", "fitas28.bin", "fitas29.bin", "fitas30.bin", "fitas31.bin",
        "fitas32.bin", "fitas33.bin", "fitas34.bin", "fitas35.bin", "fitas36.bin", "fitas37.bin", "fitas38.bin", "fitas39.bin",
        "fitas40.bin", "fitas41.bin"};

    for (int i = 0; i < quantidadeFitas; i++) {
        vetorFitas[i] = fopen(nome[i], "w+b");
        if (vetorFitas[i] == NULL) {
            cout << "erro ao abrir arquivo" << vetorFitas[i];
        }
    }

    TipoDados fimDeFitas;
    fimDeFitas.nota = -1;
    rewind(file);
    int fitaAtual = 0;
    int quantidadeFitasEntrada = quantidadeFitas / 2;
    
    TipoDados heap[MAXTAM + 1];
    TipoDados heapTemp;
    
    int tamHeap = MAXTAM;
    long posAtual = ftell(file);
    fseek(file, 0, SEEK_END);
    int itens = ftell(file) / sizeof (TipoDados);
    fseek(file, posAtual, SEEK_SET);
    qntItensIBSS = itens;
    int variavelMarcado = 0;

    //Preenchendo o heap sort
    for (int i = 0; i < tamHeap; i++) {
        numeroTransferenciaLeitura++;
        fread(&heapTemp, sizeof (TipoDados), 1, file);
        heap[i + 1] = heapTemp;
    }
    constroiHeap(heap, &tamHeap);
    TipoDados tmpHeap;
    // compara as notas, assim marcando a nota menor e removendo do heap
    while (!feof(file)) {
        fitaAtual = fitaAtual % (quantidadeFitas / 2);
        numeroTransferenciaLeitura++;
        if (fread(&tmpHeap, sizeof (TipoDados), 1, file)) {
            TipoDados saindoHeap = removeMenorElemento(heap, &tamHeap);
            if (tmpHeap.nota < saindoHeap.nota) {
                tmpHeap.nota = INT_MAX - tmpHeap.nota;
                variavelMarcado++;
            }
            insereHeap(&tmpHeap, heap, &tamHeap);

            numeroTransferenciaEscrita++;
            fwrite(&saindoHeap, sizeof (TipoDados), 1, vetorFitas[fitaAtual]);
           
            //Verificação das notas marcadas no heap sort
            if (variavelMarcado == tamHeap) {
                variavelMarcado = 0;
                for (int i = 1; i <= tamHeap; i++) {
                    heap[i].nota = INT_MAX - heap[i].nota;
                }
                constroiHeap(heap, &tamHeap);
                numeroTransferenciaEscrita++;
                fwrite(&fimDeFitas, sizeof (TipoDados), 1, vetorFitas[fitaAtual]);
                fitaAtual++;
            }
        }
    }
    //Verificando o heap para que existe alguma nota marcada
    for (int i = 1; i <= tamHeap; i++) {
        if (heap[i].nota > INT_MAX - 800000)
            heap[i].nota = INT_MAX - heap[i].nota;
    }
    constroiHeap(heap, &tamHeap);
    
    //Escrevendo no restante do heap
    while (tamHeap > 0) {
        TipoDados saindoHeap = removeMenorElemento(heap, &tamHeap);
        numeroTransferenciaEscrita++;
        fwrite(&saindoHeap, sizeof (TipoDados), 1, vetorFitas[fitaAtual]);
    }
    numeroTransferenciaEscrita++;
    fwrite(&fimDeFitas, sizeof (TipoDados), 1, vetorFitas[fitaAtual]);

    int fitasEntrada = 0;
    int fitasSaida = quantidadeFitasEntrada;
    bool variavelInversa = false;
    int posRetorno;
    while (intercalacaoIBSS(vetorFitas, fitasEntrada, fitasSaida, &posRetorno) != 1) {
    
        //Reinicia os arquivos de entrada que serao os novos arquivos de saida
        for (int i = fitasEntrada; i < fitasEntrada + (quantidadeFitas / 2); i++) {
            fclose(vetorFitas[i]);
            vetorFitas[i] = fopen(nome[i], "w+b");
        
            //Leia ate chegar ao fim de arquivo
            int temp;
            fread(&temp, sizeof (int), 1, vetorFitas[i]);
        }
        if (variavelInversa) {
            fitasEntrada = 0;
            fitasSaida = quantidadeFitasEntrada;
        } else {
            fitasEntrada = quantidadeFitasEntrada;
            fitasSaida = 0;
        }        
        variavelInversa = !variavelInversa;
    }
    
    rewind(file);
    rewind(vetorFitas[posRetorno]);
    
    while (fread(&fimDeFitas, sizeof (TipoDados), 1, vetorFitas[posRetorno])) {
        fwrite(&fimDeFitas, sizeof (TipoDados), 1, file);
    }
    for (int i = 0; i < quantidadeFitas; i++) {
            fclose(vetorFitas[i]);
        }
    
}



// QuickSort externo

#define TamAREA 5 // Tamnaho da area de memÃ³ria principal para ordenaÃ§Ã£o dos dados
#define TRUE 1
#define FALSE 0

// contadores para anÃ¡lise do algoritmo

long numero_transferencia_leitura = 0;
long numero_transferencia_escrita = 0;
long numero_comparacao = 0;
float tempo_execucao = 0;

typedef int TApontador;

typedef struct TCelula { // celula que contem um item e apontadores para o anterior e prÃ³ximo
    TipoDados Item;
    TApontador pProx, Ant;
} TCelula;

typedef struct TipoArea { //area de memoria interna para ordenaÃ§Ã£o do arquivo
    TCelula Itens[TamAREA];
    TApontador CelulasDisp, Primeiro, Ultimo;
    int NumCelOcupadas;
} TipoArea;

void FAVazia(TipoArea *Area) { // inicializa area de memÃ³ria interna para ordenaÃ§Ã£o de dados  
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

void RetiraPrimeiro(TipoArea *Area, TipoDados *Item) { // retira o primeiro item da area de memÃ³ria interna 
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

void RetiraUltimo(TipoArea *Area, TipoDados *Item) { // retira o ultimo item da area de memÃ³ria interna 
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

// Procedimentos utilizados pelo funÃ§Ã£o Particao do quicksort externo 

void LeSup(FILE **ArqLEs, TipoDados *UltLido, int *Ls, short *OndeLer) { // lÃª dados do limite superior (fim do arquivo)
    fseek(*ArqLEs, (*Ls - 1) * sizeof (TipoDados), SEEK_SET);
    fread(UltLido, sizeof (TipoDados), 1, *ArqLEs);
    numero_transferencia_leitura++;
    (*Ls)--;
    *OndeLer = FALSE;
}

void LeInf(FILE **ArqLi, TipoDados *UltLido, int *Li, short *OndeLer) { // lÃª dados do limite inferio (inicio do arquivo)
    fread(UltLido, sizeof (TipoDados), 1, *ArqLi);
    numero_transferencia_leitura++;
    (*Li)++;
    *OndeLer = TRUE;
}

void InserirArea(TipoArea *Area, TipoDados *UltLido, int *NRArea) {//Insere dados de forma ordenada na Area de memÃ³ria interna
    InsereItem(*UltLido, Area);
    *NRArea = ObterNumCelOcupadas(Area);
}

void EscreveMax(FILE **ArqLEs, TipoDados R, int *Es) { // escreve o maior da area de memÃ³ria principal no na posiÃ§Ã£o do ponteiro ArqLEs arquivo lido
    fseek(*ArqLEs, (*Es - 1) * sizeof (TipoDados), SEEK_SET);
    fwrite(&R, sizeof (TipoDados), 1, *ArqLEs);
    (*Es)--;
    numero_transferencia_escrita++;
}

void EscreveMin(FILE **ArqEi, TipoDados R, int *Ei) { // escreve o menor da area de memÃ³ria principal no na posiÃ§Ã£o do ponteiro ArqEi arquivo lido
    fwrite(&R, sizeof (TipoDados), 1, *ArqEi);
    (*Ei)++;
    numero_transferencia_escrita++;
}

void RetiraMax(TipoArea *Area, TipoDados *R, int *NRArea) { // retira o maior valor da area e memÃ³ria principal
    RetiraUltimo(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

void RetiraMin(TipoArea *Area, TipoDados *R, int *NRArea) { // retira o menor valor da area e memÃ³ria principal
    RetiraPrimeiro(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j) { /* cria partiÃ§Ãµes e realiza as comparaÃ§Ãµes ,
    entre os dados e chama as funÃ§Ãµe de leitura e escrita no arquivo e de inserÃ§Ã£o e retirada da area de memÃ³ria interna */
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq, NRArea = 0, Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = TRUE;
    TipoDados UltLido, R;
    fseek(*ArqLi, (Li - 1) * sizeof (TipoDados), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof (TipoDados), SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;
    while (Ls >= Li) { // enquanto os limites superior e inferior nÃ£o forem iguais 
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
    while (Ei <= Es) {
        numero_comparacao++;
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqEi, R, &Ei);
    }

}

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir) {
    int i, j;
    TipoArea Area;
    if (Dir - Esq < 1)
        return;
    FAVazia(&Area);
    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j);
    if (i - Esq < Dir - j) {
        //chamada recurssiva para ordenar primeiro o subarquivo menor
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
    } else {
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
    }
}

//

void selectSort(TipoDados* v, int n) {
    int i, j, Max;
    TipoDados aux;
    for (i = 0; i < n - 1; i++) {
        Max = i;
        for (j = i + 1; j < n; j++)
            if (v[j].nota > v[Max].nota)
                Max = j;
        if (i != Max) {
            aux = v[Max];
            v[Max] = v[i];
            v[i] = aux;
        }
    }
}

int criaFitas() {
    FILE *fita1E, *fita2E, *fita3E, *fita4E, *fita5E, *fita6E, *fita7E, *fita8E, *fita9E, *fita10E;
    FILE *fita11E, *fita12E, *fita13E, *fita14E, *fita15E, *fita16E, *fita17E, *fita18E, *fita19E, *fita20E;

    FILE *fita1S, *fita2S, *fita3S, *fita4S, *fita5S, *fita6S, *fita7S, *fita8S, *fita9S, *fita10S;
    FILE *fita11S, *fita12S, *fita13S, *fita14S, *fita15S, *fita16S, *fita17S, *fita18S, *fita19S, *fita20S;

    fita1S = fopen("fita1S.bin", "wb");
    fclose(fita1S);
    fita2S = fopen("fita2S.bin", "wb");
    fclose(fita2S);
    fita3S = fopen("fita3S.bin", "wb");
    fclose(fita3S);
    fita4S = fopen("fita4S.bin", "wb");
    fclose(fita4S);
    fita5S = fopen("fita5S.bin", "wb");
    fclose(fita5S);
    fita6S = fopen("fita6S.bin", "wb");
    fclose(fita6S);
    fita7S = fopen("fita7S.bin", "wb");
    fclose(fita7S);
    fita8S = fopen("fita8S.bin", "wb");
    fclose(fita8S);
    fita9S = fopen("fita9S.bin", "wb");
    fclose(fita9S);
    fita10S = fopen("fita10S.bin", "wb");
    fclose(fita10S);
    fita11S = fopen("fita11S.bin", "wb");
    fclose(fita11S);
    fita12S = fopen("fita12S.bin", "wb");
    fclose(fita12S);
    fita13S = fopen("fita13S.bin", "wb");
    fclose(fita13S);
    fita14S = fopen("fita14S.bin", "wb");
    fclose(fita14S);
    fita15S = fopen("fita15S.bin", "wb");
    fclose(fita15S);
    fita16S = fopen("fita16S.bin", "wb");
    fclose(fita16S);
    fita17S = fopen("fita17S.bin", "wb");
    fclose(fita17S);
    fita18S = fopen("fita18S.bin", "wb");
    fclose(fita18S);
    fita19S = fopen("fita19S.bin", "wb");
    fclose(fita19S);
    fita20S = fopen("fita20S.bin", "wb");
    fclose(fita20S);

    fita1E = fopen("fita1E.bin", "wb");
    fclose(fita1E);
    fita2E = fopen("fita2E.bin", "wb");
    fclose(fita2E);
    fita3E = fopen("fita3E.bin", "wb");
    fclose(fita3E);
    fita4E = fopen("fita4E.bin", "wb");
    fclose(fita4E);
    fita5E = fopen("fita5E.bin", "wb");
    fclose(fita5E);
    fita6E = fopen("fita6E.bin", "wb");
    fclose(fita6E);
    fita7E = fopen("fita7E.bin", "wb");
    fclose(fita7E);
    fita8E = fopen("fita8E.bin", "wb");
    fclose(fita8E);
    fita9E = fopen("fita9E.bin", "wb");
    fclose(fita9E);
    fita10E = fopen("fita10E.bin", "wb");
    fclose(fita10E);
    fita11E = fopen("fita11E.bin", "wb");
    fclose(fita11E);
    fita12E = fopen("fita12E.bin", "wb");
    fclose(fita12E);
    fita13E = fopen("fita13E.bin", "wb");
    fclose(fita13E);
    fita14E = fopen("fita14E.bin", "wb");
    fclose(fita14E);
    fita15E = fopen("fita15E.bin", "wb");
    fclose(fita15E);
    fita16E = fopen("fita16E.bin", "wb");
    fclose(fita16E);
    fita17E = fopen("fita17E.bin", "wb");
    fclose(fita17E);
    fita18E = fopen("fita18E.bin", "wb");
    fclose(fita18E);
    fita19E = fopen("fita19E.bin", "wb");
    fclose(fita19E);
    fita20E = fopen("fita20E.bin", "wb");
    fclose(fita20E);

    return 1;
}

int exibeFitasE() {
    FILE *fita1E, *fita2E, *fita3E, *fita4E, *fita5E, *fita6E, *fita7E, *fita8E, *fita9E, *fita10E;
    FILE *fita11E, *fita12E, *fita13E, *fita14E, *fita15E, *fita16E, *fita17E, *fita18E, *fita19E, *fita20E;
    TipoDados leitura;
    fita1E = fopen("fita1E.bin", "rb");
    cout << "FITA 1 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita1E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita1E);

    fita2E = fopen("fita2E.bin", "rb");
    cout << "FITA 2 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita2E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita2E);

    fita3E = fopen("fita3E.bin", "rb");
    cout << "FITA 3 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita3E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita3E);

    fita4E = fopen("fita4E.bin", "rb");
    cout << "FITA 4 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita4E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita4E);

    fita5E = fopen("fita5E.bin", "rb");
    cout << "FITA 5 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita5E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita5E);

    fita6E = fopen("fita6E.bin", "rb");
    cout << "FITA 6 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita6E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita6E);

    fita7E = fopen("fita7E.bin", "rb");
    cout << "FITA 7 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita7E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita7E);

    fita8E = fopen("fita8E.bin", "rb");
    cout << "FITA 8 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita8E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita8E);

    fita9E = fopen("fita9E.bin", "rb");
    cout << "FITA 9 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita9E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita9E);

    fita10E = fopen("fita10E.bin", "rb");
    cout << "FITA 10 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita10E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita10E);

    fita11E = fopen("fita11E.bin", "rb");
    cout << "FITA 11 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita11E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita11E);

    fita12E = fopen("fita12E.bin", "rb");
    cout << "FITA 12 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita12E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita12E);

    fita13E = fopen("fita13E.bin", "rb");
    cout << "FITA 13 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita13E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita13E);

    fita14E = fopen("fita14E.bin", "rb");
    cout << "FITA 14 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita14E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita14E);

    fita15E = fopen("fita15E.bin", "rb");
    cout << "FITA 15 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita15E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita15E);

    fita16E = fopen("fita16E.bin", "rb");
    cout << "FITA 16 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita16E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita16E);

    fita17E = fopen("fita17E.bin", "rb");
    cout << "FITA 17 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita17E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita17E);

    fita18E = fopen("fita18E.bin", "rb");
    cout << "FITA 18 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita18E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita18E);

    fita19E = fopen("fita19E.bin", "rb");
    cout << "FITA 19 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita19E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita19E);

    fita20E = fopen("fita20E.bin", "rb");
    cout << "FITA 20 ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita20E) == 1) {
        cout << leitura.nota << " ";
    }
    cout << endl;
    fclose(fita20E);



    return 1;
}

int buscaMaior(TipoDados *bloco, int *marcaFita) {
    int maior = 0, i;
    for (i = 1; i < 20; i++) {
        if ((bloco[i].nota > bloco[maior].nota)&&(marcaFita[i] != 0))
            maior = i;
    }
    return maior;
}

int ibvc_pt2(int *marcaFita, int n, int *totalnaFita) {
    int i, contFitas[20];
    TipoDados bloco[20], leitura;
    int maior, x = 0;
    FILE *fita1E, *fita2E, *fita3E, *fita4E, *fita5E, *fita6E, *fita7E, *fita8E, *fita9E, *fita10E;
    FILE *fita11E, *fita12E, *fita13E, *fita14E, *fita15E, *fita16E, *fita17E, *fita18E, *fita19E, *fita20E;
    FILE *fita1S;
    for (i = 0; i < 20; i++)
        contFitas[i] = 0; //inicializa o vetor contfitas com 0
    fita1S = fopen("fita1S.bin", "ab");

    if (marcaFita[0] > 0) { //se a fita foi utilizada, o primeiro elemento dela Ã© jogado na memoria na posicao equivalente
        fita1E = fopen("fita1E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita1E) == 1) {
            bloco[0] = leitura; // no caso da fita 1, a posical da memoria Ã© a '0'
        }
        contFitas[0]++;
    }
    if (marcaFita[1] > 0) {
        fita2E = fopen("fita2E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita2E) == 1) {
            bloco[1] = leitura;
        }
        contFitas[1]++;
    }
    if (marcaFita[2] > 0) {
        fita3E = fopen("fita3E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita3E) == 1) {
            bloco[2] = leitura;
        }
        contFitas[2]++;
    }
    if (marcaFita[3] > 0) {
        fita4E = fopen("fita4E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita4E) == 1) {
            bloco[3] = leitura;
        }
        contFitas[3]++;
    }
    if (marcaFita[4] > 0) {
        fita5E = fopen("fita5E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita5E) == 1) {
            bloco[4] = leitura;
        }
        contFitas[4]++;
    }
    if (marcaFita[5] > 0) {
        fita6E = fopen("fita6E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita6E) == 1) {
            bloco[5] = leitura;
        }
        contFitas[5]++;
    }
    if (marcaFita[6] > 0) {
        fita7E = fopen("fita7E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita7E) == 1) {
            bloco[6] = leitura;
        }
        contFitas[6]++;
    }
    if (marcaFita[7] > 0) {
        fita8E = fopen("fita8E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita8E) == 1) {
            bloco[7] = leitura;
        }
        contFitas[7]++;
    }
    if (marcaFita[8] > 0) {
        fita9E = fopen("fita9E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita9E) == 1) {
            bloco[8] = leitura;
        }
        contFitas[8]++;
    }
    if (marcaFita[9] > 0) {
        fita10E = fopen("fita10E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita10E) == 1) {
            bloco[9] = leitura;
        }
        contFitas[9]++;
    }
    if (marcaFita[10] > 0) {
        fita11E = fopen("fita11E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita11E) == 1) {
            bloco[10] = leitura;
        }
        contFitas[10]++;
    }
    if (marcaFita[11] > 0) {
        fita12E = fopen("fita12E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita12E) == 1) {
            bloco[11] = leitura;
        }
        contFitas[11]++;
    }
    if (marcaFita[12] > 0) {
        fita13E = fopen("fita13E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita13E) == 1) {
            bloco[12] = leitura;
        }
        contFitas[12]++;
    }
    if (marcaFita[13] > 0) {
        fita14E = fopen("fita14E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita14E) == 1) {
            bloco[13] = leitura;
        }
        contFitas[13]++;
    }
    if (marcaFita[14] > 0) {
        fita15E = fopen("fita15E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita15E) == 1) {
            bloco[14] = leitura;
        }
        contFitas[14]++;
    }

    if (marcaFita[15] > 0) {
        fita16E = fopen("fita16E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita16E) == 1) {
            bloco[15] = leitura;
        }
        contFitas[15]++;
    }

    if (marcaFita[16] > 0) {
        fita17E = fopen("fita17E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita17E) == 1) {
            bloco[16] = leitura;
        }
        contFitas[16]++;
    }
    if (marcaFita[17] > 0) {
        fita18E = fopen("fita18E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita18E) == 1) {
            bloco[17] = leitura;
        }
        contFitas[17]++;
    }
    if (marcaFita[18] > 0) {
        fita19E = fopen("fita19E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita19E) == 1) {
            bloco[18] = leitura;
        }
        contFitas[18]++;
    }
    if (marcaFita[19] > 0) {
        fita20E = fopen("fita20E.bin", "rb");
        if (fread(&leitura, sizeof (TipoDados), 1, fita20E) == 1) {
            bloco[19] = leitura;
        }
        contFitas[19]++;
    }
    TipoDados auxiliar[20];
    while (n > 0) { //enquanto houver elementos para serem distribuidos
        x++;
        for (i = 0; i < 20; i++)
            cout << bloco[i].nota << " "; //exibe os elemtnos na memoria (desnecessario)
        maior = buscaMaior(bloco, marcaFita); //funcao que retorna qual Ã© a posicao do maior elemento na memoria
        cout << endl << maior << endl; //onde esta o maior    (desnecessario)   
        cout << bloco[maior].nota << endl; //quem Ã© o maior     (desnecessario)
        fwrite(&bloco[maior], sizeof (TipoDados), 1, fita1S); //escreve na fita de saida o maior elemento

        switch (maior) { //pega o proximo da fita de origem do maior elemento removido
            case 0:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita1E) == 1)&&(contFitas[maior] < 20)) { // o elemento lido existe e estÃ¡ dentro do limite de 20 por etapa de escalonamento
                    bloco[0] = leitura; // bloco recebe o elemento lido
                    contFitas[0]++; //contador de elementos lido nesta fita
                } else {
                    bloco[maior].nota = -1; //caso jÃ¡ tinha sido lidos mais de 20 elementos na fita, ou a fita estÃ¡ vazia, a posicao dela na memoria Ã© ocupada pelo elemento '-1'
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior]; // o total de elementos na fita Ã© diminuido pela quantidade de elementos lido
                    if (totalnaFita[maior] > 0) { // caso ainda tenha elementos para serem lidos numa segunda etapa
                        auxiliar[maior] = leitura; //o proximo destes elementos Ã© salvo num vetor auxiliar
                    } else {
                        auxiliar[maior].nota = -1; // caso nao tenha mais elementos para serem lidos, o vetor auxiliar recebe -1
                    }
                }
                break;
            }
            case 1:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita2E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[1] = leitura;
                    contFitas[1]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 2:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita3E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[2] = leitura;
                    contFitas[2]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }

            case 3:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita4E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[3] = leitura;
                    contFitas[3]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }

            case 4:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita5E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[4] = leitura;
                    contFitas[4]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 5:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita6E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[5] = leitura;
                    contFitas[5]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 6:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita7E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[6] = leitura;
                    contFitas[6]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 7:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita8E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[7] = leitura;
                    contFitas[7]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 8:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita9E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[8] = leitura;
                    contFitas[8]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 9:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita10E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[9] = leitura;
                    contFitas[9]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 10:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita11E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[10] = leitura;
                    contFitas[10]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 11:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita12E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[11] = leitura;
                    contFitas[11]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 12:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita13E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[12] = leitura;
                    contFitas[12]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 13:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita14E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[13] = leitura;
                    contFitas[13]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 14:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita15E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[14] = leitura;
                    contFitas[14]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 15:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita16E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[15] = leitura;
                    contFitas[15]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 16:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita17E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[16] = leitura;
                    contFitas[16]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 17:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita18E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[17] = leitura;
                    contFitas[17]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 18:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita19E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[18] = leitura;
                    contFitas[18]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
            case 19:
            {
                if ((fread(&leitura, sizeof (TipoDados), 1, fita20E) == 1)&&(contFitas[maior] < 20)) {
                    bloco[19] = leitura;
                    contFitas[19]++;
                } else {
                    bloco[maior].nota = -1;
                    totalnaFita[maior] = totalnaFita[maior] - contFitas[maior];
                    if (totalnaFita[maior] > 0) {
                        auxiliar[maior] = leitura;
                    } else {
                        auxiliar[maior].nota = -1;
                    }
                }
                break;
            }
        }
        if (x == 400) { //se encheu a primeira fita de saida
            for (i = 0; i < 20; i++) {
                contFitas[i] = 1; //reseta o contador da fita (para que nunca extrapole 20)
                if (totalnaFita[i] > 0)
                    bloco[i] = auxiliar[i];
                //cout<<totalnaFita[i]<<" ";
            }
            x = 0;
        }
        n--;
    }
    fclose(fita1S);
    fita1S = fopen("fita1S.bin", "rb");
    cout << "Fita de saida ";
    while (fread(&leitura, sizeof (TipoDados), 1, fita1S) == 1) { //exibe a fita de saida, onde todos os elementos foram salvos, ordenados de 20 em 20
        cout << leitura.nota << " ";
    }

    return 1;
}


int main(int argc, char** argv) {

    if (!(argc == 4 || argc == 5)) { // testa o numero de argumentos para que o programa funcione corretamente
        cout << "entrada inconsistente. Considere: ordena <metodo> <quantidade> <situacao> [-P]" << endl;
        return 0;
    }
    TipoDados dado; // declaraÃƒÂ§ÃƒÂ£o da estrutura da dados manipulados 
    char nome[20];

    int Esq = 1, Dir = atoi(argv[2]), sit = atoi(argv[3]);

    if (sit == 1) {
        strcpy(nome, "PROVAO_BIN_ASC.bin");
    }
    if (sit == 2) {
        strcpy(nome, "PROVAO_BIN_DES.bin");
    }
    if (sit == 3) {
        strcpy(nome, "PROVAOBIN.bin");
    }
    FILE *ArqLEs, *ArqLi, *ArqEi, *tmp, *entrada; // ponteiro para arquivos auxiliares

    // cria arquivo temporario para comparaÃƒÂ§ÃƒÂ£os

    if ((entrada = fopen(nome, "rb")) == NULL) {
        cout << "erro ao abrir arquivo: " << nome << endl;
        return 0;
    }

    if ((tmp = fopen("tmp.bin", "wb")) == NULL) {
        cout << "erro ao abrir arquivo tmp.txt" << endl;
        return 0;
    }

    while (!feof(entrada)) { //enquanto nÃƒÂ£o for o final do arquivo entrada
        fread(&dado, sizeof (TipoDados), 1, entrada); // lÃƒÂª o dados de entrada 
        //imprime o dado lido 
        //cout << dado.insc << " " << dado.nota << " " << dado.estado << " " << dado.cidade << " " << dado.curso << endl;
        // escreve os dados nos arquivos de saida  
        fwrite(&dado, sizeof (TipoDados), 1, tmp);
    }
    fclose(tmp);
    // ordena <mÃƒÂ©todo> <quantidade> <situaÃƒÂ§ÃƒÂ£o> [-P]

    switch (atoi(argv[1])) {
        case 1:
        {
            cout << "  (1) IntercalaÃ§Ã£o balanceada de vÃ¡rios caminhos I" << endl;

            if (atoi(argv[3]) == 2) {
                cout << "Teste descendente" << endl;
                FILE *binario;
                FILE *fita1E, *fita2E, *fita3E, *fita4E, *fita5E, *fita6E, *fita7E, *fita8E, *fita9E, *fita10E;
                FILE *fita11E, *fita12E, *fita13E, *fita14E, *fita15E, *fita16E, *fita17E, *fita18E, *fita19E, *fita20E;
                //    FILE *fita1S, *fita2S, *fita3S, *fita4S, *fita5S, *fita6S, *fita7S, *fita8S, *fita9S, *fita10S;
                //    FILE *fita11S, *fita12S, *fita13S, *fita14S, *fita15S, *fita16S, *fita17S, *fita18S, *fita19S, *fita20S;
                TipoDados bloco[20];
                TipoDados leitura;
                int controle = 20, n, contaFitas = 1, i, marcaFita[20], totalnaFita[20];
                //txt_para_binario();
                criaFitas(); //cria todas as fitas 
                for (i = 0; i < 20; i++)
                    marcaFita[i] = 0; // inicializa um vetor para marcar quais fitas foram usadas

                for (i = 0; i < 20; i++)
                    totalnaFita[i] = 0; //contador de itens em cada fita

                //cin >> n; //leitura da entrada
                n = atoi(argv[2]);
                int n2 = n; //somente para guardar o valor de n, Ã© passado como parametro na segunda parte
                if ((binario = fopen("PROVAOBIN.bin", "rb")) == NULL) {
                    cout << "erro ao abrir arquivo" << endl;
                    return 0;
                }

                while (n > 0) {
                    if (n < 20)
                        controle = n; //lendo blocos de 20, se o bloco for menor que 20, a variavel controle guarda o valor exato
                    for (i = 0; i < controle; i++) {
                        if (fread(&leitura, sizeof (TipoDados), 1, binario) == 1) {
                            bloco[i] = leitura;
                        }
                    }
                    n = n - 20; //lendo de 20 em 20
                    selectSort(bloco, controle);
                    switch (contaFitas) {//contafitas comeÃ§a com 1
                        case 1:
                        {
                            fita1E = fopen("fita1E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle; //incrementa o contador de elementos no vetor totalnafita
                            fclose(fita1E);
                            break;
                        }
                        case 2:
                        {
                            fita2E = fopen("fita2E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita2E);
                            break;
                        }
                        case 3:
                        {
                            fita3E = fopen("fita3E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita3E);
                            break;
                        }
                        case 4:
                        {
                            fita4E = fopen("fita4E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita4E);
                            break;
                        }
                        case 5:
                        {
                            fita5E = fopen("fita5E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita5E);
                            break;
                        }
                        case 6:
                        {
                            fita6E = fopen("fita6E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita6E);
                            break;
                        }
                        case 7:
                        {
                            fita7E = fopen("fita7E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita7E);
                            break;
                        }
                        case 8:
                        {
                            fita8E = fopen("fita8E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita8E);
                            break;
                        }
                        case 9:
                        {
                            fita9E = fopen("fita9E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita9E);
                            break;
                        }
                        case 10:
                        {
                            fita10E = fopen("fita10E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita10E);
                            break;
                        }
                        case 11:
                        {
                            fita11E = fopen("fita11E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita11E);
                            break;
                        }
                        case 12:
                        {
                            fita12E = fopen("fita12E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita12E);
                            break;
                        }
                        case 13:
                        {
                            fita13E = fopen("fita13E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita13E);
                            break;
                        }
                        case 14:
                        {
                            fita14E = fopen("fita14E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita14E);
                            break;
                        }
                        case 15:
                        {
                            fita15E = fopen("fita15E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita15E);
                            break;
                        }
                        case 16:
                        {
                            fita16E = fopen("fita16E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita16E);
                            break;
                        }
                        case 17:
                        {
                            fita17E = fopen("fita17E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita17E);
                            break;
                        }
                        case 18:
                        {
                            fita18E = fopen("fita18E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita18E);
                            break;
                        }
                        case 19:
                        {
                            fita19E = fopen("fita19E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita19E);
                            break;
                        }
                        case 20:
                        {
                            fita20E = fopen("fita20E.bin", "ab");
                            for (i = 0; i < controle; i++) {
                                fwrite(&bloco[i], sizeof (TipoDados), 1, fita1E);
                            }
                            totalnaFita[contaFitas - 1] = totalnaFita[contaFitas - 1] + controle;
                            fclose(fita20E);
                            break;
                        }
                    }
                    marcaFita[contaFitas - 1]++; //marca a fita como usada
                    contaFitas++; //incrementa o contador de qual fita foi usada
                    if (contaFitas > 20)
                        contaFitas = 1; //se todas as 20 fitas forem usadas, volta a utilizar a primeira

                }
                exibeFitasE(); //funÃ§Ã£o somente para exibir as futas de entrada preenchidas (desnecessario)
                for (i = 0; i < 20; i++)
                    cout << marcaFita[i] << " "; // somente para exibir o vetor marcafita (desnecessario)
                cout << endl;
                for (i = 0; i < 20; i++)
                    cout << totalnaFita[i] << " "; //exibe a quantidade de elementos na fita (desnecessario)

                ibvc_pt2(marcaFita, n2, totalnaFita); // chama a funÃ§Ã£o de intercalacao

                fclose(binario);
                return 0;
            }
            if (atoi(argv[3]) == 3) {
                cout << "Teste Aleatorio" << endl;


            }

        }


            break;
        case 2:
        {
            cout << " (2) Intercalacao balanceada de varios caminhos II" << endl;


            if (atoi(argv[3]) == 1) {
                cout << "Teste ascendente" << endl;
                if ((tmp = fopen("tmp.bin", "w+b")) == NULL) {
                    cout << "erro ao abrir arquivo tmp.bin" << endl;
                    return 0;
                }
                clock_t inicial = clock();
                IBSS(tmp);
                clock_t final = clock();
                tempo_execucao1 = (((double) final - (double) inicial) / 1000) * CLOCKS_PER_SEC;
                strcpy(nome, "tmp.bin");
                if (argc == 5) {
                    if ((atoi(argv[1])) == 5) {
                        if (strcmp(argv[4], "-P") == 0) {
                            print(tmp, Dir, nome);
                        }
                    }
                }
                cout << "numero transferencia leitura: " << numeroTransferenciaLeitura << "\n"
                        << "numero_transferencia_escrita: " << numeroTransferenciaEscrita << "\n"
                        << "tempo_execucao: " << tempo_execucao1 << "\n"
                        << "numero_comparacao: " << comparacoes << endl;
            }
            if (atoi(argv[3]) == 2) {
                cout << "Teste descendente" << endl;
                if ((tmp = fopen("tmp.bin", "w+b")) == NULL) {
                    cout << "erro ao abrir arquivo tmp.bin" << endl;
                    return 0;
                }
                clock_t inicial = clock();
                IBSS(tmp);
                clock_t final = clock();
                tempo_execucao1 = (((double) final - (double) inicial) / 1000) * CLOCKS_PER_SEC;

                strcpy(nome, "tmp.bin");
                if (argc == 5) {
                    if ((atoi(argv[1])) == 5) {
                        if (strcmp(argv[4], "-P") == 0) {
                            print(tmp, Dir, nome);
                        }
                    }
                }
                cout << "numero transferencia leitura: " << numeroTransferenciaLeitura << "\n"
                        << "numero_transferencia_escrita: " << numeroTransferenciaEscrita << "\n"
                        << "tempo_execucao: " << tempo_execucao1 << "\n"
                        << "numero_comparacao: " << comparacoes << endl;

            }
            if (atoi(argv[3]) == 3) {
                cout << "Teste Aleatorio" << endl;
                if ((tmp = fopen("tmp.bin", "w+b")) == NULL) {
                    cout << "erro ao abrir arquivo tmp.bin" << endl;
                    return 0;
                }
                clock_t inicial = clock();
                IBSS(tmp);
                clock_t final = clock();
                tempo_execucao1 = (((double) final - (double) inicial) / 1000) * CLOCKS_PER_SEC;
                strcpy(nome, "tmp.bin");
                if (argc == 5) {
                    if ((atoi(argv[1])) == 5) {
                        if (strcmp(argv[4], "-P") == 0) {
                            print(tmp, Dir, nome);
                        }
                    }
                }
                cout << "numero transferencia leitura: " << numeroTransferenciaLeitura << "\n"
                        << "numero_transferencia_escrita: " << numeroTransferenciaEscrita << "\n"
                        << "tempo_execucao: " << tempo_execucao1 << "\n"
                        << "numero_comparacao: " << comparacoes << endl;
            }
            // remove arquivo manipulaÃƒÂ§ÃƒÂ£o temporaria.
            remove("tmp.bin");
        }
            break;
        case 3:
        {
            cout << "IntercalaÃƒÂ§ÃƒÂ£o polifÃƒÂ¡sica I" << endl;

        }
            break;
        case 4:
        {
            cout << "IntercalaÃƒÂ§ÃƒÂ£o polifÃƒÂ¡sica II" << endl;

        }
            break;
        case 5:
        {
            cout << "Quicksort externo" << endl;
            if (atoi(argv[3]) == 1) {
                cout << "Teste ascendente" << endl;
                if ((ArqLEs = fopen("tmp.bin", "r+b")) == NULL) {
                    cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
                    return 0;
                }
                if ((ArqLi = fopen("tmp.bin", "r+b")) == NULL) {
                    cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
                    return 0;
                }
                if ((ArqEi = fopen("tmp.bin", "r+b")) == NULL) {
                    cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
                    return 0;
                }
                clock_t inicial = clock();
                QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, Esq, Dir);
                clock_t final = clock();
                tempo_execucao = (((double) final - (double) inicial) / 1000) * CLOCKS_PER_SEC;
                fflush(ArqLi);
                fclose(ArqEi);
                fclose(ArqLEs);
                fseek(ArqLi, 0, SEEK_SET);
                strcpy(nome, "tmp.bin");
                if (argc == 5) {
                    if ((atoi(argv[1])) == 5) {
                        if (strcmp(argv[4], "-P") == 0) {
                            print(tmp, Dir, nome);
                        }
                    }
                }
                cout << "numero transferencia leitura: " << numero_transferencia_leitura << "\n"
                        << "numero_transferencia_escrita: " << numero_transferencia_escrita << "\n"
                        << "tempo_execucao: " << tempo_execucao << "\n"
                        << "numero_comparacao: " << numero_comparacao << endl;

            }
            if (atoi(argv[3]) == 2) {
                cout << "Teste descendente" << endl;

                if ((ArqLEs = fopen("tmp.bin", "r+b")) == NULL) {
                    cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
                    return 0;
                }
                if ((ArqLi = fopen("tmp.bin", "r+b")) == NULL) {
                    cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
                    return 0;
                }
                if ((ArqEi = fopen("tmp.bin", "r+b")) == NULL) {
                    cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
                    return 0;
                }

                clock_t inicial = clock();
                QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, Esq, Dir);
                clock_t final = clock();
                tempo_execucao = (((double) final - (double) inicial) / 1000) * CLOCKS_PER_SEC;
                fflush(ArqLi);
                fclose(ArqEi);
                fclose(ArqLEs);
                fseek(ArqLi, 0, SEEK_SET);
                strcpy(nome, "tmp.bin");
                if (argc == 5) {
                    if ((atoi(argv[1])) == 5) {
                        if (strcmp(argv[4], "-P") == 0) {
                            print(tmp, Dir, nome);
                        }
                    }
                }
                cout << "numero transferencia leitura: " << numero_transferencia_leitura << "\n"
                        << "numero_transferencia_escrita: " << numero_transferencia_escrita << "\n"
                        << "tempo_execucao: " << tempo_execucao << "\n"
                        << "numero_comparacao: " << numero_comparacao << endl;
            }
            if (atoi(argv[3]) == 3) {
                cout << "Teste Aleatorio" << endl;

                if ((ArqLEs = fopen("tmp.bin", "r+b")) == NULL) {
                    cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
                    return 0;
                }
                if ((ArqLi = fopen("tmp.bin", "r+b")) == NULL) {
                    cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
                    return 0;
                }
                if ((ArqEi = fopen("tmp.bin", "r+b")) == NULL) {
                    cout << "erro ao abrir arquivo PROVAO_BIN_ASC.bin" << endl;
                    return 0;
                }

                clock_t inicial = clock();
                QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, Esq, Dir);
                clock_t final = clock();
                tempo_execucao = (((double) final - (double) inicial) / 1000) * CLOCKS_PER_SEC;
                fflush(ArqLi);
                fclose(ArqEi);
                fclose(ArqLEs);
                fseek(ArqLi, 0, SEEK_SET);
                strcpy(nome, "tmp.bin");
                if (argc == 5) {
                    if ((atoi(argv[1])) == 5) {
                        if (strcmp(argv[4], "-P") == 0) {
                            print(tmp, Dir, nome);
                        }
                    }
                }
                cout << "numero transferencia leitura: " << numero_transferencia_leitura << "\n"
                        << "numero_transferencia_escrita: " << numero_transferencia_escrita << "\n"
                        << "tempo_execucao: " << tempo_execucao << "\n"
                        << "numero_comparacao: " << numero_comparacao << endl;
            }
            // remove arquivo manipulaÃƒÂ§ÃƒÂ£o temporaria.
            remove("tmp.bin");
        }
            break;
        default: cout << "entrada inconsistente" << endl;
            break;
    }
    return 0;
}
