#ifndef INVESTIMENTO_H
#define INVESTIMENTO_H

// Macros
#define MAX_NAME_LENGTH 50
#define MAX_INVESTIMENTOS 100

// Enum para os tipos de investimento
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

// Estrutura para representar um investimento
typedef struct {
    int id;
    Date dataAplicacao;
    Date dataVencimento;
    double valorBruto;
    double valorAplicado;
    double imposto;
    double taxaJuros;
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

#endif
