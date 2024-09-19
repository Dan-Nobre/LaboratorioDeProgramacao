#include <stdio.h>
#include "calculo_investimento.h"
#include "gerenciamento_investimento.h"

int main() {
    Titular titular = {1, "Maria", {}, 0};

    // Criar investimentos
    Date dataAplicacao = {25, 3, 2021};
    Date dataVencimento = {25, 3, 2026};

    Investimento inv1 = {1, dataAplicacao, dataVencimento, 0, 500.00, 50.00, 12.0, Selic, "Selic"};
    Investimento inv2 = {2, dataAplicacao, dataVencimento, 0, 300.00, 30.00, 10.0, CDI, "CDI"};

    adicionarInvestimento(&titular, inv1);
    adicionarInvestimento(&titular, inv2);

    printTitular(&titular);

    // Calcular e exibir valores brutos e líquidos
    double valorBrutoTotal = calcularValorBrutoTotal(&titular);
    printf("Valor Bruto Total: R$ %.2f\n", valorBrutoTotal);

    double valorLiquidoTotal = calcularValorLiquidoTotal(&titular);
    printf("Valor Líquido Total: R$ %.2f\n", valorLiquidoTotal);

    return 0;
}