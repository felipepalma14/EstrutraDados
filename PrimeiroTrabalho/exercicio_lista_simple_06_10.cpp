#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <ctype.h>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoXY(int x, int y);

struct Data{
	int dia;
	int mes;
	int ano;
};
struct Contato{
	char email[40];
	char fone[8];
	char celular[9];
};

struct Profissional{
	int matricula;
	char nome[50];
	int cpf;
	char especialidade[50];
	Contato contato;
	Data data;
	char situacao[30];	
	struct Profissional *proximo;
	
}; 
//Variaveis globais
Profissional inicio,*pAux,*pAnt, *pProx;
int opcao,cont=0,ultimaMatricula;
char resp;
FILE *arquivo;

int lengthList(){
	Profissional *pTemp = inicio.proximo;
	int cont = 0;
	while(pTemp->proximo != NULL){
		cont++;
		pTemp = pTemp->proximo;
	}
	return cont; 
}

void gotoXY(int x, int y) 
{ 
CursorPosition.X = x; // Locates column
CursorPosition.Y = y; // Locates Row
SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
}

static void ClearLine(int tempCpf){
		char str[11];
		sprintf(str,"%d",tempCpf);
		//printf("%d",strlen(str));
        SetConsoleCursorPosition(console,CursorPosition);
        WriteConsole(console,("                     "),strlen(str),NULL,NULL);
		//Write(new string(' ', Console.WindowWidth)); 
        SetConsoleCursorPosition(0, CursorPosition);
    }
// ************************** MENU *******************************
void menu(){
		system("cls");
		gotoXY(20,4);
		printf("APS - Atendimento Profissional de Saude");
		//printf("\t\t\nEscolha sua a opcao desejada:\n");
		gotoXY(22,8);
		printf("Inserir_______________________ [1]\n");
		gotoXY(22,9);
		printf("Imprimir______________________ [2]\n");
		gotoXY(22,10);
		printf("Atualizar_____________________ [3]\n");
		gotoXY(22,11);
		printf("Remover_______________________ [4]\n");
		gotoXY(22,12);
		printf("Aniversarios__________________ [5]\n");
		gotoXY(22,13);
		printf("Sair__________________________ [6]\n");
		gotoXY(22,14);
		
		gotoXY(22,15);
		printf("Opcao: ........................ ");
		scanf("%d",&opcao);
}


void menu_niver(){
	system("cls");
	gotoXY(25,4);
	printf("Aniversariante do mes");
		gotoXY(18,6);
		printf("Janeiro_______________________ [1]");
		gotoXY(18,7);
		printf("Fevereiro_____________________ [2]");
		gotoXY(18,8);
		printf("Marco_________________________ [3]");
		gotoXY(18,9);
		printf("Abril_________________________ [4]");
		gotoXY(18,10);
		printf("Maio__________________________ [5]");
		gotoXY(18,11);
		printf("Junho_________________________ [6]");
		gotoXY(18,12);
		printf("Julho_________________________ [7]");
		gotoXY(18,13);
		printf("Agosto________________________ [8]");
		gotoXY(18,14);
		printf("Setembro______________________ [9]");
		gotoXY(18,15);
		printf("Outubro_______________________ [10]");
		gotoXY(18,16);
		printf("Novembro______________________ [11]");
		gotoXY(18,17);
		printf("Dezembro______________________ [12]");
		printf("\n");
		gotoXY(18,18);
		printf("__________________________________\n");
		
}

int retiraEspaco(char nome[60]){
	int i;
	for(i=0;i < strlen(nome);i++){
		//printf("\na letra: %c",nome[i]);
		if(nome[i] == ' '){
			nome[i] = '_';
		}
	}
	//printf("novo nome: %s",nome);
}

int colocaEspaco(char nome[60]){
	int i;
	for(i=0;i < strlen(nome);i++){
		//printf("\na letra: %c",nome[i]);
		if(nome[i] == '_'){
			nome[i] = ' ';
		}
	}
	//printf("novo nome: %s",nome);
}


// #################### ARQUIVOS @#####################3

/*
Cria um arquivo
*/
FILE *criarArquivo(){
	arquivo = fopen("baseDados.txt","w");
	if(arquivo == NULL)
		printf("Erro ao criar o arquivo!!!!");
	
	return (arquivo);
}

/*
Abre arquivo pra ler
*/
FILE *abrirArquivo(FILE *arq){
	arq = fopen("baseDados.txt","r");
	if(arq == NULL){
		printf("Arquivo nao existe!!\n");
	
	}else{
		printf("Arquivo Aberto com sucesso!!!\n");
		return (arq);
	}
}

/*
Grava dados no arquivo
*/

