#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    char telefone[20];
} Contato;

typedef struct TipoNo {
    Contato contato;
    struct TipoNo *esq;
    struct TipoNo *dir;
    int altura;
} TipoNo;

TipoNo* criarNo(Contato contato);
TipoNo* inserir(TipoNo* raiz, Contato contato, int *rotacoes);
TipoNo* remover(TipoNo* raiz, char *telefone, int *encontrado, int *rotacoes);
TipoNo* buscar(TipoNo* raiz, char *telefone, int *comparacoes);
void ordem(TipoNo* raiz);
void liberarArvore(TipoNo* raiz);
int alturaNo(TipoNo* n);
int fatorBalanceamento(TipoNo* n);

#endif
