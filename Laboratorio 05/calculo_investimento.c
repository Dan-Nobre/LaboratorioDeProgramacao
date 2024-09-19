#include <math.h>
#include "calculo_investimento.h"

// Função para calcular a diferença em dias entre duas datas
int calcularDiferencaDias(Date data1, Date data2) {
    int diasAno1 = data1.year * 365 + data1.day;
    int diasAno2 = data2.year * 365 + data2.day;

    int diasMes1 = (data1.month - 1) * 30;
    int diasMes2 = (data2.month - 1) * 30;

    return (diasAno2 + diasMes2) - (diasAno1 + diasMes1);
}

// Função para atualizar o valorBruto de um investimento
void atualizarInvestimento(Investimento *inv) {
    int dias = calcularDiferencaDias(inv->dataAplicacao, inv->dataVencimento);
    double taxaDiaria = inv->taxaJuros / 100.0 / 365.0;
    inv->valorBruto = inv->valorAplicado * pow(1 + taxaDiaria, dias);
}

// Função para calcular o valor bruto total
double calcularValorBrutoTotal(Titular *titular) {
    double valorBrutoTotal = 0.0;
    for (int i = 0; i < titular->numeroInvestimentos; i++) {
        atualizarInvestimento(&titular->investimentos[i]);
        valorBrutoTotal += titular->investimentos[i].valorBruto;
    }
    return valorBrutoTotal;
}

// Função para calcular o valor líquido total
double calcularValorLiquidoTotal(Titular *titular) {
    double valorLiquidoTotal = 0.0;
    for (int i = 0; i < titular->numeroInvestimentos; i++) {
        atualizarInvestimento(&titular->investimentos[i]);
        valorLiquidoTotal += titular->investimentos[i].valorBruto - titular->investimentos[i].imposto;
    }
    return valorLiquidoTotal;
}
