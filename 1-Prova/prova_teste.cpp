#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int x, int y){
CursorPosition.X = x; // Locates column
CursorPosition.Y = y; // Locates Row
SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
}


struct NodoDicionario{
	char palavra[200];
	NodoDicionario *proximo;
};


struct TipoListaDicionario{
	NodoDicionario *inicio = NULL;
	NodoDicionario *fim = NULL;
};

struct NodoLista{
	int quantNodoSecundario;
	char letraInicial;
	TipoListaDicionario dicionario;
	NodoLista *proximo;
};

struct TipoListaNodoLetras{
	NodoLista *inicio = NULL;
	NodoLista *fim = NULL;
};


TipoListaNodoLetras lista;
FILE *arquivo,*arquivoPalavras;

void gravarLetras(TipoListaNodoLetras *pLista);
void gravarPalavras(TipoListaDicionario *pLista);

void iniciaListaLetras(TipoListaNodoLetras *pLista){
	pLista->inicio = NULL;
	pLista->fim = NULL;
} 

void iniciaListaDicionario(TipoListaDicionario *pLista){
	pLista->inicio = NULL;
	pLista->fim = NULL;
} 



int contaPalavras(TipoListaNodoLetras *pLista,char letra){
	int cont = 0;
	NodoLista *letras = pLista->inicio;
	NodoDicionario *palavras;

	while(letras !=NULL){
		if(letras->letraInicial == letra){
			palavras = letras->dicionario.inicio;
			break;
		}
		letras = letras->proximo;
	}
	//conta palavras na lista
	
	while(palavras !=NULL){
		cont++;
		palavras = palavras->proximo;
	}
	return cont;
}

bool hasPalavra(TipoListaDicionario *pLista,char palavra[200]){
	NodoDicionario *aux = pLista->inicio;
	while(aux!=NULL){
		if(strcmp(palavra,aux->palavra)){
			return true;
		}
		aux = aux->proximo;
	}
	return false;
}

bool hasLetra(TipoListaNodoLetras *pLista,char letra){
	NodoLista *aux = pLista->inicio;	
	while(aux != NULL){
		if(letra==aux->letraInicial){
			return true;
		}
		aux = aux->proximo;
	}return false;
}

NodoLista* hasLetraNodo(TipoListaNodoLetras *pLista,char letra){
	NodoLista *aux = pLista->inicio;	
	while(aux != NULL){
		if(letra==aux->letraInicial){
			return aux;
		}
		aux = aux->proximo;
	}return NULL;
}

void inserirPalavra(TipoListaDicionario *pLista,char palavra[200]){
	char tempPalavra[200];
	NodoDicionario *aux = pLista->inicio;
	NodoDicionario *novoNodo = new NodoDicionario;
	
	strcpy(novoNodo->palavra,palavra);

	novoNodo->proximo = NULL;
	printf("Verificando dicionario\n");
	if(aux == NULL){
		pLista->inicio = novoNodo;
		pLista->fim = novoNodo;
		
	}else{
		printf("Adicionando na Lista\n");
		aux = pLista->fim;
		pLista->fim = novoNodo;
		aux->proximo = pLista->fim;
	}
}

void inserir(TipoListaNodoLetras *pLista){
	char tempPalavra[200];
	NodoLista *aux = pLista->inicio;
	NodoLista *novoNodo = new NodoLista;
	printf("Verificando dados\n");
	
	printf("Digite a palavra: ");
	fflush(stdin);
	gets(tempPalavra);
	
	novoNodo->letraInicial = toupper(tempPalavra[0]);
	
	novoNodo->proximo = NULL;
	
	if(aux == NULL){
		printf("Lista Vazia\n");
		printf("iniciando lista\n");
		pLista->inicio = novoNodo;
		pLista->fim = novoNodo;
		
		iniciaListaDicionario(&novoNodo->dicionario);
		inserirPalavra(&novoNodo->dicionario,tempPalavra);
		system("pause");
		
	}else if(hasLetra(&lista,novoNodo->letraInicial)){
		NodoLista *aux = hasLetraNodo(&lista,novoNodo->letraInicial);
		
		
		if(hasPalavra(&aux->dicionario,tempPalavra)){
			printf("inserido\n");
			inserirPalavra(&aux->dicionario,tempPalavra);	
		}else{
			printf("palavra ja existe!!!\n");
		}
		
		aux->quantNodoSecundario = contaPalavras(&lista,novoNodo->letraInicial);
		system("pause");
		
		
	}else{
		printf("Adicionando na Lista\n");
		
		iniciaListaDicionario(&novoNodo->dicionario);
		printf("lol");
		inserirPalavra(&novoNodo->dicionario,tempPalavra);
		
		aux = pLista->fim;
		pLista->fim = novoNodo;
		aux->proximo = pLista->fim;
	}
	
	novoNodo->quantNodoSecundario = contaPalavras(&lista,novoNodo->letraInicial);
	gravarLetras(&lista);
}

