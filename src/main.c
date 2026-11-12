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
