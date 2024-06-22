#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da árvore binária
typedef struct no {
    int conteudo;           // Conteúdo do nó
    struct no *esquerda;    // Ponteiro para o nó à esquerda
    struct no *direita;     // Ponteiro para o nó à direita
} No;

// Estrutura da árvore binária
typedef struct {
    No *raiz;               // Ponteiro para a raiz da árvore
    int tam;                // Tamanho da árvore (não utilizado neste código)
} ArvB;

// Função para inserir elemento à esquerda de um nó
void inserirEsquerda(No *no, int valor) {
    // Se não há nó à esquerda
    if (no->esquerda == NULL) {
        No *novo = (No *)malloc(sizeof(No)); // Aloca memória para o novo nó
        novo->conteudo = valor;              // Define o conteúdo do novo nó
        novo->esquerda = NULL;               // Define o ponteiro da esquerda como NULL
        novo->direita = NULL;                // Define o ponteiro da direita como NULL
        no->esquerda = novo;                 // Faz o ponteiro da esquerda apontar para o novo nó
    } else {
        // Se tem na esquerda
        if (valor < no->esquerda->conteudo)  // Se o valor é menor que o conteúdo do nó à esquerda
            inserirEsquerda(no->esquerda, valor); // Chama para inserir à esquerda
        if (valor > no->esquerda->conteudo)  // Se o valor é maior que o conteúdo do nó à esquerda
            inserirDireita(no->esquerda, valor); // Chama para inserir à direita
    }
}

// Função para inserir elemento na direita de um nó
void inserirDireita(No *no, int valor) {
    // Se não há nó à direita
    if (no->direita == NULL) {
        No *novo = (No *)malloc(sizeof(No)); // Aloca memória para o novo nó
        novo->conteudo = valor;              // Define o conteúdo do novo nó
        novo->esquerda = NULL;               // Define o ponteiro da esquerda como NULL
        novo->direita = NULL;                // Define o ponteiro da direita como NULL
        no->direita = novo;                  // Faz o ponteiro da direita apontar para o novo nó
    } else {
        // Se já há nó à direita
        if (valor > no->direita->conteudo)   // Se o valor é maior que o conteúdo do nó à direita
            inserirDireita(no->direita, valor); // Chama para inserir à direita
        if (valor < no->direita->conteudo)   // Se o valor é menor que o conteúdo do nó à direita
            inserirEsquerda(no->direita, valor); // Chama para inserir à esquerda
    }
}

// Função para inserir um valor na árvore binária
void inserir(ArvB *arv, int valor) {
    // Se a árvore está vazia (raiz é NULL)
    if (arv->raiz == NULL) {
        No *novo = (No *)malloc(sizeof(No)); // Aloca memória para o novo nó
        novo->conteudo = valor;              // Define o conteúdo do novo nó
        novo->esquerda = NULL;               // Define o ponteiro da esquerda como NULL
        novo->direita = NULL;                // Define o ponteiro da direita como NULL
        arv->raiz = novo;                    // Faz a raiz apontar para o novo nó
    } else {
        // Se a árvore não está vazia
        if (valor < arv->raiz->conteudo)     // Se o valor é menor que o conteúdo da raiz
            inserirEsquerda(arv->raiz, valor); // Insere à esquerda
        if (valor > arv->raiz->conteudo)     // Se o valor é maior que o conteúdo da raiz
            inserirDireita(arv->raiz, valor); // Insere à direita
    }
}

// Função para inserir um valor na árvore binária (nova versão)
No* inserirNovaVersao(No *raiz, int valor) {
    // Se a raiz é NULL
    if (raiz == NULL) {
        No *novo = (No *)malloc(sizeof(No)); // Aloca memória para o novo nó
        novo->conteudo = valor;              // Define o conteúdo do novo nó
        novo->esquerda = NULL;               // Define o ponteiro da esquerda como NULL
        novo->direita = NULL;                // Define o ponteiro da direita como NULL
        return novo;                         // Retorna o novo nó
    } else {
        // Se a raiz não é NULL
        if (valor < raiz->conteudo)          // Se o valor é menor que o conteúdo da raiz
            raiz->esquerda = inserirNovaVersao(raiz->esquerda, valor); // Insere à esquerda
        if (valor > raiz->conteudo)          // Se o valor é maior que o conteúdo da raiz
            raiz->direita = inserirNovaVersao(raiz->direita, valor); // Insere à direita
        return raiz;                         // Retorna a raiz
    }
}

// Função para calcular o tamanho da árvore
int tamanho(No *raiz) {
    // Se a raiz é NULL, o tamanho é 0
    if (raiz == NULL)
        return 0;
    else
        // Calcula o tamanho somando 1 (nó atual) com os tamanhos das subárvores esquerda e direita
        return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);
}

// Função para buscar um valor na árvore
int buscar(No *raiz, int chave) {
    // Se a raiz é NULL, o valor não rtem
    if (raiz == NULL) {
        return 0;
    } else {
        // Se o conteúdo da raiz é igual à chave, o valor foi encontrado
        if (raiz->conteudo == chave)
            return 1;
        else {
            // Se a chave é menor que o conteúdo da raiz, busca na subárvore esquerda
            if (chave < raiz->conteudo)
                return buscar(raiz->esquerda, chave);
            else
                // Se a chave é maior que o conteúdo da raiz, busca na subárvore direita
                return buscar(raiz->direita, chave);
        }
    }
}

