#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_clientes.h"
#include "hashtable.h"
#include "nos.h"

NóCliente* Inserir_Cliente_Arvore(NóCliente *raiz, Cliente novo_cliente) {
    if (raiz == NULL) {
        NóCliente *novo_no = Criar_No_Cliente(novo_cliente);
        if (novo_no == NULL) {
            printf("Erro: Falha ao alocar memória para o cliente %d.\n", novo_cliente.Id);
            return NULL;
        }
        return novo_no;
    }

    if (novo_cliente.Id < raiz->dados.Id) {
        raiz->esquerda = Inserir_Cliente_Arvore(raiz->esquerda, novo_cliente);
    } 
    else if (novo_cliente.Id > raiz->dados.Id) {
        raiz->direita = Inserir_Cliente_Arvore(raiz->direita, novo_cliente);
    }

    return raiz;
}

NóCliente* Pesquisar_Cliente_Arvore(NóCliente *raiz, int id_cliente) {
    if (raiz == NULL || raiz->dados.Id == id_cliente) {
        return raiz;
    }

    if (id_cliente < raiz->dados.Id) {
        return Pesquisar_Cliente_Arvore(raiz->esquerda, id_cliente);
    }
    return Pesquisar_Cliente_Arvore(raiz->direita, id_cliente);
}

void Imprimir_Clientes_Ordem(NóCliente *raiz) {
    if (raiz == NULL) return;
    Imprimir_Clientes_Ordem(raiz->esquerda);
    printf("ID: %d\tNome: %s\tIdade: %d\n", raiz->dados.Id, raiz->dados.Nome, raiz->dados.Idade);
    Imprimir_Clientes_Ordem(raiz->direita);
}

void Ver_Clientes(Sistema sis) {
    if (sis.Raiz_Clientes == NULL) {
        printf("Não há clientes cadastrados.\n");
        return;
    }
    printf("\n=== Clientes ===\n");
    Imprimir_Clientes_Ordem(sis.Raiz_Clientes);
}

void Adicionar_Cliente(Sistema *sis) {
    Cliente c;
    printf("ID do cliente: ");
    if (scanf("%d", &c.Id) != 1) {
        printf("ID inválido.\n");
        while (getchar() != '\n' && !feof(stdin));
        return;
    }
    while (getchar() != '\n' && !feof(stdin));

    if (Pesquisar_Cliente_Arvore(sis->Raiz_Clientes, c.Id) != NULL) {
        printf("Cliente com este ID já existe.\n");
        return;
    }

    printf("Nome do cliente: ");
    if (fgets(c.Nome, sizeof(c.Nome), stdin) == NULL) {
        printf("Erro na leitura do nome.\n");
        return;
    }
    size_t len = strlen(c.Nome);
    if (len > 0 && c.Nome[len - 1] == '\n') {
        c.Nome[len - 1] = '\0';
    }

    printf("Idade do cliente: ");
    if (scanf("%d", &c.Idade) != 1) {
        printf("Idade inválida.\n");
        while (getchar() != '\n' && !feof(stdin));
        return;
    }
    while (getchar() != '\n' && !feof(stdin));

    c.tabelaProdutos = Inicializar_Tabela_Hash(TAMANHO_TABELA_PRODUTOS);
    if (c.tabelaProdutos == NULL) {
        printf("Erro ao criar tabela de produtos.\n");
        return;
    }
    c.Tamanho_Tabela = TAMANHO_TABELA_PRODUTOS;
    c.Total_Produtos = 0;
    c.Tempo_Atendimento = 0;

    sis->Raiz_Clientes = Inserir_Cliente_Arvore(sis->Raiz_Clientes, c);
    sis->Num_Clientes++;
    printf("Cliente adicionado.\n");
}