void remover(TipoListaNodoLetras *pLista){
	NodoLista *aux = pLista->inicio;
	TipoListaDicionario listaPalavras;
	NodoLista *listaLetras;
	NodoDicionario *auxPalavras,*atual,*prox;
	
	auxPalavras = NULL;
	
	char tempPalavra[200];
	char tempLetra;
	
	printf("Digite a palavra: ");
	
	fflush(stdin);
	gets(tempPalavra);	
	
	tempLetra = tempPalavra[0];
	printf("print achou letra: %c\n",tempLetra);
	while(aux!=NULL){
		printf("print achou letra\n");
		if(aux->letraInicial ==toupper(tempLetra)){
			listaLetras = aux;
			listaPalavras = aux->dicionario;
			break;
		}
		aux = aux->proximo;
			
	}
	auxPalavras = listaPalavras.inicio;
	if(auxPalavras != NULL){
		if(auxPalavras->proximo == NULL){
			free(auxPalavras);
			iniciaListaDicionario(&listaPalavras);
			listaLetras->quantNodoSecundario = 0;
			printf("excluido\n");
		}else{
			
			while(auxPalavras!=NULL){
				int num = strcmp(auxPalavras->palavra,tempPalavra);
				printf("entrou no loop %d",num);
				
				if(strcmp(auxPalavras->palavra,tempPalavra)==0){
					atual = auxPalavras;
					prox = auxPalavras->proximo;
					atual->proximo = prox->proximo;
					atual = prox;
					
					free(auxPalavras);
					printf("excluiu");
					system("pause");
					/*
					ERRO AQUI
					*/
					
				}
				auxPalavras = auxPalavras->proximo;
			}
		}
	}else{
		printf("Palavra nao encontrada\n");
		}

	system("pause");
	
}

void imprimirPalavras(TipoListaDicionario *pLista){
	NodoDicionario *aux = pLista->inicio;
		while(aux!=NULL){
			printf("%s\n",aux->palavra);
			aux = aux->proximo;
		}
		printf("\n");
}
void imprimirNodoLetras(TipoListaNodoLetras *pLista){
	NodoLista *aux = pLista->inicio;
	
	while(aux!=NULL){
		printf("Letra: %c\n",aux->letraInicial);
		printf("Quantidade: %d\n",aux->quantNodoSecundario);
		printf("---------------------\n");
		printf("Palavras:\n");
		imprimirPalavras(&aux->dicionario);
		printf("*********************\n");
		aux = aux->proximo;
	} 
	system("pause");
}


void gravarPalavras(TipoListaDicionario *pLista){
	arquivoPalavras = fopen("palavras.txt","w");
	if(arquivoPalavras == NULL){
		printf("Nao foi possivel abrir o arquivo\n");
		system("pause");
	}else{
		NodoDicionario *aux;
		aux = pLista->inicio;
		while(aux != NULL){
			fprintf(arquivoPalavras,"%s\n",aux->palavra); 
			fflush(arquivo);
			aux = aux->proximo;
		}
		fclose(arquivoPalavras);	
	}
	
}

