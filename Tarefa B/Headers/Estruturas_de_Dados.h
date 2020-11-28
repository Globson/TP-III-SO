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
#define FIRSTFIT 1 //1 para Firstfit e 0 para NextFit


typedef char Instrucao[20]; //Armazena uma instrução

typedef struct Memvirutal{
    int memoria[MAXMEM*2];
    int mapadebits[MAXMEM*2];
}Memvirutal;

typedef struct Disco{
    int memoria[MAXMEM*10];
    int mapadebits[MAXMEM*10];
}Disco;

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

Memvirutal memvirtual;
Disco disco;
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
  int V_Disco;
  int V_Memvirtual;
  int Pos_Memvirtual;
  int Pos_Disco;
  int *Inteiro;
  int Cont;
  int Tam;
  Instrucao Programa[20];
}EstadoProcesso;

#endif //ESTRUTURAD_DE_DADOS_H

int AlocaDisco(int temp[],int qtd,int n,int flag,int *pos);
void DesalocaDisco(int qtd,int pos);
int AlocaNextFit(int temp[],int qtd,int n,int flag,int *pos);
int AlocaFirstFit(int temp[],int qtd,int n,int flag,int *pos,int *vpos,int *vflag);
void DesalocaMemVirtual(int qtd,int pos);
