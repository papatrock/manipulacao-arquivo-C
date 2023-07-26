#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "liblista.h"
#define LINESIZE 1024
  

void readLog(struct dirent *entity, char dirname[LINESIZE],lista_t *listaBicicleta,listaChar_t *listaNomes);

void readDir (char dirname[LINESIZE], lista_t *listaBicicleta,listaChar_t *listaNomes);

bicicleta_t *readHeader(char fileName[LINESIZE], char linha[LINESIZE],char linha2[LINESIZE],lista_t *listaBicicleta,listaChar_t *listaNomes);

int insereBarra(char string[LINESIZE]);

void menu ();

void adicionaAtributo(bicicleta_t *bicicleta, char linha[LINESIZE],dados_t *dados);

int totalPercorrido(lista_t *lista);

void imprimeNomeBici(listaChar_t *lista);

void resumo(lista_t *listaBicicleta,char nome[LINESIZE]);

void ordenaPorDistancia(lista_t *lista);

void ordenaPorData(lista_t *lista);

void trocaStruct (nodo_l_t *a,nodo_l_t *b);

void ordenaPorSubida(lista_t *lista);

void histograma(lista_t *lista,char nome[LINESIZE]);

int maiorValor(lista_t *lista,char nome[LINESIZE]);

int menorValor(lista_t *lista,char nome[LINESIZE]);