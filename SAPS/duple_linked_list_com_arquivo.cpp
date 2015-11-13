#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>


using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int x, int y){
CursorPosition.X = x; // Locates column
CursorPosition.Y = y; // Locates Row
SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
}

// ARQUIVO
FILE *arquivoCliente;
FILE *arquivoProfissional;
FILE *arquivoAtendimento;
char opcao;

int retiraEspaco(char nome[60]){
	int i;
	for(i=0;i < strlen(nome);i++){
		if(nome[i] == ' '){
			nome[i] = '_';
		}
	}
}

int colocaEspaco(char nome[60]){
	int i;
	for(i=0;i < strlen(nome);i++){
		if(nome[i] == '_'){
			nome[i] = ' ';
		}
	}
}


static void ClearLine(){
    SetConsoleCursorPosition(console,CursorPosition);
    WriteConsole(console,("                              "),30,NULL,NULL);
	//Write(new string(' ', Console.WindowWidth)); 
    SetConsoleCursorPosition(0, CursorPosition);
    }


// criando a estrutura
struct Data{
	int dia,mes,ano;
};

struct Contato{
	char telefone[9],celular[9],email[50];
};

struct Endereco{
	char logradouro[100],complemento[60],estado[2];
	long CEP;
};

struct CategoriaProfissional{
	struct CategoriaProfissional *anterior;
	int codigo;
	char nome[200];
	char status[50];
	struct CategoriaProfissional *proximo;
};

struct Cliente{
	struct Cliente *anterior;
	int codigo;
	char nome[200];
	char cpf[11];
	Data nascimento;
	char tipoSanguineo[40];//Colocar um menu de opcoes
	double peso;
	Contato contato;
	Endereco endereco;
	struct Cliente *proximo;
	
};
struct ProfissionalSaude{
	struct ProfissionalSaude *anterior;
	int matricula;
	int regisProfis;
	CategoriaProfissional categoria;
	char cpf[18],nome[200];
	Data nascimento;
	Endereco endereco;	
	struct ProfissionalSaude *proximo;
};

struct FichaAtendimento{
	FichaAtendimento *anterior;
	int codigoAtendimento;
	ProfissionalSaude profissional;
	CategoriaProfissional categAtendimento;
	Cliente cliente;
	Data dataAtendimento;
	char descricao[200];
	Data diaAgendado;
	FichaAtendimento *proximo;
};

struct TipoListaAtendimento{
	FichaAtendimento *inicio = NULL;
	FichaAtendimento *fim = NULL;
};

TipoListaAtendimento listaAtendimento;



void iniciaListaCategoria(TipoListaAtendimento *pLista){
	pLista->inicio = NULL;
	pLista->fim = NULL;
}


struct TipoListaCategoria{
	CategoriaProfissional *inicio = NULL;
	CategoriaProfissional *fim = NULL;
};


struct TipoListaProfissional{
	ProfissionalSaude *inicio = NULL;
	ProfissionalSaude *fim = NULL;
}; 


struct TipoListaCliente{
	Cliente *inicio = NULL;
	Cliente *fim = NULL;
};
 
/*
VARIAVEIS
*/
TipoListaProfissional listaDuplaCadeadaProfisional;
TipoListaCategoria listaCategoria;
TipoListaCliente listaDuplaCadeadaCliente;
//##########################################################
 
// Categoria
void menuPrincipal();
void inserirCategoria(TipoListaCategoria *pLista);
void imprimirCategoria(TipoListaCategoria *pLista);
void atualizarCategoria(TipoListaCategoria *pLista);
void excluirCategoria(TipoListaCategoria *pLista);
void gravaTudo(TipoListaCategoria *pLista);
void ler(TipoListaCategoria *pLista);

void iniciaListaCategoria(TipoListaCategoria *pLista){
	pLista->inicio = NULL;
	pLista->fim = NULL;
}


void menuCategoria(TipoListaCategoria *pLista){
	system("cls");
	int opt; 
	gotoXY(30,4);
	printf("Menu Categoria");
	gotoXY(20,6);
	printf("1 - inserir Categoria Profissional");
	gotoXY(20,7);
	printf("2 - Imprimir Categorias");
	gotoXY(20,8);
	printf("3 - Excluir Categoria Profissional");
	gotoXY(20,9);
	printf("4 - Atualizar Categoria Profissional");
	gotoXY(20,10);
	printf("5 - Sair");
	gotoXY(20,11);
	printf(">>> ");
	scanf("%d",&opt);
		
	do{
		
		switch(opt){
			case 1:
				inserirCategoria(pLista);
				break;
			case 2:
				imprimirCategoria(pLista);
				break;
			case 3:
				excluirCategoria(pLista);
				break;
			case 4:
				atualizarCategoria(pLista);
				break;
			case 5:
				opt = 0;
				menuPrincipal();
				break;
			default:
				printf("opt invalida!!!\n");
				menuCategoria(pLista);
				break;
		}
	opt=0;
	}while(opt != 0);
}


void inserirCategoria(TipoListaCategoria *pLista){
	CategoriaProfissional *novaCategoria;
	novaCategoria = new CategoriaProfissional;
	
	printf("Digite codigo da Categoria: ");
	scanf("%d",&novaCategoria->codigo);
	
	fflush(stdin);
	printf("Digite a Categoria: ");
	gets(novaCategoria->nome);
	
	fflush(stdin);
	printf("Status: ");
	gets(novaCategoria->status);
	
	novaCategoria->proximo = NULL;
	novaCategoria->anterior = NULL;
	
	if(pLista->inicio == NULL){
		pLista->inicio = novaCategoria;
		pLista->fim = novaCategoria;
	}
	else{
		// Apontando para o novo Elemento
		pLista->fim->proximo =novaCategoria;
		//Fazendo a volta (Duplo encadeado)
		novaCategoria->anterior = pLista->fim;
		//Novo fim para a lista 
		pLista->fim = novaCategoria;
	}
	
	printf("Categoria Cadastrada!!!");
	system("pause");
	gravaTudo(pLista);
	menuCategoria(pLista);
}

void imprimirCategoria(TipoListaCategoria *pLista){	
	system("cls");
	CategoriaProfissional *aux;
	int linha =5;
	gotoXY(20,2);
	printf("CATEGORIAS");
	gotoXY(1,3);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	gotoXY(1,4);
	printf("|");
	gotoXY(3,4);
	printf("ID");
	gotoXY(7,4);
	printf("|");
	gotoXY(10,4);
	printf("Descricao");
	gotoXY(25,4);
	printf("|");
			
	if(pLista->inicio == NULL){
		printf("Lista Vazia\n");
	}else{
		aux = pLista->inicio;
		while(aux != NULL){
			gotoXY(3,linha);
			printf("%d",aux->codigo);
			gotoXY(9,linha);
			printf("%s",aux->nome);
			aux = aux->proximo;
			linha++;
		}
	}
	gotoXY(20,linha++);
	system("pause");
	menuCategoria(pLista);
}

void atualizarCategoria(TipoListaCategoria *pLista){
	CategoriaProfissional *aux;
	aux= pLista->inicio;
	int tempCodigo;
	char tempNome[200];
	system("cls");
	gotoXY(30,2);
	printf("ATUALIZAR REGISTRO");
	gotoXY(1,3);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

	
	do{
		gotoXY(2,4);
		printf("Digite codigo da Categoria: ");
		scanf("%d",&tempCodigo);
		char tempNome[200];
		system("cls");
		gotoXY(30,6);
		printf("DADOS DA CATEGORIA");
		while(aux->codigo != tempCodigo && aux->proximo != NULL){
			aux = aux->proximo;
		}if(aux->codigo == tempCodigo){
			gotoXY(1,6);
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			gotoXY(15,9);
			printf("Categoria:.................... %s",aux->nome);
			gotoXY(15,10);
			printf("Status:....................... %s",aux->status);			
			gotoXY(1,11);
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			gotoXY(20,12);
			printf("Qual campo deseja atualizar?");
			gotoXY(17,13);
			printf("Descricao______________________[1]");
			gotoXY(17,14);
			printf("Status_________________________[2]");
			gotoXY(17,15);
			printf("Sair___________________________[0]");
			
						
			gotoXY(17,16);
			printf(">>> ");
			scanf("%s",&opcao);
	
			switch(opcao){
				case '1':
					gotoXY(17,18);
					printf("Digite a descricao: ");
					scanf("%s",aux->nome); 
					gotoXY(20,19);
					printf("Dados Atualizados!!!");
					gotoXY(20,20);
					system("pause");
					system("cls");
					break;
				case '2':
					gotoXY(17,18);
					printf("Digite o status: ");
					scanf("%d",&aux->status);
					
					gotoXY(20,19);
					printf("Dados Atualizados!!!");
					gotoXY(20,20);
					system("pause");
					system("cls"); 
					break;
				case '0':
					gotoXY(17,18);
					break;
				default:
					gotoXY(17,18);
					printf("opcao invalida!!!");
					break;								
				
				}
				
			system("cls");
			gotoXY(20,10);
			printf("Deseja continuar atualizando?");
			gotoXY(20,11);
			printf("Sim[S] / Nao [outra tecla] >>> ");
			scanf("%s",&opcao);
			system("cls"); 
		}else{
			gotoXY(25,8);
			printf("Categoria inexistente!!!");
			gotoXY(20,9);
			system("pause");
			system("cls");
			
		}
		//system("cls");
		
	}while(opcao == 's');

	
			gravaTudo(pLista);
			menuCategoria(pLista);
}

