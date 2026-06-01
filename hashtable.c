#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "nos.h"

NóHashProduto** Inicializar_Tabela_Hash(int tamanho) {
    NóHashProduto **tabela = (NóHashProduto **)malloc(tamanho * sizeof(NóHashProduto *));
    if (tabela == NULL) return NULL;

    for (int i = 0; i < tamanho; i++) {
        *(tabela + i) = NULL; 
    }
    return tabela;
}

int Funcao_Hash(int id_produto, int tamanho) {
    return id_produto % tamanho;
}

void Inserir_Produto_Hash(Cliente *cliente, Produto novo_produto) {
    if (cliente == NULL || cliente->tabelaProdutos == NULL) return;

    int indice = Funcao_Hash(novo_produto.Id_Produto, cliente->Tamanho_Tabela);

    NóHashProduto *novo_no = Criar_No_Produto(novo_produto);
    if (novo_no == NULL) return;
    
    novo_no->proximo = *(cliente->tabelaProdutos + indice); 
    *(cliente->tabelaProdutos + indice) = novo_no; 
    
    cliente->Total_Produtos++;
}

Produto* Pesquisar_Produto_Hash(Cliente *cliente, int id_produto) {
    if (cliente == NULL || cliente->tabelaProdutos == NULL) return NULL;

    int indice = Funcao_Hash(id_produto, cliente->Tamanho_Tabela);

    NóHashProduto *atual = *(cliente->tabelaProdutos + indice); 

    while (atual != NULL) {
        if (atual->dados.Id_Produto == id_produto) {
            return &(atual->dados);
        }
        atual = atual->proximo;
    }
    return NULL;
}

void Imprimir_Produtos_Cliente(Cliente *cliente) {
    if (cliente == NULL || cliente->tabelaProdutos == NULL) {
        return;
    }

    int encontrado = 0;
    for (int i = 0; i < cliente->Tamanho_Tabela; i++) {
        NóHashProduto *atual = *(cliente->tabelaProdutos + i);
        while (atual != NULL) {
            printf("ID: %d\tPreço: %.2f\tTipo: %s\n",
                   atual->dados.Id_Produto,
                   atual->dados.Preco_Produto,
                   atual->dados.Tipo);
            encontrado = 1;
            atual = atual->proximo;
        }
    }
    if (!encontrado) {
        printf("Nenhum produto encontrado.\n");
    }
}

void Libertar_Tabela_Hash(Cliente *cliente) {
    if (cliente == NULL || cliente->tabelaProdutos == NULL) return;

    for (int i = 0; i < cliente->Tamanho_Tabela; i++) {
        NóHashProduto *atual = *(cliente->tabelaProdutos + i); 
        
        while (atual != NULL) {
            NóHashProduto *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        *(cliente->tabelaProdutos + i) = NULL;
    }
    
    free(cliente->tabelaProdutos);
    cliente->tabelaProdutos = NULL;
}