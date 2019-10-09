#include <bits/stdc++.h>

using namespace std;

#define M 5

typedef struct dado{

    unsigned long chave1;
    float chave2;

}Dado;

struct comparacaoCustomizadaFODA {
    bool operator()(const Dado& lhs, const Dado& rhs) {
        if(lhs.chave1==rhs.chave1){
            return lhs.chave2<rhs.chave2;
        }
        return lhs.chave1 < rhs.chave1;
    }
};

void criaFitas(){

  FILE* f;
  char aux[50];

  for(int i = 0; i < M*2; i++){
    sprintf(aux, "fita%d", i+1);

    f = fopen(aux,"w");

    if(f==NULL){
        printf("Falha na criação do arquivo.\n");
        return;
    }

    fclose(f);

  }

}

void leArquivo(){

  FILE* f;

  f = fopen("saida","r");

  if(f==NULL){
      printf("Falha na leitura do arquivo.\n");
      return;
  }

  int i = 0;

  while(!feof(f)){

    Dado aux[M];
    fread(&aux,sizeof(Dado),M,f);
    sort(aux, aux + M, comparacaoCustomizadaFODA());

    FILE* fita;
    char nome[50];
    i%=M;
    i++;
    sprintf(nome, "fita%d", i);

    fita = fopen(nome,"a");

    if(fita==NULL){
        printf("Falha na leitura do arquivo.\n");
        return;
    }

    fwrite(&aux,sizeof(Dado),5,fita);

    fclose(fita);

  }

  fclose(f);

}

void debugFita(int i){

  FILE* f;
  char aux[50];

  sprintf(aux, "fita%d", i);

  f = fopen(aux,"r");

  if(f==NULL){
      printf("Falha na leitura do arquivo.\n");
      return;
  }

  printf("Fita %d:\n",i);
  Dado a;
  while(!feof(f)){
    fread(&a,sizeof(Dado),1,f);
    printf("%lu\t\t%f\n", a.chave1, a.chave2);
  }

  fclose(f);

}


int superMin( vector<Dado> dados ){
    Dado minimo = dados[0];
    int indice=0;
    for(int i = 1; i < dados.size();i++){
        Dado auxMinimo = minimo;
        minimo = min( minimo, dados[i], comparacaoCustomizadaFODA() );
        if(!(auxMinimo.chave1==minimo.chave1 && auxMinimo.chave2==minimo.chave2)){
            indice=i;
        }
    }
    return indice;
}

// é o soft só q hard
void hardMerge(int indice){

  int iFitaEntrada = 0;
  int iFitaSaida = M;
  Dado dadoFitaEntrada[M];
  int iFitasEntrada[M];
  unsigned long long int tamanhoBloco=(unsigned long long int)pow(M,indice+1);

  memset(iFitasEntrada,0,sizeof(iFitasEntrada));

  FILE *fitasEntrada[M],*fitasSaida[M];

  // abrindo todas as fitas de entrada
  for(int i = (indice%2)*M; i <(indice%2)*M + M; i++){

    char nome[50];
    sprintf(nome, "fita%d", i+1);
    fitasEntrada[i%M] = fopen(nome,"r");

    if(fitasEntrada[i]==NULL){
        printf("Falha na leitura do arquivo.\n");
        return;
    }

  }

  // abrindo todas as fitas de saida
  for(int i = ((indice+1)%2)*M; i < ((indice+1)%2)*M+M; i++){

    char nome[50];
    sprintf(nome, "fita%d", i+1);
    fitasSaida[i%M] = fopen(nome,"a");

    if(fitasSaida[i]==NULL){
        printf("Falha na leitura do arquivo.\n");
        return;
    }

  }

  //Criar um jeito de ler TODOS os blocos
  int N=(5);
  while(--N){
      memset(iFitasEntrada,0,sizeof(iFitasEntrada));

      // lendo primeiras posicoes das fitas de entrada
      vector<Dado> dadosAux;
      for(int i = 0; i <M; i++){

          Dado aux;
          if(fread(&aux,sizeof(Dado),1,fitasEntrada[i])==1){
              dadosAux.push_back(aux);
          }

      }

      //Ler até o final dos blocos
      for(long long int j = 0; j < tamanhoBloco*M; j++){
          int iMenorDado;

          iMenorDado = superMin( dadosAux );
          //Salvar o menor dado na fita de saida respectiva
          fwrite(&dadosAux[iMenorDado],sizeof(Dado),1,fitasSaida[j/tamanhoBloco]);

          iFitasEntrada[iMenorDado]++;

          Dado aux;
          if(iFitasEntrada[iMenorDado]<tamanhoBloco){
              if(fread(&aux,sizeof(Dado),1,fitasEntrada[iMenorDado])==1){
                  dadosAux[iMenorDado] = aux;
              }
          }else{
              aux.chave1=ULONG_MAX;
              aux.chave2=FLT_MAX;
              dadosAux[iMenorDado] = aux;
          }
          // paramos aqui

      }
  }

  // fechando todas as fitas
  for(int i = 0; i < M; i++){
    fclose(fitasSaida[i]);
    fclose(fitasEntrada[i]);
  }

}

int main(int argc, char const *argv[]) {

    int quantidadeiteracoes=1;
    criaFitas();

    leArquivo();

    // for(int i = 0; i < M; i++){
    //   debugFita(i+1);
    // }
    for(int i = 0 ; i < quantidadeiteracoes ; i++ ){
        hardMerge(i);
    }

    return 0;
}
