#include <bits/stdc++.h>
using namespace std;
#define TAM   475*1000*1000
// #define TAM   1000*50

typedef struct dados{

  unsigned long chave1;
  float chave2;

}Dado;

int main(int argc, char const *argv[]) {

  char nome[80]="saida";

  FILE* f;
  f=fopen(nome,"w");
  srand(time(NULL));
  int i;
  for(i=0;i<(TAM)/sizeof(Dado);i++){

    Dado aux;
    aux.chave1 = (unsigned long)(((unsigned long)rand())*rand());
    aux.chave2 = (float)((rand()*rand())/(rand()+0.0));
    fwrite(&aux,sizeof(Dado),1,f);
  }
  fclose(f);
  printf("Total de Registros Criados: %d\n", i);

}
