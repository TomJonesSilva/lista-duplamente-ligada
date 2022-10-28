#include "conjunto.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// grupo 1
conjunto criaconjunto() {

  // alocando um espaço vazio no conjunto
  conjunto novo = malloc(sizeof(struct lista));
  novo->ant = NULL;
  novo->prox = NULL;

  return novo;
}

conjunto leconjunto(FILE *f) {
  // cria um novo conjunto
  conjunto novo = criaconjunto();

  // pegar a primeira linha do arquivo e insere
  int n;
  fscanf(f, "%i", &n);
  insere(novo, n);

  // lendo as demais linihas e inserindo no conjunto
  for (int i = 0; i < n; i++) {
    int x;
    fscanf(f, "%i", &x);
    insere(novo, x);
  }
  return novo;
}

void salvaconjunto(FILE *f, conjunto X) {

  // veficar a quantidade de inteiros no conjunto
  int cont = cardinalidade(X);
  cont--; // cont-1 pois a primeira linha do arquivo é a quantidade de inteiros
  // colocando a quantidade de inteiros na primeira linha
  fprintf(f, "%i\n", cont);
  // colocando os inteiros em cada linha do arquivo

  conjunto P = X->prox;
  for (int i = 0; i < cont; i++) {
    fprintf(f, "%i\n", P->conteudo);
    P = P->prox;
  }
  fclose(f);
}

void insere(conjunto X, int z) {
  // verificar se o z existe no conjunto
  bool verificar = pertence(X, z);

  // se ele não existir
  if (verificar == 0) {
    insercao(X, z);
  }
}

void retira(conjunto X, int z) {
  // verifica se z pertence a X
  bool verificar = pertence(X, z);
  // se pertencer remove z
  if (verificar == 1)
    retirar(X, z);
}

bool pertence(conjunto X, int z) { return busca(X, z); }

conjunto uniao(conjunto X, conjunto Y) {

  conjunto uniao, no, nox;

  // criando um novo conjunto
  uniao = criaconjunto();

  // inserindo todos os elementos de X  na uniao
  nox = X->prox;
  while (nox != NULL) {
    insere(uniao, nox->conteudo);
    nox = nox->prox;
  }

  // inserindo todos os elementos de Y na uniao
  no = Y->prox;
  while (no != NULL) {
    // a função inserir já trata elementos repetidos
    insere(uniao, no->conteudo);
    no = no->prox;
  }

  return uniao;
}

conjunto interseccao(conjunto X, conjunto Y) {
  // criando um novo conjunto
  conjunto nox, intersec;
  intersec = criaconjunto();

  // pecorre X e a cada elemento de X verifica se ele pertence a Y
  nox = X->prox;
  while (nox != NULL) {
    bool verificar = pertence(Y, nox->conteudo);

    // se ele pertencer a Y adiciona no novo conjunto
    if (verificar == 1)
      insere(intersec, nox->conteudo);

    nox = nox->prox;
  }
  return intersec;
}

void imprimelista(conjunto X) {

  conjunto p;
  p = X->prox;
  while (p != NULL) {
    printf("%i\n", p->conteudo);
    p = p->prox;
  }
}
// grupo 2
bool subconjunto(conjunto X, conjunto Y) {
  // percorre X e verifica se cada elemtnos de X pertence a Y
  // se não pertencer retorna falso
  conjunto nox = X->prox;
  while (nox != NULL) {
    bool verificar = pertence(Y, nox->conteudo);
    if (verificar == 0)
      return false;

    nox = nox->prox;
  }
  return true;
}

conjunto diferenca(conjunto X, conjunto Y) {
  // cria uma novo conjunto diferença e faz a união de X e Y
  // faz a intersecção de X e Y
  // percorre a intersecção e retira cada elemento da intersecção da
  // união
  conjunto no, diferenca, iguais;
  diferenca = uniao(X, Y);
  iguais = interseccao(X, Y);
  no = iguais->prox;
  while (no != NULL) {
    retira(diferenca, no->conteudo);
    no = no->prox;
  }
  free(no);
  free(iguais);
  return diferenca;
}

int cardinalidade(conjunto X) {
  // a cada elemento de X conta +1
  conjunto no = X->prox;
  int cont = 0;
  while (no != NULL) {
    cont++;
    no = no->prox;
  }
  return cont;
}

bool vazio(conjunto X) {
  // se o primeiro elementos de X for vazio o X é vazio
  conjunto no = X->prox;
  if (no == NULL)
    return true;
  else
    return false;
}