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

#define CAPACIDADE_INICIAL_CLIENTE 32
#define CAPACIDADE_INICIAL_EMPREGADOS 16
#define CAPACIDADE_INICIAL_PRODUTOS 128

typedef struct Produto {
    int Id_Produto;
    float Preco_Produto;
    char Tipo[20];
} Produto;

typedef struct Cliente {
    int Id;
    char Nome[40];
    int Idade;

    Produto *Produtos;//lista dinâmica de produtos desse cliente
    int Total_Produtos;
    int Capacidade_Produtos;

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
    FilaCliente *inicio;//início da fila de clientes na caixa
    FilaCliente *fim;//fim da fila
    int Tamanho_Fila;
    int Tempo_Total_Fila;
    Empregado *Empregado_Caixa;
    int Estado;//0=fechada, 1=aberta, 2=ocupada
} Caixa;

typedef struct Sistema {
    char Nome_Programa[40];

    Cliente *Sis_clientes;//array dinâmico de clientes
    int Num_Clientes;
    int Capacidade_Clientes;

    Empregado *Sis_Empregados;//array dinâmico de empregados
    int Num_Empregados;
    int Capacidade_Empregados;

    Produto *Sis_Produtos;//array dinâmico de produtos
    int N_Produtos;
    int Capacidade_Produtos;

    Caixa *Sis_Caixas;//array de caixas (pode ser pequeno e fixo)
    int Num_Caixas;
} Sistema;

#endif