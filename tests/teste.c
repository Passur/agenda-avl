#include "../include/avl.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

static Contato contato(int id, const char *telefone) {
    Contato c;
    c.id = id;
    snprintf(c.nome, sizeof(c.nome), "Contato %d", id);
    snprintf(c.telefone, sizeof(c.telefone), "%s", telefone);
    return c;
}

static int verificarArvore(TipoNo *raiz, const char *minimo, const char *maximo) {
    if (raiz == NULL) {
        return -1;
    }
    if (minimo != NULL) {
        assert(strcmp(raiz->contato.telefone, minimo) > 0);
    }
    if (maximo != NULL) {
        assert(strcmp(raiz->contato.telefone, maximo) < 0);
    }
    int alturaEsquerda = verificarArvore(raiz->esq, minimo, raiz->contato.telefone);
    int alturaDireita = verificarArvore(raiz->dir, raiz->contato.telefone, maximo);
    int alturaCalculada = 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
    assert(raiz->altura == alturaCalculada);
    assert(alturaEsquerda - alturaDireita >= -1);
    assert(alturaEsquerda - alturaDireita <= 1);
    assert(fatorBalanceamento(raiz) == alturaEsquerda - alturaDireita);
    return alturaCalculada;
}

static void testarRotacaoInsercao(const char *a, const char *b, const char *c,
                                  const char *raizEsperada, int rotacoesEsperadas) {
    TipoNo *raiz = NULL;
    int rotacoes = 0;
    raiz = inserir(raiz, contato(1, a), &rotacoes);
    raiz = inserir(raiz, contato(2, b), &rotacoes);
    raiz = inserir(raiz, contato(3, c), &rotacoes);
    assert(strcmp(raiz->contato.telefone, raizEsperada) == 0);
    assert(rotacoes == rotacoesEsperadas);
    assert(verificarArvore(raiz, NULL, NULL) == 1);
    liberarArvore(raiz);
}

static void testarRotacoesDeInsercao(void) {
    testarRotacaoInsercao("30", "20", "10", "20", 1);
    testarRotacaoInsercao("10", "20", "30", "20", 1);
    testarRotacaoInsercao("30", "10", "20", "20", 2);
    testarRotacaoInsercao("10", "30", "20", "20", 2);
}

static void testarRotacaoRemocao(const char *valores[], int quantidade,
                                 const char *telefoneRemovido,
                                 int rotacoesEsperadas) {
    TipoNo *raiz = NULL;
    int rotacoes = 0;
    int encontrado = 0;
    char chaveRemovida[20];
    for (int i = 0; i < quantidade; i++) {
        raiz = inserir(raiz, contato(i + 1, valores[i]), &rotacoes);
    }
    rotacoes = 0;
    snprintf(chaveRemovida, sizeof(chaveRemovida), "%s", telefoneRemovido);
    raiz = remover(raiz, chaveRemovida, &encontrado, &rotacoes);
    assert(encontrado == 1);
    assert(rotacoes == rotacoesEsperadas);
    verificarArvore(raiz, NULL, NULL);
    liberarArvore(raiz);
}

static void testarRotacoesDeRemocao(void) {
    const char *ll[] = {"4", "2", "5", "1", "3"};
    const char *rr[] = {"2", "1", "4", "3", "5"};
    const char *lr[] = {"40", "20", "60", "10", "30", "50", "25", "35"};
    const char *rl[] = {"40", "20", "60", "10", "50", "70", "45", "55"};
    testarRotacaoRemocao(ll, 5, "5", 1);
    testarRotacaoRemocao(rr, 5, "1", 1);
    testarRotacaoRemocao(lr, 8, "50", 2);
    testarRotacaoRemocao(rl, 8, "10", 2);
}

static void testarBuscaEOrdemDeInsercao(void) {
    TipoNo *crescente = NULL;
    TipoNo *decrescente = NULL;
    int rotacoes = 0;
    int comparacoes = 0;
    for (int i = 1; i <= 7; i++) {
        char telefone[20];
        snprintf(telefone, sizeof(telefone), "%02d", i);
        crescente = inserir(crescente, contato(i, telefone), &rotacoes);
    }
    rotacoes = 0;
    for (int i = 7; i >= 1; i--) {
        char telefone[20];
        snprintf(telefone, sizeof(telefone), "%02d", i);
        decrescente = inserir(decrescente, contato(i, telefone), &rotacoes);
    }
    assert(verificarArvore(crescente, NULL, NULL) == 2);
    assert(verificarArvore(decrescente, NULL, NULL) == 2);
    assert(buscar(crescente, "07", &comparacoes) != NULL);
    assert(comparacoes == 3);
    liberarArvore(crescente);
    liberarArvore(decrescente);
}

static void testarBuscaERemocao(void) {
    TipoNo *raiz = NULL;
    int rotacoes = 0;
    int comparacoes = 0;
    int encontrado = 0;
    Contato valores[] = {
        {10, "Ana", "1111-1111"},
        {20, "Bruno", "2222-2222"},
        {30, "Carlos", "3333-3333"}
    };
    for (int i = 0; i < 3; i++) {
        raiz = inserir(raiz, valores[i], &rotacoes);
    }
    assert(verificarArvore(raiz, NULL, NULL) == 1);
    TipoNo *resultado = buscar(raiz, "1111-1111", &comparacoes);
    assert(resultado != NULL);
    assert(strcmp(resultado->contato.telefone, "1111-1111") == 0);
    assert(comparacoes == 2);
    comparacoes = 0;
    assert(buscar(raiz, "9999-9999", &comparacoes) == NULL);
    assert(comparacoes == 2);
    raiz = remover(raiz, "2222-2222", &encontrado, &rotacoes);
    assert(encontrado == 1);
    comparacoes = 0;
    assert(buscar(raiz, "2222-2222", &comparacoes) == NULL);
    verificarArvore(raiz, NULL, NULL);
    liberarArvore(raiz);
}

int main() {
    testarRotacoesDeInsercao();
    testarRotacoesDeRemocao();
    testarBuscaEOrdemDeInsercao();
    testarBuscaERemocao();
    printf("TODOS OS TESTES DA AVL PASSARAM COM SUCESSO!
");
    return 0;
}
