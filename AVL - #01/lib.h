/*
 * File:   lib.h
 * Author: Aleffer Rocha
 *
 * Created on 8 de Maio de 2018, 16:19
 */

#ifndef _H_AVL_
#define _H_AVL_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Sobre int bal (balanceamento):
 *     -1 se a subarvore esquerda e maior;
 *     0 se esta balanceado;
 *     1 se a subarvore direita e maior.
 */

 #ifndef _H_NO_AVL_
 #define _H_NO_AVL_

// Estrutura de um nó da arvore AVL
typedef struct _no {
    int chave; // Valor chave
    int bal; // Indice de balanceamento
    struct _no *esq; // Ponteiro para a subarvore esquerda
    struct _no *dir; // Ponteiro para a subarvore direita
} No;

#endif

// Recebe um inteiro x e um no **p que aponta para a raiz da arvore
// Insere x na arvore
int insere_no(No **p, int x); // OK

int salvaMatriz(matriz_esparsa *mat);

No *del(No **p);

int delete(No **p, int x);

int bal_esq(No **p);

int bal_dir(No **p);


// Recebe um inteiro x e um no **p que aponta para a raiz da arvore
// Retorna o endereco do no caso x existe na arvore e NULL caso x nao existe
No *busca_no(No **p, int x) ;

// Recebe um no **p que aponta para a raiz da arvore
// Imprime o item chave de cada no da arvore pre ordem
void pre_ordem(No **p); // OK

// Recebe um inteiro x e um no **p que aponta para a raiz da arvore
// Imprime o item chave de cada no da arvore em ordem
void em_ordem(No **p); // OK

// Recebe um no **p que aponta para a raiz da arvore
// Imprime o item chave de cada no da arvore pos ordem
void pos_ordem(No **p); // OK

// Recebe um no **p que aponta para a raiz da arvore
int altura(No **p); // OK

// Recebe um no **p que aponta para a raiz da arvore
// Rotaciona este no para a direita
int rot_dir(No **p); // OK

// Recebe um no **p que aponta para a raiz da arvrore
// Rotaciona este no para a esquerda
int rot_esq(No **p); // OK

#endif
