#ifndef COMBATE_H
#define COMBATE_H

#include "inventario.h"

// Estrutura para representar um inimigo
typedef struct {
    char nome[50];
    int vida;
    int dano;
    int defesa;
} Inimigo;

// Estrutura para representar o jogador
typedef struct {
    int vida;
    int energia;
    int nivel;
    int experiencia;
} Jogador;

// Funções de combate
void iniciarCombate(Inventario *inv, Jogador *jogador);
void menuAcoes(Inventario *inv, Jogador *jogador);
void atacarInimigo(Inventario *inv, Jogador *jogador, Inimigo *inimigo);
void usarItem(Inventario *inv, Jogador *jogador);
void verificarLevel(Jogador *jogador);

// Funções de eventos
void eventoAleatorio(Inventario *inv, Jogador *jogador);
void encontrarRecursos(Inventario *inv);
void emboscada(Inventario *inv, Jogador *jogador);

#endif