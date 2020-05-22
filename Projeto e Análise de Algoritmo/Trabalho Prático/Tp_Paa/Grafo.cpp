/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Grafo.cpp
 * Author: freada
 * 
 * Created on July 26, 2016, 10:56 AM
 */

#include "Grafo.h"
#include <iostream>
Grafo::Grafo() {
}

Grafo::Grafo(const Grafo& orig) {
}

Grafo::~Grafo() {
}

void Grafo::SetGrafo(map<string, list<string> > grafo) {
    this->grafo = grafo;
}

map<string, list<string> > Grafo::GetGrafo() const {
    return grafo;
}
void Grafo::addAresta(string origin, string dest, string peso){
    grafo[origin].push_front(peso+dest);
    grafo[dest].push_front(peso+origin);
    
}
void Grafo::removeAresta(string origin, string peso, string dest){
    list<string>::iterator it = grafo[origin].begin();
    while(*it != peso+dest){
        it++;
    }
    grafo[origin].erase(it);
    it = grafo[dest].begin();
    while(*it != peso+origin){
        it++;
    }
    grafo[dest].erase(it);
}

void Grafo::addNo(string nome){
    list<string> lista;
    lista.push_back("0 "+nome);
    cout<<grafo.insert(make_pair(nome, lista) ).second<<endl;
}