#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions_main.h"
#include "arvore_clientes.h"
#include "hashtable.h"
#include "lista_empregados.h"


int Verificar_Sistema(){
    FILE *f1 = fopen("clientes.txt", "r");
    FILE *f2 = fopen("funcionarios.txt", "r");
    int existe = 0;
    if(f1 != NULL && f2 != NULL){
        char linha[200];
        int tem_dados1 = (fgets(linha, sizeof(linha), f1) != NULL);
        int tem_dados2 = (fgets(linha, sizeof(linha), f2) != NULL);
        if(tem_dados1 && tem_dados2){
            existe = 1;
        }
    }

    if (f1 != NULL) fclose(f1);
    if (f2 != NULL) fclose(f2);
    return existe;
}

Sistema Carregar_Sistema() {
    Sistema sis = Criar_Sistema();

    FILE *f = fopen("funcionarios.txt", "r");
    if (f != NULL) {
        char linha[200];
        while (fgets(linha, sizeof(linha), f) != NULL) {
            Empregado e;
            if (sscanf(linha, "%d\t%39[^\n]", &e.Id, e.Nome) == 2 || sscanf(linha, "%d,%39[^\n]", &e.Id, e.Nome) == 2) {
                Inserir_Empregado_Lista(&sis, e);
            }
        }
        fclose(f);
    }

    f = fopen("clientes.txt", "r");
    if (f != NULL) {
        char linha[200];
        while (fgets(linha, sizeof(linha), f) != NULL) {
            Cliente c;
            c.Idade = 0;
            if (sscanf(linha, "%d\t%39[^	\n]\t%d", &c.Id, c.Nome, &c.Idade) == 3 ||
                sscanf(linha, "%d\t%39[^\n]", &c.Id, c.Nome) == 2 ||
                sscanf(linha, "%d,%39[^\n]", &c.Id, c.Nome) == 2) {
                c.tabelaProdutos = Inicializar_Tabela_Hash(TAMANHO_TABELA_PRODUTOS);
                c.Tamanho_Tabela = TAMANHO_TABELA_PRODUTOS;
                c.Total_Produtos = 0;
                c.Tempo_Atendimento = 0;
                sis.Raiz_Clientes = Inserir_Cliente_Arvore(sis.Raiz_Clientes, c);
                sis.Num_Clientes++;
            }
        }
        fclose(f);
    }

    return sis;
}

void Guardar_Dados(Sistema sis) {
    FILE *f = fopen("funcionarios.txt", "w");
    if (f != NULL) {
        NóEmpregado *atual = sis.Sis_Empregados;
        while (atual != NULL) {
            fprintf(f, "%d\t%s\n", atual->dados.Id, atual->dados.Nome);
            atual = atual->proximo;
        }
        fclose(f);
    }

    f = fopen("clientes.txt", "w");
    if (f != NULL) {
        Salvar_Clientes_Arvore(f, sis.Raiz_Clientes);
        fclose(f);
    }
}

void Terminar_Sistema(Sistema sis) {
    Guardar_Dados(sis);
    Libertar_Arvore_Clientes(sis.Raiz_Clientes);
    Libertar_Lista_Empregados(sis.Sis_Empregados);
    free(sis.Sis_Caixas);
    printf("Sistema terminado.\n");
    exit(0);
}

Sistema Criar_Sistema() {
    Sistema sis;
    strcpy(sis.Nome_Programa, "Sistema de Atendimento");
    sis.Raiz_Clientes = NULL;
    sis.Num_Clientes = 0;
    sis.Sis_Empregados = NULL;
    sis.Num_Empregados = 0;
    sis.Sis_Caixas = NULL;
    sis.Num_Caixas = 0;
    return sis;
}
