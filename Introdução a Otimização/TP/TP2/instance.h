/* 
 * File:   instance.h
 * Author: USER
 *
 * Created on 8 de Agosto de 2016, 14:22
 */

#ifndef INSTANCE_H
#define	INSTANCE_H

typedef struct {
    int n; /* nr. de items         */
    int *custoProd; /* custo de producao do item i no periodo t */
    int *custoEstoque; /* #custo de estoque de uma unidade  do produto  i no periodo t  */
    int *custoPreparacao; /*custo de preparacao para produzir o item i no periodo t */
    int *unidadeReq; /*unidaes requeridas do total da capacidade Ct para a produção de um unidade  do item i*/
    int *tempoProd; /*tempo gasto para preparar o recurso para produzir item i*/
    int *capProd; /*#capacidade de producao em cada periodo t"*/
    int *qtoProdItem;// quantidade produzida em cada periodo;
    int *nivelEstoq; //nivel de estoque de cada periodo
    int tempo; /* tempo */
    int res;
} Instance;

/* cria um objeto instância e preenche com dados do arquivo */
Instance *readInstance(const char *fileName);


#endif	/* INSTANCE_H */

