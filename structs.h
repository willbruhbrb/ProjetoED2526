#ifndef MENUS_H
#define MENUS_H

#define MAX_ESPERA 120
#define N_CAIXAS 6
#define TEMPO_ATENDIMENTO_PRODUTO 6
#define MAX_PRECO 40
#define MAX_FILA 7
#define MIN_FILA 3
#define TEMPO_MIN_PASSAGEM 2
#define TEMPO_MAX_PASSAGEM 10
#define PRECO_MIN_PRODUTO 0.01f
#define PRECO_MAX_PRODUTO MAX_PRECO

#define TAMANHO_TABELA_PRODUTOS 64//tamanho inicial da hash table de produtos por cliente

typedef struct Produto {
    int Id_Produto;
    float Preco_Produto;
    char Tipo[20];
} Produto;

typedef struct NóHashProduto {
    Produto dados;
    struct NóHashProduto *proximo;//para encadeamento em caso de colisão
} NóHashProduto;

typedef struct Cliente {
    int Id;
    char Nome[40];
    int Idade;

    NóHashProduto **tabelaProdutos;//hash table de produtos (específicos deste cliente)
    int Tamanho_Tabela;
    int Total_Produtos;

    int Tempo_Atendimento;
} Cliente;

typedef struct NóCliente {
    Cliente dados;
    struct NóCliente *esquerda;
    struct NóCliente *direita;
} NóCliente;

typedef struct FilaCliente {
    Cliente *cliente;
    struct FilaCliente *proximo;
} FilaCliente;

typedef struct Empregado {
    int Id;
    char Nome[40];
} Empregado;

typedef struct NóEmpregado {
    Empregado dados;
    struct NóEmpregado *proximo;
} NóEmpregado;

typedef struct Caixa {
    int NumeroCaixa;
    FilaCliente *inicio;//início da fila de clientes na caixa
    FilaCliente *fim;//fim da fila
    int Tamanho_Fila;
    int Tempo_Total_Fila;
    Empregado *Empregado_Caixa;
    int Estado;//0=fechada, 1=aberta, 2=ocupada
} Caixa;

typedef struct Sistema {
    char Nome_Programa[40];

    NóCliente *Sis_clientes;//raiz da árvore binária de clientes
    int Num_Clientes;

    NóEmpregado *Sis_Empregados;//início da lista ligada de empregados
    int Num_Empregados;

    Caixa *Sis_Caixas;//array dinâmico de caixas
    int Num_Caixas;
} Sistema;

#endif