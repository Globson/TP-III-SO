#include "../Headers/P_Controle.h"
#include "../Headers/P_Impressao.h"
int Executar_P_Controle(){
  int fd[2],fd_s[2]; // File descriptor para Pipe
  pid_t pid;

  char str_enviada[BUFFER],str_recebida[BUFFER], Instrucao[20];
  FILE *ArquivoPrograma;
  int Quant_Instrucoes=0;
  Programa Prog;
  if(pipe(fd) < 0){ //pipe
    perror("pipe");
    return -1; //retorna -1 em caso de Erro
  }
  if((pid = fork())<0){ //processo filho, caso fork retorne numero negativo, houve erro
    perror("fork");
    exit(1);
  }
  /* //identificação de processos pai e filho
  if(pid == 0)
    {
        printf("pid do Filho: %d\n", getpid());
    }
    else
    {
        printf("pid do Pai: %d\n", getpid());
    }
  */
  if(pid > 0){ //processo pai
    //Para escrever no pai, teremos que fechar a leitura do Pipe.
    close(fd[0]);
    int a=0;
    while(a!=1 && a!=2){
    printf("\nDeseja ler do arquivo de entrada ou pelo teclado?\n\t1 - Arquivo de entrada\n\t2 - Teclado\nEntre: ");
    scanf("%d",&a);
    if(a!=1 && a!=2){
      printf("\nErro! Entrada invalida!\n");
    }}
    if(a==1){
      LerArquivo(str_enviada); // Ler a partir de um arquivo
    }else{
      LerTerminal(str_enviada);
    }
    printf("String enviada pelo Controle(PID %i) para o Gerenciador: %s \n", getpid(),str_enviada);

    //Escrevendo no pipe:
    write(fd[1], str_enviada,sizeof(str_enviada)+1);
    exit(0);
    return 1; // return 1 se entrou em pai
  }
  else{ //Processo filho, o gerenciador.
    EstadoEmExec estadoexec;
    EstadoPronto estadopronto;
    EstadoBloqueado estadobloqueado;
    PcbTable pcbTable;
    Cpu cpu;
    Time time;

    Processo processoDesbloqueado;
    int desenfileirou;

    /* Criando Pipe. */
    if (pipe(fd_s) < 0) {
        perror("pipe");
        return -1;
    }
    Inicializa(&estadoexec, &estadopronto, &estadobloqueado, &pcbTable, &cpu, &time);

    ArquivoPrograma = fopen("./Arquivos_Entrada/Programa.txt", "r");

    if (ArquivoPrograma == NULL) {
        printf("Erro, nao foi possivel abrir o arquivo ArquivoProgramaIni.txt\n");
    } else {
        while((fgets(Instrucao, sizeof(Instrucao), ArquivoPrograma)) != NULL ){
                AdicionaProgramaFila(&Prog, Instrucao);
                Quant_Instrucoes++;
              }
      fclose(ArquivoPrograma);
    }

    // printf("Quantidade de Instruções: %d\n", Quant_Instrucoes);


    Prog.Tam = Quant_Instrucoes;

    Processo processo = criarPrimeiroSimulado(&Prog, &time, Quant_Instrucoes, getpid());

    /* No filho, vamos ler. Então vamos fechar a entrada de ESCRITA do pipe. */
    close(fd[1]);

    /* Lendo o que foi escrito no pipe, e armazenando isso em 'str_recebida'. */
    read(fd[0], str_recebida, sizeof(str_recebida));
    printf("String recebida pelo Gerenciador de PID %i enviada pelo Controle: '%s'\n\n", getpid(), str_recebida);

    EnfileiraPronto(&estadopronto, &processo);

    // ImprimePronto(&estadopronto);

    InserePcbTable(&pcbTable, processo);


    processo = colocarProcessoCPU(&cpu, &estadopronto);
    for (unsigned int j = 0; j < strlen(str_recebida); j++) {
        //printf("\n%c\n", str_recebida[j]);
        switch (str_recebida[j]) {
            case 'U': // Fim de uma unidade de tempo. Executa próxima instrução.
                ExecutaCPU(&cpu, &time, &pcbTable, &estadoexec, &estadobloqueado, &estadopronto, &processo);
                break;
            case 'L': // Desbloqueia o primeiro processo simulado na fila bloqueada.
                desenfileirou = DesenfileiraBloqueado(&estadobloqueado, &processoDesbloqueado);
                if(desenfileirou){
                  DesalocaDisco(processoDesbloqueado.Estado_Processo.Quant_Inteiros,processoDesbloqueado.Estado_Processo.Pos_Disco);
                  if(FIRSTFIT)
                    AlocaFirstFit(processoDesbloqueado.Estado_Processo.Inteiro,processoDesbloqueado.Estado_Processo.Quant_Inteiros,
                    0,0,&processoDesbloqueado.Estado_Processo.Pos_Alocado,
                    &processoDesbloqueado.Estado_Processo.Pos_Memvirtual,&processoDesbloqueado.Estado_Processo.V_Memvirtual);
                  else
                    AlocaNextFit(processoDesbloqueado.Estado_Processo.Inteiro,processoDesbloqueado.Estado_Processo.Quant_Inteiros,
                    0,0,&processoDesbloqueado.Estado_Processo.Pos_Alocado);
                  if (processoDesbloqueado.Estado_Processo.V_Memvirtual == 1){
                        DesalocaMemVirtual(processoDesbloqueado.Estado_Processo.Quant_Inteiros,processoDesbloqueado.Estado_Processo.Pos_Memvirtual);
                        processoDesbloqueado.Estado_Processo.V_Memvirtual = 0;
                    }
                  for(int i = 1;i < processoDesbloqueado.Estado_Processo.Quant_Inteiros;i++){
                    if(FIRSTFIT)
                    AlocaFirstFit(processoDesbloqueado.Estado_Processo.Inteiro,processoDesbloqueado.Estado_Processo.Quant_Inteiros,
                    i,processoDesbloqueado.Estado_Processo.Alocado_V_inteiros,&processoDesbloqueado.Estado_Processo.Pos_Alocado,
                    &processoDesbloqueado.Estado_Processo.Pos_Memvirtual,&processoDesbloqueado.Estado_Processo.V_Memvirtual);
                    else
                    AlocaNextFit(processoDesbloqueado.Estado_Processo.Inteiro,processoDesbloqueado.Estado_Processo.Quant_Inteiros,
                    i,processoDesbloqueado.Estado_Processo.Alocado_V_inteiros,&processoDesbloqueado.Estado_Processo.Pos_Alocado);
                  }
                  EnfileiraPronto(&estadopronto, &processoDesbloqueado);
                  // processo = colocarProcessoCPU(&cpu, &estadopronto);
                }
                break;
            case 'I': // Imprime o estado atual do sistema.
                ImprimeSistemaCompleto(&cpu,&pcbTable,&estadobloqueado,&estadopronto);
                break;
            case 'M': // Imprime o tempo médio do ciclo e finaliza o sistema.
                ImprimeTempoMedioCiclo(&time);
                exit(0);
                break;
            default:
                // printf("Comando '%c' não aceito!\n", str_recebida[j]);
                break;
        }
    }
    //ImprimeBloqueado(&estadobloqueado);
    //ImprimePcbTable(&pcbTable);


    return 0; // return 0 se entrou em else
  }
}

