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

typedef struct {
    int id;
    char nome[MAX_NAME_LENGTH];
    Investimento investimentos[MAX_INVESTIMENTOS];
    int numeroInvestimentos;
} Titular;

