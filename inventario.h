#ifndef INVENTARIO_H
#define INVENTARIO_H

#define MAX_ITENS 100
#define MAX_NOME 50

// Enumeração para tipos de itens
typedef enum {
    ALIMENTO,
    ARMA,
    FERRAMENTA
} TipoItem;

// Estrutura para representar um item
typedef struct {
    char nome[MAX_NOME];
    TipoItem tipo;
    int prioridade;
    int quantidade;
} Item;

// Estrutura para o inventário (lista estática)
typedef struct {
    Item itens[MAX_ITENS];
    int quantidade;
} Inventario;

// Funções do inventário
void inicializarInventario(Inventario *inv);
int adicionarItem(Inventario *inv, char nome[], TipoItem tipo, int prioridade, int quantidade);
int removerItem(Inventario *inv, int indice);
void listarItens(Inventario *inv);
void menuInventario(Inventario *inv);

#endif