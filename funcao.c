#include <stdio.h>
#include <string.h>
#include "funcao.h"
#include "liblista.h"

int insereBarra(char string[LINESIZE]){
    int i;
    for(i=0;string[i]!='\0';i++){}
    string[i]='/';
    string[i+1]='\0';
    return 1;
}

void menu (){

  printf("1.Mostrar bicicletas encontradas.\n");
  printf("2.Ver resumo da bicicleta.\n");
  printf("3.Listar atividades ordenadas pela data.\n");
  printf("4.Listar atividades ordenadas pela distância.\n");
  printf("5.Listar atividades ordenadas pela subida acumulada.\n");
  printf("6.Histograma.\n");
  printf("7.Imprimir menu\n");
  printf("0.Sair\n");
}
  
bicicleta_t *criaBicicleta(){
    bicicleta_t *bicicleta;

    if(!(bicicleta = malloc(sizeof(bicicleta_t))))
        return NULL;
    
    bicicleta->distancia = 0;
    bicicleta->veloMed = 0;
    bicicleta->veloMax = 0;
    bicicleta->HrMedio = 0;
    bicicleta->HrMax = 0;
    bicicleta->cadenciaMed = 0;
    bicicleta->subidaAcu = 0;
    return bicicleta;

}

dados_t *criaDados(){
  dados_t *dados;

  if(!(dados = malloc(sizeof(dados_t))))
    return NULL;

  dados->speed = 0;
  dados->maxSpeed = 0;
  dados->timestamp = 0;
  dados->speedxTimestamp = 0;
  dados ->somaTempo = 0;
  dados->heartRate = 0;
  dados->heartRatexTimestamp = 0;
  dados->hearRateMax = 0;
  dados->distance = 0;
  dados->cadence = 0;
  dados->cadencexTimestamp = 0;
  dados->altitudeIni = 0;
  dados->altitude = 0;

  return dados;
}

void imprimeNomeBici(listaChar_t *lista){
  nodoChar_t *tmp = lista->ini;
  int i = 1;
  printf("Bicicletas encontradas:\n");
  while (tmp != NULL){
    printf("%d:",i);
    printf("%s",tmp->nome);
    i++;
    tmp = tmp->prox;
  }
  printf("\n");


}

void adicionaAtributo(bicicleta_t *bicicleta, char linha[LINESIZE],dados_t *dados){
  bicicleta->veloMed = (dados->speedxTimestamp / dados->somaTempo) * 3.6;
  bicicleta->veloMax = dados->maxSpeed * 3.6;
  bicicleta->HrMedio = dados->heartRatexTimestamp / dados->somaTempo;
  bicicleta->HrMax = dados->hearRateMax;
  bicicleta->distancia = dados->distance / 1000;
  bicicleta->cadenciaMed = dados->cadencexTimestamp / dados->somaTempo;
  bicicleta->subidaAcu = dados->altitude;
  return ;
}

/*VERIFICAR SE CHAR LINHA[] ESTA CERTO*/
void leDados(dados_t *dados,char linha[LINESIZE]){
  char *token = strtok(linha,": ");
  double val;

  if(!(strcmp(token,"speed"))){
    token = strtok(NULL,": ");//valor em m/s
    val = atof(token);
    if(val > dados->maxSpeed)
      dados->maxSpeed = val;
    dados->speed = val;

  }

  else if(!(strcmp(token,"heart_rate"))){
    token = strtok(NULL,": ");//valor em bpm
    val = atof(token);
    if(val > dados->hearRateMax)
      dados->hearRateMax = val;
    dados->heartRate = val;
    
  }

  else if(!(strcmp(token,"distance"))){
    token = strtok(NULL,": ");//distancia em metros
    val = atof(token);
    if(val > dados->distance)
      dados->distance =val;    
  }

  else if(!(strcmp(token,"cadence"))){
    token = strtok(NULL,": ");//cadencia em rpm
    val = atof(token);
    dados->cadence = val;

  }

  else if(!(strcmp(token,"altitude"))){
    token = strtok(NULL,": ");//cadencia em rpm
    val = atof(token);

    if(dados->altitudeIni == 0)
      dados->altitudeIni = val;
    else{
      if(val > dados->altitudeIni)
        dados->altitude = dados->altitude + (val - dados->altitudeIni);
      dados->altitudeIni = val;
    }

  }

  else if(!(strcmp(token,"timestamp"))){
    double hr,min,seg;
    token = strtok(NULL,": ");//data
    token = strtok(NULL,": ");//horas
    hr = atof(token);
    token = strtok(NULL,": ");//minutos
    min = atof(token);
    token = strtok(NULL,": ");//segundo
    seg = atof(token);

    dados->timestamp = (3600 * hr) + (min * 60) + seg;
    dados->somaTempo = dados->somaTempo + dados->timestamp;
    if(dados->speed != 0)
      dados->speedxTimestamp = dados->speedxTimestamp + dados->speed * dados->timestamp;
    
    if (dados->heartRate != 0)
      dados->heartRatexTimestamp = dados->heartRatexTimestamp + dados->heartRate * dados->timestamp;
    
    if(dados->cadence != 0)
      dados->cadencexTimestamp = dados->cadencexTimestamp + dados->cadence * dados->timestamp;
  
  }

}