void Pesquisar_Cliente(Sistema sis) {
    int id_cliente;
    printf("ID do cliente: ");
    if (scanf("%d", &id_cliente) != 1) {
        printf("ID inválido.\n");
        while (getchar() != '\n' && !feof(stdin));
        return;
    }
    while (getchar() != '\n' && !feof(stdin));

    NóCliente *no = Pesquisar_Cliente_Arvore(sis.Raiz_Clientes, id_cliente);
    if (no == NULL) {
        printf("Cliente não encontrado.\n");
        return;
    }

    printf("ID: %d\nNome: %s\nIdade: %d\nTotal de produtos: %d\nTempo de atendimento: %d\n",
           no->dados.Id, no->dados.Nome, no->dados.Idade,
           no->dados.Total_Produtos, no->dados.Tempo_Atendimento);
}

void Adicionar_Produto_Cliente(Sistema *sis) {
    int id_cliente;
    printf("ID do cliente: ");
    if (scanf("%d", &id_cliente) != 1) {
        printf("ID inválido.\n");
        while (getchar() != '\n' && !feof(stdin));
        return;
    }
    while (getchar() != '\n' && !feof(stdin));

    NóCliente *no = Pesquisar_Cliente_Arvore(sis->Raiz_Clientes, id_cliente);
    if (no == NULL) {
        printf("Cliente não encontrado.\n");
        return;
    }

    Produto p;
    printf("ID do produto: ");
    if (scanf("%d", &p.Id_Produto) != 1) {
        printf("ID de produto inválido.\n");
        while (getchar() != '\n' && !feof(stdin));
        return;
    }
    while (getchar() != '\n' && !feof(stdin));

    printf("Preço do produto: ");
    if (scanf("%f", &p.Preco_Produto) != 1) {
        printf("Preço inválido.\n");
        while (getchar() != '\n' && !feof(stdin));
        return;
    }
    while (getchar() != '\n' && !feof(stdin));

    printf("Tipo do produto: ");
    if (fgets(p.Tipo, sizeof(p.Tipo), stdin) == NULL) {
        printf("Erro na leitura do tipo de produto.\n");
        return;
    }
    size_t len = strlen(p.Tipo);
    if (len > 0 && p.Tipo[len - 1] == '\n') {
        p.Tipo[len - 1] = '\0';
    }

    Inserir_Produto_Hash(&no->dados, p);
    printf("Produto adicionado ao cliente %d.\n", id_cliente);
}

void Ver_Produtos_Cliente(Sistema sis) {
    int id_cliente;
    printf("ID do cliente: ");
    if (scanf("%d", &id_cliente) != 1) {
        printf("ID inválido.\n");
        while (getchar() != '\n' && !feof(stdin));
        return;
    }
    while (getchar() != '\n' && !feof(stdin));

    NóCliente *no = Pesquisar_Cliente_Arvore(sis.Raiz_Clientes, id_cliente);
    if (no == NULL) {
        printf("Cliente não encontrado.\n");
        return;
    }

    if (no->dados.Total_Produtos == 0 || no->dados.tabelaProdutos == NULL) {
        printf("Nenhum produto cadastrado para este cliente.\n");
        return;
    }

    printf("\n=== Produtos do Cliente %s ===\n", no->dados.Nome);
    Imprimir_Produtos_Cliente(&no->dados);
}

void Salvar_Clientes_Arvore(FILE *f, NóCliente *raiz) {
    if (f == NULL || raiz == NULL) return;
    Salvar_Clientes_Arvore(f, raiz->esquerda);
    fprintf(f, "%d\t%s\t%d\n", raiz->dados.Id, raiz->dados.Nome, raiz->dados.Idade);
    Salvar_Clientes_Arvore(f, raiz->direita);
}

void Libertar_Arvore_Clientes(NóCliente *raiz) {
    if (raiz == NULL) return;
    
    Libertar_Arvore_Clientes(raiz->esquerda);
    Libertar_Arvore_Clientes(raiz->direita);
    
    Libertar_Tabela_Hash(&(raiz->dados));

    free(raiz);
}