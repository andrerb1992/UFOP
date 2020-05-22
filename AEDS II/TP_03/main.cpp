/* 
 * File:   main.cpp
 * Author:  Thiago Resende
 *			Douglas ferreira
 *			Andre Ribeiro
 *
 */
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <limits.h>
#include <fstream>
#include <limits>
#include <set>
#include <list>

using namespace std;

typedef char TipoTexto;
typedef char TipoPadrao;
// struct Vocabulario
typedef struct {
    string palavra;
    int nFrequencia;
    int posicao[10000];
} Tvocabulario;

// forca bruta
int tamanhoTabela = 1000;
// função usada para comparar duas palavras .. retornando 1 se for a primeira for menor que a segunda e 0 caso contrario
struct classcomp {

    bool operator() (const Tvocabulario& lhs, const Tvocabulario& rhs) const {
        return lhs.palavra < rhs.palavra;
    }
};
// função compara atravez da chave frequencia
bool cmp(Tvocabulario t1, Tvocabulario t2) {
    return (t1.nFrequencia > t2.nFrequencia);
}
// forca bruta
void forcaBruta(TipoTexto *Texto, long n, TipoPadrao *Padrao, long m, long &forcabruta, FILE *resultadofb, char *nomes) {

    long i = 0, j = 0, k = 0;
    
	// for para percorrer o texto ate o tamanho do texto - o tamanho do padrao
    for (i = 0; i <= (n - m + 1); i++) {
        k = i;
        j = 1;
        // para cada caracter do texto eh feita a pesquisa avancando de um em um...
        //enquanto o caracter do texto for igual ao caracter do padrao e nao for final do arquivo
		while (Texto[k - 1] == Padrao[j - 1] && j <= m) {
            j++;//incrementa o j do padrao
            k++;// incrementa o k do texto
						
			forcabruta++;//incrementa o numero de comparacoes
            //se j for maior que o tamanho do meu padrao
			if (j > m) {
				// casamento encontrado
                fprintf(resultadofb, "Casamento encontrado no arquivo %s na posicao: %ld \n", nomes, i);
            }
        }
		//incrementa o numero de comparacoes
        forcabruta++;
    }
}