void excluirCategoria(TipoListaCategoria *pLista){
	system("cls");
	int tempCodigo;
	CategoriaProfissional *elem_atual, *elem_proximo,*elem_anterior;
	gotoXY(25,3);
	printf("REMOVER CATEGORIA");
	gotoXY(1,4);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	
	CategoriaProfissional *inicio,*fim;
	inicio = pLista->inicio;
	fim = pLista->fim;
	if(inicio == NULL){
		// se matricula nao cadastrada
		gotoXY(25,6);
		printf("Nao ha dados!!!");
		gotoXY(20,7);
		system("pause");
		menuCategoria(pLista);
	}else{
		gotoXY(2,5);
		printf("Digite o codigo: ");
		scanf("%d",&tempCodigo);
		elem_atual = inicio;
		while(elem_atual != NULL){
			elem_proximo = elem_atual->proximo;
			elem_anterior = elem_atual->anterior;
			
			if(elem_atual->codigo == tempCodigo){
				gotoXY(2,6);
				printf("Categoria: %s",elem_atual->nome);
				fflush(stdin);
				gotoXY(2,8);
				printf("Deseja realmente excluir? [s/n] >> ");
				scanf("%s",&opcao);
				if(opcao == 's'){
					if(elem_anterior != NULL)//verifica do meio
						if(elem_proximo != NULL){
							elem_anterior->proximo = elem_proximo; 
							elem_proximo->anterior = elem_anterior;
							free(elem_atual);
						}else{
							// verifica do fim
						
							elem_anterior->proximo = NULL;
							pLista->fim = elem_anterior;
							free(elem_atual);
			
						}
					else if(elem_proximo != NULL){
						
						elem_proximo->anterior = NULL;
						pLista->inicio = elem_proximo;
						free(elem_atual);
						
					}else{
						
						free(elem_atual);
						pLista->inicio = pLista->fim = NULL;
						
					}
				gotoXY(20,9);
				printf("Dado removido com sucesso!!!");
				gotoXY(20,10);
				system("pause");
				gravaTudo(pLista);
				menuCategoria(pLista);
				break;
				}else{
					menuCategoria(pLista);
					break;
				}
		}
		elem_atual = elem_atual->proximo;
		}
			gotoXY(20,6);
			printf("Codigo nao encontrado!!!");
			gotoXY(20,7);
			system("pause");
			menuCategoria(pLista);
	}

} 

void gravaTudo(TipoListaCategoria *pLista){
	char tempNome[200];
	CategoriaProfissional *categoria = new CategoriaProfissional;
	arquivoCliente = fopen("categorias.txt","w");
	if(arquivoCliente == NULL){
		printf("Nao foi possivel criar o arquivo\n");
		system("pause");
	}else{
		CategoriaProfissional *aux;
		aux = pLista->inicio;
		while(aux != NULL){
			strcpy(tempNome,aux->nome);
			retiraEspaco(tempNome);
			fprintf(arquivoCliente,"%d %s %s\n",aux->codigo, tempNome,aux->status); 
			fflush(arquivoCliente);
			aux = aux->proximo;
		}
		
	}
		
	fclose(arquivoCliente);
}


void ler(TipoListaCategoria *pLista){
	iniciaListaCategoria(pLista);
	//FILE *arquivoLer; 
	char tempNome[200];
	CategoriaProfissional *aux;
	aux = new CategoriaProfissional;
	
	aux->proximo = NULL;
	aux->anterior = NULL;
	arquivoCliente = fopen("categorias.txt","r");
	
	if(arquivoCliente == NULL){
		printf("impossivel abrir o arquivo\n");
	}else{
		while(fscanf(arquivoCliente,"%d %s %s\n",&aux->codigo,tempNome,aux->status) != EOF){
			colocaEspaco(tempNome);
			strcpy(aux->nome,tempNome);
			//ultimaMatricula = pAux->matricula;
	
			if(pLista->inicio == NULL){
				pLista->inicio = aux;
				pLista->fim = aux;
			}
			else{
				// Apontando para o novo Elemento
				pLista->fim->proximo =aux;
				//Fazendo a volta (Duplo encadeado)
				aux->anterior = pLista->fim;
				//Novo fim para a lista 
				pLista->fim = aux;
			}
			aux = aux->proximo;
			aux = new CategoriaProfissional;
		}
	}
	fclose(arquivoCliente);
	
}


/*
##################################################################################
PROFISSIONAL
##################################################################################
*/

void inserirProfissional(TipoListaProfissional *pLista);
void atualizarProfissional(TipoListaProfissional *pLista);
void excluirProfissional(TipoListaProfissional *pLista);
void imprimirProfissional(TipoListaProfissional *pLista,TipoListaCategoria *categorias);
void imprimirDeTras(TipoListaProfissional *pLista);
void lerProfissional(TipoListaProfissional *pLista);
void gravarProfissional(TipoListaProfissional *pLista);
void gravarProfissionalRelatorio(TipoListaProfissional *pLista);
char* verificaCategoriaProfissionalRelatorio(int codigoCategoriaProfissional);
// MENU PRINCIPAL




void menuPrincipal(){
	system("cls");
	gotoXY(30,4);
	printf("MENU PRINCIPAL");
	gotoXY(20,6);
	printf("1 - Profissionais");
	gotoXY(20,7);
	printf("2 - Clientes");
	gotoXY(20,8);
	printf("3 - Ficha de Atendimento");
	gotoXY(20,9);
	printf("4 - Categorias");
	gotoXY(20,10);
	printf("5 - Aniversario");
	gotoXY(20,11);
	printf("6 - Relatorios");
	gotoXY(20,12);
	printf("7 - Sair");
}
/*
* PROFISSONAL
*/


void verificaCategoriaProfissional(int codigoCategoriaProfissional);

void menuProfissional(TipoListaProfissional *pLista){
	system("cls");
	int opt; 
	gotoXY(30,4);
	printf("Menu Profissional");
	gotoXY(20,6);
	printf("1 - inserir Profissional de Saude");
	gotoXY(20,7);
	printf("2 - Imprimir Profissionais de Saude");
	gotoXY(20,8);
	printf("3 - Excluir Profissional de Saude");
	gotoXY(20,9);
	printf("4 - Atualizar Profissional de Saude");
	gotoXY(20,10);
	printf("5 - Sair");
	gotoXY(20,11);
	printf(">>> ");
	scanf("%d",&opt);
		
	do{
		
		switch(opt){
			case 1:
				inserirProfissional(pLista);
				break;
			case 2:
				imprimirProfissional(pLista,&listaCategoria);
				break;
			case 3:
				excluirProfissional(pLista);
				break;
			case 4:
				atualizarProfissional(pLista);
				break;
			case 5:
				opt = 0;
				menuPrincipal();
				break;
			default:
				printf("opt invalida!!!\n");
				break;
		}
	opt=0;
	}while(opt != 0);
}
// cria a lista
void iniciaListaProfissional(TipoListaProfissional *pLista){
	pLista->inicio = NULL;
	pLista->fim = NULL;
}



void mostrarCategorias(TipoListaCategoria *pLista){
	CategoriaProfissional *aux;
	int linha = 7;
		aux = pLista->inicio;
		while(aux != NULL){
			gotoXY(60,6);
			printf("ID\tDescricao");
			gotoXY(60,linha);
			printf("%d\t%s",aux->codigo,aux->nome);
			linha++;
			aux = aux->proximo;
		}
}

