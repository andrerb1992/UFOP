/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Artigo.h
 * Author: gustavo
 *
 * Created on 27 de Julho de 2016, 20:04
 */

#ifndef ARTIGO_H
#define ARTIGO_H
#include <stdlib.h>
#include <list>
#include <string>

using namespace std;

class Artigo{
    
    
public:
    Artigo();
    Artigo(const Artigo& orig);
    virtual ~Artigo();
    void setNome(string nome);
    string getNome();
    void addAutor(string autor);
    void addNomeParte(string nome_parte);
    void addRevistaParte(string revista_parte);
    void setSubConjunto(int sub_conjunto);
    void setRevista(string revista);
    string getRevista();
    int  getSubConjunto();
    void setCitacao(int citacao);
    int  getCitacao();
    void setAutores(list<string> autores);
    list<string> getAutores() const;
private:
    string nome;
    string revista;
    list<string> autores;
    list<string> nome_partes;
    list<string> revista_partes;
    int sub_conjunto;
    int citacao;
};

#endif /* ARTIGO_H */

