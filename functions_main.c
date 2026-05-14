#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions_main.h"

//vamos fazer arvore binária para clientes para acesso eficiente
//empregados utilizam listas ligadas
//filas das caixas são listas ligadas

int Verificar_Sistema(){
    //função para verficiar se já existe um sistema salvo
    FILE *f1 = fopen("clientes.txt", "r");
    //abre "clientes.txt"
    FILE *f2 = fopen("funcionarios.txt", "r");
    //abre "funcionarios.txt"
    int existe = 0;
    if(f1 != NULL && f2 != NULL){
        // Verificar se há pelo menos uma linha em cada arquivo
        char linha[200];
        int tem_dados1 = (fgets(linha, sizeof(linha), f1) != NULL);
        int tem_dados2 = (fgets(linha, sizeof(linha), f2) != NULL);
        if(tem_dados1 && tem_dados2){
            existe = 1;
        }
        fclose(f1);
        fclose(f2);
    }
    else{
        if(f1) fclose(f1);
        if(f2) fclose(f2);
    }
    return existe;
}

// Carrega dados do sistema dos ficheiros
// Carrega empregados e clientes; produtos e caixas podem ser adicionados
Sistema Carregar_Sistema() {
    Sistema sis = Criar_Sistema();
    // Carregar empregados
    FILE *f = fopen("funcionarios.txt", "r");
    if (f) {
        char linha[100];
        while (fgets(linha, sizeof(linha), f) && sis.Num_Empregados < sis.Capacidade_Empregados) {
            Empregado e;
            if (sscanf(linha, "%d,%39[^\n]", &e.Id, e.Nome) == 2) {
                sis.Sis_Empregados[sis.Num_Empregados++] = e;
            }
        }
        fclose(f);
    }
    // Carregar clientes
    f = fopen("clientes.txt", "r");
    if (f) {
        char linha[100];
        while (fgets(linha, sizeof(linha), f) && sis.Num_Clientes < sis.Capacidade_Clientes) {
            Cliente c;
            c.Produtos = NULL;
            c.Total_Produtos = 0;
            c.Capacidade_Produtos = 0;
            c.Tempo_Atendimento = 0;
            if (sscanf(linha, "%d,%39[^,],%d", &c.Id, c.Nome, &c.Idade) == 3) {
                sis.Sis_clientes[sis.Num_Clientes++] = c;
            }
        }
        fclose(f);
    }
    return sis;
}

// Guarda dados do sistema nos ficheiros
void Guardar_Dados(Sistema sis) {
    // Guardar empregados
    FILE *f = fopen("funcionarios.txt", "w");
    if (f) {
        for (int i = 0; i < sis.Num_Empregados; i++) {
            fprintf(f, "%d,%s\n", sis.Sis_Empregados[i].Id, sis.Sis_Empregados[i].Nome);
        }
        fclose(f);
    }
    // Guardar clientes
    f = fopen("clientes.txt", "w");
    if (f) {
        for (int i = 0; i < sis.Num_Clientes; i++) {
            fprintf(f, "%d,%s,%d\n", sis.Sis_clientes[i].Id, sis.Sis_clientes[i].Nome, sis.Sis_clientes[i].Idade);
        }
        fclose(f);
    }
}

// Termina o sistema, guardando dados e libertando memória
void Terminar_Sistema(Sistema sis) {
    Guardar_Dados(sis);
    free(sis.Sis_clientes);
    free(sis.Sis_Empregados);
    free(sis.Sis_Produtos);
    free(sis.Sis_Caixas);
    printf("Sistema terminado.\n");
    exit(0);
}

// Cria um novo sistema vazio
Sistema Criar_Sistema() {
    Sistema sis;
    strcpy(sis.Nome_Programa, "Sistema de Atendimento");
    
    //criar clientes
    sis.Sis_clientes = malloc(CAPACIDADE_INICIAL_CLIENTE * sizeof(Cliente));
    sis.Num_Clientes = 0;
    sis.Capacidade_Clientes = CAPACIDADE_INICIAL_CLIENTE;
    
    //criar empregados
    sis.Sis_Empregados = malloc(CAPACIDADE_INICIAL_EMPREGADOS * sizeof(Empregado));
    sis.Num_Empregados = 0;
    sis.Capacidade_Empregados = CAPACIDADE_INICIAL_EMPREGADOS;
    

    //criar produtos
    sis.Sis_Produtos = malloc(CAPACIDADE_INICIAL_PRODUTOS * sizeof(Produto));
    sis.N_Produtos = 0;
    sis.Capacidade_Produtos = CAPACIDADE_INICIAL_PRODUTOS;
    
    //criar caixas
    sis.Sis_Caixas = malloc(N_CAIXAS * sizeof(Caixa));
    sis.Num_Caixas = 0;
    
    return sis;
}

void Ver_Clientes(Sistema sis) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpar buffer
    
}

void Adicionar_Empregado(Sistema *sis) {
    //por fazer
}

void Ver_Empregados(Sistema sis) {
    //por fazer
}