bool validaCategoria(TipoListaCategoria *pLista, int codCategoria){
	CategoriaProfissional *aux;
	aux = pLista->inicio;
	while(aux != NULL){
		if(aux->codigo == codCategoria){
			return true;
			
		}
	aux = aux->proximo;
	}
	return false;
}
//inserir no final
void inserirProfissional(TipoListaProfissional *pLista){
	// variaveis
	char tempNome[200],tempCpf[11];
	ProfissionalSaude *novoProfissional;
	novoProfissional = new ProfissionalSaude;
	system("cls");
	gotoXY(20,2);
	printf("CADASTRO DE PROFISSIONAL DE SAUDE");
	gotoXY(10,4);
	printf("Matricula: ");
	scanf("%d",&novoProfissional->matricula);
	gotoXY(10,5);
	printf("Registro Profissional: ");
	scanf("%d",&novoProfissional->regisProfis);
	
	mostrarCategorias(&listaCategoria);
	
	gotoXY(10,6);
	printf("Categoria: ");
	
	int tempCodCategoria;
	scanf("%d",&tempCodCategoria);
	while(!validaCategoria(&listaCategoria,tempCodCategoria)){
		// ARRUMAR AQUI
		gotoXY(20,6);
		printf("Categoria invalida!!!");
		sleep(3);
		ClearLine();
		gotoXY(10,6);
		printf("Categoria: ");

		scanf("%d",&tempCodCategoria);	
	}
	gotoXY(40,6);
	printf("OK");
	novoProfissional->categoria.codigo = tempCodCategoria;
	
	
	/*
	CRIAR FUNCAO QUE MOSTRA TODOS OS PROFISSIONAIS
	POR TIPO DE CATEGORIA(ESPECIALIDADE)
	*/
	gotoXY(10,7);
	printf("Nome: ");
	fflush(stdin);
	gets(tempNome);
	strcpy(novoProfissional->nome, tempNome);
	
	
	// VERIFICAR O CPF SE EH EXISTENTE
	gotoXY(10,8);
	printf("CPF: ");
	scanf("%s",novoProfissional->cpf);
	gotoXY(20,9);
	printf("ENDERECO");
	gotoXY(10,10);
	printf("Logradouro: ");
	fflush(stdin);
	gets(novoProfissional->endereco.logradouro);
	gotoXY(10,11);
	printf("Complemento: ");
	fflush(stdin);
	gets(novoProfissional->endereco.complemento);
	gotoXY(50,11);
	printf("Estado: ");
	fflush(stdin);
	gets(novoProfissional->endereco.estado);
	
	gotoXY(10,12);
	printf("CEP: ");
	scanf("%d",&novoProfissional->endereco.CEP);
	
	gotoXY(20,13);
	printf("DATA DE NASCIMENTO");
	gotoXY(10,14);
	printf("Dia: ");
	scanf("%d",&novoProfissional->nascimento.dia);
	gotoXY(20,14);
	printf("Mes: ");
	scanf("%d",&novoProfissional->nascimento.mes);
	gotoXY(30,14);
	printf("Ano: ");
	scanf("%d",&novoProfissional->nascimento.ano);
		
	
	novoProfissional->proximo = NULL;
	novoProfissional->anterior = NULL;
	
	if(pLista->inicio == NULL){
		pLista->inicio = novoProfissional;
		pLista->fim = novoProfissional;
	}
	else{
		// Apontando para o novo Elemento
		pLista->fim->proximo =novoProfissional;
		//Fazendo a volta (Duplo encadeado)
		novoProfissional->anterior = pLista->fim;
		//Novo fim para a lista 
		pLista->fim = novoProfissional;
	}
	printf("Profissional %s Inserido!!!\n",novoProfissional->nome);
	system("pause");
	gravarProfissional(pLista);
	menuProfissional(pLista);
}


void atualizarProfissional(TipoListaProfissional *pLista){
	ProfissionalSaude *aux;
	int tempMatricula;
	aux = pLista->inicio;
	system("cls");
	gotoXY(30,2);
	printf("ATUALIZAR REGISTRO");
	gotoXY(1,3);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	do{
		gotoXY(2,4);
		printf("Matricula: ");
		scanf("%d",&tempMatricula);
		char tempNome[200];
		system("cls");
		gotoXY(30,6);
		printf("DADOS DO PROFISSIONAL");
		while(aux->proximo != NULL && aux->matricula != tempMatricula){
			aux = aux->proximo;
		}if(aux->matricula == tempMatricula){
			gotoXY(1,6);
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			gotoXY(15,9);
			printf("Profissional:.................... %s",aux->nome);
			gotoXY(15,10);
			printf("N* de Registro:.................. %d",aux->regisProfis);
			gotoXY(15,11);
			printf("CPF:............................. %s",aux->cpf);			
			gotoXY(15,12);
			printf("Categoria:....................... ");
			verificaCategoriaProfissional(aux->categoria.codigo);			
			gotoXY(1,13);
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			gotoXY(20,14);
			printf("Qual campo deseja atualizar?");
			gotoXY(17,15);
			printf("Nome_________________________[1]");
			gotoXY(17,16);
			printf("N* Registro__________________[2]");
			gotoXY(17,17);
			printf("CPF__________________________[3]");
			gotoXY(17,18);
			printf("Categoria____________________[4]");
			gotoXY(17,19);
			printf("Sair_________________________[0]");
			
						
			gotoXY(17,20);
			printf(">>> ");
			scanf("%s",&opcao);
	
			switch(opcao){
				case '1':
					fflush(stdin);
					gotoXY(17,18);
					printf("Digite nome: ");
					gets(tempNome);
					strcpy(aux->nome,tempNome); 
					gotoXY(20,19);
					printf("Dados Atualizados!!!");
					gotoXY(20,20);
					system("pause");
					system("cls");
					break;
				case '2':
					gotoXY(17,18);
					printf("Digite N* Registro: ");
					scanf("%d",&aux->regisProfis);
					gotoXY(20,19);
					printf("Dados Atualizados!!!");
					gotoXY(20,20);
					system("pause");
					system("cls"); 
					break;
				case '3':
					gotoXY(17,18);
					printf("Digite CPF: ");
					scanf("%s",aux->cpf);
					gotoXY(20,19);
					printf("Dados Atualizados!!!");
					gotoXY(20,20);
					system("pause");
					system("cls"); 
					break;
				case '4':
					system("cls");
					mostrarCategorias(&listaCategoria);
					gotoXY(5,6);
					printf("Digite nova Categoria: ");
					scanf("%d",&aux->categoria.codigo);
					gotoXY(20,19);
					printf("Dados Atualizados!!!");
					gotoXY(20,20);
					system("pause");
					system("cls"); 
					break;
				case '0':
					gotoXY(17,18);
					break;
				default:
					gotoXY(17,18);
					printf("opcao invalida!!!");
					break;								
				
				}
				
			system("cls");
			gotoXY(20,10);
			printf("Deseja continuar atualizando?");
			gotoXY(20,11);
			printf("Sim[S] / Nao [outra tecla] >>> ");
			scanf("%s",&opcao);
			system("cls"); 
		}else{
			gotoXY(25,8);
			printf("Profissional inexistente!!!");
			gotoXY(20,9);
			system("pause");
			system("cls");
			
		}
		//system("cls");
		
	}while(opcao == 's');

	gravarProfissional(pLista);
	menuProfissional(pLista);
}


void excluirProfissional(TipoListaProfissional *pLista){
	int tempMatricula;
	system("cls");
	ProfissionalSaude *elem_atual, *elem_proximo,*elem_anterior;
	
	ProfissionalSaude *inicio,*fim;
	inicio = pLista->inicio;
	fim = pLista->fim;
	
	gotoXY(25,3);
	printf("REMOVER PROFISSIONAL");
	gotoXY(1,4);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	
	if(inicio == NULL){
		// se matricula nao cadastrada
		gotoXY(25,6);
		printf("Nao ha dados!!!");
		gotoXY(20,7);
		system("pause");
		menuProfissional(pLista);
	}else{
		gotoXY(2,5);
		printf("Digite a matricula: ");
		scanf("%d",&tempMatricula);
		elem_atual = inicio;
		while(elem_atual != NULL){
			elem_proximo = elem_atual->proximo;
			elem_anterior = elem_atual->anterior;
			
			if(elem_atual->matricula == tempMatricula){
				gotoXY(2,6);
				printf("Profissional: %s",elem_atual->nome);
				fflush(stdin);
				gotoXY(2,8);
				printf("Deseja realmente excluir? [s/n] >> ");
				scanf("%s",&opcao);
				if(opcao == 's'){
					if(elem_anterior != NULL)//verifica do meio
						if(elem_proximo != NULL){
							elem_anterior->proximo = elem_proximo; 
							elem_proximo->anterior = elem_anterior;
							free(elem_atual);
						}else{
							// verifica do fim
						
							elem_anterior->proximo = NULL;
							pLista->fim = elem_anterior;
							free(elem_atual);
			
						}
					else if(elem_proximo != NULL){
						
						elem_proximo->anterior = NULL;
						pLista->inicio = elem_proximo;
						free(elem_atual);
						
					}else{
						
						free(elem_atual);
						pLista->inicio = pLista->fim = NULL;
						
					}
				gotoXY(20,9);
				printf("Dado removido com sucesso!!!");
				gotoXY(20,10);
				system("pause");
				gravarProfissional(pLista);
				menuProfissional(pLista);
				break;
				}else{
					menuProfissional(pLista);
					break;
				}
		}
		elem_atual = elem_atual->proximo;
		}
			gotoXY(20,6);
			printf("Matricula nao encontrada!!!");
			gotoXY(20,7);
			system("pause");
			menuProfissional(pLista);
	}

} 


