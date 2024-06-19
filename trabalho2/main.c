#include <stdio.h>
#include <stdlib.h>

// Nó
typedef struct no {
    int conteudo;
    struct no *esquerda, *direita;
} No;

// Árvore ponteiro nó
typedef struct {
    No *raiz;
    int tam;
} ArvB;


// Inserir elemento esquerda
void inserirEsquerda(No *no, int valor) {
    if (no->esquerda == NULL) {
        No *novo = (No *)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->esquerda = novo;
    } else {
        if (valor < no->esquerda->conteudo)
            inserirEsquerda(no->esquerda, valor);
        if (valor > no->esquerda->conteudo)
            inserirDireita(no->esquerda, valor);
    }
}

// Inserir elemento direita
void inserirDireita(No *no, int valor) {
    if (no->direita == NULL) {
        No *novo = (No *)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->direita = novo;
    } else {
        if (valor > no->direita->conteudo)
            inserirDireita(no->direita, valor);
        if (valor < no->direita->conteudo)
            inserirEsquerda(no->direita, valor);
    }
}

void inserir(ArvB *arv, int valor) {
    if (arv->raiz == NULL) {
        No *novo = (No *)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        arv->raiz = novo;
    } else {
        if (valor < arv->raiz->conteudo)
            inserirEsquerda(arv->raiz, valor);
        if (valor > arv->raiz->conteudo)
            inserirDireita(arv->raiz, valor);
    }
}

No* inserirNovaVersao(No *raiz, int valor) {
    if (raiz == NULL) {
        No *novo = (No *)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    } else {
        if (valor < raiz->conteudo)
            raiz->esquerda = inserirNovaVersao(raiz->esquerda, valor);
        if (valor > raiz->conteudo)
            raiz->direita = inserirNovaVersao(raiz->direita, valor);
        return raiz;
    }
}

// Tamanho
int tamanho(No *raiz) {
    if (raiz == NULL)
        return 0;
    else
        return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);
}

// Buscar
int buscar(No *raiz, int chave) {
    if (raiz == NULL) {
        return 0;
    } else {
        if (raiz->conteudo == chave)
            return 1;
        else {
            if (chave < raiz->conteudo)
                return buscar(raiz->esquerda, chave);
            else
                return buscar(raiz->direita, chave);
        }
    }
}

// Imprimir (In-order)
void imprimir(No *raiz) {
    if (raiz != NULL) {
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

// Remoção nó
No* remover(No *raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return NULL;
    } else {
        if (raiz->conteudo == chave) {
            if (raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                return NULL;
            } else {
                if (raiz->esquerda == NULL || raiz->direita == NULL) {
                    No *aux;
                    if (raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    return aux;
                } else {
                    No *aux = raiz->esquerda;
                    while (aux->direita != NULL)
                        aux = aux->direita;
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = chave;
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                }
            }
        } else {
            if (chave < raiz->conteudo)
                raiz->esquerda = remover(raiz->esquerda, chave);
            else
                raiz->direita = remover(raiz->direita, chave);
            return raiz;
        }
    }
}

// Função de percurso pré-ordem (pre-order)
void preOrdem(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->conteudo);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

// Função de percurso pós-ordem (post-order)
void posOrdem(No *raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->conteudo);
    }
}

int main() {
    int op, valor;
    ArvB arv;
    arv.raiz = NULL;

    No *raiz = NULL;

    do {
        printf("\n0 - sair\n1 - inserir\n2 - imprimir in-order\n3 - Buscar\n4 - Remover\n5 - imprimir pre-order\n6 - imprimir post-order\n");
        scanf("%d", &op);

        switch(op) {
        case 0:
            printf("\nSaindo...\n");
            break;
        case 1:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            raiz = inserirNovaVersao(raiz, valor);
            break;
        case 2:
            printf("\nImpressao da arvore binaria (in-order):\n");
            imprimir(raiz);
            printf("\n");
            printf("Tamanho: %d\n", tamanho(raiz));
            break;
        case 3:
            printf("Qual valor deseja buscar? ");
            scanf("%d", &valor);
            printf("Resultado da busca: %d\n", buscar(raiz, valor));
            break;
        case 4:
            printf("Digite um valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        case 5:
            printf("\nImpressao da arvore binaria (pre-order):\n");
            preOrdem(raiz);
            printf("\n");
            break;
        case 6:
            printf("\nImpressao da arvore binaria (post-order):\n");
            posOrdem(raiz);
            printf("\n");
            break;
        default:
            printf("\nOpcao invalida...\n");
        }
    } while(op != 0);
}
