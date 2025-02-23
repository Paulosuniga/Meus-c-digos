 /******************************************************************************
//     listaLigadaD2.c
// Este programa gerencia listas lineares duplamente ligadas 
//   (implementacao dinamica).
// As listas gerenciadas podem ter um numero arbitrario de elementos.
// N�o usaremos sentinela nesta estrutura.
******************************************************************************/
#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
  // outros campos...
} REGISTRO;


typedef struct aux{
  REGISTRO reg;
  struct aux *ant, *prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
  PONT inicio;
} LISTA;

/* Inicializa��o da lista ligada (a lista jah esta criada e eh apontada 
pelo endereco em l) */
void inicializarLista(LISTA* l){
  l->inicio = NULL;
} /* inicializarLista */

/* Exibi��o da lista seq�encial */
void exibirLista(LISTA* l){
  PONT end = l->inicio;
  printf("Lista: \" ");
  while (end != NULL){
    printf("%d ", end->reg.chave); // soh lembrando TIPOCHAVE = int
    end = end->prox;
  }
  printf("\"\n");
} /* exibirLista */ 


/* Verifica consistencia da lista duplamente ligada */
bool verificarListaDuplamenteLigada(LISTA* l){
  bool res = true;
  if (!l->inicio) return res;
  PONT ant;
  PONT pos = l->inicio;
  if (pos->ant){
    res = false;
    printf("Problema na verificacao (1): endereco anterior do primeiro elemento difere de NULL.\n");                
  }
  while (pos != NULL){
    ant = pos;
    pos = pos->prox;
    if (pos && pos->ant != ant){
      printf("TESTE %p x %p.\n", pos->ant, ant);    
      printf("Problema na verificacao (1): endereco anterior do elemento %i difere do endereco de %i: %p x %p.\n", pos->reg.chave, ant->reg.chave, pos->ant, ant);
      res = false;
    }
  }
  return res;
} /* verificarListaDuplamenteLigada */ 

/* Retornar o tamanho da lista (numero de elementos) */
int tamanho(LISTA* l) {
  PONT end = l->inicio;
  int tam = 0;
  while (end != NULL){
    tam++;
    end = end->prox;
  }
  return tam;
} /* tamanho */

/* Retornar o tamanho em bytes da lista. Neste caso, isto depende do numero
   de elementos que estao sendo usados.   */
int tamanhoEmBytes(LISTA* l) {
  return(tamanho(l)*sizeof(ELEMENTO))+sizeof(LISTA); // sizeof(LISTA) = sizeof(PONT) pois a "LISTA" possui apenas um ponteiro para o 1o elemento
} /* tamanhoEmBytes */

/* Busca sequencial (lista ordenada ou nao) */
PONT buscaSequencial(LISTA* l, TIPOCHAVE ch){
  PONT pos = l->inicio;
  while (pos != NULL){
    if (pos->reg.chave == ch) return pos;
    pos = pos->prox;
  }
  return NULL;
} /* buscaSequencial */


/* Busca sequencial (lista ordenada) */
PONT buscaSeqOrd(LISTA* l, TIPOCHAVE ch){
  PONT pos = l->inicio;
  while (pos != NULL && pos->reg.chave < ch) pos = pos->prox;
  if (pos != NULL && pos->reg.chave == ch) return pos;
  return NULL;
} /* buscaSequencial */

/* Busca sequencial - funcao de exclusao (retorna no endere�o *ant o indice do
   elemento anterior ao elemento que est� sendo buscado [ant recebe o elemento
   anterior independente do elemento buscado ser ou n�o encontrado]) */
PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant){
  *ant = NULL;
  PONT atual = l->inicio;
  while (atual != NULL && atual->reg.chave<ch){
    *ant = atual;
    atual = atual->prox;
  }
  if ((atual != NULL) && (atual->reg.chave == ch)) return atual;
  return NULL;
}
/* buscaSequencialExc */

/* Exclus�o do elemento de chave indicada */
bool excluirElemLista(LISTA* l, TIPOCHAVE ch){
  PONT ant, i;
  i = buscaSeqExc(l,ch,&ant);
  if (i == NULL) return false;
  if (ant == NULL) l->inicio = i->prox;
  else ant->prox = i->prox;
  if (i->prox) i->prox->ant = ant;
  free(i);
  return true;
} /* excluirElemLista */

/* Destrui��o da lista sequencial 
   libera a memoria de todos os elementos da lista*/