void verificaCategoriaProfissional(int codigoCategoriaProfissional){
	CategoriaProfissional *categoria =  listaCategoria.inicio;
	while(categoria !=NULL){
				if(codigoCategoriaProfissional == categoria->codigo){
					printf("%s",categoria->nome);
					break;		
				}
				categoria = categoria->proximo;
			}
}
void imprimirProfissional(TipoListaProfissional *pLista,TipoListaCategoria *categorias){
	system("cls");	
	ProfissionalSaude *aux;
	CategoriaProfissional *categoria;
	categoria = categorias->inicio;
	int linha=6;
	gotoXY(20,2);
	printf("Relacao de Profissionais");
	gotoXY(1,3);
	printf("-------------------------------------------------------------------------");
	gotoXY(1,4);
	printf("ID");
	gotoXY(4,4);
	printf("|");
	gotoXY(6,4);
	printf("Profissional");
	gotoXY(20,4);
	printf("|");
	gotoXY(22,4);
	printf("CPF");
	gotoXY(33,4);
	printf("|");
	gotoXY(34,4);
	printf("Registro");
	gotoXY(45,4);
	printf("|");
	gotoXY(47,4);
	printf("Categoria");
	gotoXY(60,4);
	printf("|");
	gotoXY(65,4);
	printf("Nascimento");
	gotoXY(80,4);
	printf("|");
	gotoXY(1,5);
	printf("--------------------------------------------------------------------------");
	
	if(pLista->inicio == NULL){
		gotoXY(20,7);
		printf("SEM PROFISSIONAIS CADASTRADOS!!!");
	}else{
		aux = pLista->inicio;
		while(aux != NULL){
			gotoXY(1,linha);
			printf("%d",aux->matricula);
			gotoXY(6,linha);
			printf("%s",aux->nome);
			gotoXY(21,linha);
			printf("%s",aux->cpf);
			gotoXY(34,linha);
			printf("%d",aux->regisProfis);
			gotoXY(46,linha);
			verificaCategoriaProfissional(aux->categoria.codigo);
			gotoXY(65,linha);
			printf("%d/%d/%d",aux->nascimento.dia,aux->nascimento.mes,aux->nascimento.ano);
			
			aux = aux->proximo;
			linha++;
		}
	}
	gotoXY(20,linha+2);
	system("pause");
	menuProfissional(pLista);
}

// teste para verificar duplo encadeamento
void imprimirDeTras(TipoListaProfissional *pLista){
	ProfissionalSaude *aux;
	if(pLista->fim == NULL){
		printf("Lista vazia\n"); 
	}else{
		aux =pLista->fim;
		while(aux != NULL){
			printf("Dados >>> %s\n",aux->nome);
			//system("pause");
			aux = aux->anterior;
		}
	
	printf("Fim da lista\n");
	}
	system("pause");
	menuProfissional(pLista);
}

void gravarProfissional(TipoListaProfissional *pLista){
	//FILE *arquivo;
	char tempNome[200], tempLogradouro[200],tempComplemento[200];
	ProfissionalSaude *profissional = new ProfissionalSaude;
	arquivoProfissional = fopen("profissional.txt","w");
	if(arquivoProfissional == NULL){
		printf("Nao foi possivel criar o arquivo\n");
		system("pause");
	}else{
		ProfissionalSaude *aux;
		aux = pLista->inicio;
		while(aux != NULL){
			strcpy(tempNome,aux->nome);
			strcpy(tempLogradouro,aux->endereco.logradouro);
			strcpy(tempComplemento,aux->endereco.complemento);		
			retiraEspaco(tempNome);
			retiraEspaco(tempLogradouro);
			retiraEspaco(tempComplemento);
			fprintf(arquivoProfissional,"%d %s %s %d %d %s %d %s %s %d %d %d\n",
			aux->matricula,tempNome,aux->cpf,aux->regisProfis,aux->categoria.codigo,tempLogradouro,aux->endereco.CEP,tempComplemento,aux->endereco.estado,aux->nascimento.dia,aux->nascimento.mes,aux->nascimento.ano); 
			fflush(arquivoProfissional);
			aux = aux->proximo;

		}
		
	}
		
	fclose(arquivoProfissional);
}

void lerProfissional(TipoListaProfissional *pLista){
	
	iniciaListaProfissional(pLista);
	//FILE *arquivoLer; 
	char tempNome[200], tempLogradouro[200],tempComplemento[200];
	ProfissionalSaude *aux = new ProfissionalSaude;
	aux->proximo = NULL;
	aux->anterior = NULL;
	arquivoProfissional = fopen("profissional.txt","r");
	
	if(arquivoProfissional == NULL){
		printf("impossivel abrir o arquivo\n");
	}else{
		while(fscanf(arquivoProfissional,"%d %s %s %d %d %s %d %s %s %d %d %d\n",&aux->matricula,tempNome,aux->cpf,&aux->regisProfis,&aux->categoria.codigo,tempLogradouro,&aux->endereco.CEP,tempComplemento,aux->endereco.estado,&aux->nascimento.dia,&aux->nascimento.mes,&aux->nascimento.ano) != EOF){
			colocaEspaco(tempNome);
			strcpy(aux->nome,tempNome);
			
			colocaEspaco(tempLogradouro);
			strcpy(aux->endereco.logradouro,tempLogradouro);
			
			colocaEspaco(tempComplemento);
			strcpy(aux->endereco.complemento,tempComplemento);
			//ultimaMatricula = pAux->matricula;
	
			if(pLista->inicio == NULL){
				pLista->inicio = aux;
				pLista->fim = aux;
			}
			else{
				// Apontando para o novo Elemento
				pLista->fim->proximo =aux;
				//Fazendo a volta (Duplo encadeado)
				aux->anterior = pLista->fim;
				//Novo fim para a lista 
				pLista->fim = aux;
			}
			aux = aux->proximo;
			aux = new ProfissionalSaude;
		}
	}
	fclose(arquivoProfissional);
	
}

char* verificaCategoriaProfissionalRelatorio(int codigoCategoriaProfissional){
	CategoriaProfissional *categoria =  listaCategoria.inicio;
	while(categoria !=NULL){
				if(codigoCategoriaProfissional == categoria->codigo){
					return categoria->nome;
							
				}
				categoria = categoria->proximo;
			}
	return NULL;
}

