#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"
#include "lista.h"

int altura(No* no);
No* balanceamento(No* no);
void plota(No* no);

void inicializa_arvore(Arvore *arvore) {
    arvore->raiz = NULL;
}

int arvore_vazia(Arvore *arvore) {
    return arvore->raiz == NULL;
}

void remove_no(Arvore *arvore, No *no) {
    if (no->esquerda) {
        remove_no(arvore, no->esquerda); 
    }
    if (no->direita) {
        remove_no(arvore, no->direita);
    }
    if (!no->pai) {
        arvore->raiz = NULL;
    } else {
        if (no->pai->esquerda == no) {
            no->pai->esquerda = NULL;
        } else {
            no->pai->direita = NULL;
        }
    }
    free(no);
}

void percorrer_InOrder(No* no, void (*callback) (int)) {
    if (no) {
        percorrer_InOrder(no->esquerda, callback);
        callback(no->valor);
        percorrer_InOrder(no->direita, callback);
    }
}

void percorrer_PreOrder(No* no, void (*callback) (int)) {
    if (no) {
        callback(no->valor);
        percorrer_PreOrder(no->esquerda, callback);
        percorrer_PreOrder(no->direita, callback);
    }
}

void percorrer_PosOrder(No* no, void (*callback) (int)) {
    if (no) {
        percorrer_PosOrder(no->esquerda, callback);
        percorrer_PosOrder(no->direita, callback);
        callback(no->valor);
    }
}

int max(int x, int y) { 
    return (x > y) ? x : y;
} 

int altura(No* no) {
    if (!no || (!no->esquerda && !no->direita))
        return 0;
    return 1 + max(altura(no->esquerda), altura(no->direita));
}

int fb(No* no) {
    int altura_esquerda = 0, altura_direita = 0;
    if (no->esquerda) {
        altura_esquerda = altura(no->esquerda) + 1;
    }
    if (no->direita) {
        altura_direita = altura(no->direita) + 1;
    }
    return altura_esquerda - altura_direita;
}

No* rse(No* satelite) {
    No *pai = satelite->pai, *pivo = satelite->direita, *rebarba = pivo->esquerda;
    printf("* Rotação à esquerda de %d em torno de %d:\n", satelite->valor, pivo->valor);
    satelite->pai = pivo;
    pivo->esquerda = satelite;
    if (!rebarba)
        satelite->direita = NULL;
    else {
        rebarba->pai = satelite;
        satelite->direita = rebarba;
    }
    pivo->pai = pai;
    if (pai && pai->esquerda == satelite)
        pai->esquerda = pivo;
    else if (pai)
        pai->direita = pivo;
    plota(pivo);
    return pivo;
}

No* rsd(No* satelite) {
    No *pai = satelite->pai, *pivo = satelite->esquerda, *rebarba = pivo->direita;
    printf("* Rotação à direita de %d em torno de %d:\n", satelite->valor, pivo->valor);
    satelite->pai = pivo;
    pivo->direita = satelite;
    if (!rebarba)
        satelite->esquerda = NULL;
    else {
        rebarba->pai = satelite;
        satelite->esquerda = rebarba;
    }
    pivo->pai = pai;
    if (pai && pai->esquerda == satelite)
        pai->esquerda = pivo;
    else if (pai)
        pai->direita = pivo;
    plota(pivo);
    return pivo;
}

No* rde(No* satelite) {
    satelite->direita = rsd(satelite->direita);
    return rse(satelite);
}

No* rdd(No* satelite) {
    satelite->esquerda = rse(satelite->esquerda);
    return rsd(satelite);
}

No* balanceamento(No* no) {
    while (no) {
        int fator = fb(no);
        if (fator > 1) {
            int fatorFilho = fb(no->esquerda);
            if (fatorFilho > 0) {
                return rsd(no);
            } else {
                return rdd(no);
            }
        } else if (fator < -1) {
            int fatorFilho = fb(no->direita);
            if (fatorFilho < 0) {
                return rse(no);
            } else {
                return rde(no);
            }
        }
        no = no->pai;
    }
    return no;
}

