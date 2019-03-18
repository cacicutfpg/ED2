#include "lib.h"

int insere_no(No **p, int x) {
    int cresceu;

    // O no raiz esta vazio
    if(*p == NULL) {
        *p = (No *) malloc(sizeof(No));

        (*p)->chave = x;
        (*p)->dir = (*p)->esq = NULL;
        (*p)->bal = 0;

        // Esta subarvore cresceu
        cresceu = 1;
    }
    // Senao, verifica se tem que inserir a esquerda
    else if ((*p)->chave >= x) {
        // Tenta inserir a esquerda e ve se a subarvore cresceu

        // puts("Chamando insereAVL (esquerda) again");
        cresceu = insere_no(&(*p)->esq, x);

        // Se cresceu for diferente de 0, logo a arvore cresceu
        if(cresceu) {
            // Verifica o estado atual de balanceamento
            switch ((*p)->bal) {
                // Se a arvore direita era maior entao nao ha crescimento
                case 1:
                    (*p)->bal = 0;
                    cresceu = 0;
                    break;
                // Se a subarvore direita tinha tamanho igual entao houve crescimento
                case 0:
                    (*p)->bal = -1;
                    cresceu = 1;
                    break;
                // Se a subarvore da esquerda ja era maior entao deve-se re-balancear
                case -1:
                    if((*p)->esq->bal == -1) {
                        // Rotacao para a direita
                        rot_dir(p);
                        // Arruma os balanceamentos
                        (*p)->bal = (*p)->dir->bal = 0;
                    }
                    else {
                        // Rotacao dupla
                        // Rotaciona primeiro a esquerda
                        rot_esq(&(*p)->esq);
                        // Depois rotaciona a direita
                        rot_dir(p);
                        // Acerta balanceamentos
                        if((*p)->bal == -1) {
                            (*p)->esq->bal = 0;
                            (*p)->dir->bal = 1;
                        }
                        else {
                            (*p)->dir->bal = 0;
                            (*p)->esq->bal = -(*p)->bal;
                        }

                        (*p)->bal = 0;
                    }

                    cresceu = 0;
            }
        }
    }
    // Verifica se tem que inserir a direita
    else if((*p)->chave < x) {
        // Tenta inserir a direita e ve se a sub-arvore cresceu
        cresceu = insere_no(&(*p)->dir, x);

        if(cresceu) {
            // Verifica o estado atual de balanceamento
            switch ((*p)->bal) {
                // Se a arvore esquerda era maior entao nao ha crescimento
                case -1:
                    (*p)->bal = 0;
                    cresceu = 0;
                    break;
                // Se a arvore esquerda tinha tamanho igual entao houve crescimento
                case 0:
                    (*p)->bal = 1;
                    cresceu = 1;
                    break;
                // Se a arvore da direita ja era maior entao deve-se re-balancear
                case 1:
                    // Verifica qual o caso de re-balanceamentos
                    if((*p)->dir->bal == 1) {
                        // Rotacao para a esquerda
                        rot_esq(p);
                        // Acerta os balanceamentos
                        (*p)->bal = (*p)->esq->bal = 0;
                    }
                    else {
                        // Rotacao dupla
                        // Primeiro a direita
                        rot_dir(&(*p)->dir);
                        // Depois a esquerda
                        rot_esq(p);
                        // Acerta os balanceamentos
                        if((*p)->bal == -1) {
                            (*p)->esq->bal = 0;
                            (*p)->dir->bal = 1;
                        }
                        else {
                            (*p)->dir->bal = 0;
                            (*p)->esq->bal = -(*p)->bal;
                        }

                        (*p)->bal = 0;
                    }

                    cresceu = 0;
            }
        }
    }
    else
        cresceu = 0;

    return cresceu;
}

No *del(No **p) {
    No *aux = (*p), *pai = (*p);

    while(aux->dir != NULL) {
        pai = aux;
        aux = aux->dir;
    }

    pai->dir = NULL;
    bal_dir(&pai);
    return aux;
}

int delete(No **p, int x) {
    No *q, *aux = NULL;
    int flag = 0;

    if((*p) == NULL) {
        return 0;
    }
    else if((*p)->chave > x) {
        flag = delete(&(*p)->esq, x);

        if(flag){
            puts("Mandei balancear");
            bal_esq(&(*p));
        }
    }
    else if((*p)->chave < x) {
        flag = delete(&(*p)->dir, x);

        if(flag){
            puts("Mandei balancear");
            bal_dir(&(*p));
        }
    }
    else {
        q = (*p);

        if(q->dir == NULL) {
            (*p) = q->esq;
            return 1;
        }
        else if(q->esq == NULL) {
            (*p) = q->dir;
            return 1;
        }
        else {
            aux = del(&q->esq);

            (*p)->chave = aux->chave;
            (*p)->bal = aux->bal;
            // free(aux);

        }
    }
}