/*funcao que vai verificar se a bicicleta já está na lista, se sim retorna-a, se ñ cria e retorna (SEM ATUALIZAR LISTA) */
bicicleta_t *readHeader(char fileName[LINESIZE], char linha[LINESIZE],char linha2[LINESIZE],lista_t *listaBicicleta,listaChar_t *listaNomes){
  char *token = strtok(linha,":");
  char *token2,tmp[LINESIZE];
  bicicleta_t *bicicleta;
  bicicleta =  criaBicicleta();

  if(!(bicicleta))
    return NULL;

  while (token){
    if (!(strcmp(token,"Gear"))){
      token = strtok(NULL,":");
        strcpy(bicicleta->name, token);
      if(!(lista_pertence(listaNomes,token))){
        if(!(listaInsereNome(listaNomes,token))){
          printf("erro ao adicionar a lista\n");
          return NULL;
        }
      }


    }
    token = strtok(NULL,":");
    }

  token2 = strtok(linha2,":"); 

  while (token2){

      /*AQUI TEM O HORARIO TBM QUE DEVE SER PROCESSADO*/
      if(!(strcmp(token2,"Date"))){
      token2 = strtok(NULL,": ");//mes
      /*converte mês escrito em numerico*/
      if(!(strcmp(token2,"Jan")))
        token2 = "01";
      else if (!(strcmp(token2,"Feb")))
        token2 = "02";
      else if (!(strcmp(token2,"Mar")))
        token2 = "03";
      else if (!(strcmp(token2,"Apr")))
        token2 = "04";
      else if (!(strcmp(token2,"May")))
        token2 = "05";
      else if (!(strcmp(token2,"Jun")))
        token2 = "06";
      else if (!(strcmp(token2,"Jul")))
        token2 = "07";
      else if (!(strcmp(token2,"Aug")))
        token2 = "08";
      else if (!(strcmp(token2,"Sep")))
        token2 = "09";
      else if (!(strcmp(token2,"Oct")))
        token2 = "10";
      else if (!(strcmp(token2,"Nov")))
        token2 = "11";
      else if (!(strcmp(token2,"Dec")))
        token2 = "12";

      strcpy(tmp,token2);
      insereBarra(tmp);
      strcpy(bicicleta->date, tmp);
      token2 = strtok(NULL,": ");//dia
      strcat(bicicleta->date,token2);

    }
    token2 = strtok(NULL,":");

  }
  return bicicleta;
}