int adiciona_no(Arvore *arvore, int valor) {
    No* no = malloc(sizeof(No));
    if (!no)
        return 0;
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    if (arvore_vazia(arvore)) {
        no->pai = NULL;
        arvore->raiz = no;
        plota(no);
        return 1;
    } else {
        No *i = arvore->raiz, *pivo = NULL;
        do {
            if (i->valor == valor) {
                free(no);
                return ERRO_CHAVE_REPETIDA;
            } else if (valor < i->valor) {
                if (!i->esquerda) {
                    no->pai = i;
                    i->esquerda = no;
                    plota(no);
                    pivo = balanceamento(i->pai);
                    if (pivo && !pivo->pai)
                        arvore->raiz = pivo;
                    return 1;
                } else {
                    i = i->esquerda;
                }
            } else {
                if (!i->direita) {
                    no->pai = i;
                    i->direita = no;
                    plota(no);
                    pivo = balanceamento(i->pai);
                    if (pivo && !pivo->pai)
                        arvore->raiz = pivo;
                    return 1;
                } else {
                    i = i->direita;
                }
            }
        } while (1);
    }        
}

No* acha_raiz(No* no) {
    if (!no->pai)
        return no;
    return acha_raiz(no->pai);
}

int p2(int exp) {
    if (!exp)
        return 1;
    return 2 * p2(exp - 1);
}

int logb10(int p) {
    if (p < 10)
        return 1;
    return logb10(p / 10) + 1;
}

void mostra_no(void *x) {
    No* y = *(No**) x;
    if (y)
        printf("%d", y->valor);
    else
        printf(" ");
}

// montagem gráfica da árvore
void plota(No* no) {
    // achar a raiz
    No* raiz = acha_raiz(no);
    // calcular a altura da raiz
    int h = altura(raiz);
    // calcular a largura da árvore
    int l = h ? p2(h) * 2 - 1 : 1;
    // gerar vetor de listas de nós do tamanho da altura e preenchê-los com NULL
    int i, j, k, m;
    No* nulo = NULL;
    LDE niveis[h];
    for (i = 0; i <= h; i++) {
        inicializa_LDE(&niveis[i], sizeof(No*));
        for (j = 0; j < l; j++) {
            insereNoFim(&niveis[i], &nulo);
        }
    }
    // percorrer a árvore desde a raiz, preenchendo as listas de acordo com seus níveis correspondentes
    modificaNaPos(&niveis[0], &raiz, l / 2);
    No* aux = raiz;
    int expansao, retracao;
    for (i = 1; i <= h; i++) { // percorre listas
        expansao = 0;
        retracao = 0;
        for (j = 0; j < niveis[i].qtd; j++) { // percorre itens na lista
            leNaPos(&niveis[i - 1], &aux, j);
            if (aux) {
                expansao += logb10(aux->valor) - 1;
                for (k = i; k <= h; k++) {
                    for (m = 0; m < expansao; m++) {
                        insereNoFim(&niveis[k], &nulo);
                    }
                }
                if (aux->esquerda) {
                    retracao += logb10(aux->esquerda->valor) - 1;
                    modificaNaPos(&niveis[i], &aux->esquerda, j - p2(h - i) + expansao - retracao);
                }
                if (aux->direita) {
                    retracao += logb10(aux->direita->valor) - 1;
                    modificaNaPos(&niveis[i], &aux->direita, j + p2(h - i) + expansao - retracao / 2);
                }
            }
        }
    }
    // imprimir as listas no terminal e desalocá-las da memória
    for (i = 0; i <= h; i++) {
        mostra_LDE(niveis[i], mostra_no);
        limpa_LDE(&niveis[i]);
        printf("\n");
    }
}

void limpa_subarvore(Arvore *arvore, No *no) {
    if (no) {
        limpa_subarvore(arvore, no->esquerda);
        limpa_subarvore(arvore, no->direita);
        remove_no(arvore, no);
    }
}
