#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "inventario.h"

// Funções de ordenação
void selectionSort(Inventario *inv);
void bubbleSort(Inventario *inv);
void quickSort(Inventario *inv, int inicio, int fim);

// Menu de ordenação
void menuOrdenacao(Inventario *inv);

// Funções para torre de fuga
void construirTorreFuga(Inventario *inv);
int verificarRecursos(Inventario *inv);

#endif