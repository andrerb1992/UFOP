/* 
 * File:   main.cpp
 * Author: USER
 *
 * Created on 8 de Agosto de 2016, 14:21
 */

/*
 * ga.c
 * example of a Genetic Algorithm for the knapsack problem
 * Copyright (C) 2016 H.G. Santos <haroldo.santos@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include "instance.h"

#include <time.h>   
#include <iostream>
#include <math.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// computes a random number [0,1)
#define DBL_RND (((double)rand()) / (((double)RAND_MAX)+1.0))

/* instance with problem data */
Instance *inst;

typedef struct {
    /* incidence vector indicating if each element will or not be chosen */
    char *iv;
    double fitness;
} Individual;

/* parameters of the algorithm */
int popSize = 10000; /* population size */
float mtRate = 0.01; /* mutation rate */
int generations = 250; /* number of generations */

/* statistics about the population, best, worst and average */
double bestFit;
double worstFit;
double avFit;

/* individuals are stored as binary vectors   
 * population of solutions, space for current and next generation  */

Individual *currGen;
Individual *nextGen;

void allocate_memory_population();

/* fills initial population */
void populate();

/* binary tournament */
void selectTwoIndividuals(Individual *pop, int *i1, int *i2);

/* generates new population by uniform crossover */
void applyCrossover();

void applyMutation();
//void restricao();// restricao da funcao objetiva
void evaluatePopulation(Individual *population);

int main(int argc, const char **argv) {
    srand(time(NULL));
    printf("\n teste1");

    if (argc < 2) {
        fprintf(stderr, "enter instance name.\n");
        exit(EXIT_FAILURE);
    }

    inst = readInstance(argv[1]);
    printf("quantidade de itens %d .\n", inst->n);
    printf("quantidade de tempo %d .\n", inst->tempo);

//    for (int i = 0; i < 6; i++) {
//        printf(" ", inst->custoProd[i]);
//    }
//    for (int i = 0; i < 6; i++) {
//        printf(" ", inst->custoEstoque[i]);
//    }
//    for (int i = 0; i < 6; i++) {
//        printf(" ", inst->custoPreparacao[i]);
//    }
//    for (int i = 0; i < 3; i++) {
//        printf(" ", inst->unidadeReq[i]);
//    }
//    for (int i = 0; i < 3; i++) {
//        printf(" ", inst->tempoProd[i]);
//    }
//    for (int i = 0; i < inst->tempo; i++) {
//        printf(" ", inst->capProd[i]);
//    }
//    for (int i = 0; i < 6; i++) {
//        printf(" ", inst->qtoProdItem[i]);
//    }
//    for (int i = 0; i < 6; i++) {
//        printf(" ", inst->nivelEstoq[i]);
//    }


    printf("\n teste1");
    allocate_memory_population();
    printf("teste2");
    populate();

    int gen;
    for (gen = 1; (gen<+generations); ++gen) {
        evaluatePopulation(currGen);

        /* generates new population by crossover */
        applyCrossover();

        /* mutates */
        applyMutation();

        printf("generation %06d, fitness: (worst, average, best): %14.0f %14.0f %14.0f\n", gen + 1, worstFit, avFit, bestFit);

        /* swaping populations */
        Individual *temp = currGen;
        currGen = nextGen;
        nextGen = temp;
    }
}

void applyCrossover() {
    int i;
    for (i = 0; (i < popSize); ++i) {
        int i1, i2;
        selectTwoIndividuals(currGen, &i1, &i2);

        /* creating new individual by uniform crossover */
        int j;
        for (j = 0; j < ((inst->n)*(inst->tempo)); ++j)
            nextGen[i].iv[j] = (rand() % 2 == 0) ? currGen[i1].iv[j] : currGen[i2].iv[j];
    }
}

