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
    vector<Dado> dados;

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
        fita.blocos.back().dados.push_back(dado);
        fita.blocos.back().tamanho++;
    }else{
        Bloco auxBloco;
        fita.blocos.push_back(auxBloco);
        fita.blocos.back().dados.push_back(dado);
        fita.blocos.back().tamanho++;
    }
    //printf("%lu\n", fita.blocos.back().dados[fita.blocos.back().tamanho].chave1);
    sort(fita.blocos.back().dados.begin(), fita.blocos.back().dados.end(),comparacaoCustomizadaFODA());
}


void lerArquivo(Leitura &leitura){

    FILE* f;
    f=fopen("saida","r");
    if(f==NULL){
        printf("Arquivo Invalido\n");
        return;
    }
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

int superMin( vector<Dado> dados ){
    Dado minimo = dados[0];
    int indice=0;
    for(int i = 1; i < dados.size();i++){
        Dado auxMinimo = minimo;
        minimo =min(minimo,dado[i],comparacaoCustomizadaFODA());
        if(!(auxMinimo.chave1==minimo.chave1 && auxMinimo.chave2==minimo.chave2)){
            indice=i;
        }
    }
    return indice;
}

void MergeSoft(Leitura &leitura, Escrita &escrita){

    vector<int> is(TAMANHO, 0);

    for(int i = 0; i < TAMANHO; i++){
        for(int j = 0; j < leitura.fitas[i].blocos.size(); j++){
            for(int k = 0; k < leitura.fitas[j].blocos[i].dados.size();k++){
                //insereDadoNaFita( escrita.fitas[i], leitura.fitas[j].blocos[i].dados );
                // PAREI AQUI
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



int main(int argc, char const *argv[]) {
    Leitura lt;
    Escrita et;
    lerArquivo(lt);
    MergeSoft(lt,et);
    for(int i =0;i< TAMANHO;i++){
        printf("FITA %d\n", i);
        for(int j =0;j<et.fitas[i].blocos.size();j++){
            printf("BLOCO %d\n", j);
            for(int k =0;k<et.fitas[i].blocos[j].dados.size();k++){
                printf("\t%lu\t%f\n", et.fitas[i].blocos[j].dados[k].chave1,et.fitas[i].blocos[j].dados[k].chave2);
            }
        }
    }
    return 0;
}