void readLog(struct dirent *entity, char dirname[LINESIZE],lista_t *listaBicicleta,listaChar_t *listaNomes){
  FILE *arq;
  bicicleta_t *bicicleta;
  int lc=1;
  char linha[LINESIZE+1],arquivo[LINESIZE],path[LINESIZE];
  dados_t *dados = criaDados();

  /*getcwd retorna o path do diretorio atual e coloca em path*/
  if(!(getcwd(path,sizeof(path))))
    return;

  /*colocar um / no fim do path*/
  insereBarra(path);
  /*strcat concatena a + b*/
  strcat(path,dirname);
  
  /*concatena path + entity->d_name (nome do arquivo) e salva na variavel arquivo*/  
  strcat(strcpy(arquivo,path),entity->d_name);
  /*nome do log em arquivo*/

  arq = fopen (arquivo, "r") ;
  if ( ! arq ){
      perror ("Erro ao abrir arquivo") ;
      return ;
  }

  fgets (linha,LINESIZE,arq);		
  while (!feof(arq)){
  /*Separa o titulo e a data verificando a linha*/
    if (lc<=2){
        char linha2[LINESIZE];
        fgets(linha2,LINESIZE,arq);
        bicicleta = readHeader(entity->d_name,linha,linha2,listaBicicleta,listaNomes);
        if (!(bicicleta)){
          printf("Erro ao criar bicicleta");
          return;
        }

        fgets (linha,LINESIZE,arq);
        lc = lc+2;
        continue;
    }

    /*ignora linhas vazias (strlen retorna tamanho da linha*/
    if (strlen(linha)<2){
      fgets (linha,LINESIZE,arq);
      lc++;
      continue;
    }
    /*remove os \n para arrumar visualização*/
    if (linha != NULL && linha[strlen(linha)-1] == '\n') 
      linha[strlen(linha)-1] = '\0';


    leDados(dados,linha);

    fgets (linha,LINESIZE,arq);		    
  }
  adicionaAtributo(bicicleta,linha,dados);
  lista_insere_fim(listaBicicleta,bicicleta);
  fclose (arq);
  free(dados);
  return;
}

void readDir (char dirname[LINESIZE], lista_t *listaBicicleta,listaChar_t *listaNomes){
  DIR *dir = opendir(dirname);
  if(dir == NULL){
    return ;
  }


  struct dirent *entity;
  entity = readdir(dir);

  while(entity != NULL){

    //printf("%hd %s %s\n",entity->d_type,dirname, entity->d_name);
    /*só chama a funcao se for do tipo arquivo*/
    if (entity->d_type == 8)
        readLog(entity,dirname,listaBicicleta,listaNomes);
    entity = readdir(dir);
  }
  closedir(dir);

}

int totalPercorrido(lista_t *lista){
  nodo_l_t *tmp;
  int soma = 0;
  tmp = lista->ini;

  while (tmp != NULL){
    soma = soma + tmp->elemento->distancia;
    tmp = tmp->prox;
  }
  return soma;
}

int pedalMaisLongo(lista_t *lista){
  nodo_l_t *tmp;
  int maior;
  tmp = lista->ini;
  maior = tmp->elemento->distancia;

  while(tmp != NULL){
    if(tmp->elemento->distancia > maior)
      maior = tmp->elemento->distancia;
    tmp = tmp->prox;
  }

  return maior;
}

int pedalMaisCurto(lista_t *lista){
  nodo_l_t *tmp = lista->ini;
  int menor = tmp->elemento->distancia;

  while(tmp != NULL){
    if(tmp->elemento->distancia < menor)
      menor = tmp->elemento->distancia;
    tmp = tmp->prox;
  }
  return menor;
}

void resumo(lista_t *listaBicicleta,char nome[LINESIZE]){
  nodo_l_t *tmp = listaBicicleta->ini;
  printf("Bicicleta: %s",nome);
  printf(" Data   Distância(km)   Velocidade Média   Velocidade Máxima(km/h)   HR Médio(bpm)   HR Máximo(bpm)   Cadência Média(rpm)   Subida Acumulada(m)\n");
  while (tmp != NULL){

    if(!(strcmp(tmp->elemento->name,nome))){
      printf(" %s      %.2f            %.2f                 %.2f                 %.0f             %.0f                %.0f                  %.2f\n",tmp->elemento->date,tmp->elemento->distancia,tmp->elemento->veloMed,tmp->elemento->veloMax,tmp->elemento->HrMedio,tmp->elemento->HrMax,tmp->elemento->cadenciaMed,tmp->elemento->subidaAcu);
            /* Data   Distância(km)   Velocidade Média   Velocidade Máxima(km/h)   HR Médio(bpm)   HR Máximo(bpm)   Cadência Média(rpm)   Subida Acumulada(m)*/
    }
  tmp = tmp->prox;
  }
}

