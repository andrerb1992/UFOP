#include "instance.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

Instance *readInstance(const char *fileName) {
    Instance *inst = (Instance *) malloc(sizeof (Instance));

    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        fprintf(stderr, "fileName %s not found.\n", fileName);
        abort();
    }

    fscanf(f, "%d", &(inst->n));
    fscanf(f, "%d", &(inst->tempo));

    inst->custoProd = (int *) malloc(sizeof (int)*((inst->n)*(inst->tempo)));
    inst->custoEstoque = (int *) malloc(sizeof (int)*((inst->n)*(inst->tempo)));
    inst->custoPreparacao = (int *) malloc(sizeof (int)*((inst->n)*(inst->tempo)));
    inst->unidadeReq = (int *) malloc(sizeof (int)*inst->n);
    inst->tempoProd = (int *) malloc(sizeof (int)*inst->n);
    inst->capProd = (int *) malloc(sizeof (int)*((inst->tempo)));
    inst->qtoProdItem = (int *) malloc(sizeof (int)*((inst->n)*(inst->tempo)));
    inst->nivelEstoq = (int *) malloc(sizeof (int)*((inst->n)*(inst->tempo)));


    int i;
    for (i = 0; i < 6; i++)
        fscanf(f, "%d ", &(inst->custoProd[i]));
    for (i = 0; (i < ((inst->n)*(inst->tempo))); i++)
        fscanf(f, "%d", &(inst->custoEstoque[i]));
    for (i = 0; (i < ((inst->n)*(inst->tempo))); i++)
        fscanf(f, "%d", &(inst->custoPreparacao[i]));
    for (i = 0; (i < inst->n); i++)
        fscanf(f, "%d", &(inst->unidadeReq[i]));
    for (i = 0; (i < inst->n); i++)
        fscanf(f, "%d", &(inst->tempoProd[i]));
    for (i = 0; (i < inst->tempo); i++)
        fscanf(f, "%d", &(inst->capProd[i]));
    for (i = 0; (i < ((inst->n)*(inst->tempo))); i++)
        fscanf(f, "%d", &(inst->qtoProdItem[i]));
    for (i = 0; (i < ((inst->n)*(inst->tempo))); i++)
        fscanf(f, "%d", &(inst->nivelEstoq[i]));




    fclose(f);

    return inst;
}

