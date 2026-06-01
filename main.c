#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions_main.h"
#include "arvore_clientes.h"
#include "lista_empregados.h"

int main(){

    Sistema sis;
    int opcao;

    opcao = Verificar_Sistema();
    if(opcao == 1){ 
        sis = Carregar_Sistema();
    }
    else{
        sis = Criar_Sistema();
    }

    int escolha;
    do {
        printf("\n--- Sistema de Atendimento ---\n");
        printf("1. Adicionar Empregado\n");
        printf("2. Adicionar Cliente\n");
        printf("3. Ver Clientes\n");
        printf("4. Ver Empregados\n");
        printf("5. Pesquisar Cliente\n");
        printf("6. Adicionar Produto a Cliente\n");
        printf("7. Ver Produtos de Cliente\n");
        printf("8. Terminar Programa\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        while (getchar() != '\n' && !feof(stdin));

        switch(escolha) {
            case 1:
                Adicionar_Empregado(&sis);
                break;
            case 2:
                Adicionar_Cliente(&sis);
                break;
            case 3:
                Ver_Clientes(sis);
                break;
            case 4:
                Ver_Empregados(sis);
                break;
            case 5:
                Pesquisar_Cliente(sis);
                break;
            case 6:
                Adicionar_Produto_Cliente(&sis);
                break;
            case 7:
                Ver_Produtos_Cliente(sis);
                break;
            case 8:
                Terminar_Sistema(sis);
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while(escolha != 4);

    return 0;
}