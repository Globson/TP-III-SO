#include "../Headers/P_Impressao.h"
void ImprimeSistemaCompleto(Cpu* cpu, PcbTable *pcbTable, EstadoBloqueado *estadobloqueado, EstadoPronto *estadopronto){
  printf("\n--Inicio impresssao do estado do sistema---\n\n");
  ImprimirCPU(cpu);
  printf("\n\n");
  ImprimePronto(estadopronto);
  printf("\n\n");
  ImprimeBloqueado(estadobloqueado);
  printf("\n\n");
  ImprimePcbTable(pcbTable);
  printf("\n\n--Fim da impresssao do estado do sistema---\n\n");
  if(FIRSTFIT)
    PrintMemoriaFirstFit();
  else
    PrintMemoriaNextFit();
}

void VerificaFragmentosFirstFit(){
    int frag = 0;
    int cont = 0;
    for(int i = 0;i < MAXMEM;i++){
        if(firstfit.mapadebits[i] == 0 && cont == 0){
            frag++;
            cont = 1;
        }
        else if(firstfit.mapadebits[i] == 1 && cont == 1){
            cont = 0;
        }
    }
    firstfit.totalfragmentos = frag;
}

void VerificaFragmentosNextFit(){
    int frag = 0;
    int cont = 0;
    for(int i = 0;i < MAXMEM;i++){
        if(nextfit.mapadebits[i] == 0 && cont == 0){
            frag++;
            cont = 1;
        }
        else if(nextfit.mapadebits[i] == 1 && cont == 1){
            cont = 0;
        }
    }
    nextfit.totalfragmentos = frag;
}

void PrintMemoriaFirstFit(){
    VerificaFragmentosFirstFit();
    printf("\nNúmero de Fragmentos: %d\n",firstfit.totalfragmentos);
    printf("\nNúmero de Nos Medios Percorridos: %d\n",firstfit.nospercorridos/firstfit.totalalocados);
    printf("\nPorcentual de negação de alocação %d \n",firstfit.erroemalocar/firstfit.totalalocados * 100);
    printf("\nMemoria FirstFit:\n");
    for(int i = 0;i < MAXMEM;i++){
        if(firstfit.mapadebits[i] == 1){
            printf("%d\n",firstfit.memoria[i]);
        }
        else{
            printf("#\n");
        }
    }
}

void PrintMemoriaNextFit(){
    VerificaFragmentosNextFit();
    printf("\nNúmero de Fragmentos: %d\n",nextfit.totalfragmentos);
    printf("\nNúmero de Nos Medios Percorridos: %d\n",nextfit.nospercorridos/nextfit.totalalocados);
    printf("\nPorcentual de negação de alocação %d \n",nextfit.erroemalocar/nextfit.totalalocados * 100);
    printf("\nMemoria NextFit:\n");
    for(int i = 0;i < MAXMEM;i++){
        if(nextfit.mapadebits[i] == 1){
            printf("%d\n",nextfit.memoria[i]);
        }
        else{
            printf("#\n");
        }
    }
}


void ImprimeTempoMedioCiclo(Time *time){
  double tempomedio=0;
  tempomedio = time->time/time->QuantProcessosCriados;
  printf("\n---- O tempo de ciclo medio foi de %.2lf ----\n\nFinalizando...\n",tempomedio);
}
