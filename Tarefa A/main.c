#include "Headers/P_Controle.h"
#include "Headers/P_Gerenciador_Processos.h"
#include "Headers/P_Impressao.h"
#include "Headers/Estruturas_de_Dados.h"
#include <time.h>


void iniciamemoria(){
    for(int i=0;i < MAXMEM;i++){
        firstfit.memoria[i] = 0;
        firstfit.mapadebits[i] = 0;
        nextfit.memoria[i] = 0;
        nextfit.mapadebits[i] = 0;
    }
    firstfit.totalalocados = 0;
    firstfit.nospercorridos = 0;
    firstfit.totalfragmentos = 0;
    firstfit.erroemalocar = 0;
    nextfit.totalalocados = 0;
    nextfit.nospercorridos = 0;
    nextfit.totalfragmentos = 0;
    nextfit.erroemalocar = 0;
    nextfit.ultimaalocacao = 0;
}


int main(int argc, char const *argv[]) {
  srand(time(NULL));
  iniciamemoria();
  //Test(memoria);
  Executar_P_Controle();
  printf("\n\tExecutou TUDO!");
  return 0;
}

