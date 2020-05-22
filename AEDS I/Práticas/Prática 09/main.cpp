#include "TContact.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;

int main() {

	int c, n, p;

	long phoneAux;
	int contAux;
	int totalCompare;

	TDictionary *dict;
	TContact contact;
	
	TArvore *raiz = new TArvore;

	//Arvore
	TArvore_Inicia(raiz);

	//cout << "Numero de casos: ";
	cin >> c;

	getchar();

	for (int i = 0; i < c; ++i) {
		//cout << "Numero de contatos: ";
		cin >> n;
		//cout << "Numero de pesquisas: ";
		cin >> p;

		dict = newDictionary(n);

		for (int i = 0; i < n; ++i) {
		
			cin >> contact.name;
			cin >> contact.birthday;
			cin >> contact.phone;

			insertDictionary(dict, contact);
			TArvore_Insere(raiz, contact);
		}

		for (int i = 0; i < p; ++i) {
			cin >> phoneAux;	
			cout << phoneAux << endl;

			totalCompare = 0;
			contAux = searchSequential(dict, phoneAux, &totalCompare);

			if (contAux != -1) {
				cout << dict->contact[contAux].name << " ";
				cout << setw(4) << setfill('0') << dict->contact[contAux].birthday << " ";
				cout << contAux << " ";
				cout << totalCompare << endl;
			} else {
				cout << "Nao encontrado" << " " << contAux << " " << totalCompare << endl;
			}

			totalCompare = 0;
			contAux = searchBinary(dict, phoneAux, &totalCompare);

			if (contAux != -1) {
				cout << dict->contact[contAux].name << " ";
				cout << setw(4) << setfill('0') << dict->contact[contAux].birthday << " ";
				cout << contAux << " ";
				cout << totalCompare << endl;
			} else {
				cout << "Nao encontrado" << " " << contAux << " " << totalCompare << endl;
			}

			totalCompare = 0;
			contAux = TArvore_Pesquisa(*(raiz), phoneAux, &contact, &totalCompare);

			if (contAux == 1) {
				cout << contact.name << " ";
				cout << setw(4) << setfill('0') << contact.birthday << " ";
				cout << "1" << " ";
				cout << totalCompare << endl;
			} else {
				cout << "Nao encontrado" << " " << "-1" << " " << totalCompare << endl;
			}

			cout << endl;

		}

		delete[] dict;
	}

	return 0;
}