// classifica a agenda pela idade Versão 1.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // funções de tempo para identificar melhor
                   // método
typedef struct agenda ag;

struct agenda
{
   char name[15];
   char address[30];
   int  age;
};

const int LEN = sizeof(ag);
const int MAXREC= 10;

void sort(ag *MyAg, size_t tam); // implementa inserção
void recTempFile(FILE *arq, FILE *aux, ag *MyAg, size_t tam);
void merge(ag *A, int p, int q, int r);
void mergeSort(ag *A, int p, int r);

int main()
{
   int qt, ts,i;
   size_t tRead; // size_t equivalente ao int
   ag *mAg=(ag *) malloc(LEN*MAXREC); // exatamente igual ag mAg[MAXREC];
   ag p;
   char *nomearq="Agenda.dat"; // ou char nomeArq[]="Agenda.dat"
   char *tp[]={"temp1","temp2"};
   FILE *arq, *aux1, *aux2;
   printf("\nMetodo de ordenacao interna a ser utilizado: (0 Insertion 1 Merge): ");
   scanf("%d",&ts);
   printf("\nQuantidade de registros a gerar: ");
   scanf("%d",&qt);
   printf("\nGerando registros aleatorios....\n");
   //
   srand(time(NULL)); // gera a semente aleatória
   arq=fopen(nomearq,"w+b");
   char nome[15];
   char end[30];

   for (i=0;i<qt;i++)
   {
      p.age=rand()%100;
      sprintf(nome, "Pessoa%d", i);
      strcpy(p.name,nome);
      sprintf(end, "Endereco%d", i);
      strcpy(p.address,end);
      fwrite(&p, LEN, 1, arq);
      printf("\b\b\b\b\b\b\b\b\b\b\b%d",i+1);
   }
   fclose(arq);

   // abre o arquivo binário para leitura e gravação
   // cria os arquivos auxiliares
   printf("\nClassificando....");
   time_t ini = time(NULL);
   arq = fopen(nomearq, "r+b");
   aux1 = fopen(tp[0], "w+b");
   aux2 = fopen(tp[1], "w+b");
   tRead = fread(mAg, LEN, MAXREC, arq);
   if (ts)  mergeSort(mAg,0,tRead);
   else sort(mAg,tRead);
   i = 1;
   // printf("\nBloco %d Ordenado",i);

   recTempFile(aux1, aux2, mAg, tRead);
   int ind = 0;
   while (!feof(arq))
   {
      tRead = fread(mAg,LEN,MAXREC,arq);
      if (ts)  mergeSort(mAg,0,tRead);
      else sort(mAg,tRead);
     // printf("\nBloco %d ordenado",++i);
      recTempFile(aux2,aux1,mAg,tRead);
      fclose(aux1);
      fclose(aux2);
      aux1 = fopen(tp[ind==0 ? 1:0], "r+b");
      aux2 = fopen(tp[ind==0 ? 0:1], "w+b");
      ind = ind==0? 1:0;
   }
   fclose(aux1);
   fclose(aux2);
   fclose(arq);
   time_t total=time(NULL)-ini;

   free(mAg);
   printf("\nFim....");

    // lista arquivo gerado
    // abre arquivo binário para leitura
    // o último arquivo deve ser renomeado para Agenda.dat
    // Isso será feito na versão 2.0 :)
    arq = fopen(tp[ind==0?0:1], "rb");
    fread(&p, LEN, 1, arq); qt=0;

    while (!feof(arq))
    {
       printf("\n Nome: %.15s Endereco: %.30s Idade %5d",p.name, p.address, p.age);
       fread(&p, LEN, 1, arq);
    }

    printf("\nFim da classificacao e apresentacao....%d s",(int)total);
    return 1;
}

void sort(ag *myAg, size_t tam) // utiliza o método Inserção
{
     ag aAg;
     int j;
     for (j=1;j<tam;j++)
     {
       aAg=myAg[j];
       int i=j-1;
       while (i>=0 && myAg[i].age>aAg.age)
         {
           myAg[i+1]=myAg[i];
           i--;
         }
         myAg[i+1]=aAg;
      }
}

void recTempFile(FILE *arq, FILE *aux, ag *myAg, size_t tam)
{
   int i=0;
   ag aAg;
   fseek(aux,0,SEEK_SET);
   fread(&aAg,LEN,1,aux);
   while (!feof(aux) || i < tam)
   {
       if (i < tam && (aAg.age > myAg[i].age || feof(aux)))
       {
          fwrite(&myAg[i],LEN,1,arq);
          i++;
       }
       else
       {
           if (i == tam || aAg.age < myAg[i].age)
           {
              fwrite(&aAg,LEN,1,arq);
              fread(&aAg,LEN,1,aux);
           }
           else
           {
              fwrite(&myAg[i],LEN,1,arq);
              i++;
              fwrite(&aAg,LEN,1,arq);
              fread(&aAg,LEN,1,aux);
           }
       }

   }
}
//////
void mergeSort(ag *A, int p, int r)
{
     if (p<r-1)
     {
       int q=(int) (p+r)/2;
       mergeSort(A,p,q);
       mergeSort(A,q,r);
       merge(A,p,q,r);
     }
}


void merge  (ag *A, int p, int q, int r)
{
   int i, j, k;
   ag B[r-p];
   i = p; j = q;
   k = 0;

   while (i < q && j < r) {
      if (A[i].age <= A[j].age)  B[k++] = A[i++];
      else  B[k++] = A[j++];
   }
   while (i < q)  B[k++] = A[i++];
   while (j < r)  B[k++] = A[j++];
   for (i = p; i < r; ++i)  A[i] = B[i-p];
}
