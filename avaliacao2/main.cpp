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

// Conta todos os registros do arquivo
int countReg(int iFita){

  FILE *fp;
  int count;
  char aux[50];

  sprintf(aux, "fita%d", iFita+1);

  if ((fp = fopen(aux, "r")) == NULL)
  {
    printf("Erro na abertura do arquivo 1");
    exit(1);
  }

  fseek(fp, 0L, SEEK_END);
  count = ftell(fp) / sizeof(Dado);

  fclose(fp);

  return count;

}

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

    fwrite(&aux,sizeof(Dado),M,fita);

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
    printf("%lu\t\t\t%f\n", a.chave1, a.chave2);
  }

  fclose(f);

}


int superMin( vector<Dado> dados ){
    Dado minimo = dados[0];
    int indice=0;
    for(unsigned int i = 1; i < dados.size();i++){
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

  unsigned int iFitasEntrada[M];
  unsigned long long int tamanhoBloco = (unsigned long long int)pow( M, indice + 1 );

  memset(iFitasEntrada,0,sizeof(iFitasEntrada));

  FILE *fitasEntrada[M],*fitasSaida[M];

  // abrindo todas as fitas de entrada
  for(int i = (indice%2)*M; i <(indice%2)*M + M; i++){

    char nome[50];
    sprintf(nome, "fita%d", i+1);
    fitasEntrada[i%M] = fopen(nome,"r");

    if(fitasEntrada[i%M]==NULL){
        printf("Falha na leitura do arquivo.\n");
        return;
    }

  }

  // abrindo todas as fitas de saida
  for(int i = ((indice+1)%2)*M; i < ((indice+1)%2)*M+M; i++){

    char nome[50];
    sprintf(nome, "fita%d", i+1);

    // limpando a fita de saida
    FILE *auxF = fopen(nome,"w");
    fclose(auxF);

    // abrindo como append para adicionar valores em seu final
    fitasSaida[i%M] = fopen(nome,"a");

    if(fitasSaida[i%M]==NULL){
        printf("Falha na leitura do arquivo.\n");
        return;
    }

  }

  //Criar um jeito de ler TODOS os blocos
  unsigned long long int numBlocos = countReg((indice%2)*M) / tamanhoBloco;
  unsigned long long int iFitaSaida = 0;

  printf("%d %ul\n", indice, numBlocos);

  for(unsigned int k = 0; k < numBlocos; k++){

    memset(iFitasEntrada,0,sizeof(iFitasEntrada));

    // lendo primeiras posicoes das fitas de entrada
    vector<Dado> dadosAux;
    for(int i = 0; i < M; i++){

      Dado aux;
      if(!feof(fitasEntrada[i])){
          fread(&aux,sizeof(Dado),1,fitasEntrada[i]);
          dadosAux.push_back(aux);
      }else{
          aux.chave1=ULONG_MAX;
          aux.chave2=INT_MAX + FLT_MAX;
          dadosAux.push_back(aux);
      }

    }

    bool continua = false;

    for(int i = 0; i < M; i++){
      if( iFitasEntrada[i] < tamanhoBloco && !feof(fitasEntrada[i]) ){
        continua = true;
        break;
      }
    }

    //Ler até o final do bloco[numBloco] de todas as fitas
    while( continua ){

      int iMenorDado;

      iMenorDado = superMin( dadosAux );
      //Salvar o menor dado na fita de saida respectiva
      fwrite(&dadosAux[iMenorDado],sizeof(Dado),1,fitasSaida[iFitaSaida%M]);

      iFitasEntrada[iMenorDado]++;

      Dado aux;
      if( iFitasEntrada[iMenorDado] < tamanhoBloco && !feof(fitasEntrada[iMenorDado]) ){
          fread(&aux,sizeof(Dado),1,fitasEntrada[iMenorDado]);
          dadosAux[iMenorDado] = aux;
      }else{
          aux.chave1=ULONG_MAX;
          aux.chave2=INT_MAX + FLT_MAX;
          dadosAux[iMenorDado] = aux;
      }

      continua = false;

      for(int i = 0; i < M; i++){
        if( iFitasEntrada[i] < tamanhoBloco && !feof(fitasEntrada[i]) ){
          continua = true;
          break;
        }
      }

    }

    iFitaSaida++;

  }

  // fechando todas as fitas
  for(int i = 0; i < M; i++){
    fclose(fitasSaida[i]);
    fclose(fitasEntrada[i]);
  }

}

int main(int argc, char const *argv[]) {

  setbuf(stdout, NULL);

  /*
  n = 29687500
  m = 5
  f = 5
  P(n) = 9,690835916581937 ~ 10

  n = 3125
  m = 5
  f = 5
  P(n) = 4
  */

  // int quantidadeiteracoes = 4; // se TAM == 1000*50
  int quantidadeiteracoes = 10; // se TAM == 475*1000*1000
  criaFitas();

  leArquivo();

  for(int i = 0 ; i < quantidadeiteracoes ; i++ ){
      hardMerge(i);
  }

  for(int i = 0; i < M; i++){
      debugFita(i+1);
  }

  return 0;
}
