#include "../Headers/RodaInstrucao.h"
#include "../Headers/Estruturas_de_Dados.h"
#include "../Headers/P_Gerenciador_Processos.h"

int AlocaDisco(int temp[],int qtd,int n,int flag,int *pos){  // retorna 0 caso haja erro e 1 caso tenha sido alocado
    int espaco = 0;
    if(flag == 0){
        for(int i = 0;i < MAXMEM*10;i++){
            if(disco.mapadebits[i] == 0){
                espaco++;
            }
            else{
                espaco = 0;
            }
            if(qtd == espaco){
                disco.memoria[i+1-espaco+n] = temp[n];
                disco.mapadebits[i+1-espaco+n] = 1;
                *pos = i+1-espaco;
                //printf("\nAlocado %d em %d\n no disco\n",temp[n],i+1-espaco+n);
                for(int j = *pos+1;j < *pos+qtd;j++){
                    disco.mapadebits[j] = 1;
                    //printf("\nAlocado 0 em %d\n no disco\n",j);
                }
                return 1;
            }
        }
    }
    else{
        disco.memoria[*pos+n] = temp[n];
        disco.mapadebits[*pos+n] = 1;
        //printf("\nAlocado %d em %d\n no disco\n",temp[n],*pos+n);
        return 1;
    }
    //printf("\nERRO! Disco cheio\n");
    return 0;
}


int AlocaMemVirtual(int temp[],int qtd,int n,int *vflag,int *pos){  // retorna 0 caso haja erro e 1 caso tenha sido alocado
    int espaco = 0;
    if(*vflag == 0){
        for(int i = 0;i < MAXMEM*2;i++){
            if(memvirtual.mapadebits[i] == 0){
                espaco++;
            }
            else{
                espaco = 0;
            }
            if(qtd == espaco){
                memvirtual.memoria[i+1-espaco+n] = temp[n];
                memvirtual.mapadebits[i+1-espaco+n] = 1;
                *pos = i+1-espaco;
                *vflag = 1;
                //printf("\nAlocado %d em %d\n virtual",temp[n],i+1-espaco+n);
                for(int j = *pos+1;j < *pos+qtd;j++){
                    memvirtual.mapadebits[j] = 1;
                    //printf("\nAlocado 0 em %d\n virtual",j);
                }
                return 1;
            }
        }
    }
    else{
        memvirtual.memoria[*pos+n] = temp[n];
        //printf("\nAlocado %d em %d virtual \n",temp[n],*pos+n);
        return 1;
    }
    return 0;
}

int AlocaFirstFit(int temp[],int qtd,int n,int flag,int *pos,int *vpos,int *vflag){  // retorna 0 caso haja erro e 1 caso tenha sido alocado
    int espaco = 0;
    if(flag == 0){
        for(int i = 0;i < MAXMEM;i++){
            if(firstfit.mapadebits[i] == 0){
                espaco++;
            }
            else{
                espaco = 0;
            }
            if(qtd == espaco){
                firstfit.memoria[i+1-espaco+n] = temp[n];
                firstfit.mapadebits[i+1-espaco+n] = 1;
                *pos = i+1-espaco;
                firstfit.nospercorridos += *pos;
                firstfit.totalalocados += 1;
                //printf("\nAlocado %d em %d\n",temp[n],i+1-espaco+n);
                for(int j = *pos+1;j < *pos+qtd;j++){
                    firstfit.mapadebits[j] = 1;
                    //printf("\nAlocado 0 em %d\n",j);
                }
                return 1;
            }
        }
    }
    else{
        firstfit.memoria[*pos+n] = temp[n];
        //printf("\nAlocado %d em %d\n",temp[n],*pos+n);
        return 1;
    }
    if(*vflag == 0){
        AlocaMemVirtual(temp,qtd,n,vflag,vpos);
        //npos = MMU(*vpos);
        }
    return 0;
}

