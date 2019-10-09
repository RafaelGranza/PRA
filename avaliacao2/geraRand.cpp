#include <bits/stdc++.h>
using namespace std;
#define TAM   475*1000*1000

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
  // for(i=0;i<(1000*50)/sizeof(Dado);i++){
  for(i=0;i<(TAM)/sizeof(Dado);i++){

    Dado aux;
    aux.chave1 = (unsigned long)(((unsigned long)rand())*rand());
    aux.chave2 = (float)((rand()*rand())/(rand()+0.0));
    //printf("%lu\t%f\n", aux.chave1,aux.chave2);
    fwrite(&aux,sizeof(Dado),1,f);
  }
  fclose(f);
  printf("%d %lu %lu\n", i, sizeof(Dado), 100*1000*1000/sizeof(Dado));

}

/*
n = 29687500
m = 6250000
f = 5
P(n) = 0,9681296842883644
*/
