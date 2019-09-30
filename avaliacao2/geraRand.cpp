#include <bits/stdc++.h>
using namespace std;

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
  for(i=0;i<(475*1000*1000)/sizeof(Dado);i++){

    Dado aux;
    aux.chave1 = (unsigned long)(((unsigned long)rand())*rand());
    aux.chave2 = (float)((rand()*rand())/(rand()+0.0));
    //printf("%lu\t%f\n", aux.chave1,aux.chave2);
    fwrite(&aux,sizeof(Dado),1,f);
  }
  printf("%d\n", i);

}
