/* IFAM - Instituto Federal de Ensino, Ciencia e Tecnologia do Amazonas
   Curso: Tecnologia em Análise e Desenvolvimento de Sistemas
   Prof.: Sergio Augusto C. Bezerra
   Programa "AB_INSPF_dev_2015.CPP" para exemplificar uma insercao em arvores binarias.
   Além de caminhamento pré-fixado.
*/
#include <stdio.h>
#include <new>    //<alloc.h>
#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoXY(int x, int y);

/****************** VARIAVEIS GLOBAIS ******************/

  char resp;
  char opcao;
  float valor;

  struct Notas {
    float valor;   /* numeros de 1 a no maximo 40 */
    struct Notas *pEsq, *pDir; //ponteiros Esquerdo e Direito
				//para as proximas notas */
  } inicio, *pPercorre, *pAloc;

/****************** DECLARACAO DAS FUNCOES ******************/
void inserir(float valorFunc);
void pre_fixado(Notas *pPF);
void titulo();

/****************** FUNCAO OPCAO INSERIR ******************/
void opcaoInserir(){
   do{
     system("cls");
     titulo();
     gotoXY(3,9);
     cout << "Valor da Nota: ";
     cin >> valor;
     pPercorre = inicio.pDir;
     inserir(valor);
     gotoXY(3,11);
     cout << "Deseja continuar? Sim[S] Nao[outra tecla]---->";
     cin >> resp;
     resp = toupper(resp);
   }while (resp == 'S');
}
/****************** FUNCAO CAMINHO PRE-FIXADO ******************/
void opcaoCaminhoPreFixado(){
  system("cls");
  titulo(); 
  gotoXY(3,7);
  if(inicio.pDir == NULL){
     cout << "Arvore Vazia";
  }
  else{  	
    cout << "Caminho Pre-Fixado: ";
    pre_fixado(inicio.pDir);    
  }  
  gotoXY(3,8);
  system("pause");
  
}
/****************** FUNCAO TITULO DO PROGRAMA ******************/
void titulo(){
  system("cls");
  gotoXY(3,5);
  cout << "CADASTRO E EXIBICAO DE NOTAS EM ARVORE BINARIA";
}


/****************** FUNCAO MENU ******************/
void menu(){
  do{
    titulo();
    gotoXY(3,7);
    cout << "***** MENU *****";
    gotoXY(3,9);
    cout << "[1] Inserir";
    gotoXY(3,11);
    cout << "[2] Caminho Pre-Fixado";
    gotoXY(3,13);
    cout << "[3] Sair";
    gotoXY(3,15);
    cout << "Escolha uma opcao:  ";
    cin >> opcao;
     
    if(opcao=='1' || opcao=='2' || opcao=='3'){   
	  if(opcao=='1') 
	    opcaoInserir();
	  else if(opcao=='2')
	    opcaoCaminhoPreFixado();
	  else
         break;
    }
    else{
      gotoXY(30,15);
      cout << "Opcao Invalida";
      printf("\n");
      gotoXY(30,16);
	  system("pause");	
    }
            
  }while(opcao != '0' );

}

/****************** FUNCAO ALOCA ******************/
void alocar(float valorAloc){
  pAloc = new(Notas);
  pAloc->valor = valorAloc;
  pAloc->pEsq = NULL;
  pAloc->pDir = NULL;
}
/****************** FUNCAO INSERIR ******************/
void inserir(float valorFunc){
  if(inicio.pDir==NULL){
    alocar(valorFunc);
    inicio.pDir = pAloc;
    pPercorre = inicio.pDir;
  }
  else{
    if(valorFunc < pPercorre->valor){
      if(pPercorre->pEsq != NULL){
        pPercorre = pPercorre->pEsq;
        inserir(valorFunc);
      }
      else{
        alocar(valorFunc);
        pPercorre->pEsq = pAloc;
      }
    }
    else{
	if(pPercorre->pDir != NULL){
	  pPercorre = pPercorre->pDir;
	  inserir(valorFunc);
	}
	else{
	  alocar(valorFunc);
	  pPercorre->pDir = pAloc;
	}
    }
  }
}
/****************** FUNCAO PRE-FIXADO ******************/
/* Caminhamento pre-fixado:
     1 - visita a raiz
     2 - percorre a subarvore da esquerda
     3 - percorre a subarvore da direita
*/
void pre_fixado(Notas *pPF){
  if(pPF!=NULL){
    cout << pPF->valor << "  ";
    pre_fixado(pPF->pEsq);
    pre_fixado(pPF->pDir);
  }

}

/****************** FUNCAO para Posicionar o prompt ******************/
void gotoXY(int x, int y) 
{ 
  CursorPosition.X = x; // Locates column
  CursorPosition.Y = y; // Locates Row
  SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
}

/****************** FUNCAO PRINCIPAL ******************/
int main(void){
   valor = 0;
   inicio.pDir = NULL;
   inicio.pEsq = NULL;

   menu();
   pAloc = NULL;
   pPercorre = NULL;
   
   printf("\n");
   system("pause");
   return 0;
}
