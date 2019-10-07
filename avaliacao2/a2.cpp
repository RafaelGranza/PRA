#include <bits/stdc++.h>

using namespace std;

int TAMANHO=5;
#define TAM 5

typedef struct dado{

    unsigned long chave1;
    float chave2;

}Dado;

typedef struct bloco{

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

  vector<Bloco> blocos;

}Fita;

typedef struct listaFitas{

    int numBlocos = 0;
    Fita fitas[TAM];

}ListaFitas;

// adiciona bloco em todas as fitas de uma vez para que fiquem balanceadas.
void addBlocos( ListaFitas &lf ){

    Bloco auxBloco;

    for( int i = 0; i < TAM; i++ ){
        lf.fitas[i].blocos.push_back(auxBloco);
    }

    lf.numBlocos++;

}

void lerArquivo(ListaFitas &leitura){

    FILE* f;

    f = fopen("saida","r");

    if(f==NULL){
        printf("Arquivo Invalido\n");
        return;
    }

    int i, fitaAtual = 0, iFita = 0;

    addBlocos( leitura );

    for(i=0;i<(475*1000*1000)/sizeof(Dado);i++){

      Dado aux;
      fread(&aux,sizeof(Dado),1,f);
      leitura.fitas[fitaAtual].blocos.back().dados.push_back(aux);
      iFita++;
      if(iFita == TAMANHO){
          sort(leitura.fitas[fitaAtual].blocos.back().dados.begin(), leitura.fitas[fitaAtual].blocos.back().dados.end(),comparacaoCustomizadaFODA());
          fitaAtual++;
          iFita = 0;
          if(fitaAtual == TAMANHO){
              fitaAtual = 0;
              addBlocos( leitura );
          }
      }

    }

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

// REVER TEM BASTANTE ERRO
void MergeSoft(ListaFitas &leitura, ListaFitas &escrita){

    vector<int> is(TAMANHO, 0);
    int iEscolhido, fitaAtual = 0;

    // ta errado esses fors
    for( int k = 0; k < leitura.numBlocos; k++ ){

        for(int i = 0; i < TAMANHO; i++){

            for(int j = 0; j < TAMANHO; j++){

                vector<Dado> compDados;

                for( auto ix:is ){

                    if( ix < leitura.fitas[j].blocos[i].dados.size() )
                        compDados.push_back( leitura.fitas[j].blocos[i].dados[ix] );

                }

                iEscolhido = superMin( compDados );
                escrita.fitas[fitaAtual].blocos.back().dados.push_back( compDados[iEscolhido] );
                is[iEscolhido]++;

            }

        }

        fitaAtual++;
        if( fitaAtual == TAMANHO )
            fitaAtual = 0;

    }

}

int main(int argc, char const *argv[]) {
    ListaFitas lt;
    ListaFitas et;
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