void gravarProfissionalRelatorio(TipoListaProfissional *pLista){
	//FILE *arquivo;
	char tempNome[200], tempCategoria[200],tempComplemento[200];
	ProfissionalSaude *profissional = new ProfissionalSaude;
	arquivoProfissional = fopen("relatorioProfissional.txt","w");
	if(arquivoProfissional == NULL){
		printf("Nao foi possivel criar o arquivo\n");
		system("pause");
	}else{
		ProfissionalSaude *aux;
		aux = pLista->inicio;
		fprintf(arquivoAtendimento,"\t\tRelatorio de Profissionais\n");
		fprintf(arquivoAtendimento,"                                                Data de emissao: %s\n",__DATE__);
		fprintf(arquivoAtendimento,"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		fprintf(arquivoAtendimento,"| Matricula   |   Profissional                 |  Categoria                 |\n");
		fprintf(arquivoAtendimento,"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

		while(aux != NULL){
			strcpy(tempNome,aux->nome);		
			strcpy(tempCategoria,verificaCategoriaProfissionalRelatorio(aux->categoria.codigo));
			fprintf(arquivoProfissional," %d            %s                             %s\n",aux->matricula,tempNome,tempCategoria); 
			fprintf(arquivoAtendimento,"----------------------------------------------------------------------------|\n");
			fflush(arquivoProfissional);
			aux = aux->proximo;

		}
		
	}
		
	fclose(arquivoProfissional);
	gotoXY(20,20);
	printf("Relatorio Gerado com Sucesso!!!\n");
	system("pause");
}



/*
#################################################################
* CLIENTE
#################################################################
*/

void gravarCliente(TipoListaCliente *pLista);
void lerCliente(TipoListaCliente *pLista);
void menuCliente(TipoListaCliente *pLista);
// cria a lista
void iniciaListaCliente(TipoListaCliente *pLista){
	pLista->inicio = NULL;
	pLista->fim = NULL;
}

//inserir no final
void inserirCliente(TipoListaCliente *pLista){
	// variaveis
	char tempNome[200],tempCpf[11];
	Cliente *novoCliente;
	novoCliente = new Cliente;
	system("cls");
	gotoXY(25,2);
	printf("CADASTRO DE CLIENTE");
	
	gotoXY(10,4);
	printf("Matricula: ");
	scanf("%d",&novoCliente->codigo);
	
	gotoXY(10,5);
	printf("Nome: ");
	fflush(stdin);
	gets(tempNome);
	strcpy(novoCliente->nome, tempNome);
	
	gotoXY(10,6);
	printf("CPF: ");
	scanf("%s",novoCliente->cpf);
	fflush(stdin);
	
	gotoXY(30,6);
	printf("Peso em Kg: ");
	scanf("%lf",&novoCliente->peso);
	
	gotoXY(50,6);
	printf("Tipo Sanguineo: ");
	scanf("%s",novoCliente->tipoSanguineo);
	fflush(stdin);
	gotoXY(20,8);
	printf("DATA DE NASCIMENTO");
	gotoXY(10,9);
	printf("Dia: ");
	scanf("%d",&novoCliente->nascimento.dia);
	fflush(stdin);
	gotoXY(20,9);
	printf("Mes: ");
	scanf("%d",&novoCliente->nascimento.mes);
	fflush(stdin);
	gotoXY(30,9);
	printf("Ano: ");
	scanf("%d",&novoCliente->nascimento.ano);
		
	fflush(stdin);
	gotoXY(20,10);
	printf("CONTATO");
	gotoXY(10,11);
	printf("Telefone: ");
	scanf("%d",&novoCliente->contato.telefone);
	
	fflush(stdin);
	gotoXY(30,11);
	printf("Celular: ");
	scanf("%d",&novoCliente->contato.celular);
	
	fflush(stdin);
	gotoXY(10,12);
	printf("Email: ");
	scanf("%s",novoCliente->contato.email);
	
	gotoXY(20,13);
	printf("ENDERECO");
	gotoXY(10,14);
	printf("Logradouro: ");
	fflush(stdin);
	gets(novoCliente->endereco.logradouro);
	gotoXY(10,15);
	printf("Complemento: ");
	fflush(stdin);
	gets(novoCliente->endereco.complemento);
	gotoXY(50,15);
	printf("Estado: ");
	fflush(stdin);
	gets(novoCliente->endereco.estado);
	
	gotoXY(10,17);
	printf("CEP: ");
	scanf("%d",&novoCliente->endereco.CEP);
	
	
	novoCliente->proximo = NULL;
	novoCliente->anterior = NULL;
	
	if(pLista->inicio == NULL){
		pLista->inicio = novoCliente;
		pLista->fim = novoCliente;
	}
	else{
		// Apontando para o novo Elemento
		pLista->fim->proximo = novoCliente;
		//Fazendo a volta (Duplo encadeado)
		novoCliente->anterior = pLista->fim;
		//Novo fim para a lista 
		pLista->fim = novoCliente;
	}
	printf("Inserido...\n");
	
	printf("%d %d",novoCliente->contato.celular,novoCliente->contato.telefone);
	system("pause");
	
	gravarCliente(pLista);
	menuCliente(pLista);
}

void atualizarCliente(TipoListaCliente *pLista){
	Cliente *aux;
	int tempCodigo;
	aux = pLista->inicio;
	system("cls");
	gotoXY(30,2);
	printf("ATUALIZAR REGISTRO");
	gotoXY(1,3);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

	do{
		gotoXY(2,4);
		printf("Codigo Cliente: ");
		scanf("%d",&tempCodigo);
		char tempNome[200];
		system("cls");
		gotoXY(30,6);
		printf("DADOS DO CLIENTE");
		while(aux->proximo != NULL && aux->codigo != tempCodigo){
			aux = aux->proximo;
		}if(aux->codigo == tempCodigo){
			gotoXY(1,6);
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			gotoXY(15,9);
			printf("Cliente:.................... %s",aux->nome);
			gotoXY(15,10);
			printf("Peso:....................... %.2f",aux->peso);			
			gotoXY(1,11);
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			gotoXY(20,12);
			printf("Qual campo deseja atualizar?");
			gotoXY(17,13);
			printf("Nome_________________________[1]");
			gotoXY(17,14);
			printf("Peso_________________________[2]");
			gotoXY(17,15);
			printf("Sair_________________________[0]");
			
						
			gotoXY(17,16);
			printf(">>> ");
			scanf("%s",&opcao);
	
			switch(opcao){
				case '1':
					fflush(stdin);
					gotoXY(17,18);
					printf("Digite a descricao: ");
					gets(tempNome);
					strcpy(aux->nome,tempNome); 
					gotoXY(20,19);
					printf("Dados Atualizados!!!");
					gotoXY(20,20);
					system("pause");
					system("cls");
					break;
				case '2':
					gotoXY(17,18);
					printf("Digite o peso: ");
					scanf("%lf",&aux->peso);
					
					gotoXY(20,19);
					printf("Dados Atualizados!!!");
					gotoXY(20,20);
					system("pause");
					system("cls"); 
					break;
				case '0':
					gotoXY(17,18);
					break;
				default:
					gotoXY(17,18);
					printf("opcao invalida!!!");
					break;								
				
				}
				
			system("cls");
			gotoXY(20,10);
			printf("Deseja continuar atualizando?");
			gotoXY(20,11);
			printf("Sim[S] / Nao [outra tecla] >>> ");
			scanf("%s",&opcao);
			system("cls"); 
		}else{
			gotoXY(25,8);
			printf("Categoria inexistente!!!");
			gotoXY(20,9);
			system("pause");
			system("cls");
			
		}
		//system("cls");
		
	}while(opcao == 's');

	gravarCliente(pLista);
	menuCliente(pLista);
}


void excluirCliente(TipoListaCliente *pLista){
	int tempCodigo;
	system("cls");
	Cliente *elem_atual, *elem_proximo,*elem_anterior;
	
	Cliente *inicio,*fim;
	inicio = pLista->inicio;
	fim = pLista->fim;
	
	gotoXY(25,3);
	printf("REMOVER CLIENTE");
	gotoXY(1,4);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	
	if(inicio == NULL){
		// se matricula nao cadastrada
		gotoXY(25,6);
		printf("Nao ha dados!!!");
		gotoXY(20,7);
		system("pause");
		menuCliente(pLista);
	}else{
		gotoXY(2,5);
		printf("Digite o codigo: ");
		scanf("%d",&tempCodigo);
		elem_atual = inicio;
		while(elem_atual != NULL){
			elem_proximo = elem_atual->proximo;
			elem_anterior = elem_atual->anterior;
			
			if(elem_atual->codigo == tempCodigo){
				gotoXY(2,6);
				printf("Cliente: %s",elem_atual->nome);
				fflush(stdin);
				gotoXY(2,8);
				printf("Deseja realmente excluir? [s/n] >> ");
				scanf("%s",&opcao);
				if(opcao == 's'){
					if(elem_anterior != NULL)//verifica do meio
						if(elem_proximo != NULL){
							elem_anterior->proximo = elem_proximo; 
							elem_proximo->anterior = elem_anterior;
							free(elem_atual);
						}else{
							// verifica do fim
						
							elem_anterior->proximo = NULL;
							pLista->fim = elem_anterior;
							free(elem_atual);
			
						}
					else if(elem_proximo != NULL){
						
						elem_proximo->anterior = NULL;
						pLista->inicio = elem_proximo;
						free(elem_atual);
						
					}else{
						
						free(elem_atual);
						pLista->inicio = pLista->fim = NULL;
						
					}
				gotoXY(20,9);
				printf("Dado removido com sucesso!!!");
				gotoXY(20,10);
				system("pause");
				gravarCliente(pLista);
				menuCliente(pLista);
				break;
				}else{
					
					menuCliente(pLista);
					break;
				}
		}
		elem_atual = elem_atual->proximo;
		}
			gotoXY(20,6);
			printf("Matricula nao encontrada!!!");
			gotoXY(20,7);
			system("pause");
			menuCliente(pLista);
			
	}

} 

void imprimirCliente(TipoListaCliente *pLista){	
	system("cls");	
	Cliente *aux;
	int linha=6;
	gotoXY(20,2);
	printf("Relacao de Cliente");
	gotoXY(1,3);
	printf("---------------------------------------------------------------------");
	gotoXY(1,4);
	printf("ID");
	gotoXY(4,4);
	printf("|");
	gotoXY(6,4);
	printf("Cliente");
	gotoXY(20,4);
	printf("|");
	gotoXY(25,4);
	printf("CPF");
	gotoXY(35,4);
	printf("|");
	gotoXY(36,4);
	printf("Tipo Sanguineo");
	gotoXY(50,4);
	printf("|");
	gotoXY(55,4);
	printf("Nascimento");
	gotoXY(70,4);
	printf("|");
	gotoXY(1,5);
	printf("---------------------------------------------------------------------");
	
	if(pLista->inicio == NULL){
		gotoXY(20,7);
		printf("SEM CLIENTES CADASTRADOS!!!");
	}else{
		aux = pLista->inicio;
		while(aux != NULL){
			gotoXY(1,linha);
			printf("%d",aux->codigo);
			gotoXY(6,linha);
			printf("%s",aux->nome);
			gotoXY(21,linha);
			printf("%s",aux->cpf);
			gotoXY(36,linha);
			printf("%s",aux->tipoSanguineo);
			gotoXY(56,linha);
			printf("%d/%d/%d",aux->nascimento.dia,aux->nascimento.mes,aux->nascimento.ano);
			
			aux = aux->proximo;
			linha++;
		}
	}
	gotoXY(20,linha+2);
	system("pause");
	menuCliente(pLista);
}


// teste para verificar duplo encadeamento
void imprimirDeTrasCliente(TipoListaCliente *pLista){
	Cliente *aux;
	if(pLista->fim == NULL){
		printf("Lista vazia\n"); 
	}else{
		aux =pLista->fim;
		while(aux != NULL){
			printf("Dados >>> %s\n",aux->nome);
			//system("pause");
			aux = aux->anterior;
		}
	
	printf("Fim da lista\n");
	}
	system("pause");
	menuCliente(pLista);	
}

void menuCliente(TipoListaCliente *pLista){
	system("cls");
	int opt; 
	gotoXY(30,4);
	printf("Menu Cliente");
	gotoXY(20,6);
	printf("1 - inserir Cliente de Saude");
	gotoXY(20,7);
	printf("2 - Imprimir Cliente de Saude");
	gotoXY(20,8);
	printf("3 - Excluir Cliente de Saude");
	gotoXY(20,9);
	printf("4 - Atualizar Cliente de Saude");
	gotoXY(20,10);
	printf("5 - Sair");
	gotoXY(20,11);
	printf(">>> ");
	scanf("%d",&opt);
		
	do{
		
		switch(opt){
			case 1:
				inserirCliente(pLista);
				break;
			case 2:
				imprimirCliente(pLista);
				break;
			case 3:
				excluirCliente(pLista);
				break;
			case 4:
				atualizarCliente(pLista);
				break;
			case 5:
				opt=0;
				menuPrincipal();
				break;
			default:
				printf("opt invalida!!!\n");
				break;
		}
	opt=0;
	}while(opt != 0);
}


void gravarCliente(TipoListaCliente *pLista){
	//FILE *arquivo;
	char tempNome[200], tempLogradouro[200],tempComplemento[200];
	Cliente *cliente = new Cliente;
	arquivoCliente = fopen("cliente.txt","w");
	if(arquivoCliente == NULL){
		printf("Nao foi possivel criar o arquivo\n");
		system("pause");
	}else{
		Cliente *aux;
		aux = pLista->inicio;
		while(aux != NULL){
			strcpy(tempNome,aux->nome);
			strcpy(tempLogradouro,aux->endereco.logradouro);
			strcpy(tempComplemento,aux->endereco.complemento);		
			retiraEspaco(tempNome);
			retiraEspaco(tempLogradouro);
			retiraEspaco(tempComplemento);
			fprintf(arquivoCliente,"%d %s %s %s %s %s %d %d %d %s %s %lf %d %d %d\n",aux->codigo,tempNome,aux->cpf,tempLogradouro,aux->tipoSanguineo,aux->contato.email,aux->contato.celular,aux->contato.telefone, aux->endereco.CEP,tempComplemento,aux->endereco.estado,aux->peso,aux->nascimento.dia,aux->nascimento.mes,aux->nascimento.ano); 
			fflush(arquivoCliente);
			aux = aux->proximo;

		}
		
	}
		
	fclose(arquivoCliente);
}

void lerCliente(TipoListaCliente *pLista){
	
	iniciaListaCliente(pLista);
	//FILE *arquivoLer; 
	char tempNome[200], tempLogradouro[200],tempComplemento[200];
	Cliente *aux = new Cliente;
	aux->proximo = NULL;
	aux->anterior = NULL;
	arquivoCliente = fopen("cliente.txt","r");
	
	if(arquivoCliente == NULL){
		printf("impossivel abrir o arquivo\n");
	}else{
		while(fscanf(arquivoCliente,"%d %s %s %s %s %s %d %d %d %s %s %lf %d %d %d\n",&aux->codigo,tempNome,aux->cpf,tempLogradouro,aux->tipoSanguineo,aux->contato.email,&aux->contato.celular,&aux->contato.telefone,&aux->endereco.CEP,tempComplemento,aux->endereco.estado,&aux->peso,&aux->nascimento.dia,&aux->nascimento.mes,&aux->nascimento.ano)!= EOF){
			colocaEspaco(tempNome);
			strcpy(aux->nome,tempNome);
			
			colocaEspaco(tempLogradouro);
			strcpy(aux->endereco.logradouro,tempLogradouro);
			
			colocaEspaco(tempComplemento);
			strcpy(aux->endereco.complemento,tempComplemento);
			//ultimaMatricula = pAux->matricula;
	
			if(pLista->inicio == NULL){
				pLista->inicio = aux;
				pLista->fim = aux;
			}
			else{
				// Apontando para o novo Elemento
				pLista->fim->proximo =aux;
				//Fazendo a volta (Duplo encadeado)
				aux->anterior = pLista->fim;
				//Novo fim para a lista 
				pLista->fim = aux;
			}
			aux = aux->proximo;
			aux = new Cliente;
		}
	}
	fclose(arquivoCliente);
	
}


/*
FICHA DE ATENDIMENTO
*/
void iniciaListaFichaAtendimento(TipoListaAtendimento *pLista){
	pLista->inicio = NULL;
	pLista->fim = NULL;
}


void inserirFichaAtendimento(TipoListaAtendimento *pLista);
void imprimirFichaAtendimento(TipoListaAtendimento *pLista);
void gravarAtendimento(TipoListaAtendimento *pLista);
void excluirFichaAtendimento(TipoListaAtendimento *pLista);

bool verificaProfissionais(int categoria){
	bool retorno = false;
	ProfissionalSaude *profissional;
	int linha = 11;
	profissional = listaDuplaCadeadaProfisional.inicio;
	gotoXY(60,10);
	printf("PROFISSIONAIS");
	while(profissional != NULL){
		if(profissional->categoria.codigo == categoria){
			gotoXY(60,linha);
			printf("%d",profissional->matricula);
			gotoXY(64,linha);
			printf("%s",profissional->nome);
			retorno = true;
		}
		linha++;
		profissional = profissional->proximo;
		
	}
	
	return retorno;
	
}

void menuFichaAtendimento(TipoListaAtendimento *pLista){
	system("cls");
	int opt; 
	gotoXY(30,4);
	printf("Menu Ficha de Atendimento");
	gotoXY(20,6);
	printf("1 - Nova Ficha de Atendimento");
	gotoXY(20,7);
	printf("2 - Imprimir Fichas de Atendimento");
	gotoXY(20,8);
	printf("3 - Alterar Dados da Ficha de Atendimento");
	gotoXY(20,9);
	printf("4 - Excluir Ficha de Atendimento");
	gotoXY(20,10);
	printf("5 - Sair");
	gotoXY(20,12);
	printf(">>> ");
	scanf("%d",&opt);
		
	do{
		switch(opt){
			case 1:
				inserirFichaAtendimento(pLista);
				break;
			case 2:
				imprimirFichaAtendimento(pLista);
				break;
			case 3:
				//atualizarCliente(pLista);
				break;
			case 4:
				excluirFichaAtendimento(pLista);
				break;
			case 5:
				opt=0;
				menuPrincipal();
				break;
			default:
				printf("opt invalida!!!\n");
				break;
		}
	opt=0;
	}while(opt != 0);
}


bool mostraCliente(char cpf[11]){
	Cliente *aux;
	aux = listaDuplaCadeadaCliente.inicio;
	while(aux != NULL){
		if(strcmp(aux->cpf,cpf) == 0){
			//gotoXY(2,8);
			printf("%s",aux->nome);
			return true;
		}
		aux = aux->proximo;
	}
	return false;
}

bool mostraProfissional(int matricula){
	ProfissionalSaude *aux;
	aux = listaDuplaCadeadaProfisional.inicio;
	while(aux != NULL){
		if(aux->matricula == matricula){
			//gotoXY(2,11);
			printf("%s",aux->nome);
			return true;
		}
		aux = aux->proximo;
	}
	printf("Profissional nao encontrado!!!");
	sleep(2);
	ClearLine();
	return false;
}

bool mostrarCategoria(int codigo){
	CategoriaProfissional *aux;
	aux = listaCategoria.inicio;
	while(aux != NULL){
		if(aux->codigo == codigo){
			//gotoXY(2,11);
			printf("%s",aux->nome);
			return true;
		}
		aux = aux->proximo;
	}
	printf("Categoria nao encontrado!!!");
	sleep(2);
	ClearLine();
	return false;
}



void inserirFichaAtendimento(TipoListaAtendimento *pLista){
	if(listaDuplaCadeadaCliente.inicio == NULL || listaDuplaCadeadaProfisional.inicio == NULL){
		gotoXY(20,5);
		printf("Nao ha profissionais ou cliente cadastrados!!!");
		gotoXY(20,6);
		system("pause");
		
	}else{
	
	char tempNome[200],tempCpf[11];
	FichaAtendimento *novoAtendimento;
	novoAtendimento = new FichaAtendimento;
	system("cls");
	gotoXY(15,2);
	printf("Ficha de Atendimento");
	gotoXY(1,3);
	printf("-------------------------------------------------------");	
	gotoXY(2,6);
	printf("Protocolo: ");
	scanf("%d",&novoAtendimento->codigoAtendimento);
	gotoXY(2,7);
	printf("CPF: ");// CODIGO DEVE SER GERADO AUTOMATICAMENTE
	fflush(stdin);
	gets(tempCpf);
	gotoXY(2,8);
	printf("Cliente: ");
	while(!mostraCliente(tempCpf)){
		gotoXY(7,7);
		ClearLine();
		gotoXY(20,7);
		printf("cliente nao encontrado");
		sleep(2);
		ClearLine();
		gotoXY(7,7);
		fflush(stdin);
		gets(tempCpf);
		gotoXY(10,8);
		//ClearLine();
	}
	strcpy(novoAtendimento->cliente.cpf,tempCpf);
	gotoXY(2,9);
	printf("Especialidade: ");
	mostrarCategorias(&listaCategoria);
	
	int tempCodCategoria;
	gotoXY(17,9);
	scanf("%d",&tempCodCategoria);
	while(!validaCategoria(&listaCategoria,tempCodCategoria)){
		gotoXY(17,9);
		ClearLine();
		gotoXY(20,9);
		printf("Especialidade invalida!!!");
		sleep(3);
		ClearLine();
		gotoXY(2,9);
		printf("Especialidade: ");
		gotoXY(17,9);
		scanf("%d",&tempCodCategoria);	
	}
	gotoXY(30,9);
	printf("OK");
	novoAtendimento->categAtendimento.codigo = tempCodCategoria;
	gotoXY(2,10);
	// verificar se profissional existe 
	printf("Profissional: ");
	if(!verificaProfissionais(novoAtendimento->categAtendimento.codigo)){
		gotoXY(15,11);
		printf("Nao ha profissionais para essa categoria!!!");
		gotoXY(20,12);
		system("pause");
		menuFichaAtendimento(pLista);
	}
	gotoXY(16,10);
	scanf("%d",&novoAtendimento->profissional.matricula);
	//Fazer um WHILE
	gotoXY(2,11);
	while(!mostraProfissional(novoAtendimento->profissional.matricula)){
		gotoXY(16,10);
		ClearLine();
		sleep(2);
		ClearLine();
		gotoXY(16,10);
		scanf("%d",&novoAtendimento->profissional.matricula);
		gotoXY(2,11);
		
	}
	
	gotoXY(20,12);
	printf("Dia do Atendimento");
	gotoXY(2,13);
	printf("Dia: ");
	gotoXY(7,13);
	scanf("%d",&novoAtendimento->dataAtendimento.dia);
	gotoXY(10,13);
	printf("Mes: ");
	gotoXY(15,13);
	scanf("%d",&novoAtendimento->dataAtendimento.mes);
	gotoXY(20,13);
	printf("Ano: ");
	gotoXY(25,13);
	scanf("%d",&novoAtendimento->dataAtendimento.ano);
	
	fflush(stdin);
	gotoXY(2,14);
	printf("Descricao de Atendimento: ");
	char tempDescricao[200];
	gets(tempDescricao);
	strcpy(novoAtendimento->descricao,tempDescricao);
	gotoXY(25,15);
	printf("AGENDAMENTO");
	gotoXY(1,16);
	printf("-------------------------------------------------------");
	gotoXY(2,17);
	printf("Dia: ");
	gotoXY(7,17);
	scanf("%d",&novoAtendimento->diaAgendado.dia);
	gotoXY(10,17);
	printf("Mes: ");
	gotoXY(15,17);
	scanf("%d",&novoAtendimento->diaAgendado.mes);
	gotoXY(20,17);
	printf("Ano: ");
	gotoXY(25,17);
	scanf("%d",&novoAtendimento->diaAgendado.ano);
	
	
	novoAtendimento->proximo = NULL;
	novoAtendimento->anterior = NULL;
	
	if(pLista->inicio == NULL){
		pLista->inicio = novoAtendimento;
		pLista->fim = novoAtendimento;
	}
	else{
		// Apontando para o novo Elemento
		pLista->fim->proximo = novoAtendimento;
		//Fazendo a volta (Duplo encadeado)
		novoAtendimento->anterior = pLista->fim;
		//Novo fim para a lista 
		pLista->fim = novoAtendimento;
	}
	
	gravarAtendimento(&listaAtendimento);
	gotoXY(20,20);
	printf("Ficha criada com sucesso!!!");
	gotoXY(15,21);
	system("pause");
	menuFichaAtendimento(pLista);
	}
}



void imprimirFichaAtendimento(TipoListaAtendimento *pLista){	
	system("cls");	
	FichaAtendimento *aux;
	int linha=6;
	gotoXY(25,2);
	printf("FICHAS DE ATENDIMENTO");
	gotoXY(1,3);
	printf("------------------------------------------------------------------------------");
	gotoXY(2,4);
	printf("ID");
	gotoXY(6,4);
	printf("|");
	gotoXY(8,4);
	printf("Categoria");
	gotoXY(20,4);
	printf("|");
	gotoXY(25,4);
	printf("Paciente");
	gotoXY(35,4);
	printf("|");
	gotoXY(36,4);
	printf("Especialista");
	gotoXY(50,4);
	printf("|");
	gotoXY(51,4);
	printf("Abertura");
	gotoXY(60,4);
	printf("|");
	gotoXY(62,4);
	printf("Agendado");
	gotoXY(75,4);
	printf("|");
	gotoXY(1,5);
	printf("------------------------------------------------------------------------------");
	
	if(pLista->inicio == NULL){
		gotoXY(20,7);
		printf("SEM FICHAS CADASTRADAS!!!");
	}else{
		aux = pLista->inicio;
		while(aux != NULL){
			gotoXY(1,linha);
			printf("%d",aux->codigoAtendimento);
			gotoXY(8,linha);
			mostrarCategoria(aux->categAtendimento.codigo);
			gotoXY(21,linha);
			mostraCliente(aux->cliente.cpf);
			gotoXY(36,linha);
			mostraProfissional(aux->profissional.matricula);
			gotoXY(51,linha);
			printf("%d/%d/%d",aux->dataAtendimento.dia,aux->dataAtendimento.mes,aux->dataAtendimento.ano);
			gotoXY(63,linha);
			printf("%d/%d/%d",aux->diaAgendado.dia,aux->diaAgendado.mes,aux->diaAgendado.ano);
			
			aux = aux->proximo;
			linha++;
		}
	}
	gotoXY(20,linha+2);
	system("pause");
	menuFichaAtendimento(pLista);
}


void excluirFichaAtendimento(TipoListaAtendimento *pLista){
	int tempCodigo;
	system("cls");
	FichaAtendimento *elem_atual, *elem_proximo,*elem_anterior;
	
	FichaAtendimento *inicio,*fim;
	inicio = pLista->inicio;
	fim = pLista->fim;
	
	gotoXY(25,3);
	printf("REMOVER FICHA DE ATENDIMENTO");
	gotoXY(1,4);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	
	if(inicio == NULL){
		// se matricula nao cadastrada
		gotoXY(25,6);
		printf("Nao ha dados!!!");
		gotoXY(20,7);
		system("pause");
		menuFichaAtendimento(pLista);
	}else{
		gotoXY(2,5);
		printf("Digite o protocolo: ");
		scanf("%d",&tempCodigo);
		elem_atual = inicio;
		while(elem_atual != NULL){
			elem_proximo = elem_atual->proximo;
			elem_anterior = elem_atual->anterior;
			
			if(elem_atual->codigoAtendimento == tempCodigo){
				gotoXY(2,6);
				printf("Paciente: ");
				mostraCliente(elem_atual->cliente.cpf);
				fflush(stdin);
				gotoXY(2,8);
				printf("Deseja realmente excluir? [s/n] >> ");
				scanf("%s",&opcao);
				if(opcao == 's'){
					if(elem_anterior != NULL)//verifica do meio
						if(elem_proximo != NULL){
							elem_anterior->proximo = elem_proximo; 
							elem_proximo->anterior = elem_anterior;
							free(elem_atual);
						}else{
							// verifica do fim
						
							elem_anterior->proximo = NULL;
							pLista->fim = elem_anterior;
							free(elem_atual);
			
						}
					else if(elem_proximo != NULL){
						
						elem_proximo->anterior = NULL;
						pLista->inicio = elem_proximo;
						free(elem_atual);
						
					}else{
						
						free(elem_atual);
						pLista->inicio = pLista->fim = NULL;
						
					}
				gotoXY(20,9);
				printf("Dado removido com sucesso!!!");
				gotoXY(20,10);
				system("pause");
				gravarAtendimento(pLista);
				menuFichaAtendimento(pLista);
				break;
				}else{
					
					menuFichaAtendimento(pLista);
					break;
				}
		}
		elem_atual = elem_atual->proximo;
		}
			gotoXY(20,6);
			printf("Matricula nao encontrada!!!");
			gotoXY(20,7);
			system("pause");
			menuFichaAtendimento(pLista);
			
	}
	
} 

void gravarAtendimento(TipoListaAtendimento *pLista){
	//FILE *arquivo;
	char tempNomeCliente[200], tempDescricao[200];
	FichaAtendimento *ficha = new FichaAtendimento;
	arquivoAtendimento = fopen("atendimento.txt","w");
	if(arquivoAtendimento == NULL){
		printf("Nao foi possivel criar o arquivo\n");
		system("pause");
	}else{
		FichaAtendimento *aux;
		aux = pLista->inicio;
		while(aux != NULL){
			strcpy(tempDescricao,aux->descricao);	
			retiraEspaco(tempDescricao);
			fprintf(arquivoAtendimento,"%d %d %s %d %s %d %d %d %d %d %d\n",aux->codigoAtendimento,aux->categAtendimento.codigo,aux->cliente.cpf,aux->profissional.matricula,tempDescricao,aux->dataAtendimento.dia,aux->dataAtendimento.mes,aux->dataAtendimento.ano,aux->diaAgendado.dia,aux->diaAgendado.mes,aux->diaAgendado.ano); 
			fflush(arquivoAtendimento);
			aux = aux->proximo;

		}
		
	}
		
	fclose(arquivoCliente);
}


void lerAtendimento(TipoListaAtendimento *pLista){
	
	iniciaListaFichaAtendimento(pLista);
	//FILE *arquivoLer; 
	char tempDescricao[200];
	FichaAtendimento *aux = new FichaAtendimento;
	aux->proximo = NULL;
	aux->anterior = NULL;
	arquivoAtendimento = fopen("atendimento.txt","r");
	
	if(arquivoCliente == NULL){
		printf("impossivel abrir o arquivo\n");
	}else{
		while(fscanf(arquivoAtendimento,"%d %d %s %d %s %d %d %d %d %d %d\n",&aux->codigoAtendimento,&aux->categAtendimento.codigo,aux->cliente.cpf,&aux->profissional.matricula,tempDescricao,&aux->dataAtendimento.dia,&aux->dataAtendimento.mes,&aux->dataAtendimento.ano,&aux->diaAgendado.dia,&aux->diaAgendado.mes,&aux->diaAgendado.ano)!= EOF){
			colocaEspaco(tempDescricao);
			strcpy(aux->descricao,tempDescricao);
				
			if(pLista->inicio == NULL){
				pLista->inicio = aux;
				pLista->fim = aux;
			}
			else{
				// Apontando para o novo Elemento
				pLista->fim->proximo =aux;
				//Fazendo a volta (Duplo encadeado)
				aux->anterior = pLista->fim;
				//Novo fim para a lista 
				pLista->fim = aux;
			}
			aux = aux->proximo;
			aux = new FichaAtendimento;
		}
	}
	fclose(arquivoAtendimento);
	
}

void mostrarAniversariantes(int mes){
	ProfissionalSaude *profissional = listaDuplaCadeadaProfisional.inicio;
	int linha = 5;
	system("cls");
	gotoXY(25,2);
	printf("ANIVERSARIANTES DO MES");
	gotoXY(1,3);
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	gotoXY(1,4);
	printf("|");
	gotoXY(3,4);
	printf("Nome");
	gotoXY(25,4);
	printf("|");
	gotoXY(28,4);
	printf("Nascimento");
	gotoXY(40,4);
	printf("|");
	while(profissional!=NULL){
		if((profissional->nascimento.mes == mes)){
				gotoXY(3,linha++);
				printf("%s",profissional->nome);
				gotoXY(30,linha);
				printf("%d/%d/%d",profissional->nascimento.dia,profissional->nascimento.mes,profissional->nascimento.ano);
				
			gotoXY(1,linha+2);
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			}
			//linha+=2;
			profissional = profissional->proximo;
		}
	if(linha==6){
		gotoXY(25,linha+1);
		printf("SEM DADOS PARA ESTE MES!!!");
	}
	gotoXY(20,linha+2);
	system("pause"); 
	
}


void menu_niver(){
	system("cls");
	int mes;
	gotoXY(25,4);
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
		gotoXY(18,20);
		printf(">> ");
		scanf("%d",&mes);
		mostrarAniversariantes(mes);
		
}

char* mostraClienteRelatorio(char cpf[11]){
	Cliente *aux;
	aux = listaDuplaCadeadaCliente.inicio;
	while(aux != NULL){
		if(strcmp(aux->cpf,cpf) == 0){
			//gotoXY(2,8);
			return (aux->nome);
		}
		aux = aux->proximo;
	}
	return "";
}


char* mostraDoutorRelatorio(int matricula){
	ProfissionalSaude *aux;
	aux = listaDuplaCadeadaProfisional.inicio;
	while(aux != NULL){
		if(aux->matricula == matricula){
			//gotoXY(2,8);
			return (aux->nome);
		}
		aux = aux->proximo;
	}
	return NULL;
}

void relatorioAtendimento(TipoListaAtendimento *pLista){
	//FILE *arquivo;
	char tempNomeCliente[200], tempProfissional[200];
	FichaAtendimento *ficha = new FichaAtendimento;
	arquivoAtendimento = fopen("relatorio_atendimento.txt","w");
	if(arquivoAtendimento == NULL){
		printf("Nao foi possivel criar o arquivo\n");
		system("pause");
	}else{
		FichaAtendimento *aux;
		aux = pLista->inicio;
		fprintf(arquivoAtendimento,"\t\tRelatorio de Atendimento\n");
		fprintf(arquivoAtendimento,"                                                              Data de emissao: %s\n",__DATE__);
		fprintf(arquivoAtendimento,"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		fprintf(arquivoAtendimento,"Cod   |   Paciente                 |  Doutor                  | Atendimento     |  Agendamento |\n");
		fprintf(arquivoAtendimento,"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		while(aux != NULL){
			strcpy(tempProfissional,mostraDoutorRelatorio(aux->profissional.matricula));	
			//retiraEspaco(tempDescricao);
			strcpy(tempNomeCliente, mostraClienteRelatorio(aux->cliente.cpf));
			fprintf(arquivoAtendimento,"%d    %s                     %s             %d/%d/%d         %d/%d/%d\n",aux->codigoAtendimento,tempNomeCliente,tempProfissional,aux->dataAtendimento.dia,aux->dataAtendimento.mes,aux->dataAtendimento.ano,aux->diaAgendado.dia,aux->diaAgendado.mes,aux->diaAgendado.ano); 
			fflush(arquivoAtendimento);
			fprintf(arquivoAtendimento,"------------------------------------------------------------------------------------------------|\n");
			aux = aux->proximo;

		}
		
	}
		
	fclose(arquivoCliente);
	system("cls");
	gotoXY(20,20);
	printf("Arquivo gerado com sucesso\n");
	system("pause");
}

void menuRelatorio(){
	system("cls");
	int opt; 
	gotoXY(30,4);
	printf("Menu Relatorios");
	gotoXY(20,6);
	printf("1 - Profissional");
	gotoXY(20,7);
	printf("2 - Atendimentos");
	gotoXY(20,8);
	printf("5 - Sair");
	gotoXY(20,11);
	printf(">>> ");
	scanf("%d",&opt);
		
	do{
		
		switch(opt){
			case 1:
				gravarProfissionalRelatorio(&listaDuplaCadeadaProfisional) ;
				break;
			case 2:
				relatorioAtendimento(&listaAtendimento);
				break;
			
			case 5:
				opt = 0;
				menuPrincipal();
				break;
			default:
				printf("opt invalida!!!\n");
				break;
		}
	opt=0;
	}while(opt != 0);
}

int main(void){
	int opt;
	
	do{
		ler(&listaCategoria);
		lerProfissional(&listaDuplaCadeadaProfisional);
		lerCliente(&listaDuplaCadeadaCliente);
		lerAtendimento(&listaAtendimento);
		system("cls");
		menuPrincipal();

		gotoXY(20,13);
		printf(">>> ");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				menuProfissional(&listaDuplaCadeadaProfisional);
				break;
			case 2:
				menuCliente(&listaDuplaCadeadaCliente);
				break;
			case 3:
				menuFichaAtendimento(&listaAtendimento);
				break;
			case 4:
				menuCategoria(&listaCategoria);
				break;
			case 5:
				menu_niver();
				break;
			case 6:
				menuRelatorio();
				break;
			case 7:
				gotoXY(25,13);
				printf("Obrigado, ate mais!!!");
				exit(1);
				break;
			default:
				gotoXY(25,13);
				printf("Opcao invalida MAIN!!!\n");
				system("pause");				
		}
	}while(opt != 0);	
}
