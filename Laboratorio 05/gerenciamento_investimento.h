#ifndef GERENCIAMENTO_INVESTIMENTO_H
#define GERENCIAMENTO_INVESTIMENTO_H

#include "investimentos.h"

// Funções de gerenciamento de investimento
void adicionarInvestimento(Titular *titular, Investimento investimento);
void excluirInvestimento(Titular *titular, int id);
void agruparPorTipoEOrdenarPorValor(Titular *titular);
void printTitular(const Titular *titular);

#endif