void gravarArquivo(FILE *arq){
	arq = fopen("baseDados.txt","a");
	fprintf(arq,"%s %s %d %d %d %d %d %s %s\n",pAux->nome,pAux->especialidade,pAux->matricula,pAux->cpf,pAux->data.dia,pAux->data.mes,pAux->data.ano,pAux->contato.email,pAux->situacao); 
	fflush(arq);
	gotoXY(20,19);
	printf("Dados gravados!!!\n");
	fclose(arq);
	}
void gravarTudo(FILE *arq){	
	pAux = inicio.proximo;
	char tempNome[50];
	arq = fopen("baseDados.txt","w");
	while(pAux->proximo!= NULL){
		strcpy(tempNome,pAux->nome);
		retiraEspaco(tempNome);
		fprintf(arq,"%s %s %d %d %d %d %d %s %s\n",tempNome,pAux->especialidade,pAux->matricula,pAux->cpf,pAux->data.dia,pAux->data.mes,pAux->data.ano,pAux->contato.email,pAux->situacao); 
		fflush(arq);	
		pAux = pAux->proximo;	
		}
	fclose(arq);
}	
	

void lerDados(FILE *arq){
	arq = abrirArquivo(arq);
	pAux = &inicio;
		
	char tempNome[50],especialidade[50];
	pAux->proximo = (struct Profissional*)malloc(sizeof(Profissional));
	pAux = pAux->proximo;
	while(fscanf(arq,"%s %s %d %d %d %d %d %s %s\n",tempNome,pAux->especialidade,&pAux->matricula,&pAux->cpf,&pAux->data.dia,&pAux->data.mes,&pAux->data.ano,pAux->contato.email,pAux->situacao) != EOF){
		pAux->proximo = (struct Profissional*)malloc(sizeof(Profissional));
		//printf("%s %s %d\n",pAux->nome,pAux->especialidade,pAux->matricula);
		colocaEspaco(tempNome);
		strcpy(pAux->nome,tempNome);
		ultimaMatricula = pAux->matricula;
		pAux = pAux->proximo;
	}
	
	pAux->proximo = NULL;
	cont = lengthList();
	printf("QTD dados: %d\n",cont);
	//printf("%d",ultimaMatricula);
	fclose(arq);		
}

// ********************* FUNCOES ***************************************

int verificaCPF(int cpf){
	pAnt = inicio.proximo;
	int retorno = 0;
	// PROBLEMA QUANDO  NAO TEM DADOS NO ARQUIVO
	if(cont == 0){
		pAux->cpf = cpf;
		return retorno;
	}else{
		while(pAnt->proximo != NULL){
			if(pAnt->cpf == cpf){
				//printf("Tem cpf's iguais!!\n");
				retorno = 1;
				break;
			}
			pAnt = pAnt->proximo;
		}
		pAux->cpf = cpf;
		return retorno;
}
}

void inserir_prof(){
	
	pAux = inicio.proximo;
	
	int tempCpf;
		// procura o ultimo da lista
	while(pAux->proximo){
		pAux = pAux->proximo;
	}
	
	do{
		int tam = lengthList();
		system("cls");
		gotoXY(30,4);
		printf("Inserir Profissional");
		//printf("\nInsira as informacoes necessarias:\n");
		
		pAux->proximo = (struct Profissional*)malloc(sizeof(struct Profissional));
		pAux = pAux->proximo;	// direciona para o proximo ,mostrando que eh o ultimo	
		
		char tempNome[50];	
		gotoXY(20,6);
		printf("NOME:................. ");
		
		fflush(stdin);
		gets(tempNome);
		retiraEspaco(tempNome);
		strcpy(pAux->nome,tempNome);
		//scanf("%s",&pAux->nome);
		gotoXY(20,7);
		printf("MATRICULA:............ ");
		scanf("%d",&pAux->matricula);
		
		gotoXY(20,8);
		printf("CPF:.................. ");
		
		scanf("%d",&tempCpf);
		
		//scanf("%d",&pAux->cpf);
		while(verificaCPF(tempCpf) == 1){
			gotoXY(20,8);
			printf("CPF ja registrado, digite novamente:\n");
			gotoXY(20,9);
			scanf("%d",&tempCpf);
			ClearLine(tempCpf);		
		}gotoXY(20,9);
		printf("CPF ok!!!");
		
		gotoXY(20,10);
		printf("ESPECIALIDADE:......... ");
		scanf("%s",&pAux->especialidade);
		
		gotoXY(30,11);
		printf("DATA DE NASCIMENTO");
		gotoXY(20,12);
		printf("Dia:.................... ");
		scanf("%d",&pAux->data.dia);
		gotoXY(20,13);
		printf("Mes:.................... ");
		scanf("%d",&pAux->data.mes);
		gotoXY(20,14);
		printf("Ano:.................... ");
		scanf("%d",&pAux->data.ano);
		gotoXY(30,15);
		printf("DADOS PESSOAIS");
		gotoXY(20,16);
		printf("EMAIL:.................. ");
		scanf("%s",&pAux->contato.email);
		gotoXY(20,17);
		printf("FONE:................... ");
		scanf("%s",&pAux->contato.fone);
		gotoXY(20,18);
		printf("CELULAR:................ ");
		scanf("%s",&pAux->contato.celular);
		gotoXY(20,19);
		printf("SITUACAO:............... ");
		scanf("%s",&pAux->situacao);
		
		
		if (tam < 1){
			//gotoXY(25,19);
			//printf("Criando arquivo\n");
			arquivo = criarArquivo();
			gravarArquivo(arquivo);	
		}else{
			//gotoXY(25,19);
			//printf("gravando dados\n");
			gravarArquivo(arquivo);	
		}	
				
		fclose(arquivo);
		gotoXY(15,20);
		printf("Deseja inserir + sim[s] ou nao[qualquer tecla] >>> ");
		scanf("%s",&resp);
		
		
		
		pAux->proximo = NULL;
		system("cls");
		
	}while(resp == 's');
		
}