void reinicializarLista(LISTA* l) {
  PONT end = l->inicio;
  while (end != NULL){
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  l->inicio = NULL;
} /* destruirLista */


/* Inser��o em lista ordenada sem duplica��o */
bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {


  TIPOCHAVE ch = reg.chave;
  PONT ant, i;
  i = buscaSeqExc(l,ch,&ant);
  if (i != NULL)  return false;
  i = (PONT) malloc(sizeof(ELEMENTO));
  i->reg = reg;
 if (ant == NULL) {
    i->prox = l->inicio; // prox do novo elemento aponta pro antigo primeiro elemento

    l->inicio->ant = i; // anterior do antigo primeiro elemento aponta pro novo elemento

    l->inicio = i; // inicio da lista aponta pra o novo elemento

    i->ant = NULL; // anterior do novo elemento aponta pra null
  } else { // inser??o ap?s um elemento j? existente
    i->prox = ant->prox; // prox do novo elemento aponta pro proximo do anterior

    if (ant->prox != NULL) {
      ant->prox->ant = i; // ponteiro anterior do proximo elemento aponta pro novo elemento
    }

    ant->prox = i; // ponteiro proximo do anterior aponta pro novo elemento

    i->ant = ant; // ponteiro anterior do novo elemento aponta pro elemento anterior
  }

  return true;
} /* inserirElemListaOrd */

/* retornarPrimeiro - retorna o endereco do primeiro elemento da lista e (caso
   a lista nao esteja vazia) retorna a chave desse elemento na memoria 
   apontada pelo ponteiro ch */
PONT retornarPrimeiro(LISTA* l, TIPOCHAVE *ch){
  if (l->inicio != NULL) *ch = l->inicio->reg.chave;
  return l->inicio;
} /* retornarPrimeiro */

/* retornarUltimo - retorna o endereco do ultimo elemento da lista e (caso
   a lista nao esteja vazia) retorna a chave desse elemento na memoria 
   apontada pelo ponteiro ch */
PONT retornarUltimo(LISTA* l, TIPOCHAVE *ch){
  PONT ultimo = l->inicio;
  if (l->inicio == NULL) return NULL;
  while (ultimo->prox != NULL) ultimo = ultimo->prox;
  *ch = ultimo->reg.chave;
  return ultimo;
} /* retornarUltimo */

void inserir(LISTA *l){
  TIPOCHAVE ch;
  scanf("%i",&ch);
  REGISTRO reg;
  reg.chave = ch;
  if (inserirElemListaOrd(l,reg)) printf("Elemento %i inserido corretamente.\n",ch);
  else printf("Nao foi possivel inserir elemento %i.\n",ch);
}

void buscar(LISTA *l){
  TIPOCHAVE ch;
  scanf("%i",&ch);
  PONT posicao = buscaSeqOrd(l,ch);
  if (posicao != NULL) printf("Elemento %i encontrado no endereco %p.\n",ch,posicao);
  else printf("Nao foi possivel encontrar elemento %i\n",ch);
}

void exibirPrimeiro(LISTA *l){
  TIPOCHAVE ch;
  PONT posicao = retornarPrimeiro(l,&ch);
  if (posicao != NULL) printf("Primeiro elemento %i encontrado no endereco %p.\n",ch,posicao);
  else printf("Nao foi possivel encontrar o primeiro elemento (lista vazia).\n");
}

void exibirUltimo(LISTA *l){
  TIPOCHAVE ch;
  PONT posicao = retornarUltimo(l,&ch);
  if (posicao != NULL) printf("Ultimo elemento %i encontrado no endereco %p.\n",ch,posicao);
  else printf("Nao foi possivel encontrar o ultimo elemento (lista vazia).\n");
}

void excluir(LISTA *l){
  TIPOCHAVE ch;
  scanf("%i",&ch);
  if (excluirElemLista(l,ch)) printf("Elemento %i excluido corretamente.\n",ch);
  else printf("Nao foi possivel excluir elemento %i.\n",ch);
}

void exibir(LISTA *l){
  exibirLista(l);
}


void verificarLista(LISTA *l){
  if (verificarListaDuplamenteLigada(l)){
    printf("Verificacao bem sucedida.\n");                                       
  }else printf("A verificacao retornou erro.\n");                                       
}

void meuLog(LISTA *l){
  printf("Numero de elementos na lista: %i.\n",tamanho(l));
  printf("Tamanho da lista (em bytes): %i.\n",tamanhoEmBytes(l));
}

void help(){
  printf("Comandos validos: \n");
  printf("   i <chave1>: inserir elemento com chave=chave1\n");
  printf("   e <chave1>: excluir elemento com chave=chave1\n");
  printf("   p : imprimir lista\n");
  printf("   d : destruir (zerar) lista\n");
  printf("   l : exibir log de utilizacao da lista\n");
  printf("   h : exibir esta mensagem de ajuda\n");
  printf("   b <chave1>: exibir posicao do elemento com chave=chave1\n");
  printf("   0 : exibir a chave e o endereco do primeiro elemento\n");
  printf("   u : exibir a chave e o endereco do ultimo elemento\n");
  printf("   v : verificar se a lista duplamente ligada esta consistente\n");
}

void destruir(LISTA *l){
     reinicializarLista(l);
     printf("Lista zerada.\n");
}

int main(){
  LISTA lista;
  inicializarLista(&lista);
  help();
  char comando = ' ';
  scanf("%c",&comando);
  while (comando != 'q'){
    switch (comando) {
      case 'i' : inserir(&lista); break;
      case 'e' : excluir(&lista); break;
      case 'p' : exibir(&lista); break;
      case 'd' : destruir(&lista); break;
      case 'l' : meuLog(&lista); break;
      case 'h' : help(); break;
      case 'b' : buscar(&lista); break;
      case '0' : exibirPrimeiro(&lista); break;
      case 'u' : exibirUltimo(&lista); break;
      case 'v' : verificarLista(&lista); break;

      default: {while (comando != '\n') scanf("%c",&comando);};
    } 
    scanf("%c",&comando);
  }

  return 0;
}

