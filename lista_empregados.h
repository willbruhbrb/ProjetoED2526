#ifndef LISTA_EMPREGADOS_H
#define LISTA_EMPREGADOS_H

#include "structs.h"

void Inserir_Empregado_Lista(Sistema *sis, Empregado e);
void Libertar_Lista_Empregados(NóEmpregado *inicio);
void Adicionar_Empregado(Sistema *sis);
void Ver_Empregados(Sistema sis);

#endif