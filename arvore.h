#define ERRO_CHAVE_REPETIDA -1

typedef struct no {
    struct no *pai;
    struct no *esquerda;
    struct no *direita;
    int valor;
} No;

typedef struct arvore {
    struct no *raiz;
} Arvore;

void inicializa_arvore(Arvore* arvore);
int arvore_vazia(Arvore* arvore);
int adiciona_no(Arvore* arvore, int valor);
void remove_no(Arvore* arvore, No* no);
void percorrer_InOrder(No* no, void (*callback) (int));
void percorrer_PreOrder(No* no, void (*callback) (int));
void percorrer_PosOrder(No* no, void (*callback) (int));
void limpa_subarvore(Arvore* arvore, No* no);
