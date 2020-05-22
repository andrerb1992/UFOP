

#ifndef AMOSTRADADOS_H
#define	AMOSTRADADOS_H

#define VALOR_MIN 1
#define VALOR_MAX 10

typedef struct {
    int*  dados;
    int   tamanho;
} AmostraDados;

#define SUCESSO 0
#define ERRO_LEITURA 1
#define ERRO_ALOCACAO 2

int    AmostraDados_leitura(AmostraDados*);
double AmostraDados_mediaAritmetica(AmostraDados*);
int    AmostraDados_mediana(AmostraDados*);
int    AmostraDados_moda(AmostraDados*);
void   AmostraDados_destroi(AmostraDados*);

#endif	/* AMOSTRADADOS_H */

