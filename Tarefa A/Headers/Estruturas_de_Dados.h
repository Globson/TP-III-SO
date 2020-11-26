#ifndef ESTRUTURAD_DE_DADOS_H
#define ESTRUTURAD_DE_DADOS_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#define MAXTAM 100
#define BUFFER 256
#define MAXMEM 15

typedef char Instrucao[20]; //Armazena uma instrução

typedef struct FirstFit{
    int memoria[MAXMEM];
    int mapadebits[MAXMEM];
    int nospercorridos;
    int totalalocados;
    int erroemalocar;
    int totalfragmentos;
}FirstFit;

typedef struct NextFit{
    int memoria[MAXMEM];
    int mapadebits[MAXMEM];
    int nospercorridos;
    int ultimaalocacao;
    int totalalocados;
    int erroemalocar;
    int totalfragmentos;
}NextFit;

FirstFit firstfit;
NextFit nextfit;

typedef struct Programa{
  Instrucao instrucoes[20]; //Armazena instruções de um programa
  int Tam; //Tamanho do programa;
  int Frente,Tras; //Fila de programas
}Programa;

typedef struct EstadoProcesso{
  int Quant_Inteiros;
  int Alocado_V_inteiros;
  int Pos_Alocado;
  int *Inteiro;
  int Cont;
  int Tam;
  Instrucao Programa[20];
}EstadoProcesso;

#endif //ESTRUTURAD_DE_DADOS_H
