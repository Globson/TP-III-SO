#include "Headers/P_Controle.h"
#include "Headers/P_Gerenciador_Processos.h"
#include "Headers/P_Impressao.h"
#include "Headers/Estruturas_de_Dados.h"
#include <time.h>


void iniciamemoria(int memoria[]){
    for(int i=0;i < MAXMEM;i++){
        memoria[i] = 0;
        mapadebits[i] = 0;
    }
}


int main(int argc, char const *argv[]) {
  srand(time(NULL));
  iniciamemoria(memoria);
  //Test(memoria);
  Executar_P_Controle();
  printf("\n\tExecutou TUDO!");
  return 0;
}