int bal_esq(No **p) {
    No *p1, *p2;

    if((*p) == NULL) {
        return 0;
    }

    printf("Esq: Chave [%d] \n Bal [%d]\n\n", (*p)->chave, (*p)->bal);

    if((*p)->bal == -1) {
        (*p)->bal = 0;
        return 1;
    }
    else if((*p)->bal == 0) {
        (*p)->bal = 1;
        return 0;
    }
    else {
        p1 = (*p)->dir;

        if(p1->bal >= 0) {
            (*p)->dir = p1->esq;
            p1->esq = (*p);

            if(p1->bal == 0) {
                (*p)->bal = 1;
                p1->bal = -1;
            }
            else {
                (*p)->bal = 0;
                p1->bal = 0;
            }

			(*p) = p1;

			return 1;
        }
        else {
            p2 = p1->esq;
            p1->esq = p2->dir;
            p2->dir = p1;
            (*p)->dir = p2->esq;
            p2->esq = (*p);

            if(p2->bal == 1) {
                (*p)->bal = -1;
            }
            else {
                (*p)->bal = 0;
            }

            if(p2->bal == -1) {
                p1->bal = 1;
            }
            else {
                p1->bal = 0;
            }

            (*p) = p2;
            p2->bal = 0;

            return 1;
        }
    }
}

int bal_dir(No **p) {
    No *p1, *p2;
    int b2;

    if((*p) == NULL) {
        return 0;
    }

    printf("Dir: Chave [%d] -- Bal [%d]\n\n", (*p)->chave, (*p)->bal);

    if((*p)->bal == 1) {
        (*p)->bal = 0;
        return 1;
    }
    else if((*p)->bal == 0) {
        (*p)->bal = -1;
        return 0;
    }
    else {
        p1 = (*p)->esq;

        if(p1->bal <= 0) {
            (*p)->esq = p1->dir;
            p1->dir = (*p);

            if(p1->bal == 0) {
                (*p)->bal = -1;
                p1->bal = 1;
                (*p) = p1;
                return 0;
            }
            else {
                (*p)->bal = 0;
                p1->bal = 0;
                (*p) = p1;
                return 1;
            }
        }
        else {
            p2 = p1->dir;
            b2 = p2->bal;
            p1->dir = p2->esq;
            p2->esq = (*p);

            if(p2->bal == -1) {
                (*p)->bal = 1;
            }
            else {
                (*p)->bal = 0;
            }

            if(p2->bal == 1) {
                p1->bal = -1;
            }
            else {
                p1->bal = 0;
            }

            (*p) = p2;
            p2->bal = 0;

            return 1;
        }
    }
}


No *busca_no(No **p, int x) {
    if((*p) == NULL) {
        puts("A arvore esta vazia.");
        return NULL;
    }

    if((*p)->chave == x) {
        return (*p);
    }
    else {
        if((*p)->chave >= x) {
            return busca_no(&(*p)->dir, x);
        }
        else {
            return busca_no(&(*p)->esq, x);
        }
    }
}

int rot_dir(No **p) {
    No *q, *aux;

    if((*p) == NULL) return 1;

    q = (*p)->esq;
    aux = q->dir;
    q->dir = (*p);
    (*p)->esq = aux;
    (*p) = q;

    return 0;
}

int rot_esq(No **p) {
    No *q, *aux;

    if((*p) == NULL) return 1;

    q = (*p)->dir;
    aux = q->esq;
    q->esq = (*p);
    (*p)->dir = aux;
    (*p) = q;

    return 0;
}

void pre_ordem(No **p) {
    if((*p) != NULL){
        pre_ordem(&(*p)->esq);
        pre_ordem(&(*p)->dir);
        printf("%d\n", (*p)->chave);
    }
}

void em_ordem(No **p) {
    if((*p) != NULL){
        em_ordem(&(*p)->esq);
        printf("Chave [%d] --- Bal [%d]\n", (*p)->chave, (*p)->bal);
        em_ordem(&(*p)->dir);
    }
}

void pos_ordem(No **p) {
    if((*p) != NULL){
        printf("%d\n", (*p)->chave);
        pos_ordem(&(*p)->esq);
        pos_ordem(&(*p)->dir);
    }
}

int altura(No **p) {
    int alt_esq = 0, alt_dir = 0;

    if((*p) == NULL) {
        return -1;
    }
    else {
        alt_esq = altura(&(*p)->esq);
        alt_dir = altura(&(*p)->dir);

        if(alt_esq > alt_dir)
            return alt_esq + 1;
        else
            return alt_dir + 1;
    }
}