int LerArquivo(char *str_enviada){ //Simplifiquei algumas coisas
    FILE *ArquivoControle;
    char str[2];
    ArquivoControle = fopen("./Arquivos_Entrada/Controle.txt","r");
    if( ArquivoControle == NULL){
      printf("Erro ao abrir arquivo de entrada Controle.txt\n");
      return 0; //ERRO
    }
    else{
      while(fscanf(ArquivoControle,"%s",str) != EOF){
        strcat(str_enviada,str);
        strcat(str_enviada," ");
      }
      fclose(ArquivoControle);
    }
    return 1;
}

void LerTerminal(char *str_enviada){
    char comando;
    int i = 0;
    printf("Entre com o comando um a um (M finaliza leitura):\n");
    do{
        scanf("%c",&comando);
        str_enviada[i] = comando;
        strcat(str_enviada," ");
        i+=2; //Adicionei espaços entre os caracteres para manter padrão da string.
    }while(comando != 'M');
}

void FFilaVazia(Programa *prog){
  prog->Frente = 0;
  prog->Tras = 0;
}
int EstaVazia(Programa prog){
  return (prog.Frente == prog.Tras);
}

void AdicionaProgramaFila(Programa *prog, char *instrucao){
  if(prog->Tras% MAXTAM +1 == prog->Frente)
    printf("Erro! Fila de programas cheia!\n");
  else{
    strcpy(prog->instrucoes[prog->Tras],instrucao);
    prog->Tras = prog->Tras % MAXTAM +1;
  }
}
int RetiraProgramaFila(Programa *prog,char *instrucao,int indice){
  /*if(EstaVazia(*prog))
    printf("Erro! A fila esta vazia.\n");
  else{
    strcpy(instrucao,prog->instrucoes[prog->Frente]);
    prog->Frente = prog->Frente % MAXTAM +1;
  }
  */
  //printf("\n---Indice da fila de instrucoes: %d---",indice);
  if(EstaVazia(*prog)){
    printf("\n\tErro! Fila de programa Vazia!\n");
    return -1;
  }
  else if (indice >= prog->Tras) {
      // printf("\n\tErro! Posicao nao existe na fila de Instrucoes deste processo! Indice de tras: %d \n",prog->Tras);
      return 0;
  }
  strcpy(instrucao,prog->instrucoes[indice]);
  return 1;
}
