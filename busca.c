#include <stdio.h>
#include <string.h>
#include "busca.h"

int buscaSequencial(Inventario *inv, char nome[]) {
    for (int i = 0; i < inv->quantidade; i++) {
        if (strcmp(inv->itens[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

int buscaBinariaIterativa(Inventario *inv, char nome[]) {
    int inicio = 0;
    int fim = inv->quantidade - 1;
    
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int comparacao = strcmp(inv->itens[meio].nome, nome);
        
        if (comparacao == 0) {
            return meio;
        } else if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    return -1;
}

int buscaBinariaRecursiva(Inventario *inv, char nome[], int inicio, int fim) {
    if (inicio > fim) {
        return -1;
    }
    
    int meio = (inicio + fim) / 2;
    int comparacao = strcmp(inv->itens[meio].nome, nome);
    
    if (comparacao == 0) {
        return meio;
    } else if (comparacao < 0) {
        return buscaBinariaRecursiva(inv, nome, meio + 1, fim);
    } else {
        return buscaBinariaRecursiva(inv, nome, inicio, meio - 1);
    }
}

void menuBusca(Inventario *inv) {
    int opcao;
    do {
        printf("\nMenu de Busca:\n");
        printf("1. Busca Sequencial\n");
        printf("2. Busca Binaria Iterativa\n");
        printf("3. Busca Binaria Recursiva\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        if (opcao >= 1 && opcao <= 3) {
            char nome[MAX_NOME];
            printf("Digite o nome do item a buscar: ");
            scanf(" %[^\n]", nome);
            
            int resultado;
            switch(opcao) {
                case 1:
                    resultado = buscaSequencial(inv, nome);
                    break;
                case 2:
                    resultado = buscaBinariaIterativa(inv, nome);
                    break;
                case 3:
                    resultado = buscaBinariaRecursiva(inv, nome, 0, inv->quantidade - 1);
                    break;
            }
            
            if (resultado != -1) {
                printf("Item encontrado na posicao %d:\n", resultado);
                printf("Nome: %s\n", inv->itens[resultado].nome);
                printf("Tipo: %d\n", inv->itens[resultado].tipo);
                printf("Prioridade: %d\n", inv->itens[resultado].prioridade);
                printf("Quantidade: %d\n", inv->itens[resultado].quantidade);
            } else {
                printf("Item nao encontrado.\n");
            }
        }
    } while(opcao != 0);
}