int main(int argc, char** argv) {
    //casamento <metodo> <padrao> [-P]
    FILE * pA[1000], *pNomes; //  vetor de ponteiros de 1000 posicoes e um ponteiro de arquivo
    char nomes[1000][50]; // matriz de char para ler as palavras
    long fb, invertido; //contadores de comparacoes
    long tamPadrao = 0;// recebe o tamanho do padrao
    list<Tvocabulario> listaVoc;// listaVoc usada para fazer o arquivo invertido
	string arg1, arg2; 
    int aux30;
    clock_t t;//variavel usada para calcular o tempo
    TipoPadrao padrao[130]; // usado para guardar o padrao
    strcpy(padrao, argv[2]);//passando o argumento para a variavel padrao
    tamPadrao = strlen(padrao);//pegando o tamanho da palavra
	
	// verifica se foi possivel abrir o arquivo para leitura
	if ((pNomes = fopen("nomes.txt", "r")) == NULL) {
        cout << "erro ao abrir arquivo nomes.txt" << endl;
        return 0;
    }
	// lendo os 1000 arquivos e passando para o vetor
    for (int i = 0; i < 1000; i++) {
        fscanf(pNomes, "%s", nomes[i]);
        //cout<< nomes[i] << endl;
    }
	
    fclose(pNomes); // fecha o arquivo
	
    if (!(argc == 4 || argc == 5)) { // testa o numero de argumentos para que o programa funcione corretamente
        cout << "entrada inconsistente. Considere: casamento <mÃ©todo> <padrÃ£o> [-P]" << endl;
        return 0;
    }

    switch (atoi(argv[1])) {
        case 1:
        {
            int palavras = 0; // contador de palavras
            string palavra; // palavra
            set<Tvocabulario, classcomp> voc;// set( usado como ferramenta para criacao do arquivo invertido)
            set<Tvocabulario>::iterator it;//iterador para Tvocabulario
            Tvocabulario aux; //aux.. do tipo Tvocabulario
            t = clock(); // iniciando o clock
            // for de i ate a quantidade de arquivos
			for (int i = 0; i < 500; i++) {
				
                ifstream entrada(nomes[i], ios::in);// efetua a leitura do arquivo
                palavras++;//cont palavras ++
                //enquanto nao acabar o arquivo
				while (!entrada.eof()) {
                    entrada>>palavra;       //entrada coloca palavra na variavel palavra
                    aux.palavra = palavra; // e para o aux tambem
                    //se ja houver uma ocorrencia
					if (voc.count(aux) > 0) {
                        invertido++; // comparacao ++
                        it = voc.find(aux); // procura onde esta
                        aux = *it; // aux recebe o iterador para poder incrementar
                        aux.nFrequencia++; // frequencia da palavra ++
                        aux.posicao[(*it).nFrequencia - 1] = palavras; // como ja houve ocorrencia posicao recebe o em qual lugar deve colocar a proxima palavra
                        voc.erase(it);// retira o it para poder incrementar a frequencia
                        voc.insert(aux);// insere o aux ja incrementado
                    } else {// se ainda nao houver a palavra
                        invertido++; // comparador ++ 
                        aux.palavra = palavra; //aux recebe a palavra
                        aux.posicao[0] = palavras;// insere a palavra na posição 0
                        aux.nFrequencia = 1;// e frequencia recebe 1, pois eh primeira ocorrencia da palavra
                        voc.insert(aux);// insere o aux no voc
                    }
                }
                //fecha o arquivo
                entrada.close();
            }
            ofstream saida("invertido.txt"); // saida usada para escrever no arquivo invertido.txt
            it = voc.begin();//iterador recebe a primeira posicao do voc
			//for usado para percorrer toda a voc
            for (unsigned int j = 0; j < voc.size(); j++) {
                
				saida << (*it).palavra<<"        "; // insere as palavras dentro do arquivo.txt
				// for de k ate o tamanho da frequencia da palavra
                for (int k = 0; k < (*it).nFrequencia; k++) {
                    
					saida << (*it).posicao[k]<<" ";// escreve a posicao da palavra
					
				}
                saida << "\n";
                it++;
            }
			// criando aux2 do tipo Tvocabulario
            Tvocabulario aux2;
			//criando um iterador para Tvocabulario
            set<Tvocabulario>::iterator it2;
			// 
            if (argc == 5 || argc == 4) {
				
				
					// if para verificar se tem apenas um padrao
					
					if (strcmp(argv[3], "-P") == 0) {
						aux.palavra = argv[2];
						it = voc.find(aux);                   
							cout << (*it).palavra<<"   frequencia:"<<(*it).nFrequencia<<endl;                

					} else if (argc == 5) {
						//if para verificar se tem 2 padroes
						if(strcmp(argv[4], "-P") == 0) {
							aux.palavra = argv[2]; // pega a primeira palavra
							aux2.palavra = argv[3]; // pega a segunda palavra
							it = voc.find(aux);// procura a primeira palavra
							it2 = voc.find(aux2); // priocura a segunda palavra
							//verifica a quantas  vezes apareceu um padrao seguido do outro
							for (int i = 0; i < (*it).nFrequencia; i++) {
								for (int k = 0; k < (*it2).nFrequencia; k++) {
									if ((*it).posicao[i] == (*it2).posicao[k] + 1) {
										aux30++;
										
									}
								}
								
										
							}
							cout << (*it).palavra << " " << (*it2).palavra << "   frequencia: "<<aux30<<endl;
						}
					}
				
			}
			
            list<Tvocabulario> lista;
            it = voc.begin();
            // joga todo o voc para dentro da lista
			for (unsigned int j = 0; j < voc.size(); j++) {
                lista.push_front((*it));
                it++;
            }
            lista.sort(cmp);// ordena o arquivo
            list<Tvocabulario>::iterator itList = lista.begin();// iterador na primeira posicao da lista
            // ate it ser menor que o tamanho da lista
			for (; itList != (lista.end()); itList++) {
                //cout << (*itList).palavra << "  " << (*it).nFrequencia << endl;
            }
			
            saida.close();
            t = clock() - t;
			//verifica o -P
            if (argc == 5 || argc == 4) {
                if ((atoi(argv[1])) == 1) {
                    if (strcmp(argv[3], "-P") == 0 || strcmp(argv[4], "-P") == 0) {
                        cout << "Numero de comparacoes Entre os caracteres do padrao e do texto: " << invertido << endl;
                        cout << "Tempo de execucao: " << (((float) t) / CLOCKS_PER_SEC) << " seg" << endl;
                    }
                }
            }
        }

            break;
        case 2:
        {
            FILE *resultadofb;
            float tempo;

            cout << "forca bruta " << endl;

            if ((resultadofb = fopen("fb.txt", "w")) == NULL) {
                cout << "erro ao abrir arquivoe fb.txt" << endl;
            }
            clock_t inicial = clock();
            for (int i = 0; i < 500; i++) {

                long tamTexto = 0;
                TipoTexto *texto;

                texto = (TipoTexto*) malloc(sizeof (TipoTexto)*100000);

                if ((pA[i] = fopen(nomes[i], "r")) == NULL) {
                    cout << "erro ao abrir arquivo " << pA[i] << endl;
                    return 0;
                }

                while (fscanf(pA[i], "%c", &texto[tamTexto]) != EOF) {
                    //cout << texto[tamTexto] << endl;
                    tamTexto++;
                }
                fclose(pA[i]);
                texto[tamTexto] = '\0';
                padrao[strlen(padrao) + 1] = '\0';
                forcaBruta(texto, tamTexto, padrao, tamPadrao, fb, resultadofb, nomes[i]);
                free(texto);

            }
            fclose(resultadofb);
            clock_t final = clock();
            tempo = (((double) final - (double) inicial) / 1000) * CLOCKS_PER_SEC;
            if (argc == 4) {
                if ((atoi(argv[1])) == 2) {
                    if (strcmp(argv[3], "-P") == 0) {
                        cout << "Numero de comparacoes Entre os caracteres do padrao e do texto: " << fb << endl;
                        cout << "Tempo de execucao: " << tempo << endl;
                    }
                }
            }

        }
            break;
        default: cout << "entrada inconsistente" << endl;
            break;
    }
    return 0;
}