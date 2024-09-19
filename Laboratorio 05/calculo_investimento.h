#ifndef CALCULO_INVESTIMENTO_H
#define CALCULO_INVESTIMENTO_H

#include "investimentos.h"

// Funções de cálculo de investimento
int calcularDiferencaDias(Date data1, Date data2);
void atualizarInvestimento(Investimento *inv);
double calcularValorBrutoTotal(Titular *titular);
double calcularValorLiquidoTotal(Titular *titular);

#endif
