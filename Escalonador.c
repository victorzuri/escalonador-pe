#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Escalonador.h"
#include "Fila.h"

typedef struct processo{
	int pid;
	int entrada;	
	int duracao;
	int prioridade;
}Processo;

struct escalonador{
	int totalProcessos;
	int tq; //tempo de quantum
	int fet; //fator de envelhecimento de tarefas
	int trace; //0 = false e 1 = true;
	int delay; //0 = false e 1 = true;
	int tDelay;
	Processo* processos;	
};

/*Imprimir todos os processo carregados*/
void imprimirProcessos(Escalonador *e){
	int i;
	system("CLS");
	printf("\nNumero de processos em memoria: %d\n\n",e->totalProcessos);
	for(i=0;i<e->totalProcessos;i++){
		printf("Processo %d - Entrada: %dns Duracao: %dns Prioridade: %dns\n",e->processos[i].pid,e->processos[i].entrada,e->processos[i].duracao,e->processos[i].prioridade);
	}	
	system("PAUSE");	
}

/*Setar as configurações do escalonador*/
void setarConfiguracoes(Escalonador* e){
	char trace,delay;
	system("CLS");
	printf("\nInforme o tempo quantum: "); scanf("%d",&e->tq);
	printf("\nInforme o fato de envelhecimento de tarefas: "); scanf("%d",&e->fet);		
	printf("\nExibir traces de execucao? (S/N) "); scanf(" %c",&trace);
	if(trace == 'S'){
		e->trace = 1;
	}else{
		e->trace = 0;
	}	
	printf("\nUtilizar o recurso de sleep para simulacao de tempo? (S/N) "); scanf(" %c",&delay);	
	if(delay == 'S'){
		e->delay = 1;
		printf("\nInforme o tempo de delay (em ms): "); scanf("%d",&e->tDelay);
	}else{
		e->delay = 0;
	}
	system("PAUSE");
}

/*Função auxiliar - Gravar no arquivo de Logs todos os escalonementos executados*/
void gravarLog(char*estrategia,float tMedioExec, float tMedioEspera){
	
	FILE *arqLog;
	
	arqLog = fopen("logExec.txt","a");
	if(arqLog == NULL){
		printf("\nERRO: Falha ao abrir o arquivo!\n");
		exit(1);
	}		
	//pegar a data hora atual
	time_t dataHoraCorrente;    
	dataHoraCorrente = time(NULL);	
	char dataHoraString[50];	
	strcpy(dataHoraString,ctime(&dataHoraCorrente));    
    dataHoraString[strlen(dataHoraString)-1] = '\0';    
    //grava no arquivo de log
	fprintf(arqLog,"%s - Estrategia: %s - Tempo Medio Execucao: %f - Tempo Medio Espera: %f\n",dataHoraString,estrategia,tMedioExec,tMedioEspera);		
	fclose(arqLog);	
}

/*Executar a estatégia de escolanomento - FCFS*/
void executarFCFS(Escalonador* e){
	int i;
	int clock = 0;
	float tMedioEspera = 0;
	float tMedioExec = 0;
	//criar fila de processos	
	Fila * filaProcessos = cria();
	for(i=0; i<e->totalProcessos; i++){
		insere(filaProcessos,e->processos[i].pid);	
	}
	//imprime(filaProcessos);
	system("PAUSE");
	while (!vazia(filaProcessos)){
		int tempoEspera = 0;
		int pid = retira (filaProcessos);
		int entrada = e->processos[pid-1000].entrada;
		int duracao = e->processos[pid-1000].duracao;
		tempoEspera = (clock - entrada);
		tMedioEspera += tempoEspera;
		clock += duracao;
		tMedioExec += (tempoEspera + duracao);
	}
	tMedioEspera = tMedioEspera / e->totalProcessos;
	tMedioExec = tMedioExec / e->totalProcessos;
	printf("\n\nTempo medio de espera: %f - Tempo medio de execucao: %f\n\n", tMedioEspera, tMedioExec);	
	/*Gravar dados da execução no arquivo LOG*/
	gravarLog("FCFS",tMedioExec,tMedioEspera);	
	system("PAUSE");	
}

/*Carregar em memória todos os processo lidos do arquivo - para serem escalonados*/
Escalonador* carregarProcessos(){
	FILE *arqProcessos;
	arqProcessos = fopen("processos.txt","r");	
	if(arqProcessos == NULL){
		printf("\nERRO: Falha ao abrir o arquivo!\n");
		return NULL;
	}
	Escalonador* e  = (Escalonador*) malloc(sizeof(Escalonador));
	if(e == NULL){
		printf("\nERRO: Falta de memoria!\n");
		return NULL;
	}
	
	e->tq = 2;
	e->fet = 1;
	e->trace = 0; //false
	e->delay = 0; //false
	e->tDelay = 0; //0 milisegundos
	
	fscanf(arqProcessos,"%d\n",&e->totalProcessos);
		
	/*Criar o vetor de processos dinamicamente*/
	e->processos = (Processo*) malloc(e->totalProcessos*sizeof(Processo));

	int i;
	for(i=0;i<e->totalProcessos;i++){
		fscanf(arqProcessos,"%d %d %d\n",&e->processos[i].entrada,
							&e->processos[i].duracao,&e->processos[i].prioridade);	
		e->processos[i].pid = 1000+i;				
	}
	fclose(arqProcessos);
	imprimirProcessos(e);
		
	system("CLS");
	printf("\n\nArquivo de processo carregado com sucesso.");
	system("PAUSE");
	
	return e;
}

