#define MAX_LISTA_ENCADEADA 3
#define MAX_PESOS_ENCADEADA 3
#define MAX_LISTA_ABERTA 10
#define MAX_PESOS_ABERTA 10

#include "TContact.h"
using namespace std;

typedef struct celula {
	struct celula *pProx;
	TContact contact;
}TCelula;

typedef struct list {
	TCelula *pPrimeiro, *pUltimo;
}TLista;

typedef struct hash {
	int n; 
	int nro_lista; 
	int nro_pesos; 
	int *p; 
	TLista *lista; 
}THash;
 

typedef TContact TDicionario[MAX_LISTA_ABERTA]; /



THash* THash_Inicia(int nLista, int nPesos);
int THash_H(THash *hash, long phone);
int THash_Pesquisa(THash *hash, long phone, TContact *contact, int *totalCompare);
TCelula* THash_PesquisaCelula(THash *hash, long phone, int *totalCompare);
int THash_Insere(THash *hash, TContact contact);


void TLista_Inicia(TLista *lista);
int TLista_EhVazia(TLista *lista);
int TLista_Insere(TLista *lista, TContact contact);


void TDicionario_Inicia(TDicionario dic);
int TDicionario_Pesquisa(TDicionario dic, long phone, int *totalCompare);
int TDicionario_H(TDicionario dic, long phone);
int TDicionario_Insere(TDicionario dic, TContact contact);

