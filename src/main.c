#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/avl.h"

int main(){
    TipoNo* raiz = NULL;
    int opcao = 0;
    Contato c;
    char telefoneBusca[20];
    int rotacoes = 0;
    int comparacoes = 0;
    int encontrado = 0;

    do{
        printf("\n--- AGENDA AVL ---\n");
        printf("1. Inserir contato\n");
        printf("2. Buscar por telefone\n");
        printf("3. Remover por telefone\n");
        printf("4. Listar contatos em ordem\n");
        printf("5. Sair\n");
        printf("Digite sua opcao: ");
        if(scanf("%d", &opcao) != 1){
            printf("Erro na leitura!\n");
            break;
        }
        if(opcao == 1){
            printf("ID: ");
            scanf("%d", &c.id);
            printf("Nome: ");
            scanf(" %[^\n]", c.nome);
            printf("Telefone: ");
            scanf(" %[^\n]", c.telefone);
            rotacoes = 0;
            raiz = inserir(raiz, c, &rotacoes);
            printf("Contato inserido com sucesso!\n");
            printf("Rotacoes realizadas: %d | Altura da arvore: %d\n", rotacoes, alturaNo(raiz));
        }else if(opcao == 2){
            printf("Digite o telefone para buscar: ");
            scanf(" %[^\n]", telefoneBusca);
            comparacoes = 0;
            TipoNo* resultado = buscar(raiz, telefoneBusca, &comparacoes);
            if(resultado != NULL){
                printf("\nContato encontrado!\n");
                printf("ID: %d | Nome: %s | Tel: %s\n", resultado->contato.id, resultado->contato.nome, resultado->contato.telefone);
            }else{
                printf("Contato nao encontrado.\n");
            }
            printf("Comparacoes de chaves: %d\n", comparacoes);
        }else if(opcao == 3){
            printf("Digite o telefone do contato para remover: ");
            scanf(" %[^\n]", telefoneBusca);
            encontrado = 0;
            rotacoes = 0;
            raiz = remover(raiz, telefoneBusca, &encontrado, &rotacoes);
            if(encontrado){
                printf("Contato removido com sucesso!\n");
            }else{
                printf("Contato nao encontrado para remocao.\n");
            }
            printf("Rotacoes realizadas: %d | Altura da arvore: %d\n", rotacoes, alturaNo(raiz));
        }else if(opcao == 4){
            printf("\n--- LISTA DE CONTATOS ---\n");
            ordem(raiz);
        }else if(opcao == 5){
            liberarArvore(raiz);
            printf("Encerrando programa e liberando memoria...\n");
        }else{
            printf("Opcao invalida, tente novamente.\n");
        }
    }while(opcao != 5);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/avl.h"

int main(){
    TipoNo* raiz = NULL;
    int opcao = 0;
    Contato c;
    char telefoneBusca[20];
    int rotacoes = 0;
    int comparacoes = 0;
    int encontrado = 0;

    do{
        printf("
--- AGENDA AVL ---
");
        printf("1. Inserir contato
");
        printf("2. Buscar por telefone
");
        printf("3. Remover por telefone
");
        printf("4. Listar contatos em ordem
");
        printf("5. Sair
");
        printf("Digite sua opcao: ");
        if(scanf("%d", &opcao) != 1){
            printf("Erro na leitura!
");
            break;
        }
        if(opcao == 1){
            printf("ID: ");
            scanf("%d", &c.id);
            printf("Nome: ");
            scanf(" %[^
]", c.nome);
            printf("Telefone: ");
            scanf(" %[^
]", c.telefone);
            rotacoes = 0;
            raiz = inserir(raiz, c, &rotacoes);
            printf("Contato inserido com sucesso!
");
            printf("Rotacoes realizadas: %d | Altura da arvore: %d
", rotacoes, alturaNo(raiz));
        }else if(opcao == 2){
            printf("Digite o telefone para buscar: ");
            scanf(" %[^
]", telefoneBusca);
            comparacoes = 0;
            TipoNo* resultado = buscar(raiz, telefoneBusca, &comparacoes);
            if(resultado != NULL){
                printf("
Contato encontrado!
");
                printf("ID: %d | Nome: %s | Tel: %s
", resultado->contato.id, resultado->contato.nome, resultado->contato.telefone);
            }else{
                printf("Contato nao encontrado.
");
            }
            printf("Comparacoes de chaves: %d
", comparacoes);
        }else if(opcao == 3){
            printf("Digite o telefone do contato para remover: ");
            scanf(" %[^
]", telefoneBusca);
            encontrado = 0;
            rotacoes = 0;
            raiz = remover(raiz, telefoneBusca, &encontrado, &rotacoes);
            if(encontrado){
                printf("Contato removido com sucesso!
");
            }else{
                printf("Contato nao encontrado para remocao.
");
            }
            printf("Rotacoes realizadas: %d | Altura da arvore: %d
", rotacoes, alturaNo(raiz));
        }else if(opcao == 4){
            printf("
--- LISTA DE CONTATOS ---
");
            ordem(raiz);
        }else if(opcao == 5){
            liberarArvore(raiz);
            printf("Encerrando programa e liberando memoria...
");
        }else{
            printf("Opcao invalida, tente novamente.
");
        }
    }while(opcao != 5);
    return 0;
}