int AlocaNextFit(int temp[],int qtd,int n,int flag,int *pos,int *vpos,int *vflag){ // retorna 0 caso haja erro e 1 caso tenha sido alocado
    int espaco = 0;
    if(flag == 0){
        for(int i = nextfit.ultimaalocacao;i < MAXMEM;i++){
            if(nextfit.mapadebits[i] == 0){
                espaco++;
            }
            else{
                espaco = 0;
            }
            if(qtd == espaco){
                nextfit.memoria[i+1-espaco+n] = temp[n];
                nextfit.mapadebits[i+1-espaco+n] = 1;
                *pos = i+1-espaco;
                nextfit.nospercorridos += *pos;
                nextfit.totalalocados += 1;
                //printf("\nAlocado %d em %d\n",temp[n],i+1-espaco+n);
                for(int j = *pos+1;j < *pos+qtd;j++){
                    nextfit.mapadebits[j] = 1;
                    //printf("\nAlocado 0 em %d\n",j);
                }
                nextfit.ultimaalocacao= *pos+qtd;
                return 1;
            }
        }
        espaco = 0;
        for(int i = 0;i < nextfit.ultimaalocacao;i++){
            if(nextfit.mapadebits[i] == 0){
                espaco++;
            }
            else{
                espaco = 0;
            }
            if(qtd == espaco){
                nextfit.memoria[i+1-espaco+n] = temp[n];
                nextfit.mapadebits[i+1-espaco+n] = 1;
                *pos = i+1-espaco;
                nextfit.nospercorridos += *pos;
                nextfit.totalalocados += 1;
                //printf("\nAlocado %d em %d\n",temp[n],i+1-espaco+n);
                for(int j = *pos;j < *pos+qtd;j++){
                    nextfit.mapadebits[j] = 1;
                    //printf("\nAlocado 0 em %d\n",j);
                }
                nextfit.ultimaalocacao= *pos+qtd;
                return 1;
            }
        }
    }
    else{
        nextfit.memoria[*pos+n] = temp[n];
        //printf("\nAlocado %d em %d\n",temp[n],*pos+n);
        return 1;
    }

    if(*vflag == 0){
        AlocaMemVirtual(temp,qtd,n,vflag,vpos);
        //npos = MMU(*vpos);
    }
    return 0;
}


void DesalocaFirstFit(int qtd,int pos){
    for(int i = pos;i < MAXMEM;i++){
        if((i - pos) == qtd)
            break;
        //printf("\nDesalocando %d da pos %d",firstfit.memoria[i],i);
        firstfit.mapadebits[i] = 0;
    //printf("\n");
    }
}

void DesalocaNextFit(int qtd,int pos){
    for(int i = pos;i < MAXMEM;i++){
        if((i - pos) == qtd)
            break;
        //printf("\nDesalocando %d da pos %d",nextfit.memoria[i],i);
        nextfit.mapadebits[i] = 0;
    }
    //printf("\n");
}

void DesalocaMemVirtual(int qtd,int pos){
    for(int i = pos;i < MAXMEM*2;i++){
        if((i - pos) == qtd)
            break;
        //printf("\nDesalocando %d da pos %d da memoria virtual",memvirtual.memoria[i],i);
        memvirtual.mapadebits[i] = 0;
    //printf("\n");
    }
}

void DesalocaDisco(int qtd,int pos){
    for(int i = pos;i < MAXMEM*10;i++){
        if((i - pos) == qtd)
            break;
        //printf("\nDesalocando %d da pos %d do disco",disco.memoria[i],i);
        disco.mapadebits[i] = 0;
    //printf("\n");
    }
}




