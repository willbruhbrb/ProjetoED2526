#ifndef FUNCTIONS_MAIN_H
#define FUNCTIONS_MAIN_H

#include "structs.h"

int Verificar_Sistema();
Sistema Carregar_Sistema();
Sistema Criar_Sistema();
void Adicionar_Empregado(Sistema *sis);
void Ver_Clientes(Sistema sis);
void Ver_Empregados(Sistema sis);
void Terminar_Sistema(Sistema sis);
void Guardar_Dados(Sistema sis);

#endif