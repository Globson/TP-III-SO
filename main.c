#include "Headers/P_Controle.h"
#include "Headers/P_Gerenciador_Processos.h"
#include "Headers/P_Impressao.h"
#include "Headers/Estruturas_de_Dados.h"
#include <time.h>

void iniciaMemoria(char memoria[]){
    for(int i=0;i < 1000;i++){
        memoria[i] = '#';
    }
}


int main(int argc, char const *argv[]) {
  Memoria memoria;
  srand(time(NULL));
  iniciaMemoria(memoria);
  Executar_P_Controle();
  printf("\n\tExecutou TUDO!");
  return 0;
}

