

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <windows.h>

#include "Racional.h"


void Mostra(char* text, Racional* r) {
    printf("%s: %d/%d\n", text, r->numerador, r->denominador);
}


double CalculaPI1(int n) {
    // Calcula os n termos, já inicializando a soma com primeiro que é 1.0
    double soma = 1.0;
    int i;
    for (i = 2; i <= n; i++) {
        soma += pow(-1.0, i - 1) / pow(2 * i - 1, 3.0);
    }
    // Calcula o valor final de pi em função da soma
    double pi = pow(32.0 * soma, 1.0 / 3.0);  // neste ponto obsersar que 1/3 
                                              // é diferente de 1.0/3.0
    return pi;
}

double CalculaPI2(int n) {
    // Calcula os n termos
    double soma = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        soma += pow(-1.0, i) / pow(2 * i + 1, 3.0);
    }
    // Calcula o valor final de pi em função da soma
    double pi = pow(32.0 * soma, 1.0 / 3.0);   // neste ponto obsersar que 1/3 
                                               // é diferente de 1.0/3.0
    return pi;
}



void PrimeiraQuestao() {
    printf("Primeira Questao\n");
    // Lendo número de termos da série e checando se é válido.
    int n = 0;
    printf("Informe o numero de termos: ");
    scanf("%d", &n);
    if (n < 1) {
        printf("Numero de termos %d invalido.", n);
        return;
    }
    double pi1 = CalculaPI1(n);
    double pi2 = CalculaPI2(n);

    printf("pi1 = %lf\n", pi1);
    printf("pi2 = %lf\n", pi2);

    printf("O valor de pi com %d termos e %lf com precisao %lf\n\n", n, pi1, (pi1 - M_PI));
}



void CalculaMediaMinimoMaximo(int* valores, int n) {

    if (n < 1) return;

    int minimo = INT_MAX;
    int maximo = INT_MIN;
    double soma = 0;
    int i;
    for (i = 0; i < n; i++) {
        soma += valores[i];
        if (valores[i] < minimo) {
            minimo = valores[i];
        } else if (valores[i] > maximo) {
            maximo = valores[i];
        }
    }
    double media = soma / n;
    printf("Minimo: %d Maximo: %d Media: %lf\n\n", minimo, maximo, media);
}


void CalculaMediaMinimoMaximo2(int* valores, int n, int* max, int* min, double* media) {

    if (n < 1) return;

    int minimo = INT_MAX;
    int maximo = INT_MIN;
    double soma = 0;
    int i;
    for (i = 0; i < n; i++) {
        soma += valores[i];
        if (valores[i] < minimo) {
            minimo = valores[i];
        } else if (valores[i] > maximo) {
            maximo = valores[i];
        }
    }
    *min = minimo;
    *max = maximo;
    *media = soma / n;
}



void SegundaQuestao() {
    int valores[] = {6,4,10,21,11,8,30,10};
    int i, n = 8;

    printf("Valores: {");
    for (i = 0; i < n; i++) {
        printf("%d ",valores[i]);
    }
    printf("}\n");
        
    printf("Segunda Questao - Item 1\n");
    CalculaMediaMinimoMaximo(valores, n);

    int min, max;
    double media;
    CalculaMediaMinimoMaximo2(valores, n, &max, &min, &media);
    printf("Segunda Questao - Item 2\n");
    printf("Minimo: %d Maximo: %d Media: %lf\n\n", min, max, media);
}


typedef struct {
    int numerador;
    int denominador;
} TRacional;


double TransformaNumero(TRacional num) {
    return (double) num.numerador / (double) num.denominador;
}

TRacional Soma(TRacional n1, TRacional n2) {
    TRacional s;
    s.numerador = (n1.numerador * n2.denominador) + (n1.denominador * n2.numerador);
    s.denominador = n1.denominador * n2.denominador;
    return s;
}


void TerceiraQuestao() {
    printf("Terceira Questao\n");
    TRacional n1, n2;
    n1.numerador = 5;
    n1.denominador = 8;

    n2.numerador = 3;
    n2.denominador = 9;
    TRacional s = Soma(n1, n2);

    printf("%lf %lf %lf %lf\n\n", TransformaNumero(n1), TransformaNumero(n2), TransformaNumero(s), TransformaNumero(Soma(n1, n2)));
    getchar();
}

void QuartaQuestao() {
    printf("Quarta Questao\n");
    Racional n1, n2;
    n1.numerador = 5;
    n1.denominador = 8;

    n2.numerador = 3;
    n2.denominador = 9;

    Racional n1_simplificado;
    simplifica(&n1, &n1_simplificado);

    Mostra("n1", &n1);
    Mostra("n1 simplificado", &n1_simplificado);

    Racional n2_simplificado;
    simplifica(&n2, &n2_simplificado);

    Mostra("n2", &n2);
    Mostra("n2 simplificado", &n2_simplificado);

    Real n2_real = transforma(&n2);
    Real n2_simplificado_real = transforma(&n2_simplificado);

    //    printf("transforma n2=%lf\n",n2_real);
    //    printf("transforma n2 simplificado=%lf\n",n2_simplificado_real);

    assert(n2_real == n2_simplificado_real); // se o resultado for igual passa direto pelo assert

    Racional s;
    soma(&n1, &n2, &s);
    printf("%d/%d + %d/%d = %d/%d\n\n", n1.numerador, n1.denominador, n2.numerador, n2.denominador, s.numerador, s.denominador);

    Racional s_simplificado;
    simplifica(&s, &s_simplificado);
    Mostra("s simplificado", &s_simplificado);
}


int main(int argc, char** argv) {
    int opcao;
    do {
        system("cls");
        printf("# Informe o numero da questao para testar #\n");
        printf(" 1 - Testa Questao 1 \n");
        printf(" 2 - Testa Questao 2 \n");
        printf(" 3 - Testa Questao 3 \n");
        printf(" 4 - Testa Questao 4 \n");
        printf(" 0 - Sair            \n\n");
        printf("> ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 0: printf("bye!!!\n");
                exit(0);
            case 1: PrimeiraQuestao();
                system("pause");
                break;
            case 2: SegundaQuestao();
                system("pause");
                break;
            case 3: TerceiraQuestao();
                system("pause");
                break;
            case 4: QuartaQuestao();
                system("pause");
                break;
            default: printf("Opcao invalida\n");
                Sleep(300); // Função da Biblioteca windows.h. Não era necessário nessa pratica.
        }
    } while (opcao != 0);

    return (EXIT_SUCCESS);
}

