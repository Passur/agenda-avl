# Agenda telefônica com Árvore AVL

Aplicação de terminal em C para cadastrar e organizar contatos pelo telefone usando uma árvore AVL. O balanceamento após inserções e remoções mantém buscas e atualizações em O(log n).

## Funcionalidades
- Inserir contatos (ID, nome e telefone).
- Buscar e remover pelo telefone.
- Listar contatos em ordem de telefone.
- Exibir altura, rotações e comparações realizadas.

## Compilar e executar
Requer GCC e GNU Make. Na raiz do projeto:

```sh
make
make run
```

Executar os testes da AVL:

```sh
make test
```

## Estrutura
- `include/avl.h`: interface e tipos do TAD.
- `src/avl.c`: operações e balanceamento AVL.
- `src/main.c`: menu da agenda.
- `tests/teste.c`: testes de inserção, busca, remoção e rotações.
- `Makefile`: compilação, execução e testes.
