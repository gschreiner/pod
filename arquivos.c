#include<stdio.h>
#include<stdlib.h>

struct pessoa {
    double altura;
    char nome[40];
    int idade;
    struct pessoa *next;
};
typedef struct pessoa Pessoa;


int main(){ 

    FILE *fileOrigem;

    Pessoa *headLista, *aux;

    headLista = (Pessoa *) malloc (sizeof(Pessoa));
    headLista->altura = 1.78;
    headLista->idade = 31;
    snprintf(headLista->nome, sizeof(headLista->nome), "%s", "Geomar"); //copia de string em c.
    headLista->next = NULL;

    aux = (Pessoa *) malloc (sizeof(Pessoa));
    aux->altura = 0.76;
    aux->idade = 540;
    snprintf(aux->nome, sizeof(aux->nome), "%s", "Yoda"); //copia de string em c.
    aux->next = NULL;

    headLista->next = aux;

    

    fileOrigem = fopen("nomeDoArquivo.aul", "wb");
    if (fileOrigem == NULL){
        printf("Deu caca!\n");
        exit(1);
    }

  //  fprintf(fileOrigem,"%s;", pes.nome);
  //  fprintf(fileOrigem,"%d\n", pes.idade);
   //Parametros fwrite (*variavel, tamanhoDaVariavel, n, *arquivo );
    for (aux = headLista; aux != NULL; aux = aux->next){
        fwrite(aux, sizeof(Pessoa), 1, fileOrigem);
    }
    

    fclose(fileOrigem);

    //limpando a lista. dando free na memória
    for (aux = headLista; aux != NULL; aux = headLista){
        headLista = aux->next;
       free(aux);
    }

   headLista = NULL;
    aux = NULL;

    Pessoa *ultimo = NULL;

    fileOrigem = fopen("nomeDoArquivo.aul", "r+b");
//     //Parametros fread(*variavel, tamanhoDaVariavel, n, *arquivo )
    aux = malloc (sizeof(Pessoa));
    while (fread(aux, sizeof(Pessoa), 1, fileOrigem) > 0){
        aux->next = NULL;
  
        if (headLista == NULL) //verifica se vai ser o primeiro
            headLista = aux;

        if (ultimo == NULL)  //controla o ultimo para encadear
            ultimo = aux;
        else{
            ultimo->next = aux;
            ultimo = aux;
        }
        aux = malloc (sizeof(Pessoa));
    }
    free(aux);


    
    for (aux = headLista; aux != NULL; aux = aux->next){
        printf("Pessoa lida: \n\tnome: %s \n\tidade: %d\n\taltura: %lf\n", aux->nome, aux->idade, aux->altura);     
    }
    

    fseek(fileOrigem, -(sizeof(Pessoa)), SEEK_END); //POSICIONADO CONFORME O FIM.
    aux = malloc (sizeof(Pessoa));
    fread(aux, sizeof(Pessoa), 1, fileOrigem);
    printf("\n\t> Nome: %s", aux->nome);

    snprintf(aux->nome, sizeof(aux->nome), "Novo_nome %s", aux->nome);
    aux->idade = 12;
    fseek(fileOrigem, 0, SEEK_SET); //POSICIONADO A PARTIR DO INICIO
    fwrite(aux, sizeof(Pessoa),1, fileOrigem);
    free(aux);

     fseek(fileOrigem, -sizeof(Pessoa) , SEEK_CUR); //A PARTIR DA POSIÇÃO ATUAL.
    aux = malloc (sizeof(Pessoa));
    fread(aux, sizeof(Pessoa), 1, fileOrigem);
    printf("\n\t> Nome: %s", aux->nome);

    fclose(fileOrigem);

    return 0;
}