void allocate_memory_population() {
    printf("teste3");
    currGen = (Individual *) malloc(sizeof (Individual) * popSize);
    //printf(currGen);
    int i;
    for (i = 0; (i < popSize); ++i)
        currGen[i].iv =(char*) ((int *) malloc(sizeof (int)* ((inst->n)*(inst->tempo)))); //-

    nextGen = (Individual *) malloc(sizeof (Individual) * popSize);
    for (i = 0; (i < popSize); ++i)
        nextGen[i].iv = (char*)((int *) malloc(sizeof (int)* ((inst->n)*(inst->tempo)))); //-
}

void populate() {
    int i;
    for (i = 0; (i < popSize); ++i) {
        int j;
        for (j = 0; (j < (inst->n)*(inst->tempo)); ++j)
            currGen[i].iv[j] = rand() % 2;
    }
}

double evaluateFitness(const Individual *ind);
double restricao1(const Individual *ind);

void evaluatePopulation(Individual *population) {
    bestFit = -DBL_MAX;
    worstFit = DBL_MAX;
    avFit = 0.0;
    int i;
    for (i = 0; (i < popSize); ++i) {
        population[i].fitness = evaluateFitness(&population[i]);
        bestFit = MAX(bestFit, population[i].fitness);
        worstFit = MIN(worstFit, population[i].fitness);
        avFit += population[i].fitness;
    }
    avFit /= ((double) popSize);
}

double restricao1(const Individual *ind) {
    double result1 = 0.0;
    double result1A = 0.0;
    int demandaD[6] = {1, 5, 3, 2, 3, 2};
    for (int i = 0; (i < inst->n); ++i) {
        result1 = (inst->nivelEstoq[i] + inst->qtoProdItem[i]);
        result1A = inst->nivelEstoq[i] + demandaD[i];
    }
    double custPre = result1 - result1A;
    if (custPre == 0) {
        printf(" ok ");
    } else
        custPre -= 1000;
    printf("  ", custPre);
    return custPre;


}

double evaluateFitness(const Individual *ind) {
    double f = 0;
    double r = 0;
    double totalWeight = 0.0;
    int dinheiroDemanda = 100; // quanto estou disposto a pagar pelo serviço
    int vetBinary[5]; // fala se produz aquele determinado item ou nao
    for (int i = 0; i < 6; i++) {
        vetBinary[i] = rand() % 2;
    }
    int i;
    for (i = 0; i < (inst->n * inst->tempo); ++i) {
        totalWeight +=(vetBinary[i] * ((inst->custoPreparacao[i] * inst->qtoProdItem[i])+(inst->custoProd[i] * inst->qtoProdItem[i])+(inst->custoEstoque[i] * inst->nivelEstoq[i])));
        f += dinheiroDemanda - ((vetBinary[i])*(ind->iv[i] * ((inst->custoEstoque[i] + inst->custoProd[i] + inst->custoPreparacao[i])* inst->qtoProdItem[i]))); /* profit */
    }
    
    // colocar aqui as restricao
    inst->res = restricao1(ind);
    const double excess = MAX(totalWeight - inst->n, 0);
    if (totalWeight != 0) {
        totalWeight -= totalWeight - 10;
        //printf("\n pena %d: ", totalWeight);
    } 
    //printf("total: %d",totalWeight);

  
    /* penalty for excess */
    f -= (excess * 10000.0) + totalWeight;

    return f;
}

/* selects two individuals, each one is selected by binary tournament */
void selectTwoIndividuals(Individual *pop, int *i1, int *i2) {
    {
        int s1 = rand() % popSize;
        int s2 = rand() % popSize;

        if (pop[s1].fitness > pop[s2].fitness)
            *i1 = s1;
        else
            *i1 = s2;
    }

    do {
        int s1 = rand() % popSize;
        int s2 = rand() % popSize;

        if (pop[s1].fitness > pop[s2].fitness)
            *i2 = s1;
        else
            *i2 = s2;

    } while (*i2 == *i1);
}

void applyMutation() {
    int i, j;
    for (i = 0; (i < popSize); ++i)
        for (j = 0; (j < ((inst->n)*(inst->tempo))); ++j)
            if (DBL_RND <= mtRate)
                currGen[i].iv[j] = rand() % 2;
}