// Função para imprimir os valores da árvore em ordem (in-order)
void imprimir(No *raiz) {
    // Se a raiz não é NULL
    if (raiz != NULL) {
        // Imprime a subárvore esquerda, o nó atual e a subárvore direita
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

// Função para remover um nó da árvore
No* remover(No *raiz, int chave) {
    // Se a raiz é NULL, o valor não foi encontrado
    if (raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return NULL;
    } else {
        // Se o conteúdo da raiz é igual à chave
        if (raiz->conteudo == chave) {
            // Caso o nó a ser removido não tenha filhos (folha)
            if (raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz); // Libera a memória do nó
                return NULL;
            } else {
                // Caso o nó a ser removido tenha apenas um filho
                if (raiz->esquerda == NULL || raiz->direita == NULL) {
                    No *aux;
                    if (raiz->esquerda != NULL) // Se há filho à esquerda
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita; // Se há filho à direita
                    free(raiz); // Libera a memória do nó
                    return aux; // Retorna o filho que substitui o nó removido
                } else {
                    // Caso o nó a ser removido tenha dois filhos
                    No *aux = raiz->esquerda;
                    // Encontra o maior nó da subárvore esquerda (ou o sucessor)
                    while (aux->direita != NULL)
                        aux = aux->direita;
                    // Substitui o conteúdo do nó a ser removido pelo do maior nó da subárvore esquerda
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = chave;
                    // Remove o nó duplicado na subárvore esquerda
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                }
            }
        } else {
            // Se a chave é menor que o conteúdo da raiz, remove na subárvore esquerda
            if (chave < raiz->conteudo)
                raiz->esquerda = remover(raiz->esquerda, chave);
            else
                // Se a chave é maior que o conteúdo da raiz, remove na subárvore direita
                raiz->direita = remover(raiz->direita, chave);
            return raiz;
        }
    }
}

// Função para percorrer a árvore em pré-ordem (crescente)
void preOrdem(No *raiz) {
    // Se a raiz não é NULL
    if (raiz != NULL) {
        printf("%d ", raiz->conteudo); // Imprime o nó atual
        preOrdem(raiz->esquerda);      // Percorre a subárvore esquerda
        preOrdem(raiz->direita);       // Percorre a subárvore direita
    }
}

// Função para percorrer a árvore em pós-ordem (decrescente)
void posOrdem(No *raiz) {
    // Se a raiz não é NULL
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);      // Percorre a subárvore esquerda
        posOrdem(raiz->direita);       // Percorre a subárvore direita
        printf("%d ", raiz->conteudo); // Imprime o nó atual
    }
}

int main() {
    int op, valor;             // Variáveis para armazenar a opção do usuário e o valor a ser manipulado
    ArvB arv;                  // Declara uma árvore binária
    arv.raiz = NULL;           // Inicializa a árvore com a raiz NULL

    No *raiz = NULL;           // Inicializa a raiz da árvore como NULL

    // Loop principal do menu de opções
    do {
        printf("\n0 - sair\n1 - inserir\n2 - imprimir in-order\n3 - Buscar\n4 - Remover\n5 - imprimir pre-order\n6 - imprimir post-order\n");
        scanf("%d", &op);      // Lê a opção do usuário

        switch(op) {
        case 0:
            printf("\nSaindo...\n");
            break;
        case 1:
            printf("Digite um valor: ");
            scanf("%d", &valor); // Lê o valor a ser inserido
            raiz = inserirNovaVersao(raiz, valor); // Insere o valor na árvore
            break;
        case 2:
            printf("\nImpressao da arvore binaria (in-order):\n");
            imprimir(raiz);     // Imprime a árvore em ordem (in-order)
            printf("\n");
            printf("Tamanho: %d\n", tamanho(raiz)); // Imprime o tamanho da árvore
            break;
        case 3:
            printf("Qual valor deseja buscar? ");
            scanf("%d", &valor); // Lê o valor a ser buscado
            printf("Resultado da busca: %d\n", buscar(raiz, valor)); // Imprime o resultado da busca
            break;
        case 4:
            printf("Digite um valor a ser removido: ");
            scanf("%d", &valor); // Lê o valor a ser removido
            raiz = remover(raiz, valor); // Remove o valor da árvore
            break;
        case 5:
            printf("\nImpressao da arvore binaria (pre-order):\n");
            preOrdem(raiz);      // Imprime a árvore em pré-ordem (pre-order)
            printf("\n");
            break;
        case 6:
            printf("\nImpressao da arvore binaria (post-order):\n");
            posOrdem(raiz);      // Imprime a árvore em pós-ordem (post-order)
            printf("\n");
            break;
        default:
            printf("\nOpcao invalida...\n");
        }
    } while(op != 0); // Continua até o usuário escolher sair (opção 0)
}
