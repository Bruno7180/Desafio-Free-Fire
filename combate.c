#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "combate.h"

// Lista de inimigos possíveis
Inimigo inimigos[] = {
    {"Soldado Inimigo", 100, 15, 5},
    {"Atirador de Elite", 80, 25, 3},
    {"Lutador Corpo a Corpo", 120, 20, 8},
    {"Boss da Zona", 200, 30, 15}
};

void iniciarCombate(Inventario *inv, Jogador *jogador) {
    srand(time(NULL));
    int tipoInimigo = rand() % 4;
    Inimigo inimigo = inimigos[tipoInimigo];
    
    printf("\n=== COMBATE INICIADO! ===\n");
    printf("Um %s apareceu!\n", inimigo.nome);
    
    while (inimigo.vida > 0 && jogador->vida > 0) {
        printf("\nStatus do Combate:\n");
        printf("Sua Vida: %d | Sua Energia: %d\n", jogador->vida, jogador->energia);
        printf("Vida do %s: %d\n", inimigo.nome, inimigo.vida);
        
        printf("\n1. Atacar\n");
        printf("2. Usar Item\n");
        printf("3. Tentar Fugir\n");
        
        int escolha;
        scanf("%d", &escolha);
        
        switch(escolha) {
            case 1:
                atacarInimigo(inv, jogador, &inimigo);
                break;
            case 2:
                usarItem(inv, jogador);
                break;
            case 3:
                if (rand() % 100 < 40) { // 40% de chance de fugir
                    printf("Voce conseguiu fugir!\n");
                    return;
                } else {
                    printf("Fuga falhou!\n");
                }
                break;
            default:
                printf("Opcao invalida!\n");
                continue;
        }
        
        // Ataque do inimigo
        if (inimigo.vida > 0) {
            int danoRecebido = inimigo.dano;
            jogador->vida -= danoRecebido;
            printf("%s te atacou! Dano recebido: %d\n", inimigo.nome, danoRecebido);
        }
    }
    
    if (jogador->vida <= 0) {
        printf("\nVoce foi derrotado!\n");
    } else {
        printf("\nVitoria! Voce derrotou o %s!\n", inimigo.nome);
        jogador->experiencia += 50;
        verificarLevel(jogador);
        encontrarRecursos(inv);
    }
}

void atacarInimigo(Inventario *inv, Jogador *jogador, Inimigo *inimigo) {
    int temArma = 0;
    int danoBase = 10; // Dano sem arma
    
    // Procura por armas no inventário
    for (int i = 0; i < inv->quantidade; i++) {
        if (inv->itens[i].tipo == ARMA) {
            danoBase = 25; // Dano com arma
            temArma = 1;
            break;
        }
    }
    
    int danoTotal = danoBase + (jogador->nivel * 2);
    inimigo->vida -= (danoTotal - inimigo->defesa);
    
    printf("Voce atacou! Dano causado: %d\n", danoTotal - inimigo->defesa);
    if (temArma) {
        printf("(Bonus de dano por ter uma arma!)\n");
    }
}

void usarItem(Inventario *inv, Jogador *jogador) {
    printf("\nItens disponiveis:\n");
    listarItens(inv);
    
    printf("Digite o ID do item para usar (ou -1 para cancelar): ");
    int id;
    scanf("%d", &id);
    
    if (id >= 0 && id < inv->quantidade) {
        if (inv->itens[id].tipo == ALIMENTO) {
            jogador->vida += 30;
            jogador->energia += 20;
            printf("Item usado! +30 Vida, +20 Energia\n");
            removerItem(inv, id);
        } else {
            printf("Este item nao pode ser usado durante o combate!\n");
        }
    }
}

void verificarLevel(Jogador *jogador) {
    int expNecessaria = jogador->nivel * 100;
    
    if (jogador->experiencia >= expNecessaria) {
        jogador->nivel++;
        jogador->experiencia -= expNecessaria;
        printf("\nPARABENS! Voce subiu para o nivel %d!\n", jogador->nivel);
        jogador->vida += 20;
        printf("+20 de Vida Maxima!\n");
    }
}

void eventoAleatorio(Inventario *inv, Jogador *jogador) {
    srand(time(NULL));
    int evento = rand() % 3;
    
    switch(evento) {
        case 0:
            printf("\nVoce encontrou uma area com recursos!\n");
            encontrarRecursos(inv);
            break;
        case 1:
            printf("\nCUIDADO! Emboscada!\n");
            emboscada(inv, jogador);
            break;
        case 2:
            printf("\nVoce encontrou um abrigo seguro!\n");
            jogador->vida += 30;
            jogador->energia += 30;
            printf("Recuperou +30 de Vida e Energia!\n");
            break;
    }
}

void encontrarRecursos(Inventario *inv) {
    srand(time(NULL));
    char *nomes[] = {"Medkit", "Bandagens", "Granada", "Pistola", "Machado", "Martelo"};
    TipoItem tipos[] = {ALIMENTO, ALIMENTO, ARMA, ARMA, FERRAMENTA, FERRAMENTA};
    
    int quantidade = rand() % 3 + 1; // 1 a 3 itens
    
    printf("\nItens encontrados:\n");
    for (int i = 0; i < quantidade; i++) {
        int item = rand() % 6;
        if (adicionarItem(inv, nomes[item], tipos[item], rand() % 5 + 1, 1)) {
            printf("- %s\n", nomes[item]);
        }
    }
}

void emboscada(Inventario *inv, Jogador *jogador) {
    printf("\n=== EMBOSCADA! ===\n");
    printf("Varios inimigos aparecem!\n");
    jogador->vida -= 20;
    printf("Voce sofreu 20 de dano!\n");
    
    iniciarCombate(inv, jogador);
}