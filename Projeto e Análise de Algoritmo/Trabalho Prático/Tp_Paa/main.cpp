/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: freada
 *
 * Created on July 26, 2016, 10:56 AM
 */

#include <cstdlib>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <fstream>

#include <math.h> 

#include "Grafo.h"
#include "Artigo.h"
using namespace std;

/*
 * 
 */
//int minimo(int n1, int n2, int n3){
//    if(n1 < n2 && n1 < n3){
//        return n1;
//    }else if(n2 < n1 && n2 < n3){
//        return n2;
//    }else return n3;
//}
//
//int calculaDistancia(string p1, string p2){
//    int m = p1.size(), n = p2.size(), c;
//    int **matriz;
//    matriz = new int*[m];
//    for(int i = 0; i < m; i++){
//        matriz[i] = new int[n];
//    }
//    for(int i = 0; i<m; i++){
//        matriz[i][0] = i;
//    }
//    for(int i = 0; i<n; i++){
//        matriz[0][i] = i;
//    }
//    
//    for(int i = 1; i < m; i++){
//        for(int j = 1; j < n; j++){
//            if(p1.at(i) == p2.at(j)){
//                c = 1;
//            }else{
//                c = 0;
//            }
////            if(matriz[i-1][j-1]+c < matriz[i-1][j]+1 && matriz[i-1][j-1]+c < matriz[i][j-1]+1)
//            matriz[i][j] = minimo(matriz[i-1][j-1]+c, matriz[i-1][j]+1, matriz[i][j-1]+1); 
//        }
//    }
//    return matriz[m-1][n-1];
//}
//
//
//void insereAresta(vector<string> no1, vector<string> no2){
//    
//}

int minimo(int n1, int n2, int n3) {
    if (n1 < n2 && n1 < n3) {
        return n1;
    } else if (n2 < n1 && n2 < n3) {
        return n2;
    } else return n3;
}

int calculaDistancia(string p1, string p2) {// p algoritimo com programação  dinamica
    int m = p1.size(), n = p2.size(), c;
    //cout << n << " nessa porra" << m << endl;
    if ((m > 1 && n > 1) && ((m < 100) && (n < 100))) {
        int **matriz;
        matriz = new int*[m];
        for (int i = 0; i < m; i++) {
            matriz[i] = new int[n];
        }
        for (int i = 0; i < m; i++) {
            matriz[i][0] = i;
        }
        for (int i = 0; i < n; i++) {
            matriz[0][i] = i;
        }

        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (p1.at(i) == p2.at(j)) {
                    c = 1;
                } else {
                    c = 0;
                }
                //            if(matriz[i-1][j-1]+c < matriz[i-1][j]+1 && matriz[i-1][j-1]+c < matriz[i][j-1]+1)
                matriz[i][j] = minimo(matriz[i - 1][j - 1] + c, matriz[i - 1][j] + 1, matriz[i][j - 1] + 1);
            }
        }
        if (n > 1 && m > 1) return matriz[m - 1][n - 1];
    } else return 1000;
}

int processaArtigos(Artigo a1, Artigo a2) {
    int peso = 500;
    int auxpeso = 500, auxpeso2 = 0;
    int dist;
    string aux, aux2;
    auxpeso = calculaDistancia(a1.getNome(), a2.getNome());
    auxpeso2 = calculaDistancia(a1.getRevista(), a2.getRevista());
    if (auxpeso > -50 && auxpeso<50)peso -= auxpeso*10;
    if (auxpeso2 > -50 && auxpeso2 < 50)peso -= auxpeso2*10;
    //    cout<<a1.getAutores().size()<<" porrra"<<endl;
    //
    if ((a1.getAutores().size() > 1 && a2.getAutores().size() > 1) && (a1.getAutores().size() < 100 && a2.getAutores().size() < 100)) {
        int n = 0, m = 0;
        list<string>::iterator it;
        cout << a1.getAutores().size() << "  " << a2.getAutores().size() << endl;
        for (list<string>::iterator it = a1.getAutores().begin(); n < a1.getAutores().size(); it++, n++) {
            try {
                list<string> auxl1 = a1.getAutores();
                for (it = auxl1.begin(); it != auxl1.end(); it++) {
                    //cout<<"ta processando porra!!"<<endl;
                    int cont = 0;
                    list<string>::iterator it2;
                    aux = *it;
                    int i = a2.getAutores().size();

                    list<string> auxl = a2.getAutores();
                    for (it2 = auxl.begin(); it2 != auxl.end(); it2++) {
                        //for (list<string>::iterator it2 = a2.getAutores().begin();m < a2.getAutores().size(); it2++, m++) {
                        cont++;
                        //cout<<*it2<<endl;

                        aux2 = *it2;
                        if ((aux != "" && aux2 != "") || aux != " " && aux2 != " ") {

                            dist = calculaDistancia(aux, aux2);
                            if (dist < 5) peso -= dist;
                        }
                    }
                }
            } catch (const std::exception &exc) {
                std::cerr << exc.what();
            }
        }


        return peso;
    }
}

