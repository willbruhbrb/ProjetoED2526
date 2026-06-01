#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "lista_empregados.h"
#include "nos.h"

void Inserir_Empregado_Lista(Sistema *sis, Empregado e) {
    NóEmpregado *no = Criar_No_Empregado(e);
    if (no == NULL) return;
    no->proximo = sis->Sis_Empregados;
    sis->Sis_Empregados = no;
    sis->Num_Empregados++;
}

void Libertar_Lista_Empregados(NóEmpregado *inicio) {
    NóEmpregado *atual = inicio;
    while (atual != NULL) {
        NóEmpregado *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

void Adicionar_Empregado(Sistema *sis) {
    Empregado e;
    printf("ID do empregado: ");
    if (scanf("%d", &e.Id) != 1) {
        printf("ID inválido.\n");
        while (getchar() != '\n' && !feof(stdin));
        return;
    }
    while (getchar() != '\n' && !feof(stdin));
    printf("Nome do empregado: ");
    if (fgets(e.Nome, sizeof(e.Nome), stdin) == NULL) {
        printf("Erro na leitura do nome.\n");
        return;
    }
    size_t len = strlen(e.Nome);
    if (len > 0 && e.Nome[len - 1] == '\n') {
        e.Nome[len - 1] = '\0';
    }
    Inserir_Empregado_Lista(sis, e);
    printf("Empregado adicionado.\n");
}

void Ver_Empregados(Sistema sis) {
    if (sis.Sis_Empregados == NULL) {
        printf("Não há empregados cadastrados.\n");
        return;
    }
    printf("\n=== Empregados ===\n");
    NóEmpregado *atual = sis.Sis_Empregados;
    while (atual != NULL) {
        printf("ID: %d\tNome: %s\n", atual->dados.Id, atual->dados.Nome);
        atual = atual->proximo;
    }
}
