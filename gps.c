#include <stdio.h>
#include "funcao.h"
#include "liblista.h"
     

     
int main (int argc, char *argv[]){
  lista_t *listaBicicleta;
  listaChar_t *listaNomes;
  nodoChar_t *tmp;
  int escolha,escolha2,totalPerco;

  if(argc != 2){
    printf("Falta parametros para iniciar a função\n");
    return 1;
  }

  listaBicicleta = lista_cria();
  listaNomes = listaCriaChar();

  printf("Programa em execução...\n\n");
  readDir(argv[1],listaBicicleta,listaNomes);
  printf("Sumario:\nQuatidade de atividades:%d\n",listaBicicleta->tamanho);
  printf("Total percorrido:%d Km\n",totalPerco = totalPercorrido(listaBicicleta));
  printf("Pedal mais longo:%d Km\n",pedalMaisLongo(listaBicicleta));
  printf("Pedal mais curto:%d Km\n",pedalMaisCurto(listaBicicleta));
  printf("Distância media:%d km\n\n",totalPerco/listaBicicleta->tamanho);
  menu();
  printf("Digite a opção desejada:");
  scanf("%d",&escolha);

  /*ARRUMAR O LOOP*/
  while(escolha){
    switch (escolha)
    {
    case (1):
      imprimeNomeBici(listaNomes);
    break;

    case (2):
      imprimeNomeBici(listaNomes);
      printf("Digite o numero da bicicleta desejada:");
      scanf("%d",&escolha2);
      tmp = listaNomes->ini;
      for(int i=2;i <= escolha2;i++){
        if(tmp == NULL){
          printf("Escolha invalida\n");
          break;
        }
        tmp = tmp->prox;
      }
      resumo(listaBicicleta,tmp->nome);

    break;

    case (3):
      imprimeNomeBici(listaNomes);
      printf("Digite o numero da bicicleta desejada:");
      scanf("%d",&escolha2);

      tmp = listaNomes->ini;
      for(int i=2;i <= escolha2;i++){
        if(tmp == NULL){
          printf("Escolha invalida\n");
          break;
        }
        tmp = tmp->prox;
      }
      ordenaPorData(listaBicicleta);
      resumo(listaBicicleta,tmp->nome);

    break;

    case(4):
      imprimeNomeBici(listaNomes);
      printf("Digite o numero da bicicleta desejada:");
      scanf("%d",&escolha2);
      tmp = listaNomes->ini;
      for(int i=2;i <= escolha2;i++){
        if(tmp == NULL){
          printf("Escolha invalida\n");
          break;
        }
        tmp = tmp->prox;
      }

      ordenaPorDistancia(listaBicicleta);
      resumo(listaBicicleta,tmp->nome);
          
    break;

    case(5):
      imprimeNomeBici(listaNomes);
      printf("Digite o numero da bicicleta desejada:");
      scanf("%d",&escolha2);
      tmp = listaNomes->ini;
      for(int i=2;i <= escolha2;i++){
        if(tmp == NULL){
          printf("Escolha invalida\n");
          break;
        }
        tmp = tmp->prox;
      }

      ordenaPorSubida(listaBicicleta);
      resumo(listaBicicleta,tmp->nome);
    break;

    case(6):
      imprimeNomeBici(listaNomes);
      printf("Digite o numero da bicicleta desejada:");
      scanf("%d",&escolha2);
      tmp = listaNomes->ini;
      for(int i=2;i <= escolha2;i++){
        if(tmp == NULL){
          printf("Escolha invalida\n");
          break;
        }
        tmp = tmp->prox;
      }
      histograma(listaBicicleta,tmp->nome);
    break;

    case(7):
      menu();
    break;
    
    default:
    printf("Valor invalido\n");
      break;
    }
  printf("Digite a opção desejada:");
  scanf("%d",&escolha);
  }


  lista_destroi(listaBicicleta);
  listaDestroiChar(listaNomes);
  
  return 0;
}


