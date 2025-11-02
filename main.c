#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"
#include "busca.h"
#include "ordenacao.h"
#include "combate.h"

int main() {
    printf("=== Mini Game de Sobrevivencia - Free Fire ===\n\n");
    
    // Inicialização do inventário e jogador
    Inventario mochila;
    inicializarInventario(&mochila);
    
    Jogador jogador = {
        .vida = 100,
        .energia = 100,
        .nivel = 1,
        .experiencia = 0
    };
    
    printf("Bem-vindo a ilha! Voce precisa sobreviver e construir uma torre de fuga!\n");
    
    // Adicionar itens iniciais
    adicionarItem(&mochila, "Pistola Basica", ARMA, 3, 1);
    adicionarItem(&mochila, "Bandagens", ALIMENTO, 2, 3);
    adicionarItem(&mochila, "Martelo", FERRAMENTA, 4, 1);
    
    int opcao;
    int turnos = 0;
    
    do {
        printf("\n=== Status do Jogador ===\n");
        printf("Vida: %d | Energia: %d | Nivel: %d | EXP: %d/%d\n", 
               jogador.vida, jogador.energia, jogador.nivel, 
               jogador.experiencia, jogador.nivel * 100);
        
        printf("\nMenu Principal:\n");
        printf("1. Gerenciar Inventario\n");
        printf("2. Buscar Items\n");
        printf("3. Ordenar Inventario\n");
        printf("4. Explorar Area (Combate/Eventos)\n");
        printf("5. Usar Item\n");
        printf("6. Construir Torre de Fuga\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                menuInventario(&mochila);
                break;
            case 2:
                menuBusca(&mochila);
                break;
            case 3:
                menuOrdenacao(&mochila);
                break;
            case 4:
                if (jogador.energia >= 20) {
                    jogador.energia -= 20;
                    printf("\nVoce explora a area...\n");
                    eventoAleatorio(&mochila, &jogador);
                    turnos++;
                    
                    // A cada 3 turnos, recupera um pouco de energia
                    if (turnos % 3 == 0) {
                        jogador.energia += 30;
                        if (jogador.energia > 100) jogador.energia = 100;
                        printf("\nVoce descansou um pouco. +30 de Energia!\n");
                    }
                } else {
                    printf("\nVoce esta muito cansado para explorar! Precisa de energia!\n");
                }
                break;
            case 5:
                usarItem(&mochila, &jogador);
                break;
            case 6:
                construirTorreFuga(&mochila);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
        
        // Verifica se o jogador morreu
        if (jogador.vida <= 0) {
            printf("\n=== GAME OVER ===\n");
            printf("Voce nao sobreviveu aos perigos da ilha...\n");
            break;
        }
        
    } while(opcao != 0 && jogador.vida > 0);
    
    return 0;
}