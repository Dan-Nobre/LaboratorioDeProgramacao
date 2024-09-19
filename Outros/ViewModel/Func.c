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