void gravarLetras(TipoListaNodoLetras *pLista){
	arquivo = fopen("letras.txt","w");
	if(arquivo == NULL){
		printf("Nao foi possivel abrir o arquivo\n");
		system("pause");
	}else{
		NodoLista *aux;
		aux = pLista->inicio;
		while(aux != NULL){
			fprintf(arquivo,"%c %d\n",aux->letraInicial,aux->quantNodoSecundario); 
			gravarPalavras(&aux->dicionario);
			fflush(arquivo);
			aux = aux->proximo;
		}
		fclose(arquivo);	
	}
	
}


void lerPalavras(TipoListaDicionario *pLista,char letra){
	
	NodoDicionario *novoNodo = new NodoDicionario;
	NodoDicionario *aux = pLista->inicio;
	
	
	arquivoPalavras = fopen("palavras.txt","r");
	if(arquivoPalavras == NULL){
		printf("impossivel abrir o arquivo\n");
		system("pause");
	}else{
		char tempPalavra[200];
		while(fscanf(arquivoPalavras,"%s\n",tempPalavra) != EOF){
			if(toupper(tempPalavra[0])== letra){ 
				strcpy(novoNodo->palavra,tempPalavra);
				novoNodo->proximo = NULL;
				if(aux == NULL){
					pLista->inicio = novoNodo;
					pLista->fim = novoNodo;
					system("pause");
					
				}else{
					
					aux = pLista->fim;
					pLista->fim = novoNodo;
					aux->proximo = pLista->fim;
			
				}
			}
			
		}
	}
	fclose(arquivoPalavras);
	
}

void ler(TipoListaNodoLetras *pLista){
	iniciaListaLetras(pLista);

	NodoLista *novoNodo = new NodoLista;
	NodoLista *aux = new NodoLista;

	
	arquivo = fopen("letras.txt","r");
	if(arquivo == NULL){
		printf("impossivel abrir o arquivo\n");
		gravarLetras(pLista);
		ler(pLista);
		system("pause");
	}else{
		while(fscanf(arquivo,"%c %d\n",&novoNodo->letraInicial,&novoNodo->quantNodoSecundario) != EOF){
			if(pLista->inicio == NULL){
				pLista->inicio = novoNodo;
				pLista->fim = novoNodo;
				
				iniciaListaDicionario(&novoNodo->dicionario);
				lerPalavras(&novoNodo->dicionario,novoNodo->letraInicial);
			
		
			}else if(hasLetra(&lista,novoNodo->letraInicial)){
				aux = hasLetraNodo(&lista,novoNodo->letraInicial);
				lerPalavras(&aux->dicionario,novoNodo->letraInicial);
		
				//aux->quantNodoSecundario = contaPalavras(&lista,novoNodo->letraInicial);
			}else{
				printf("Adicionando na Lista\n");
				iniciaListaDicionario(&aux->dicionario);
				lerPalavras(&aux->dicionario,novoNodo->letraInicial);
				
				aux = pLista->fim;
				pLista->fim = novoNodo;
				aux->proximo = pLista->fim;
			}

		}
	}
	fclose(arquivo);
	
}





int main(void){
	
	//verificar a opcao 
	int opcao;
	iniciaListaLetras(&lista);
	
	do{
		//ler(&lista);
		system("cls");
		gotoXY(20,4);
		printf("Prova de Estrutura de Dados");
		gotoXY(22,8);
		printf("Inserir_______________________ [1]\n");
		gotoXY(22,9);
		printf("Imprimir______________________ [2]\n");
		gotoXY(22,10);
		printf("Atualizar_____________________ [3]\n");
		gotoXY(22,11);
		printf("Remover_______________________ [4]\n");
		gotoXY(22,12);
		printf("Sair__________________________ [5]\n");
		gotoXY(22,13);
		gotoXY(22,14);
		printf("Opcao: ........................ ");
		scanf("%d",&opcao);
		switch(opcao){
			case 1:
				inserir(&lista);
				break;
			case 2:
				imprimirNodoLetras(&lista);
				break;
				/*
			case 3:
				atualizar();
				break;
			*/
			case 4:
				remover(&lista);
				break;
			
			case 5:
				exit(0);
				break;
			
			default:
				printf("Opcao invalida\n");
				break;
		}
	}	while(opcao != 0);
	
	system("cls");
}



