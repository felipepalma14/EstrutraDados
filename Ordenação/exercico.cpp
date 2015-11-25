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


struct Candidato{
	int nota;
	char nome[200];
	char cpf[11];
	struct Candidato *proximo;
	
};

struct TipoListaCandidato{
	Candidato *inicio = NULL;
	Candidato *fim = NULL;
};

void iniciaCandidato(TipoListaCandidato *pLista){
	pLista->inicio = NULL;
	pLista->fim = NULL;
} 

TipoListaCandidato lista;

void inserirCandidato(TipoListaCandidato *pLista){
	int nota;
	char nome[200],cpf[11];
	
	Candidato *aux = pLista->inicio;
	
	Candidato *novoNodo = new Candidato;
	
	
	printf("Digite nota: ");
	scanf("%d",&novoNodo->nota);
	
	novoNodo->proximo = NULL;

	if(aux == NULL){
		pLista->inicio = novoNodo;
		pLista->fim = novoNodo;
		
	}else{
		aux = pLista->fim;
		pLista->fim = novoNodo;
		aux->proximo = pLista->fim;
	}
}

TipoListaCandidato ordenado;


void ordena(TipoListaCandidato *pLista){
	Candidato *aux = pLista->inicio;
	Candidato *minimo;
	for(;aux != NULL;aux = aux->proximo){
			Candidato *analisado = aux;
			for(Candidato *j = aux->proximo;j !=NULL; j = j->proximo){
				
		}
			
		
}




void imprimirCandidatos(TipoListaCandidato *pLista){
	Candidato *aux = pLista->inicio;
	if(aux==NULL){
		printf("Sem Dados\n");
		system("pause");
		return;
	}
		while(aux!=NULL){
			printf("Nota: %d\n",aux->nota);
			aux = aux->proximo;
		}
		system("pause");
}

void SelectionSort(TipoListaCandidato *pLista)
{
	Candidato *atual = pLista->inicio, *min,*seguinte,*temp;
	
	for(;atual!= NULL; atual = atual->proximo){
		min = atual;
		for(seguinte = atual->proximo;seguinte !=NULL;seguinte = seguinte->proximo){
			if(seguinte->nota < min->nota){
				min = seguinte;
			}
		}
		temp = atual;
		atual = min;
		min = temp;
	}

} 
 
/* swap data field of linked list */
void swap(Candidato *p1, Candidato *p2)
{
	Candidato *temp = p1;
	p1 = p2;
	p2 = temp;
}

int main(void){
	
	//verificar a opcao 
	int opcao;
	iniciaCandidato(&lista);
	
	do{
		//ler(&lista);
		system("cls");
		gotoXY(20,4);
		printf("Candidatos");
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
				inserirCandidato(&lista);
				break;
			case 2:
				imprimirCandidatos(&lista);
				break;
			case 3:
				ordena(&lista);
				imprimirCandidatos(&lista);
				break;
			case 4:
				exit(0);
				break;
			
			default:
				printf("Opcao invalida\n");
				break;
		}
	}	while(opcao != 0);
	
	system("cls");
}