void atualizar_campo(){
	switch(resp){
		case '1':
			gotoXY(17,22);
			printf("Digite o nome: ");
			scanf("%s",pAux->nome); 
			break;
		case '2':
			gotoXY(17,22);
			printf("Digite o CPF: ");
			scanf("%d",&pAux->cpf); 
			break;				
		case '3':
			gotoXY(17,22);
			printf("Digite o Especialidade: ");
			scanf("%s",pAux->especialidade); 
			break;		
		case '4':
			gotoXY(17,22);
			printf("Digite o Situação: ");
			scanf("%s",pAux->situacao); 
			break;		
	}	
	
	gravarTudo(arquivo);
	
}
void atualizar(){
	system("cls");
	gotoXY(30,4);
	printf("ATUALIZAR REGISTRO");
	gotoXY(1,5);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	int tempMatricula;
	
	do{
		resp='0';
		gotoXY(20,6);
		printf("Digite a matricula:........... ");
		scanf("%d",&tempMatricula);
		pAux = &inicio;
		char tempNome[50];
		while(pAux->matricula != tempMatricula && pAux->proximo != NULL){
			//pAnt = pAux;
			pAux = pAux->proximo;
		}if(pAux->matricula == tempMatricula){
			gotoXY(30,8);
			printf("DADOS DO PROFISSIONAL");
			gotoXY(1,9);
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			gotoXY(15,10);
			printf("Profissional:.............. %s",&pAux->nome);
			gotoXY(15,11);
			printf("CPF:....................... %d",pAux->cpf);
			gotoXY(15,12);
			printf("Especialidade:............. %s\n",&pAux->especialidade);
			gotoXY(15,13);
			printf("Situação:.................. %s\n",&pAux->situacao);
			
			gotoXY(1,15);
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			gotoXY(20,16);
			printf("Qual campo deseja atualizar?");
			gotoXY(17,17);
			printf("nome______________________[1]");
			gotoXY(17,18);
			printf("CPF_______________________[2]");
			gotoXY(17,19);
			printf("Especialidade_____________[3]");
			gotoXY(17,20);
			printf("Situação__________________[4]");			
			gotoXY(17,21);
			printf(">>> ");
			scanf("%s",&resp);
			atualizar_campo();
			
		}
		else{
			gotoXY(25,8);
			printf("Matricula inexistente!!!");
			gotoXY(20,9);
			system("pause");
			system("cls");
			
		}
		system("cls");
		gotoXY(20,10);
		printf("Deseja continuar atualizando?");
		gotoXY(20,11);
		printf("Sim[S] / Nao [outra tecla] >>> ");
		scanf("%s",&resp);
		//system("cls");
		
	}while(resp == 's');
}
void remover(){
	system("cls");
	gotoXY(30,4);
	printf("REMOVER REGISTRO");		
	
	do{
		int tempMatricula;
		resp='0';
		gotoXY(20,10);
		printf("Digite a matricula: ");
		scanf("%d",&tempMatricula);
		pAux = &inicio;
		while(pAux->matricula != tempMatricula && pAux->proximo != NULL){
			pAnt = pAux;
			pAux = pAux->proximo;
		}if(pAux->matricula == tempMatricula){
			gotoXY(20,11);
			printf("Deseja realmente remover: %s",&pAux->nome);
			gotoXY(20,12);
			printf("Sim[S] / Nao [outra tecla] >>> ");
			scanf("%s",&resp);
			if(resp == 's'){
				pAnt->proximo = pAux->proximo;
				pAux->proximo = NULL;
				pAnt = NULL;
				//printf("%s",pAux->nome);
				delete pAux;
				gravarTudo(arquivo);
				system("cls");
				gotoXY(30,8);
				printf("Dados Apagado com sucesso!!!");
			}	
		}
		else{
			gotoXY(20,14);
			printf("Matricula inexistente!!!\n");
			system("pause");
			system("cls");
			pAnt = NULL;
			pAux = NULL;
		}
		gotoXY(20,17);
		printf("Deseja continuar removendo?");
		gotoXY(20,18);
		printf("Sim[S] / Nao [outra tecla] >>> ");
		scanf("%s",&resp);
		system("cls");
		
	}while(resp == 's');
	
	
}