void poda(Grafo* g) {
    pair<string, list<string> > par;

    for (map<string, list<string> >::iterator it = g->GetGrafo().begin(); it != g->GetGrafo().end(); it++) {
        for (list<string>::iterator it2 = par.second.begin(); it2 != par.second.end(); it2++) {
            string aux = "";
            string a2 = *it2;
            char c = a2.at(0);
            int cont = 0;
            while (c != ' ') {
                aux = aux + c;
                cont++;
                c = a2.at(cont);
            }
            istringstream buffer(aux);
            int value;
            buffer >> value;
            if (value > 500) {
                g->removeAresta(par.first, aux, *it2);
            }

        }
    }
}
typedef struct{
    string peso;
    string origin;
    string dest;
}estAux;

bool compare_nocase (const estAux& first, const estAux second)
{
    istringstream ss(first.peso), s2(second.peso);
    int v1,v2;
    ss >> v1;
    s2 >> v2;
    return ( v1 < v2);
}


void criaGrafo(Grafo* g, list<Artigo> l) {
    int auxPeso=0;
    Artigo aAux, aAux2;
    list<estAux> lA;


    for (list<Artigo>::iterator j = l.begin(); j != l.end(); j++) {
        aAux = *j;
        cout << aAux.getNome() << "doidera essa porra " << l.size() << endl;
        g->addNo(aAux.getNome());


    }
    cout << g->GetGrafo().size() << " t g" << endl;
    int cont = 0;
    for (list<Artigo>::iterator i = l.begin(); i != l.end();) {
        for (list<Artigo>::iterator j = l.begin(); j != l.end();) {
            cont++;
            estAux a1;
            a1.peso = "";
            a1.dest ="";
            a1.origin = "";
            if (i != j) {
                aAux = *i;
                aAux2 = *j;
                auxPeso = processaArtigos(aAux, aAux2);
                if (auxPeso < 400) {
                    ostringstream convert; // stream used for the conversion
                    convert << auxPeso;
                    g->addAresta(aAux.getNome(), aAux2.getNome(), convert.str());
                    a1.origin = aAux.getNome();
                    a1.peso = convert.str();
                    a1.dest = aAux2.getNome();
                    lA.push_back(a1);
                }else{
                    cout<< "aee"<<endl;
                }


            }

            if (j != l.end()) {
                j++;
            } else {
                break;
            }

        }
        list<Artigo>::iterator itaux = i;
        i++;
        l.erase(itaux);
        if (i != l.end()) {
            i++;
        } else {
            break;
        }

    }
    lA.sort(compare_nocase);
    list<estAux>::iterator itDoidao = lA.begin();
    estAux ax;
    for(int i = 0; i < ceil(lA.size()/3); i++){
        ax = *itDoidao;
        g->removeAresta(ax.origin, ax.peso, ax.dest);
    }
    
    

}

int main(int argc, char** argv) {

    // Leitura do arquivo de entrada
    ifstream arquivo;
    arquivo.open("/home/freada/Downloads/Tp_Paa/CChen.txt", ifstream::in);
    string entrada, temp;
    int i, first_pos, last_pos;

    list<Artigo> lista_Artigos;
    while (getline(arquivo, entrada)) {

        Artigo artigo;

        // Pega o subconjunto ID
        first_pos = 0;
        last_pos = entrada.find("_");
        temp = entrada.substr(first_pos, last_pos);
        i = atoi(temp.c_str());
        artigo.setSubConjunto(i);
        cout << "Sub conjunto: " << i << "\n";

        // Pega a citacao ID
        first_pos = last_pos + 1;
        last_pos = entrada.find(" ");
        temp = entrada.substr(first_pos, last_pos);
        i = atoi(temp.c_str());
        artigo.setCitacao(i);
        cout << "Citacao: " << i << "\n";

        // Pega autores
        first_pos = last_pos + 1;
        last_pos = entrada.find("<>") - 4;
        temp = entrada.substr(first_pos, last_pos);
        stringstream autores(temp);
        string autor;
        char split = ';';
        cout << "Autores : \n";
        while (getline(autores, autor, split)) {
            artigo.addAutor(autor);
            cout << autor << "\n";
        }

        //Pega o nome do artigo
        first_pos = entrada.find_first_of("<>") + 2;

        entrada = entrada.substr(first_pos, entrada.length());
        last_pos = entrada.find("<>");
        temp = entrada.substr(0, last_pos);
        cout << "Titulo: " << temp << "\n";
        artigo.setNome(temp);
        stringstream partes(temp);
        string parte;
        split = ' ';
        while (getline(partes, parte, split)) {
            artigo.addNomeParte(parte);
            cout << parte << "\n";
        }

        //Pega o nome do artigo
        first_pos = entrada.find_first_of("<>") + 2;

        entrada = entrada.substr(first_pos, entrada.length());
        last_pos = entrada.find("<>");
        temp = entrada.substr(0, last_pos);
        cout << "Revista/comgresso: " << temp << "\n";
        artigo.setRevista(temp);
        stringstream rev_partes(temp);
        string rev_parte;
        split = ' ';
        while (getline(rev_partes, rev_parte, split)) {
            artigo.addRevistaParte(rev_parte);
            cout << rev_parte << "\n";
        }

        cout << "\n\n";
        cout << artigo.getRevista() << "   " << endl;
        lista_Artigos.push_front(artigo);
    }

    Grafo g;
    criaGrafo(&g, lista_Artigos);
    poda(&g);
    
    return 0;
}

