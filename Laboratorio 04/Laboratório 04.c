#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // Para função pow()

#define MAX_NAME_LENGTH 50
#define MAX_INVESTIMENTOS 100

// Definição dos tipos de investimento possíveis (Prefixado, IPCA+, Selic, CDI)
typedef enum {
    Prefixado,
    IPCA_Mais,
    Selic,
    CDI
} TipoInvestimento;

// Estrutura para representar a data
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Variável global para a data atual
Date dataAtual = {18, 9, 2024}; // Exemplo de data atual: 18 de setembro de 2024

// Estrutura para representar um investimento
typedef struct {
    int id; // Identificador único (substituindo o UUID do swift)
    Date dataAplicacao; // data de aplicação
    Date dataVencimento; // data de vencimento
    double valorBruto; // valor total bruto
    double valorAplicado; // valor efetivamente aplicado
    double imposto; // imposto aplicado
    double taxaJuros; // taxa de juros (anual)
    TipoInvestimento tipo;
    char nome[MAX_NAME_LENGTH];
} Investimento;

// Estrutura de titular
typedef struct {
    int id;
    char nome[MAX_NAME_LENGTH];
    Investimento investimentos[MAX_INVESTIMENTOS];
    int numeroInvestimentos;
} Titular;

// Função para calcular a diferença em dias entre duas datas
int calcularDiferencaDias(Date data1, Date data2) {
    int diasAno1 = data1.year * 365 + data1.day;
    int diasAno2 = data2.year * 365 + data2.day;

    // Considera os dias do mês
    int diasMes1 = (data1.month - 1) * 30;
    int diasMes2 = (data2.month - 1) * 30;

    return (diasAno2 + diasMes2) - (diasAno1 + diasMes1);
}

// Função para atualizar o valorBruto de um investimento com base no cálculo de juros compostos
void atualizarInvestimento(Investimento *inv) {
    // Calcula a diferença de dias entre a data de aplicação e a data atual
    int dias = calcularDiferencaDias(inv->dataAplicacao, dataAtual);

    // Converte a taxa de juros anual para a taxa de juros diária
    double taxaDiaria = inv->taxaJuros / 100.0 / 365.0;

    // Calcula o valor bruto com juros compostos diários
    inv->valorBruto = inv->valorAplicado * pow(1 + taxaDiaria, dias);
}

// Função para calcular o valor bruto total de todos os investimentos
double calcularValorBrutoTotal(Titular *titular) {
    double valorBrutoTotal = 0.0;
    for (int i = 0; i < titular->numeroInvestimentos; i++) {
        atualizarInvestimento(&titular->investimentos[i]);
        valorBrutoTotal += titular->investimentos[i].valorBruto;
    }
    return valorBrutoTotal;
}

// Função para calcular o valor líquido total de todos os investimentos (valor bruto - imposto)
double calcularValorLiquidoTotal(Titular *titular) {
    double valorLiquidoTotal = 0.0;
    for (int i = 0; i < titular->numeroInvestimentos; i++) {
        atualizarInvestimento(&titular->investimentos[i]);
        valorLiquidoTotal += titular->investimentos[i].valorBruto - titular->investimentos[i].imposto;
    }
    return valorLiquidoTotal;
}

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

    if (investimentoA->valorBruto < investimentoB->valorBruto) return -1;
    if (investimentoA->valorBruto > investimentoB->valorBruto) return 1;
    return 0;
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

// Função para imprimir os detalhes de um titular e seus investimentos:
void printTitular(const Titular *titular) {
    printf("Titular: %s (ID: %d)\n", titular->nome, titular->id);
    printf("Investimentos:\n");
    for (int i = 0; i < titular->numeroInvestimentos; i++) {
        Investimento *inv = &titular->investimentos[i];

        // Atualiza o investimento antes de imprimir
        atualizarInvestimento(inv);

        printf("ID: %d | Data Aplicação: %02d/%02d/%04d | Data Vencimento: %02d/%02d/%04d | Valor Bruto: R$ %.2f | Valor Aplicado: R$ %.2f | Imposto: R$ %.2f | Taxa de Juros: %.2f%% | Tipo: %d | Nome: %s\n",
               inv->id, inv->dataAplicacao.day, inv->dataAplicacao.month, inv->dataAplicacao.year, inv->dataVencimento.day, inv->dataVencimento.month, inv->dataVencimento.year, inv->valorBruto, inv->valorAplicado, inv->imposto, inv->taxaJuros, inv->tipo, inv->nome);
    }
}

int main() {
    Titular maria = {1, "Maria", {}, 0};

    // Adicionando investimentos:
    Date dataAplicacao1 = {25, 3, 2021};
    Date dataVencimento1 = {25, 3, 2026};

    Investimento inv1 = {1, dataAplicacao1, dataVencimento1, 0, 515.00, 15.75, 11.5, Selic, "Selic"};
    Investimento inv2 = {2, dataAplicacao1, dataVencimento1, 0, 100.00, 1.00, 9.0, CDI, "LCA Agro"};

    maria.investimentos[maria.numeroInvestimentos++] = inv1;
    maria.investimentos[maria.numeroInvestimentos++] = inv2;

    // Ordenando e imprimindo:
    printf("Investimentos agrupados por tipo e ordenados por valor:\n");
    agruparPorTipoEOrdenarPorValor(&maria);
    printTitular(&maria);

    // Calculando e imprimindo o valor bruto total
    double valorBrutoTotal = calcularValorBrutoTotal(&maria);
    printf("Valor Bruto Total: R$ %.2f\n", valorBrutoTotal);

    // Calculando e imprimindo o valor líquido total
    double valorLiquidoTotal = calcularValorLiquidoTotal(&maria);
    printf("Valor Líquido Total: R$ %.2f\n", valorLiquidoTotal);

    return 0;
}
