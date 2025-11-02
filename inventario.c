#include <stdio.h>
#include <string.h>
#include "inventario.h"

void inicializarInventario(Inventario *inv) {
    inv->quantidade = 0;
}

int adicionarItem(Inventario *inv, char nome[], TipoItem tipo, int prioridade, int quantidade) {
    if (inv->quantidade >= MAX_ITENS) {
        return 0; // Inventário cheio
    }
    
    strcpy(inv->itens[inv->quantidade].nome, nome);
    inv->itens[inv->quantidade].tipo = tipo;
    inv->itens[inv->quantidade].prioridade = prioridade;
    inv->itens[inv->quantidade].quantidade = quantidade;
    inv->quantidade++;
    
    return 1;
}

int removerItem(Inventario *inv, int indice) {
    if (indice < 0 || indice >= inv->quantidade) {
        return 0; // Índice inválido
    }
    
    // Desloca os itens para preencher o espaço
    for (int i = indice; i < inv->quantidade - 1; i++) {
        inv->itens[i] = inv->itens[i + 1];
    }
    inv->quantidade--;
    
    return 1;
}

void listarItens(Inventario *inv) {
    printf("\nInventario (%d/%d itens):\n", inv->quantidade, MAX_ITENS);
    printf("ID | Nome | Tipo | Prioridade | Quantidade\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < inv->quantidade; i++) {
        const char *tipo;
        switch(inv->itens[i].tipo) {
            case ALIMENTO: tipo = "Alimento"; break;
            case ARMA: tipo = "Arma"; break;
            case FERRAMENTA: tipo = "Ferramenta"; break;
            default: tipo = "Desconhecido";
        }
        
        printf("%2d | %-20s | %-10s | %10d | %9d\n",
               i,
               inv->itens[i].nome,
               tipo,
               inv->itens[i].prioridade,
               inv->itens[i].quantidade);
    }
}

void menuInventario(Inventario *inv) {
    int opcao;
    do {
        printf("\nMenu do Inventario:\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: {
                char nome[MAX_NOME];
                int tipo, prioridade, quantidade;
                
                printf("Nome do item: ");
                scanf(" %[^\n]", nome);
                
                printf("Tipo (0-Alimento, 1-Arma, 2-Ferramenta): ");
                scanf("%d", &tipo);
                
                printf("Prioridade (1-5): ");
                scanf("%d", &prioridade);
                
                printf("Quantidade: ");
                scanf("%d", &quantidade);
                
                if (adicionarItem(inv, nome, (TipoItem)tipo, prioridade, quantidade)) {
                    printf("Item adicionado com sucesso!\n");
                } else {
                    printf("Erro ao adicionar item. Inventario cheio!\n");
                }
                break;
            }
            case 2: {
                int indice;
                printf("Digite o ID do item a remover: ");
                scanf("%d", &indice);
                
                if (removerItem(inv, indice)) {
                    printf("Item removido com sucesso!\n");
                } else {
                    printf("Erro ao remover item. ID invalido!\n");
                }
                break;
            }
            case 3:
                listarItens(inv);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}