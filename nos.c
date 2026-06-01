#include <stdlib.h>
#include "nos.h"

NóEmpregado* Criar_No_Empregado(Empregado e) {
    NóEmpregado *no = malloc(sizeof(NóEmpregado));
    if (no != NULL) {
        no->dados = e;
        no->proximo = NULL;
    }
    return no;
}

NóCliente* Criar_No_Cliente(Cliente c) {
    NóCliente *no = malloc(sizeof(NóCliente));
    if (no != NULL) {
        no->dados = c;
        no->esquerda = NULL;
        no->direita = NULL;
    }
    return no;
}

NóHashProduto* Criar_No_Produto(Produto p) {
    NóHashProduto *no = malloc(sizeof(NóHashProduto));
    if (no != NULL) {
        no->dados = p;
        no->proximo = NULL;
    }
    return no;
}