/// ******************** RELATORIOS ************************************

void imprimir(){
	int cont = lengthList();
	pAux = inicio.proximo;
	int linha = 7;
	system("cls");
	gotoXY(30,4);
	printf("EXIBINDO REGISTROS");
	gotoXY(1,5);
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	
	gotoXY(1,6);
	printf("MATRICULA");
	
	gotoXY(13,6);
	printf("NOME");
	
	gotoXY(43,6);
	printf("CPF");
	
	gotoXY(53,6);
	printf("ESPECIALIDADE");
	
	gotoXY(68,6);
	printf("STATUS");
	
	if (cont == 0){
		gotoXY(30,30);
		printf("sem profissionais cadastrados!!!");
	}else{
		
		while(pAux->proximo!= NULL){
			
			gotoXY(1,linha);
			printf("%d",pAux->matricula);
			gotoXY(13,linha);
			printf("%s",&pAux->nome);
			gotoXY(43,linha);
			printf("%d",pAux->cpf);
			gotoXY(53,linha);
			printf("%s",&pAux->especialidade);
			gotoXY(68,linha);
			printf("%s",&pAux->situacao);
			
			
			pAux = pAux->proximo;	
			linha++;
			}
		}	
	
	//printf("\nQuantidade de Dados:................. %d\n", cont);
	gotoXY(1,linha);
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	gotoXY(20,linha+1);
	system("pause");
	system("cls");
	
	}


void niverMes(){
	
	
	int linha = 8;
	int tempMes,cont = 0;
	//system("cls");
	
	do{
		menu_niver();
		pAux = &inicio;
		resp='0';
		
		gotoXY(20,20);
		printf("Digite o mes: ");
		scanf("%d",&tempMes);
		system("cls");
		
		gotoXY(25,4);
		printf("REGISTRO ANIVERSARIANTES");		
		gotoXY(1,7);
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		gotoXY(15,8);
		printf("Profissional"); // ................. %s",&pAux->nome);
		gotoXY(50,8);
		printf("Nascimento");
		gotoXY(1,9);
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		while(pAux){
			if(pAux->data.mes == tempMes){
				cont++;
				gotoXY(15,linha);
				printf("%s",&pAux->nome);
				gotoXY(50,linha);
				printf("%d/%d/%d",pAux->data.dia,pAux->data.mes,pAux->data.ano);
				//gotoXY(1,linha+2);
				//printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			}
			//gotoXY(1,linha+2);
			//printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			pAux = pAux->proximo;	
			linha++;
			}	
		gotoXY(1,linha);
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

		if(cont == 0){
			system("cls");
			gotoXY(15,7);
			printf("Nao ha dados para este mes!!!\n");
			system("pause");
			cont = 0;
			
		}		
		// error aqui ao tentar fazer outra verificacao do relatorio
		gotoXY(15,linha+1);
		printf("Exibir novo relatorio? Sim[S] / Nao [outra tecla]");
		gotoXY(15,linha+2);
		printf(">>>>> ");
		scanf("%s",&resp);
		system("cls");
		
		
	}while(resp == 's');
	
	
}

// ********************** FUNCAO PRINCIPAL ***************************
int main(void){
	
	//verificar a opcao 
	do{
		lerDados(arquivo);
		menu();
		int tam = lengthList();
		switch(opcao){
			case 1:
				inserir_prof();
				break;
			case 2:
				imprimir();
				
				break;
			case 3:
				atualizar();
				break;
			case 4:
				remover();
				break;
			case 5:
				niverMes();
				break;
			case 6:
				exit(0);
				break;
			
			default:
				printf("Opcao invalida\n");
				break;
		}
	}	while(opcao != 0);
	
	system("cls");
}
