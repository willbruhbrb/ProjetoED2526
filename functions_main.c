#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"

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
        while (fgets(linha, sizeof(linha), f)) {
            Empregado e;
            if (sscanf(linha, "%d,%39[^\n]", &e.Id, e.Nome) == 2) {
                sis.empregados = inserir_empregado(sis.empregados, e);
            }
        }
        fclose(f);
    }
    // Carregar clientes (simplificado, assumir formato id,nome,idade)
    f = fopen("clientes.txt", "r");
    if (f) {
        char linha[100];
        while (fgets(linha, sizeof(linha), f)) {
            Cliente c;
            c.produtos = NULL; // simplificado
            c.Total_Produtos = 0;
            c.Tempo_Atendimento = 0;
            if (sscanf(linha, "%d,%39[^,],%d", &c.Id, c.Nome, &c.Idade) == 3) {
                sis.raiz_clientes = inserir_cliente(sis.raiz_clientes, c);
            }
        }
        fclose(f);
    }
    // Nota: Carregar produtos e caixas pode ser adicionado posteriormente
    return sis;
}

// Guarda dados do sistema nos ficheiros
void Guardar_Dados(Sistema sis) {
    // Guardar empregados
    FILE *f = fopen("funcionarios.txt", "w");
    if (f) {
        ListaEmpregados *atual = sis.empregados;
        while (atual != NULL) {
            fprintf(f, "%d,%s\n", atual->empregado.Id, atual->empregado.Nome);
            atual = atual->proximo;
        }
        fclose(f);
    }
    // Guardar clientes (in-order traversal)
    f = fopen("clientes.txt", "w");
    if (f) {
        // Nota: Para guardar em ordem, implementar função auxiliar
        // Por simplicidade, não implementado completamente
        fclose(f);
    }
    // Nota: Guardar produtos e caixas pode ser adicionado
}

// Termina o sistema, guardando dados e libertando memória
void Terminar_Sistema(Sistema sis) {
    Guardar_Dados(sis);
    liberar_arvore(sis.raiz_clientes);
    liberar_lista_empregados(sis.empregados);
    // Liberar outras listas se necessário
    printf("Sistema terminado.\n");
    exit(0);
}