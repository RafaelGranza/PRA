#include <bits/stdc++.h>

using namespace std;

int TAMANHO=5;
#define TAM 5

typedef struct dado{

  unsigned long chave1;
  float chave2;

}Dado;

typedef struct bloco{

  int tamanho = 0;
  vector<Dado> dados =vector<Dado>(TAMANHO);

}Bloco;


struct comparacaoCustomizadaFODA {
    bool operator()(const Dado& lhs, const Dado& rhs) {
        if(lhs.chave1==rhs.chave1){
            return lhs.chave2<rhs.chave2;
        }
        return lhs.chave1 < rhs.chave1;
    }
};


typedef struct fita{

  int tamanho = 0;
  vector<Bloco> blocos;

}Fita;

typedef struct leitura{

  Fita fitas[TAM];

}Leitura;

typedef struct escrita{

  Fita fitas[TAM];

}Escrita;

void insereDadoNaFita(Fita &fita, Dado dado){

    if(fita.blocos.size()==0){
        Bloco auxBloco;
        fita.blocos.push_back(auxBloco);
    }

    if(fita.blocos.back().tamanho<TAMANHO){
        fita.blocos.back().dados[fita.blocos.back().tamanho]=dado;
        fita.blocos.back().tamanho++;
    }else{
        Bloco auxBloco;
        fita.blocos.push_back(auxBloco);
        fita.blocos.back().dados[fita.blocos.back().tamanho]=dado;
        fita.blocos.back().tamanho++;
    }
    sort(fita.blocos.back().dados.begin(), fita.blocos.back().dados.end(),comparacaoCustomizadaFODA());
}


void lerArquivo(Leitura &leitura){

    FILE* f;
    f=fopen("saida","r");
    int i, fitaAtual = 0, iFita=0;
    for(i=0;i<(475*1000*1000)/sizeof(Dado);i++){

      Dado aux;
      fread(&aux,sizeof(Dado),1,f);
      insereDadoNaFita( leitura.fitas[fitaAtual], aux );
      iFita++;
      if(iFita == TAMANHO){
          fitaAtual++;
          iFita = 0;
          if(fitaAtual == TAMANHO){
              fitaAtual = 0;
          }
      }
    }

}

// Fita iniciaFita(){
//     Fita fita;
//     Bloco auxBloco;
//     fita.blocos.push_back(auxBloco);
//     return fita;
// }


// class MergeGranza{
// public:
//
//     int fitas, bloco;
//     int blocoAtual;
//     vector<Dado> bloco[m];
//     MergeGranza( int m, int f ){
//         fitas = f;
//         bloco = m;
//         blocoAtual = 0;
//     }
//
//
//
// };


int main(int argc, char const *argv[]) {
    Leitura lt;
    lerArquivo(lt);

    return 0;
}
