#include "lldupla.h"
#include "stdlib.h"

void insercao(conjunto X, int z) {
  // cria um novo espaço la lista
  conjunto novo = malloc(sizeof(struct lista));
  novo->conteudo = z;
  novo->prox = X->prox;
  novo->ant = X;

  // se o conjunto nao estiver vazio
  if (X->prox != NULL)
    X->prox->ant = novo;

  X->prox = novo;
}

void retirar(conjunto X, int z) {
  // verifica em qual posição o inteiro z esta
  conjunto no = X->prox;
  while (no != NULL && no->conteudo != z) {
    no = no->prox;
  }

  if (no->ant == NULL) // ele é o primeiro?
    X = no->prox;
  else
    no->ant->prox = no->prox;

  if (no->prox != NULL) // não é o ultimo?
    no->prox->ant = no->ant;
}

bool busca(conjunto X, int z) {
  // verifica se o inteiro z esta na lista
  conjunto no = X->prox;
  while (no != NULL && no->conteudo != z) {
    no = no->prox;
  }
  if (no != NULL) {

    return true;
  } else {

    return false;
  }
}
