#include <stdio.h>
#include <string.h>
#include "ordenacao.h"

void selectionSort(Inventario *inv) {
    printf("Iniciando Selection Sort...\n");
    int comparacoes = 0, trocas = 0;
    
    for (int i = 0; i < inv->quantidade - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < inv->quantidade; j++) {
            comparacoes++;
            if (strcmp(inv->itens[j].nome, inv->itens[min_idx].nome) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Item temp = inv->itens[i];
            inv->itens[i] = inv->itens[min_idx];
            inv->itens[min_idx] = temp;
            trocas++;
        }
    }
    
    printf("Selection Sort concluido!\n");
    printf("Numero de comparacoes: %d\n", comparacoes);
    printf("Numero de trocas: %d\n", trocas);
}

void bubbleSort(Inventario *inv) {
    printf("Iniciando Bubble Sort...\n");
    int comparacoes = 0, trocas = 0;
    
    for (int i = 0; i < inv->quantidade - 1; i++) {
        for (int j = 0; j < inv->quantidade - i - 1; j++) {
            comparacoes++;
            if (strcmp(inv->itens[j].nome, inv->itens[j + 1].nome) > 0) {
                Item temp = inv->itens[j];
                inv->itens[j] = inv->itens[j + 1];
                inv->itens[j + 1] = temp;
                trocas++;
            }
        }
    }
    
    printf("Bubble Sort concluido!\n");
    printf("Numero de comparacoes: %d\n", comparacoes);
    printf("Numero de trocas: %d\n", trocas);
}

int particionar(Inventario *inv, int inicio, int fim) {
    Item pivo = inv->itens[fim];
    int i = (inicio - 1);
    
    for (int j = inicio; j <= fim - 1; j++) {
        if (strcmp(inv->itens[j].nome, pivo.nome) < 0) {
            i++;
            Item temp = inv->itens[i];
            inv->itens[i] = inv->itens[j];
            inv->itens[j] = temp;
        }
    }
    Item temp = inv->itens[i + 1];
    inv->itens[i + 1] = inv->itens[fim];
    inv->itens[fim] = temp;
    return (i + 1);
}

void quickSort(Inventario *inv, int inicio, int fim) {
    if (inicio < fim) {
        int pi = particionar(inv, inicio, fim);
        quickSort(inv, inicio, pi - 1);
        quickSort(inv, pi + 1, fim);
    }
}

void menuOrdenacao(Inventario *inv) {
    int opcao;
    do {
        printf("\nMenu de Ordenacao:\n");
        printf("1. Ordenar por Nome (Selection Sort)\n");
        printf("2. Ordenar por Nome (Bubble Sort)\n");
        printf("3. Ordenar por Nome (Quick Sort)\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                selectionSort(inv);
                printf("\nInventario ordenado com Selection Sort:\n");
                listarItens(inv);
                break;
            case 2:
                bubbleSort(inv);
                printf("\nInventario ordenado com Bubble Sort:\n");
                listarItens(inv);
                break;
            case 3:
                printf("Iniciando Quick Sort...\n");
                quickSort(inv, 0, inv->quantidade - 1);
                printf("Quick Sort concluido!\n");
                printf("\nInventario ordenado com Quick Sort:\n");
                listarItens(inv);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

int verificarRecursos(Inventario *inv) {
    int ferramentas = 0;
    int recursos = 0;
    
    for (int i = 0; i < inv->quantidade; i++) {
        if (inv->itens[i].tipo == FERRAMENTA && inv->itens[i].quantidade >= 1) {
            ferramentas++;
        }
    }
    
    return (ferramentas >= 2); // Necessário pelo menos 2 ferramentas
}

void construirTorreFuga(Inventario *inv) {
    printf("\n=== Construcao da Torre de Fuga ===\n");
    printf("Verificando recursos necessarios...\n");
    
    if (!verificarRecursos(inv)) {
        printf("Recursos insuficientes!\n");
        printf("Voce precisa de:\n");
        printf("- Pelo menos 2 ferramentas diferentes\n");
        return;
    }
    
    printf("\nIniciando construcao...\n");
    printf("Fase 1: Preparando o terreno...\n");
    printf("Fase 2: Construindo a base...\n");
    printf("Fase 3: Montando a estrutura...\n");
    printf("Fase 4: Finalizando a torre...\n");
    printf("\nTorre de fuga construida com sucesso!\n");
    printf("Voce pode escapar da ilha agora!\n");
    
    // Consumir recursos utilizados
    for (int i = 0; i < inv->quantidade; i++) {
        if (inv->itens[i].tipo == FERRAMENTA) {
            inv->itens[i].quantidade--;
            if (inv->itens[i].quantidade <= 0) {
                removerItem(inv, i);
                i--; // Ajusta o índice após a remoção
            }
        }
    }
}