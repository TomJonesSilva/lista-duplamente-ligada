#include "stdbool.h"
#include <stdio.h>
struct lista {
  int conteudo;
  struct lista *prox;
  struct lista *ant;
};

typedef struct lista *conjunto; // célula

//insere um inteiro z na lista
void insercao (conjunto X, int z);
//verificar se o inteiro z esta na lista
bool busca (conjunto X,int z);
//retira um elemento z da lista
void retirar(conjunto X, int z);