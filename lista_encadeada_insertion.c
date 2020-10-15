/*
    author: gschreiner

    Este é um código simples de implementação de uma lista duplamente encadeada utilizando duas estruturas. 
    Também foi desenvolvida uma solução para ordenação dos elementos, utilizando o método de ordenção de insetion sort;
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ItemLista {
    int valor;
    
   struct ItemLista *next;
   struct ItemLista *prev;
};
typedef struct ItemLista ItemLista;

typedef struct {
    ItemLista *head; //primeiro elemento da lista.
    ItemLista *tail; //o último elemento da lista.
} Lista;


#define MAX 100

/*
 Adiciona um elemento na lista em qualquer posição.
 Recebe como parametros a lista onde o elemento é inserido, o elemento anterior ao inserido e o elemento a ser inserido
*/
void adicionaElemento(Lista *lista, ItemLista *itemAnterior, ItemLista *elemento){
    
    if (itemAnterior == NULL){ //trocar a cabeça da lista, adicionar antes do primeiro elemento
        lista->head->prev = elemento; //anterior da cabeça aponta para o novo
        elemento->next = lista->head; //proximo do novo, é a cabeça da lista
        elemento->prev = NULL; //anterior do novo é nada.

        lista->head = elemento; //atualiza a cabeça da lista.
        return;
    }

    ItemLista *itemProximo = itemAnterior->next; //se itemAnterior == null , segmentation fault
    if (itemProximo == NULL){ // ele é o tail, final da lista
        itemAnterior->next = elemento;
        elemento->prev = itemAnterior;
        elemento->next = NULL;
        lista->tail = elemento;
    } else{ //qualquer elemento menos o último
        itemAnterior->next = elemento;
        elemento->prev = itemAnterior;
        elemento->next = itemProximo;
        itemProximo->prev = elemento;
        
        //  Fazer encadeamento sem variavel auxiliar.
        //elemento->next = itemAnterior->next;
        //elemento->next->prev = elemento;
        //itemAnterior->next = elemento;
        //elemento->prev = itemAnterior;
    }

    //itemProximo->prev = elemento;

}



/*
* Método responsável por criar a lista. Recebe como parâmetro a estrutura da lista e o número de elementos que será gerado.
*/
void criaLista (Lista *lista, int size){
    ItemLista *aux;

    srand((unsigned)time(NULL));
    for(int i = 0; i< size; i++){
        aux = (ItemLista *) malloc (sizeof(ItemLista));
        aux->valor = rand()%MAX;
        aux->next = NULL;
        aux->prev = NULL;

        if (lista->head == NULL){ //lista vazia
            lista->head = aux;
            lista->tail = aux;
        }else{ //faz encadeamento
            adicionaElemento(lista, lista->tail, aux);
        }
    }

}

/*
* Método que imprime a lista. Recebe como parâmetro a lista a ser impressa na tela, 
*   e um interio que define a ordem de apresentação (caso > 0 imprime em ordem de inserção, 
    caso contrário imprime em ordem inversa a inserção)
*/
void imprimeLista(Lista *lista, int order){
    ItemLista *aux;
    if (order > 0){
        for (aux=lista->head; aux != NULL; aux = aux->next){
            printf("%d, ", aux->valor);
        }
    } else {
        for (aux=lista->tail; aux != NULL; aux = aux->prev){
            printf("%d, ", aux->valor);
        }
    }

}


void insertionSort(Lista *lista){
    ItemLista *i, *j, *elemento, *aux, *aux2;


    for (i=lista->head->next; i != NULL; i = i->next){
        printf("lista: \n");
        imprimeLista(lista,1);
        printf("\n-----: \n");
        for(j = i->prev; j != NULL; j = j->prev ){
            printf("Comapra: %d %d\n", j->valor, i->valor);
            getc(stdin);
            if (j->valor <= i->valor){
                printf("Quer fazer swap\n");
                aux = i->prev; //anterior do atuals
                i->prev = j; // anterior do elemento é o j;
                aux->next = i->next; //meu ex anterior, aponta para o meu proximo.
                aux->next->prev = aux; //meu proximo, agora aponta pro meu ex anterior
                j->next->prev = i;
                i->next = j->next;
                j->next = i;
                i = aux->next;
                break;
            }        
        }
        if (j == NULL){ //foi até a cabeça da lista
            //aux2 = i->next;
            aux = i->prev;
            aux->next = i->next;
            aux->next->prev = aux;
            i->next = lista->head;
            lista->head->prev = i;
            i->prev = NULL;
            lista->head = i;
            i = aux;
        } 

    }

}

int main(){

    Lista *lista = NULL;
    
    lista = (Lista * ) malloc (sizeof(Lista)); //aloca espaço para a lista
    lista->head = NULL;
    lista->tail = NULL;
    
    
    criaLista(lista, 5);


    
    
    printf("Primeiro elemento %d;\n Ultimo Elemento: %d\n\n", lista->head->valor, lista->tail->valor);

    printf("Ordem de inserção: \n");
    imprimeLista(lista, 1);

    printf("\n\n COmeço da ordenação\n");
    insertionSort(lista);
    printf("\n\n Fim da ordenação\n");

    printf("\nApós adicionar o -23: \n");
    imprimeLista(lista, 1);
    printf("\n");

    return 0;
}