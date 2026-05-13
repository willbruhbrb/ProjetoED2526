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

#define INITIAL_CLIENTES_CAPACITY 32
#define INITIAL_EMPREGADOS_CAPACITY 16
#define INITIAL_PRODUTOS_CAPACITY 128

typedef struct Produto {
    int Id_Produto;
    float Preco_Produto;
    char Tipo[20];
} Produto;

typedef struct Cliente {
    int Id;
    char Nome[40];
    int Idade;

    Produto *Produtos;// lista dinâmica de produtos desse cliente
    int Total_Produtos;// número de produtos atuais do cliente
    int Capacidade_Produtos;// capacidade alocada para produtos do cliente

    int Tempo_Atendimento;
} Cliente;

typedef struct FilaCliente {
    Cliente *cliente;
    struct FilaCliente *proximo;
} FilaCliente;

typedef struct Empregado {
    int Id;
    char Nome[40];
} Empregado;

typedef struct Caixa {
    int NumeroCaixa;
    FilaCliente *inicio;// início da fila de clientes na caixa
    FilaCliente *fim;// fim da fila para inserções rápidas
    int Tamanho_Fila;
    int Tempo_Total_Fila;
    Empregado *Empregado_Caixa;// empregado atualmente atribuído à caixa
    int Estado;// 0=fechada, 1=aberta, 2=ocupada
} Caixa;

typedef struct Sistema {
    char Nome_Programa[40];

    Cliente *Sis_clientes;// array dinâmico de clientes
    int Num_Clientes;// número atual de clientes
    int Capacidade_Clientes;// capacidade alocada para o array de clientes

    Empregado *Sis_Empregados;// array dinâmico de empregados
    int Num_Empregados;// número atual de empregados
    int Capacidade_Empregados;// capacidade alocada para o array de empregados

    Produto *Sis_Produtos;// array dinâmico de produtos
    int N_Produtos;// número atual de produtos
    int Capacidade_Produtos;// capacidade alocada para o array de produtos

    Caixa *Sis_Caixas;// array de caixas (pode ser pequeno e fixo)
    int Num_Caixas;// número de caixas em uso
} Sistema;

#endif