void resumoPorData(lista_t *listaBicicleta,char nome[LINESIZE]){
  nodo_l_t *tmp = listaBicicleta->ini;
  printf("Bicicleta: %s",nome);
  printf(" Data   Distância(km)   Velocidade Média(km)   Velocidade Máxima(km/h)   HR Médio(bpm)   HR Máximo(bpm)   Cadência Média(rpm)   Subida Acumulada(m)\n");
  while (tmp != NULL){

    if(!(strcmp(tmp->elemento->name,nome))){
      printf(" %s      %.2f            %.2f                 %.2f                 %.0f             %.0f                %.0f                  %.2f\n",tmp->elemento->date,tmp->elemento->distancia,tmp->elemento->veloMed,tmp->elemento->veloMax,tmp->elemento->HrMedio,tmp->elemento->HrMax,tmp->elemento->cadenciaMed,tmp->elemento->subidaAcu);
            /* Data   Distância(km)   Velocidade Média   Velocidade Máxima(km/h)   HR Médio(bpm)   HR Máximo(bpm)   Cadência Média(rpm)   Subida Acumulada(m)*/
    }
  tmp = tmp->prox;
  }

}

void trocaStruct (nodo_l_t *a,nodo_l_t *b){
  nodo_l_t *tmp = cria_nodo(NULL);
  tmp->elemento = a->elemento;
  a->elemento = b->elemento;
  b->elemento = tmp->elemento;

  free(tmp);
}


void ordenaPorDistancia(lista_t *lista){
  int troca;
  nodo_l_t *ptr1;
  nodo_l_t *lptr = NULL;

  if(lista->ini->elemento == NULL){
    return;
  }

    do
    {
      troca = 0;
      ptr1 = lista->ini;

      while(ptr1->prox != lptr){
        if(ptr1->elemento->distancia > ptr1->prox->elemento->distancia){
          trocaStruct(ptr1,ptr1->prox);
          troca = 1;
        }
        ptr1 = ptr1->prox;
      }
    } while (troca);
}

void ordenaPorData(lista_t *lista){
  int troca;
  nodo_l_t *ptr1;
  nodo_l_t *lptr = NULL;

    do
    {
      troca = 0;
      ptr1 = lista->ini;
      while(ptr1->prox != lptr){
        if(atoi(ptr1->elemento->date) >atoi( ptr1->prox->elemento->date)){
          trocaStruct(ptr1,ptr1->prox);
          troca = 1;
        }
        ptr1 = ptr1->prox;
      }
    } while (troca);
}

void ordenaPorSubida(lista_t *lista){
  int troca;
  nodo_l_t *ptr1;
  nodo_l_t *lptr = NULL;

  if(lista->ini->elemento == NULL){
    return;
  }

    do
    {
      troca = 0;
      ptr1 = lista->ini;

      while(ptr1->prox != lptr){
        if(ptr1->elemento->subidaAcu > ptr1->prox->elemento->subidaAcu){
          trocaStruct(ptr1,ptr1->prox);
          troca = 1;
        }
        ptr1 = ptr1->prox;
      }
    } while (troca);
}

int menorValor(lista_t *lista,char nome[LINESIZE]){
  nodo_l_t *tmp = lista->ini;
  int menor = lista->ini->elemento->distancia;

  while(tmp != NULL){
    if(!(strcmp(tmp->elemento->name,nome))){
      if(tmp->elemento->distancia < menor)
        menor = tmp->elemento->distancia;
    }
    tmp = tmp->prox;
  }
  return menor;
}

int maiorValor(lista_t *lista,char nome[LINESIZE]){
  nodo_l_t *tmp = lista->ini;
  int maior = lista->ini->elemento->distancia;

  while(tmp != NULL){
    if(!(strcmp(tmp->elemento->name,nome))){
      if(tmp->elemento->distancia > maior)
        maior = tmp->elemento->distancia;
    }
    tmp = tmp->prox;
  }
  return maior;
}

void histograma(lista_t *lista,char nome[LINESIZE]){
  /*menor e maior faixa*/
  int menor,maior;
  nodo_l_t *tmp;

  menor = menorValor(lista,nome);
  maior = maiorValor(lista,nome);
  menor = (menor/10) * 10;
  maior = (maior/10) * 10 + 9;

  while(menor <= maior){
    printf(" %d - %d|",menor,menor+9);
    tmp = lista->ini;
    while(tmp != NULL){
      if(!(strcmp(tmp->elemento->name,nome))  && (tmp->elemento->distancia >= menor) && (tmp->elemento->distancia <= menor+9))
        printf("*");
      tmp = tmp->prox;
    }
    printf("\n");
    menor = menor + 10;
  }
  printf("        0123456789#123456789\n");
  printf("Distancia|    Quantidade\n");

}