void RodaInstrucao(Cpu *cpu, Time *time, EstadoEmExec *estadoexec, PcbTable *pcbTable, EstadoBloqueado *estadobloqueado, EstadoPronto *estadopronto, Processo *processo){
  char comando, instrucao[20];
  FILE *arqPrograma;
  Processo novoProcesso;

  strcpy(instrucao, "");
  //printf("\ncpu->contadorProgramaAtual antes de requisitar instrucao: %d", cpu->contadorProgramaAtual);

  int FinalPrograma =  RetiraProgramaFila(&cpu->programa, instrucao,cpu->contadorProgramaAtual);  //-1 fila estava vazia, 1 ainda tem instrucao do programa e 0 programa chegou ao fim.
  if(FinalPrograma == 0){
    printf("\nProcesso de PID: %d TERMINOU!\n",pcbTable->vetor[estadoexec->iPcbTable].pid);
    if(cpu->V_Memvirtual == 0){
        if(FIRSTFIT)
            DesalocaFirstFit(cpu->Quant_Inteiros,cpu->Pos_Alocado);
        else
            DesalocaNextFit(cpu->Quant_Inteiros,cpu->Pos_Alocado);
          }
    else{
        DesalocaMemVirtual(cpu->Quant_Inteiros,cpu->Pos_Memvirtual);
        cpu->V_Memvirtual = 0;
            }
    free(cpu->valorInteiro);
    RetiraPcbTable(pcbTable, estadoexec->iPcbTable, processo); // Precisa desalocar o programa.
    *processo = ColocaOutroProcessoCPU(cpu, estadopronto,estadoexec);
    return;
  }
  else if(FinalPrograma == -1){ //Se fila esta vazia, nao considerar
    RetiraPcbTable(pcbTable, estadoexec->iPcbTable, processo); // Precisa desalocar o programa.
    *processo = ColocaOutroProcessoCPU(cpu, estadopronto,estadoexec);
    return;
  }
  comando = instrucao[0];

  if(cpu->contadorProgramaAtual==0){
    printf("\nComencando execucao do processo de PID: %d \n",pcbTable->vetor[estadoexec->iPcbTable].pid);
  }
  printf("\nExecucao de instrucao -> %s\n",instrucao); //Debugando


  int i = 0,j=2,n1=0,n2=0,verificador = 0,x = 0;
  const char s[2] = " ";
  char *token;
  char *aux2,*aux3,ArquivoNovo[20]="", Path[40];
  strcpy(Path,"./Arquivos_Entrada/");
  switch (comando) {
      case 'N':
          token = strtok(instrucao, s);
          while( token != NULL ) {
            if(i == 1)
                aux2 = token;
            token = strtok(NULL, s);
            i++;
          }
          n1 = atoi(aux2);
          // printf("Valor 1: %d\n", n1);
          cpu->Quant_Inteiros = n1;
          // printf("Valor guardado em CPU: %d",cpu->Quant_Inteiros);
          cpu->contadorProgramaAtual++;
          time->time++;
          if(cpu->Alocado_V_inteiros){
            cpu->Alocado_V_inteiros = 0;
            free(cpu->valorInteiro);
          }
          break;
      case 'D':
          token = strtok(instrucao, s);
          while( token != NULL ) {
            if(i == 1)
                aux2 = token;
            token = strtok(NULL, s);
            i++;
          }
          n1 = atoi(aux2);
          // printf("Valor 1: %d\n", n1);
          if(cpu->Alocado_V_inteiros == 0){
            // printf("\nENTROU em nao alocado");
            cpu->valorInteiro = (int*) malloc(sizeof(int)*cpu->Quant_Inteiros);
            cpu->valorInteiro[n1]=0;
            if(FIRSTFIT)
              verificador = AlocaFirstFit(cpu->valorInteiro,cpu->Quant_Inteiros,n1,cpu->Alocado_V_inteiros,&cpu->Pos_Alocado,
              &cpu->Pos_Memvirtual,&cpu->V_Memvirtual);
            else
              verificador = AlocaNextFit(cpu->valorInteiro,cpu->Quant_Inteiros,n1,cpu->Alocado_V_inteiros,&cpu->Pos_Alocado,
              &cpu->Pos_Memvirtual,&cpu->V_Memvirtual);
            if(verificador){
              cpu->Alocado_V_inteiros =1; //Foi alocado, porem apenas posição especificada foi inicializada com 0;
              cpu->contadorProgramaAtual++;  //Contador do programa atual so incrementa se instrucao D foi realizada com sucesso
            }
        }
          else{
            // printf("\nENTROU alocado");
            cpu->valorInteiro[n1]=0;
            if(FIRSTFIT)
              AlocaFirstFit(cpu->valorInteiro,cpu->Quant_Inteiros,n1,cpu->Alocado_V_inteiros,&cpu->Pos_Alocado,
              &cpu->Pos_Memvirtual,&cpu->V_Memvirtual); //Caso ja encontre alocado,basta inicializar tal posicao.
            else
              AlocaNextFit(cpu->valorInteiro,cpu->Quant_Inteiros,n1,cpu->Alocado_V_inteiros,&cpu->Pos_Alocado,
              &cpu->Pos_Memvirtual,&cpu->V_Memvirtual);
            if (cpu->V_Memvirtual == 1){
                DesalocaMemVirtual(cpu->Quant_Inteiros,cpu->Pos_Memvirtual);
                cpu->V_Memvirtual = 0;
            }
            cpu->contadorProgramaAtual++; //Contador do programa atual so incrementa se instrucao D foi realizada com sucesso
          }
          time->time++;
          break;
      case 'V':  /* Define o valor da variável inteira para n, onde n é um inteiro. */
          token = strtok(instrucao, s);
          while( token != NULL ) {
            if(i == 1)
              aux2 = token;
            else
              aux3 = token;
            token = strtok(NULL, s);
            i++;
          }
          n1 = atoi(aux2);
          n2 = atoi(aux3);
          // printf("Valor 1: %d\n", n1);
          // printf("Valor 2: %d\n", n2);
          cpu->valorInteiro[n1] = n2;
          if(FIRSTFIT)
            AlocaFirstFit(cpu->valorInteiro,cpu->Quant_Inteiros,n1,cpu->Alocado_V_inteiros,&cpu->Pos_Alocado,
            &cpu->Pos_Memvirtual,&cpu->V_Memvirtual);
          else
            AlocaNextFit(cpu->valorInteiro,cpu->Quant_Inteiros,n1,cpu->Alocado_V_inteiros,&cpu->Pos_Alocado,
            &cpu->Pos_Memvirtual,&cpu->V_Memvirtual);
          // printf("Variavel inteira: %d\n", cpu->valorInteiro[n1]);
          cpu->contadorProgramaAtual++;
          time->time++;
          break;
      case 'A': /* Adiciona n ao valor da variável inteira, onde n é um inteiro. */
          token = strtok(instrucao, s);
          while( token != NULL ) {
            if(i == 1)
              aux2 = token;
            else
              aux3 = token;
            token = strtok(NULL, s);
            i++;
          }
          n1 = atoi(aux2);
          n2 = atoi(aux3);
          // printf("Valor 1: %d\n", n1);
          // printf("Valor 2:%d\n", n2);
          cpu->valorInteiro[n1] += n2;
          if(FIRSTFIT)
            AlocaFirstFit(cpu->valorInteiro,cpu->Quant_Inteiros,n1,cpu->Alocado_V_inteiros,&cpu->Pos_Alocado,
            &cpu->Pos_Memvirtual,&cpu->V_Memvirtual);
          else
            AlocaNextFit(cpu->valorInteiro,cpu->Quant_Inteiros,n1,cpu->Alocado_V_inteiros,&cpu->Pos_Alocado,
            &cpu->Pos_Memvirtual,&cpu->V_Memvirtual);
          // printf("Variavel inteira: %d\n", cpu->valorInteiro[n1]);
          cpu->contadorProgramaAtual++;
          time->time++;
          break;
      case 'S': /* Subtrai n do valor da variável inteira, onde n é um inteiro. */
          token = strtok(instrucao, s);
          while( token != NULL ) {
            if(i == 1)
              aux2 = token;
            else
              aux3 = token;
          token = strtok(NULL, s);
          i++;
          }
          n1 = atoi(aux2);
          n2 = atoi(aux3);
          // printf("Valor 1: %d\n", n1);
          // printf("Valor 2:%d\n", n2);
          cpu->valorInteiro[n1] -= n2;
          if(FIRSTFIT)
            AlocaFirstFit(cpu->valorInteiro,cpu->Quant_Inteiros,n1,cpu->Alocado_V_inteiros,&cpu->Pos_Alocado,
            &cpu->Pos_Memvirtual,&cpu->V_Memvirtual);
          else
            AlocaNextFit(cpu->valorInteiro,cpu->Quant_Inteiros,n1,cpu->Alocado_V_inteiros,&cpu->Pos_Alocado,
            &cpu->Pos_Memvirtual,&cpu->V_Memvirtual);
          // printf("Variavel inteira: %d\n", cpu->valorInteiro[n1]);
          cpu->contadorProgramaAtual++;
          time->time++;
          break;
      //
      case 'B': /* Bloqueia esse processo simulado. */
            if (FIRSTFIT){
                DesalocaFirstFit(cpu->Quant_Inteiros,cpu->Pos_Alocado);
            }
            else{
                DesalocaNextFit(cpu->Quant_Inteiros,cpu->Pos_Alocado);
            }
          AlocaDisco(cpu->valorInteiro,cpu->Quant_Inteiros,0,0,&cpu->Pos_Disco);
          for(int i = 1;i < cpu->Quant_Inteiros;i++){
            AlocaDisco(cpu->valorInteiro,cpu->Quant_Inteiros,i,1,&cpu->Pos_Disco);
            }
          //cpu->Alocado_V_inteiros = 0;
          //RetiraPcbTable(pcbTable, estadoexec->iPcbTable, processo);
          EnfileiraBloqueado(estadobloqueado, processo);
          cpu->contadorProgramaAtual++;
          time->time++;
          // *processo = ColocaOutroProcessoCPU(cpu, estadopronto);
          break;
      case 'T': /* Termina esse processo simulado. */
          printf("\nProcesso de PID: %d TERMINOU!\n",pcbTable->vetor[estadoexec->iPcbTable].pid);
          if(cpu->V_Memvirtual == 0){
              if(FIRSTFIT)
                DesalocaFirstFit(cpu->Quant_Inteiros,cpu->Pos_Alocado);
              else
                DesalocaNextFit(cpu->Quant_Inteiros,cpu->Pos_Alocado);
          }
          else{
                DesalocaMemVirtual(cpu->Quant_Inteiros,cpu->Pos_Memvirtual);
                cpu->V_Memvirtual = 0;
            }
          free(cpu->valorInteiro);
          RetiraPcbTable(pcbTable, estadoexec->iPcbTable, processo); // Precisa desalocar o programa.
          *processo = ColocaOutroProcessoCPU(cpu, estadopronto,estadoexec);
          time->time++;
          break;
      case 'F': /* Cria um novo processo simulado continuando da instrucao N. */
          token = strtok(instrucao, s);
          while( token != NULL ) {
            if(i == 1)
                aux2 = token;
            token = strtok(NULL, s);
            i++;
          }
          n1 = atoi(aux2);
          // printf("Valor 1: %d\n", n1);
          novoProcesso = criarProcessoSimulado(time, processo, (n1-1),pcbTable);
           if(processo->Estado_Processo.Alocado_V_inteiros!=0){
             if(FIRSTFIT)
               verificador = AlocaFirstFit(cpu->valorInteiro,novoProcesso.Estado_Processo.Quant_Inteiros,0,0,
               &novoProcesso.Estado_Processo.Pos_Alocado,&novoProcesso.Estado_Processo.Pos_Memvirtual,&novoProcesso.Estado_Processo.V_Memvirtual);
             else
               verificador = AlocaNextFit(cpu->valorInteiro,novoProcesso.Estado_Processo.Quant_Inteiros,0,0,
               &novoProcesso.Estado_Processo.Pos_Alocado,&novoProcesso.Estado_Processo.Pos_Memvirtual,&novoProcesso.Estado_Processo.V_Memvirtual);

             if(verificador){
                novoProcesso.Estado_Processo.Inteiro[0]= cpu->valorInteiro[0];
                for(int k=1; k<processo->Estado_Processo.Quant_Inteiros;k++){
                    novoProcesso.Estado_Processo.Inteiro[k]= cpu->valorInteiro[k];
                    if(FIRSTFIT)
                      AlocaFirstFit(cpu->valorInteiro,novoProcesso.Estado_Processo.Quant_Inteiros,k,1,
                      &novoProcesso.Estado_Processo.Pos_Alocado,&novoProcesso.Estado_Processo.Pos_Memvirtual,&novoProcesso.Estado_Processo.V_Memvirtual
                      );
                    else
                      AlocaNextFit(cpu->valorInteiro,novoProcesso.Estado_Processo.Quant_Inteiros,k,1,
                      &novoProcesso.Estado_Processo.Pos_Alocado,&novoProcesso.Estado_Processo.Pos_Memvirtual,&novoProcesso.Estado_Processo.V_Memvirtual
                      );
                }
            }
            }
           EnfileiraPronto(estadopronto, &novoProcesso);
            cpu->contadorProgramaAtual++;

           // Necessário para atualizar o contador do processo pai para a instrução logo após a instrução F.
          time->time++;
          break;
      case 'R': /* Substitui o programa do processo simulado pelo programa no arquivo nome_do_arquivo e define o contador de programa para a primeira instrução desse novo programa. */
          while((instrucao[j]!='.') && (instrucao[j+1]!='t') && (j<25)){ //Acho q funciona bem
            ArquivoNovo[j-2]=instrucao[j];
            j++;
          }
          strcat(ArquivoNovo,".txt");
          strcat(Path,ArquivoNovo);
          printf("\n\t->Nome arquivo novo: %s ",Path);
          arqPrograma = fopen(Path, "r");
          if (arqPrograma == NULL) {
              printf("\n\t->Erro, nao foi possivel abrir o arquivo de entrada!");
          } else {
            printf("\n\t->Arquivo aberto com sucesso!");
            FFilaVazia(&cpu->programa);
            int Quant_Instrucoes=0;
              while ((fgets(instrucao, sizeof(instrucao), arqPrograma)) != NULL) {
                  AdicionaProgramaFila(&cpu->programa, instrucao);
                  //printf("\n\tInstrucao lida: %s",instrucao);
                  Quant_Instrucoes++;
              }
              cpu->programa.Tam = Quant_Instrucoes;
              fclose(arqPrograma);
          }

          cpu->contadorProgramaAtual = 0;
          //free(cpu->valorInteiro);

          time->time++;
          break;
      default:
          cpu->contadorProgramaAtual++;
          time->time++;
          printf("\n\t---->Comando não suportado! ( %c )<---\n",comando);
  }

}
