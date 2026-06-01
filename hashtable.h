#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "structs.h"

NóHashProduto** Inicializar_Tabela_Hash(int tamanho);
int Funcao_Hash(int id_produto, int tamanho);
void Inserir_Produto_Hash(Cliente *cliente, Produto novo_produto);
Produto* Pesquisar_Produto_Hash(Cliente *cliente, int id_produto);
void Imprimir_Produtos_Cliente(Cliente *cliente);
void Libertar_Tabela_Hash(Cliente *cliente);

#endif