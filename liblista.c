
#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"
#include "funcao.h"

nodo_l_t* cria_nodo(bicicleta_t *elemento){
    nodo_l_t * nodo;
    if(!(nodo = malloc(sizeof(nodo_l_t))))
        return NULL;
    nodo->elemento = elemento;
    nodo->prox = NULL;
    return nodo;
}

nodoChar_t *criaNodoChar(char *nome){
    nodoChar_t *nodo;
    if(!(nodo = malloc(sizeof(nodoChar_t))))
        return NULL;
    strcpy(nodo->nome,nome);
    nodo->prox = NULL;
    return nodo;
}

lista_t* lista_cria (){
    lista_t* lista;

    if(!(lista = malloc (sizeof(lista_t))))
        return NULL;
    
    lista->ini = NULL;
    lista->tamanho = -1;
    return lista;
}

listaChar_t *listaCriaChar(){
    listaChar_t *lista;

    if(!(lista = malloc(sizeof(listaChar_t))))
        return NULL;
    lista->ini = NULL;
    return lista;
}


lista_t* lista_destroi (lista_t* lista){
    nodo_l_t *tmp,*anterior;
    if(lista_vazia(lista)){
        free (lista);
        return NULL;
    }
    
    tmp = lista->ini;
    /*percorre free em todos os nos*/
    while(tmp != NULL){
        anterior = tmp;
        tmp = tmp->prox;
        free(anterior->elemento);
        free(anterior);
    }

    free(lista);
    return NULL;
}

listaChar_t *listaDestroiChar(listaChar_t *lista){
    nodoChar_t *tmp,*anterior;
    if(lista->ini == NULL){
        free(lista);
        return NULL;
    }
    tmp = lista->ini;

    while(tmp->prox != NULL){
        anterior = tmp;
        tmp = tmp->prox;
        free(anterior);
    }
    free(tmp);
    free(lista);
    return NULL;

}

int lista_vazia (lista_t* lista){
    if (lista->ini != NULL)
        return 0;
    return 1;
}

int lista_tamanho (lista_t* lista){
    return lista->tamanho;
}

int lista_insere_inicio (lista_t* lista, bicicleta_t *elemento){
    nodo_l_t *tmp;
    if(! (tmp = cria_nodo(elemento)))
        return 0;
    /*tmp -> prox aponta para o inicio antigo*/
    tmp->prox = lista->ini;
    lista->ini = tmp;
    lista->tamanho++;
    return 1;

}

int lista_insere_fim (lista_t* lista, bicicleta_t *elemento){
    nodo_l_t *novo,*tmp;
    /*verifica se a lista está vazia, se sim insere no inicio*/
    if(lista->ini == NULL){
        lista_insere_inicio(lista,elemento);
        lista->tamanho++;
        return 1;
    }

    if(! (novo = cria_nodo(elemento)))
        return 0;
    tmp = lista->ini;
    /*percorre a lista até achar o ultimo elemento, cujo pro->NULL*/
    while (tmp->prox != NULL)
        tmp = tmp->prox;
    tmp->prox = novo;
    lista->tamanho++;

    return 1;

}

int listaInsereNome (listaChar_t* lista,char *nome ){
    nodoChar_t *novo,*tmp;
    /*verifica se a lista está vazia, se sim insere no inicio*/
    if(! (novo = criaNodoChar(nome)))
        return 0;
    if(lista->ini == NULL){
        lista->ini = novo;
        return 1;
    }

    tmp = lista->ini;
    /*percorre a lista até achar o ultimo elemento, cujo pro->NULL*/
    while (tmp->prox != NULL)
        tmp = tmp->prox;
    tmp->prox = novo;
    return 1;
}

int lista_insere_ordenado (lista_t* lista, bicicleta_t *elemento){
    nodo_l_t *novo,*tmp,*anterior;

    if(lista->ini == NULL){
        lista_insere_inicio(lista,elemento);
        return 1;
    }

    if(!(novo = cria_nodo(elemento)))
        return 0;
    /*tmp percorre a lista e o anterior aponta para o elemento anterior que tmp passou*/
    tmp = lista->ini;
    while (tmp->elemento <= elemento && tmp->prox != NULL){
        anterior = tmp;
        tmp = tmp->prox;
    }
    /*verifica se o local de insercao é o ultimo, se sim insere no fim*/
    if (tmp->prox == NULL){
        lista_insere_fim(lista,elemento);
        return 1;
    }
    if(tmp == lista->ini){
        lista_insere_inicio(lista,elemento);
        return 1;
    }

    anterior->prox = novo;
    novo->prox = tmp;
    lista->tamanho++;
    return 1;
}

bicicleta_t *lista_retorna_elemento (lista_t *lista, char *nomeBici){
    /*verifica se a lista está vazia antes de retirar*/
    if(lista_vazia(lista))
        return NULL;
    
    
    /*verifica se o elemento pertence a lista antes de retira-lo*/
    /*if(!lista_pertence(lista,elemento->name))
        return NULL;*/
    /*verifica se o elemento é o primeiro da lista, se sim remove inicio*/
    if(strcmp(lista->ini->elemento->name,nomeBici))
        return lista->ini->elemento;

    nodo_l_t *tmp = lista->ini;
    while (!(strcmp(tmp->elemento->name,nomeBici))&& tmp->prox != NULL){
        tmp = tmp->prox;
    }
    printf("elemento a ser retornado: %s\n",tmp->elemento->name);
   
    return tmp->elemento;  
}


int lista_pertence (listaChar_t* lista,char *nomeBic){
    nodoChar_t *tmp = lista->ini;
    /*tmp percorre a lista*/
    while(tmp != NULL){
        if (!(strcmp(tmp->nome,nomeBic)))
            return 1;
        tmp = tmp->prox;
    }
    return 0;
}

