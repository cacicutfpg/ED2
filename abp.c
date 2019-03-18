#include <stdlib.h>
#include <stdio.h>

typedef struct tABP{
  int chave;
  struct tABP * dir;
  struct tABP * esq;
}abp;


//Cria o nó de uma arvore livre de erros de memoria a entrada é sua chave
abp * criaNoABP(int chave);
//Insere um nó em uma arvore livre de erros de memoria a entrada é o endereço do ponteiro para arvore e a chave a ser inserida
void insereABP(abp ** prim, int chave);
//Busca o pai de um nó da arvore, a entrada é o endereço do ponteiro para arvore e a chave a ser buscada
abp ** buscaPaiABP(abp **prim, int chave);
//busca a maior chave de uma arvore, a entrada é o endereço do ponteiro para arvore
abp ** buscaPaiMaiorABP(abp **prim);
//busca a menor chave de uma arvore, a entrada é o endereço do ponteiro para arvore
abp ** buscaPaiMenorABP(abp **prim);
//remove o nó folha que é dado de entrada
void removeFolhaABP(abp **prim);
//remove o nó dado de entrada somente se tiver 1 filho
void removeUmFilhoABP(abp **prim);
//remove o nó de uma ABP independente do numero de filho, a entrada é o endereço do ponteiro para lista e a chave a ser removida
void removeABP(abp **prim, int chave);
//conta o numero de nós com uma travessia.
int contaABP(abp *prim);


abp * criaNoABP(int chave){
  abp *prim; //cria um axiliar
  prim = malloc(sizeof(abp)); //aloca dinamicamente
  prim->chave = chave; //armazena o chave em seu campo
  prim->dir = NULL; //evita erros futuros colocando NULL
  prim->esq = NULL; //evita erros futuros colocando NULL
  return prim;
}

void insereABP(abp ** prim, int chave){
  if((*prim) == NULL){ //verifica se a arvore é vazia para a criação do novo nó
    *prim = criaNoABP(chave); //chama a função de criar nó para criar o nó
  }
  if((*prim)->chave > chave) //verifica se a chave a ser inserida é menor que a que queremos inserir
    return insereABP(&((*prim)->dir),chave); //chama recursivamente a função indo para os menores
  if((*prim)->chave < chave) //verifica se a chave a ser insrrida é maior que a que queremos inserir
    return insereABP(&((*prim)->esq),chave); //chama recursivamente a funçao indo para os maiores
}

abp ** buscaPaiABP(abp **prim, int chave){
  if((*prim) == NULL) return NULL; //verifica existencia da arvore
  if((*prim)->chave == chave) //verifica se este é o pai
    return prim;
  if((*prim)->chave > chave) //verifica se o chave do nó é maior que a que queremos buscar
    return buscaPaiABP(&((*prim)->esq), chave); //chama recursivamente a função, indo para o maior
  if((*prim)->chave < chave) //verifica se o chave do nó é menor que a que queremos bucar
    return buscaPaiABP(&((*prim)->dir), chave); //chama recursivamente a função, indo para o menor
}

//Não esta sendo usada(por enquanto)
abp ** buscaPaiMaiorABP(abp **prim){
  if((*prim) == NULL) return NULL; //verifica existencia da arvore
  if((*prim)->esq == NULL) return prim; //verifica se esse é o pai do menor
  return buscaPaiMaiorABP(&((*prim)->esq)); //chama recursivamente a função, indo para o maior
}

abp ** buscaPaiMenorABP(abp **prim){
  if((*prim) == NULL) return NULL; //verifica existencia da arvore
  if((*prim)->dir == NULL) return prim; //verifica se este é o pai do menor
  return buscaPaiMenorABP(&((*prim)->dir)); //chama recursivamente a função, indo para o menor
}

void removeFolhaABP(abp **prim){
  if((*prim) == NULL) return; //Verifica existencia arvore
  if((*prim)->dir == NULL && (*prim)->esq == NULL){ //verifica se é um folha
    free(*prim); //libera nó
    *prim = NULL; //evita erros de memoria
  }
}

void removeUmFilhoABP(abp **prim){
  if((*prim) == NULL) return; //verifica existencia arvore
  abp * temp = NULL; //variavel auxiliar
  if((*prim)->dir != NULL && (*prim)->esq != NULL) return; //verifica se não tem dois filhos
  if((*prim)->dir != NULL){ //Verifica se o filho existente é o direito
    temp = (*prim)->dir; //armazena o filho no auxiliar
    free(*prim); //libera o nó
    *prim = temp; //coloca o filho no lugar do pai
    return;
  }
  //se nao estiver no direito só sobra o esquerdo
  temp = (*prim)->esq; //armazena o filho no auxiliar
  free(*prim); //libera o nó
  *prim = temp; //coloca o filho no lugar do pai
  return;
}

void removeABP(abp **prim, int chave){
  if((*prim) == NULL) return; //verifica a existencia da arvore
  abp** temp;  //variaveis auxiliares
  abp** candidato; //variaveis auxiliares
  temp = buscaPaiABP(prim, chave); //busca o pai do nó a ser removido
  if(temp == NULL) return; //elemento não encontrado na busca
  if((*temp)->dir == NULL && (*temp)->esq == NULL) //verifica se o nó é folha
    return removeFolhaABP(temp); //chama remoção de nó folha
  if(((*temp)->dir == NULL && (*temp)->esq != NULL) || ((*temp)->dir != NULL && (*temp)->esq == NULL)) //verifica se só tem um filho(não importa o lado)
    return removeUmFilhoABP(temp); //chama remoção de nó com somente um filho.
  candidato = buscaPaiMenorABP(&((*prim)->esq)); //busca o menor dos maiores
  (*temp)->chave = (*candidato)->chave; //coloca a chave do menor dos maiores no lugar da que vai ser removida
  return removeUmFilhoABP(candidato); //remove o menor dos maiores com removeUmFilhoABP que independente de ser folha ou não sera removido com sucesso
}

int contaABP(abp *prim){
  if(prim != NULL){ //verifica se existe a arvore
    printf("%d\n", prim->chave);
    return 1 + contaABP(prim->esq) + contaABP(prim->dir); //soma 1 para cada nó recursivamente
  }
  return 0; //retorna 0 se nao existir a arvore
}
