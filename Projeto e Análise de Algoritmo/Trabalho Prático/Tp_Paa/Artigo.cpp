/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Artigo.cpp
 * Author: gustavo
 * 
 * Created on 27 de Julho de 2016, 20:04
 */

#include "Artigo.h"
#include <string>


Artigo::Artigo() {
}


Artigo::~Artigo() {
}

void Artigo::setNome(string nome) {
    this->nome = nome;
}

string Artigo::getNome() {
    return nome;
}
void Artigo::addAutor(string autor) {

    if (autor == " " || autor.empty())
        return;
    
    if (autor.at(0) == ' '){
        this->autores.push_back(autor.substr(1, autor.size()));
        return;
    }
        
    
    this->autores.push_back(autor);
    return;
}
void Artigo::addNomeParte(string nome_parte) {
    this->nome_partes.push_back(nome_parte);
}
void Artigo::addRevistaParte(string revista_parte) {
    this->revista_partes.push_back(revista_parte);
}
void Artigo::setSubConjunto(int sub_conjunto) {
    this->sub_conjunto = sub_conjunto;
}
int  Artigo::getSubConjunto() {
    return sub_conjunto;
}
void Artigo::setCitacao(int citacao) {
    this->citacao = citacao;
}
int  Artigo::getCitacao() {
    return citacao;
}

void Artigo::setAutores(list<string> autores) {
    this->autores = autores;
}

list<string> Artigo::getAutores() const {
    return autores;
}

void Artigo::setRevista(string revista) {
    this->revista =  revista;
}
string Artigo::getRevista() {
    return this->revista;
}
Artigo::Artigo(const Artigo& orig) {
    this->citacao = orig.citacao;
    this->nome = orig.nome;
    this->revista = revista;
    this->sub_conjunto = orig.sub_conjunto;
    this->autores.insert(this->autores.end(), orig.autores.begin(), orig.autores.end());
    this->nome_partes.insert(this->nome_partes.end(), orig.nome_partes.begin(), orig.nome_partes.end());
    this->revista_partes.insert(this->revista_partes.end(), orig.revista_partes.begin(), orig.revista_partes.end());
}