#include <stdio.h>
#include "arvore.h"

void mostrar(int valor);

int main() {
    int in;
    Arvore a;
    inicializa_arvore(&a);
    do {
        printf("Insira o valor do próximo nó, ou uma letra para terminar: ");
        if (scanf("%d", &in)) {
            switch (adiciona_no(&a, in)) {
                case ERRO_CHAVE_REPETIDA:
                    printf("ERRO: O nó não pode ser inserido pois já existe na árvore outro nó com valor %d\n", in);
                    break;
                case 0:
                    printf("ERRO: O nó não pôde ser inserido por falta de memória.\n");
                    break;
                case 1:
                    printf("Nó com valor %d inserido com sucesso!\n", in);
            }
        } else {
            break;
        }
    } while (1);

    printf("\nPre-order: ");
    percorrer_PreOrder(a.raiz, mostrar);
    printf("\nIn-order: ");
    percorrer_InOrder(a.raiz, mostrar);
    printf("\nPos-order: ");
    percorrer_PosOrder(a.raiz, mostrar);
    printf("\n");

    limpa_subarvore(&a, a.raiz);

    return 1;
}

void mostrar(int valor) {
    printf("%d ", valor);
}
