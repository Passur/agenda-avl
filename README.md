# Agenda telefônica com Árvore AVL

## Integrantes
- Lara Geovana Almeida Melo — matrícula 5897
- Passur Caio Lelis Alves — matrícula 6590

## Descrição do problema
Este projeto tem como objetivo implementar uma agenda de contatos em linguagem C utilizando uma árvore AVL como estrutura de dados principal. A aplicação permite armazenar, localizar, remover e listar contatos de forma eficiente, mantendo a organização em ordem pelo telefone.

A escolha da AVL foi motivada pela necessidade de operações rápidas em conjuntos de dados dinâmicos, em especial em cenários com frequentes inserções e remoções. Diferente de uma árvore binária simples, a AVL mantém o balanceamento da árvore após cada operação, garantindo altura logarítmica e melhor desempenho para buscas.

## Aplicação desenvolvida
A aplicação implementa um menu interativo com as seguintes funcionalidades:
1. Inserir contato
2. Buscar contato por telefone
3. Remover contato por telefone
4. Listar contatos em ordem
5. Sair do programa

Ao inserir um contato, o usuário informa o ID, o nome e o telefone. A busca e a remoção são feitas a partir do telefone, que atua como chave de ordenação da árvore AVL.

## Estrutura de dados escolhida e justificativa técnica
A estrutura escolhida foi a Árvore AVL.

A estrutura `Contato` armazenada em cada nó possui:
- `id`: identificador do contato
- `nome`: nome da pessoa
- `telefone`: chave de busca e ordenação

A árvore organiza os contatos pela string do telefone, utilizando a comparação de strings (`strcmp`). Esse critério foi adotado porque o telefone funciona como identificador único e permite localizar rapidamente cada contato.

A AVL foi escolhida em vez de uma árvore binária comum porque, após cada inserção ou remoção, ela recalcula o fator de balanceamento e executa rotações conforme necessário. Isso mantém a altura da árvore em O(log n), o que melhora significativamente a performance de busca, inserção e remoção em comparação com estruturas não balanceadas.

## Principais operações implementadas
As operações principais da implementação são:
- `inserir`: insere um contato e realiza balanceamento da AVL
- `buscar`: busca um contato pelo telefone
- `remover`: remove um contato pelo telefone e reequilibra a árvore
- `ordem`: percorre a estrutura em ordem e imprime os contatos
- `liberarArvore`: desaloca toda a memória alocada para os nós

Além disso, a implementação também inclui funções auxiliares para:
- cálculo de altura dos nós
- cálculo do fator de balanceamento
- identificação do maior elemento da subárvore esquerda
- execução de rotações simples e duplas

## Organização dos arquivos do projeto
A organização atual do projeto é a seguinte:

- `include/avl.h` — definição da estrutura `Contato`, do nó da árvore e dos protótipos das funções
- `src/avl.c` — implementação da AVL e das operações de busca, inserção, remoção e balanceamento
- `src/main.c` — menu principal da aplicação e interação com o usuário
- `tests/teste.c` — testes de inserção, busca, remoção, rotações e fatores de balanceamento
- `Makefile` — regras para compilar, executar os testes, iniciar a aplicação e limpar os executáveis
- `README.md` — documentação do projeto

## Instruções de compilação e execução
É necessário ter o GCC e o GNU Make instalados e disponíveis no terminal. Na pasta raiz do projeto:

### Compilar a aplicação
```sh
make
```

### Executar a aplicação
```sh
make run
```

### Compilar e executar os testes
```sh
make test
```

### Remover os executáveis gerados
```sh
make clean
```

## Descrição dos testes realizados
O arquivo `tests/teste.c` usa `assert` para verificar os resultados. Os testes cobrem:
- os quatro casos de rebalanceamento na inserção: LL, RR, LR e RL
- os quatro casos de rebalanceamento após remoção, verificando uma rotação simples ou dupla
- a ordem da árvore (propriedade de busca binária), a altura armazenada em cada nó e o fator de balanceamento de todos os nós
- busca de chave existente e inexistente e a quantidade de nós visitados durante cada busca
- inserção em ordem crescente e decrescente
- remoção e confirmação de que o contato removido não é mais encontrado
- liberação da memória alocada

## Resultados experimentais e análise
As métricas consideradas são:
- **Altura:** número de arestas do caminho mais longo da raiz até uma folha. Na implementação, uma árvore vazia tem altura -1 e uma folha tem altura 0.
- **Comparações na busca:** `buscar` conta os nós visitados (uma comparação entre chaves por nó visitado). A rotina `strcmp` compara as strings dos telefones.
- **Rotações:** o contador registra rotações simples; uma rotação dupla é contabilizada como duas rotações simples.
- **Fator de balanceamento:** diferença entre as alturas das subárvores esquerda e direita. Para cada nó de uma AVL válida, seu valor deve estar entre -1 e 1.

Como experimento com sete telefones em ordem crescente ou decrescente, os testes verificam que a AVL termina com altura 2 e encontra o telefone `"07"` em 3 nós visitados. Para comparação, uma árvore binária de busca **não balanceada** construída com os mesmos telefones já ordenados teria altura 6 e poderia visitar 7 nós nessa busca. Essa árvore não balanceada é uma referência teórica; o projeto implementa e testa a AVL, não uma segunda estrutura.

Os testes também verificam que LL e RR usam uma rotação simples, enquanto LR e RL usam duas. Após remoções que causam desequilíbrio, são testados novamente os quatro formatos de rebalanceamento e a validade dos fatores de balanceamento. Assim, a AVL mantém altura O(log n) e busca, inserção e remoção O(log n) no pior caso, ao contrário da árvore não balanceada, que pode chegar a altura e custo O(n).

## Limitações conhecidas e possíveis melhorias
Algumas limitações podem ser observadas na implementação atual:
- não há persistência dos dados em arquivo, então a agenda é apagada ao encerrar o programa
- não há validação rigorosa de entradas do usuário (por exemplo, telefone com caracteres inválidos)
- a árvore não permite contatos duplicados com o mesmo telefone
- o programa não possui interface gráfica nem armazenamento em banco de dados

Possíveis melhorias incluem:
- salvar e carregar contatos em arquivo `.txt` ou `.csv`
- adicionar busca por nome, além de telefone
- validar entradas e formatar telefones automaticamente
- implementar ordenação por nome ou ID em versões futuras
- criar uma interface mais amigável, como terminal mais elaborado ou GUI

## Conclusão
Este projeto demonstrou a aplicação prática de uma Árvore AVL na implementação de uma agenda telefônica. A escolha da estrutura foi adequada para resolver o problema de forma eficiente, mantendo operações rápidas e organizadas em memória.

A implementação apresenta um código modular, com separação entre interface e lógica da estrutura, além de testes fundamentais que verificam o comportamento esperado da árvore.
