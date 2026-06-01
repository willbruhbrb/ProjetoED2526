#ifndef ARVORE_CLIENTES_H
#define ARVORE_CLIENTES_H

#include "structs.h"

NóCliente* Inserir_Cliente_Arvore(NóCliente *raiz, Cliente novo_cliente);
NóCliente* Pesquisar_Cliente_Arvore(NóCliente *raiz, int id_cliente);
void Imprimir_Clientes_Ordem(NóCliente *raiz);
void Salvar_Clientes_Arvore(FILE *f, NóCliente *raiz);
void Libertar_Arvore_Clientes(NóCliente *raiz);
void Adicionar_Cliente(Sistema *sis);
void Ver_Clientes(Sistema sis);
void Pesquisar_Cliente(Sistema sis);
void Adicionar_Produto_Cliente(Sistema *sis);
void Ver_Produtos_Cliente(Sistema sis);

#endif