#ifndef BUSCA_H
#define BUSCA_H

#include "inventario.h"

// Função de busca sequencial
int buscaSequencial(Inventario *inv, char nome[]);

// Função de busca binária iterativa
int buscaBinariaIterativa(Inventario *inv, char nome[]);

// Função de busca binária recursiva
int buscaBinariaRecursiva(Inventario *inv, char nome[], int inicio, int fim);

// Menu de busca
void menuBusca(Inventario *inv);

#endif