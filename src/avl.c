#include "../include/avl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define max(a, b) ((a) > (b) ? (a) : (b))

int alturaNo(TipoNo *no){
    if(no == NULL){
        return -1;
    }
    return no->altura;
}

TipoNo* avlMaior(TipoNo* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    while (raiz->dir != NULL) {
        raiz = raiz->dir;
    }
    return raiz;
}

int calculaAltura(TipoNo *raiz)
{
    if(raiz == NULL){
        return -1;
    }
    int alt_esq = -1, alt_dir = -1;
    if(raiz->esq != NULL){
        alt_esq = raiz->esq->altura;
    }
    if(raiz->dir != NULL){
        alt_dir = raiz->dir->altura;
    }
    raiz->altura = 1+max(alt_esq, alt_dir);
    return raiz->altura;
}

int maior_inteiro(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}

int fatorBalanceamento(TipoNo *raiz)
{
    if (raiz == NULL) {
        return 0;
    }
    int alt_esq = -1;
    int alt_dir = -1;
    if (raiz->esq != NULL) {
        alt_esq = raiz->esq->altura;
    }
    if (raiz->dir != NULL) {
        alt_dir = raiz->dir->altura;
    }
    return alt_esq - alt_dir;
}

TipoNo* criarNo(Contato contato){
    TipoNo *novo = (TipoNo*) malloc(sizeof(TipoNo));
    novo->contato = contato;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 0;
    return novo;
}

TipoNo* ratacaoDir(TipoNo* y, int *rotacoes){
    TipoNo* x = y->esq;
    TipoNo* T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = max(alturaNo(y->esq), alturaNo(y->dir)) + 1;
    x->altura = max(alturaNo(x->esq), alturaNo(x->dir)) + 1;
    if(rotacoes){
        (*rotacoes)++;
    }
    return x;
}

TipoNo* rotacaoEsq(TipoNo* x, int *rotacoes){
    TipoNo* y = x->dir;
    TipoNo* T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = max(alturaNo(x->esq), alturaNo(x->dir)) + 1;
    y->altura = max(alturaNo(y->esq), alturaNo(y->dir)) + 1;
    if(rotacoes){
        (*rotacoes)++;
    }
    return y;
}

TipoNo* inserir(TipoNo* raiz, Contato contato, int *rotacoes){
    if(raiz == NULL){
        return criarNo(contato);
    }
    int tel = strcmp(contato.telefone, raiz->contato.telefone);
    if(tel < 0){
        raiz->esq = inserir(raiz->esq, contato, rotacoes);
    }else if(tel > 0){
        raiz->dir = inserir(raiz->dir, contato, rotacoes);
    }else{
        return raiz;
    }
    raiz->altura = 1 + max(alturaNo(raiz->esq), alturaNo(raiz->dir));
    int balanceamento = fatorBalanceamento(raiz);
    if(balanceamento > 1 && strcmp(contato.telefone, raiz->esq->contato.telefone) < 0){
        return ratacaoDir(raiz, rotacoes);
    }
    if(balanceamento > 1 && strcmp(contato.telefone, raiz->esq->contato.telefone) > 0){
        raiz->esq = rotacaoEsq(raiz->esq, rotacoes);
        return ratacaoDir(raiz, rotacoes);
    }
    if(balanceamento < -1 && strcmp(contato.telefone, raiz->dir->contato.telefone) > 0){
        return rotacaoEsq(raiz, rotacoes);
    }
    if(balanceamento < -1 && strcmp(contato.telefone, raiz->dir->contato.telefone) < 0){
        raiz->dir = ratacaoDir(raiz->dir, rotacoes);
        return rotacaoEsq(raiz, rotacoes);
    }
    return raiz;
}

TipoNo* remover(TipoNo* raiz, char *telefone, int *encontrado, int *rotacoes) {
    if (raiz == NULL) {
        *encontrado = 0;
        return NULL;
    }
    int tel = strcmp(telefone, raiz->contato.telefone);
    if (tel < 0) {
        raiz->esq = remover(raiz->esq, telefone, encontrado, rotacoes);
    } else if (tel > 0) {
        raiz->dir = remover(raiz->dir, telefone, encontrado, rotacoes);
    } else {
        *encontrado = 1;
        if(raiz->esq == NULL || raiz->dir == NULL){
            TipoNo* temp = raiz->esq;
            if(temp == NULL){
                temp = raiz->dir;
            }
            if(temp == NULL){
                temp = raiz;
                raiz = NULL;
            }else{
                *raiz = *temp;
            }
            free(temp);
        }else{
            TipoNo* temp = avlMaior(raiz->esq);
            raiz->contato = temp->contato;
            raiz->esq = remover(raiz->esq, temp->contato.telefone, encontrado, rotacoes);
        }
    }
    if(raiz == NULL){
        return NULL;
    }
    raiz->altura = 1 + max(alturaNo(raiz->esq), alturaNo(raiz->dir));
    int balanceamento = fatorBalanceamento(raiz);
    if(balanceamento > 1 && fatorBalanceamento(raiz->esq) >= 0){
        return ratacaoDir(raiz, rotacoes);
    }
    if(balanceamento > 1 && fatorBalanceamento(raiz->esq) < 0){
        raiz->esq = rotacaoEsq(raiz->esq, rotacoes);
        return ratacaoDir(raiz, rotacoes);
    }
    if(balanceamento < -1 && fatorBalanceamento(raiz->dir) <= 0){
        return rotacaoEsq(raiz, rotacoes);
    }
    if(balanceamento < -1 && fatorBalanceamento(raiz->dir) > 0){
        raiz->dir = ratacaoDir(raiz->dir, rotacoes);
        return rotacaoEsq(raiz, rotacoes);
    }
    return raiz;
}

TipoNo* buscar(TipoNo* raiz, char *telefone, int *comparacoes){
    if(raiz == NULL){
        return NULL;
    }
    (*comparacoes)++;
    int tel = strcmp(telefone, raiz->contato.telefone);
    if(tel == 0){
        return raiz;
    }
    if(tel < 0){
        return buscar(raiz->esq, telefone, comparacoes);
    }
    return buscar(raiz->dir, telefone, comparacoes);
}

void liberarArvore(TipoNo* raiz){
    if(raiz != NULL){
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

void ordem(TipoNo* raiz){
    if(raiz != NULL){
        ordem(raiz->esq);
        printf("ID: %d | Nome: %s | Tel: %s\n", raiz->contato.id, raiz->contato.nome, raiz->contato.telefone);
        ordem(raiz->dir);
    }
}
