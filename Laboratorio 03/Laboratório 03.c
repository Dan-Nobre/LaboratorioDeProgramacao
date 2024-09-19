#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_INVESTIMENTOS 100


// Primeira Questão: Implementar um modelo de dados que possa representar informações financeiras (data, valor, tipo e nome).

// Definição dos tipos de investimento possíveis
typedef enum {
    Tesouro_Direto,
    Acoes,
    Fundo_Imobiliario,
    Renda_Fixa
} TipoInvestimento;

// Estrutura para representar a data
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Estrutura para representar um investimento
typedef struct {
    int id; // Identificador único (substituindo o UUID do swift)
    Date data;
    double valor;
    TipoInvestimento tipo;
    char nome[50];
} Investimento;

// Segunda questão: agrupando um titular

typedef struct {
    int id;
    char nome[MAX_NAME_LENGTH];
    Investimento investimentos[MAX_INVESTIMENTOS];
    int numeroInvestimentos;
} Titular;


// Terceira Questão e quarta questao: Agora crie funcionalidades que permitam organizar o modelo e visualizar melhor os itens: Ordenar por data, Ordenar por tipo, Ordenar por valor. Adicione uma funcionalidade de agrupamento na ordenação: Agrupar por tipo e então: Ordenar por valor, Ordenar por data.


// Função de comparação para ordenar por tipo:
int compararPorTipo(const void *a, const void *b) {
    Investimento *investimentoA = (Investimento *)a;
    Investimento *investimentoB = (Investimento *)b;
    return investimentoA->tipo - investimentoB->tipo;
}

// Função de comparação para ordenar por valor:
int compararPorValor(const void *a, const void *b) {
    Investimento *investimentoA = (Investimento *)a;
    Investimento *investimentoB = (Investimento *)b;

    if (investimentoA->valor < investimentoB->valor) return -1;
    if (investimentoA->valor > investimentoB->valor) return 1;
    return 0;
}

// Função de comparação para ordenar por data:
int compararPorData(const void *a, const void *b) {
    Investimento *investimentoA = (Investimento *)a;
    Investimento *investimentoB = (Investimento *)b;

    if (investimentoA->data.year != investimentoB->data.year)
        return investimentoA->data.year - investimentoB->data.year;
    if (investimentoA->data.month != investimentoB->data.month)
        return investimentoA->data.month - investimentoB->data.month;
    return investimentoA->data.day - investimentoB->data.day;
}

// Função para ordenar por tipo e dentro de cada tipo por valor:
void agruparPorTipoEOrdenarPorValor(Titular *titular) {
    // Ordenar por tipo
    qsort(titular->investimentos, titular->numeroInvestimentos, sizeof(Investimento), compararPorTipo);

    // Ordenar por valor dentro de cada tipo
    int inicioGrupo = 0;
    while (inicioGrupo < titular->numeroInvestimentos) {
        int fimGrupo = inicioGrupo;
        while (fimGrupo < titular->numeroInvestimentos && titular->investimentos[fimGrupo].tipo == titular->investimentos[inicioGrupo].tipo) {
            fimGrupo++;
        }
        qsort(&titular->investimentos[inicioGrupo], fimGrupo - inicioGrupo, sizeof(Investimento), compararPorValor);
        inicioGrupo = fimGrupo;
    }
}

// Ordenar por tipo e dentro de cada tipo por data:
void agruparPorTipoEOrdenarPorData(Titular *titular) {
    // Ordenar por tipo
    qsort(titular->investimentos, titular->numeroInvestimentos, sizeof(Investimento), compararPorTipo);

    // Ordenar por data dentro de cada tipo
    int inicioGrupo = 0;
    while (inicioGrupo < titular->numeroInvestimentos) {
        int fimGrupo = inicioGrupo;
        while (fimGrupo < titular->numeroInvestimentos && titular->investimentos[fimGrupo].tipo == titular->investimentos[inicioGrupo].tipo) {
            fimGrupo++;
        }
        qsort(&titular->investimentos[inicioGrupo], fimGrupo - inicioGrupo, sizeof(Investimento), compararPorData);
        inicioGrupo = fimGrupo;
    }
}

// Função para imprimir os detalhes de um titular e seus investimentos:
void printTitular(const Titular *titular) {
    printf("Titular: %s (ID: %d)\n", titular->nome, titular->id);
    printf("Investimentos:\n");
    for (int i = 0; i < titular->numeroInvestimentos; i++) {
        Investimento *inv = &titular->investimentos[i];
        printf("ID: %d | Data: %02d/%02d/%04d | Valor: R$ %.2f | Tipo: %d | Nome: %s\n",
               inv->id, inv->data.day, inv->data.month, inv->data.year, inv->valor, inv->tipo, inv->nome);
    }
}

int main() {
    Titular maria = {1, "Maria", {}, 0};

    // Adicionando investimentos:
    Date data1 = {25, 3, 2021};
    Date data2 = {15, 5, 2021};
    Date data3 = {10, 2, 2021};

    Investimento inv1 = {1, data1, 535.20, Tesouro_Direto, "Selic"};
    Investimento inv2 = {2, data2, 101.00, Renda_Fixa, "LCA Agro"};
    Investimento inv3 = {3, data3, 913.00, Acoes, "Ação XYZ"};

    maria.investimentos[maria.numeroInvestimentos++] = inv1;
    maria.investimentos[maria.numeroInvestimentos++] = inv2;
    maria.investimentos[maria.numeroInvestimentos++] = inv3;

    // Ordenando e imprimindo:
    printf("Investimentos agrupados por tipo e ordenados por valor:\n");
    agruparPorTipoEOrdenarPorValor(&maria);
    printTitular(&maria);

    printf("\nInvestimentos agrupados por tipo e ordenados por data:\n");
    agruparPorTipoEOrdenarPorData(&maria);
    printTitular(&maria);

    return 0;
}
