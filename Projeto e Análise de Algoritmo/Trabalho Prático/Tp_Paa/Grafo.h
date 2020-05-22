/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Grafo.h
 * Author: freada
 *
 * Created on July 26, 2016, 10:56 AM
 */

#ifndef GRAFO_H
#define GRAFO_H
#include <stdlib.h>
#include <map>
#include <list>
#include <string>
using namespace std;

class Grafo {
public:
    Grafo();
    Grafo(const Grafo& orig);
    virtual ~Grafo();
    void SetGrafo(map<string, list<string> > grafo);
    map<string, list<string> > GetGrafo() const;
    void addAresta(string origin, string dest, string peso);
    void removeAresta(string origin, string peso, string dest);
    void addNo(string nome);
private:
    map<string, list<string> > grafo;

};

#endif /* GRAFO_H */

