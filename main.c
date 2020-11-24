#include "Headers/P_Controle.h"
#include "Headers/P_Gerenciador_Processos.h"
#include "Headers/P_Impressao.h"
#include "Headers/Estruturas_de_Dados.h"
#include <time.h>

void iniciamapa(int mapadebits[]){
    for(int i=0;i < MAXMEM;i++){
        mapadebits[i] = 0;
    }
}

void iniciamemoria(int memoria[]){
    for(int i=0;i < MAXMEM;i++){
        memoria[i] = 0;
    }
}

/*
void Test(char memoria[]){
    for(int i=0;i < MAXMEM;i++){
        printf("%c\n",memoria[i]);
    }
}
*/

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  iniciamapa(mapadebits);
  iniciamemoria(memoria);
  //Test(memoria);
  Executar_P_Controle();
  printf("\n\tExecutou TUDO!");
  return 0;
}

