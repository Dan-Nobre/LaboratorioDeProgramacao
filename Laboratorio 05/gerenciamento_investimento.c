#include <stdio.h>
#include <string.h>
#include "gerenciamento_investimento.h"

// Função para adicionar um investimento
void adicionarInvestimento(Titular *titular, Investimento investimento) {
    if (titular->numeroInvestimentos < MAX_INVESTIMENTOS) {
        titular->investimentos[titular->numeroInvestimentos++] = investimento;
    } else {
        printf("Limite de investimentos atingido!\n");
    }
}

// Função para excluir um investimento por ID
void excluirInvestimento(Titular *titular, int id) {
    for (int i = 0; i < titular->numeroInvestimentos; i++) {
        if (titular->investimentos[i].id == id) {
            for (int j = i; j < titular->numeroInvestimentos - 1; j++) {
                titular->investimentos[j] = titular->investimentos[j + 1];
            }
            titular->numeroInvestimentos--;
            break;
        }
    }
}

// Função para ordenar por tipo e valor
void agruparPorTipoEOrdenarPorValor(Titular *titular) {
    // Lógica de ordenação aqui
}

// Função para imprimir detalhes do titular
void printTitular(const Titular *titular) {
    printf("Titular: %s\n", titular->nome);
    for (int i = 0; i < titular->numeroInvestimentos; i++) {
        Investimento *inv = &titular->investimentos[i];
        printf("ID: %d | Valor Aplicado: %.2f | Valor Bruto: %.2f\n",
               inv->id, inv->valorAplicado, inv->valorBruto);
    }
}