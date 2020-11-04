#include<stdio.h>
#include<stdlib.h>

int main(){

    FILE *file;
    int i,a [5] = {0,1,2,3,434};
    char string[13];

    file = fopen("nomeDoArquivo.aul", "r+");
    if (file == NULL){
        printf("Deu caca! -- Veja se não esta usando o R+\n");
        return 1;
    }

    for (i=0; i< 5; i++){
        fprintf(file, "%d\n", a[i]);
    }
    fclose(file);

    file = fopen("nomeDoArquivo.aul", "r");
    if (file == NULL){
        printf("Deu caca!\n");
        return 1;
    }

    for (i=0; i< 5; i++){
        fscanf(file, "%d\n", &a[i]);
        printf("lemos: %d\n", a[i]);
    }

   //fget -> char by char
   //fgets -> linha, ou o tamanho que passarmos como parametro.
   //fscanf - > lê qualquer coisa.

    fclose(file);


    return 0;
}