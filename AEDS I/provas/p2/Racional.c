#include "Racional.h"


Inteiro maximoDivisorComum(Inteiro a, Inteiro b) {
    if (b == 0) 
        return a;
    else
        return maximoDivisorComum(b, a % b);
}

Real transforma(const Racional* r) {
    return (double) r->numerador / r->denominador;
}

void soma(const Racional* r1, const Racional* r2, Racional* s) {
    s->numerador = (r1->numerador * r2->denominador + r1->denominador * r2->numerador);
    s->denominador = r1->denominador * r2->denominador;
}

void simplifica(const Racional* r, Racional* rs) {
    Inteiro mdc = maximoDivisorComum(r->numerador, r->denominador);
    rs->numerador = r->numerador / mdc;
    rs->denominador = r->denominador / mdc;
}
