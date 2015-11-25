#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <windows.h>


struct Dicionario{
	char palavra[200];
	struct Dicionario *proximo;
};

struct Arvore {
	char letra;
	struct Dicionario *inicio;
	struct Arvore * direita, * esquerda;
};

//DECLARACOES DAS FUNCOES

Arvore* search(Arvore ** raiz, char letra);
void imprimirPalavras(Dicionario *dicionario);


void insert(Arvore ** raiz, char letra,char palavra[200])
{
	Arvore *hasLetraRaiz = search(&(*raiz),letra);
	letra = toupper(letra);
    Arvore *temp = NULL;
    Dicionario *dictTemp = NULL;
    
    if(!(*raiz)){
        temp = (Arvore *)malloc(sizeof(Arvore));
        temp->esquerda = temp->direita = NULL;
        temp->letra = letra;
        
        dictTemp = (Dicionario*)malloc(sizeof(Dicionario));
		strcpy(dictTemp->palavra,palavra);
		dictTemp->proximo = NULL;
        temp->inicio = dictTemp;
        *raiz = temp;
        
		return;
    }else{
		 if(hasLetraRaiz != NULL){
			printf("Raiz com letra semelhante\n");
			
			
			dictTemp = hasLetraRaiz->inicio;
			while(dictTemp->proximo!=NULL){
				dictTemp= dictTemp->proximo;
			}	
			dictTemp->proximo = (Dicionario*)malloc(sizeof(Dicionario));
	        dictTemp = dictTemp->proximo;
	        strcpy(dictTemp->palavra,palavra);
	        dictTemp->proximo = NULL;
			
			printf("%s\n",dictTemp->palavra);
		}else{
				
		    if(letra <= (*raiz)->letra)
		    {
		        insert(&(*raiz)->esquerda, letra,palavra);
		    }
		    else if(letra >= (*raiz)->letra)  
			{
		        insert(&(*raiz)->direita,letra,palavra);
		        
		    }
		}
	}

}

void print_preorder(Arvore *raiz)
{
    if (raiz)
    {
        printf("%c\n",raiz->letra);
        print_preorder(raiz->esquerda);
        print_preorder(raiz->direita);
    }

}

void print_inorder(Arvore *raiz)
{
    if (raiz)
    {
        print_inorder(raiz->esquerda);
        printf("%c\n",raiz->letra);
        print_inorder(raiz->direita);
    }
}

void print_postorder(Arvore *raiz)
{
    if (raiz)
    {
        print_postorder(raiz->esquerda);
        print_postorder(raiz->direita);
        printf("%c\n",raiz->letra);
    }
}

void deltree(Arvore *raiz)
{
    if (raiz)
    {
        deltree(raiz->esquerda);
        deltree(raiz->direita);
        free(raiz);
    }
}

Arvore* search(Arvore ** raiz, char letra)
{
	letra = toupper(letra);
    if(!(*raiz))
    {
        return NULL;
    }
	
    if(letra < (*raiz)->letra)
    {
        search(&((*raiz)->esquerda), letra);
    }
    else if(letra > (*raiz)->letra)
    {
        search(&((*raiz)->direita), letra);
    }
    else if(letra == (*raiz)->letra)
    {
        return *raiz;
    }
}

void imprimirPalavras(Dicionario *dicionario){
	while(dicionario!=NULL){
		printf("%s\n",dicionario->palavra);
		dicionario = dicionario->proximo;
	}
	system("pause");
}

int main()
{
    Arvore *root;
    Arvore *tmp;
    //int i;
    root = NULL;
    /* Inserting nodes into tree */
    insert(&root, 'f',"felipe");
    insert(&root, 'g',"gato");
	insert(&root, 'p',"pato");
	insert(&root, 'p',"prato");
	insert(&root, 'p',"pagapaio");
	insert(&root, 'a',"abelha");
	
	
    printf("Pre Central\n");
    print_preorder(root);

    printf("Central\n");
    print_inorder(root);

    printf("Pos Central\n");
    print_postorder(root);

    /* Search node into tree */
    tmp = search(&root, 'a');
    if (tmp)
    {
        printf("Resultado do Nodo Pesquisado = %c\n", tmp->letra);
        imprimirPalavras(tmp->inicio);
    }
    else
    {
        printf("Nennhum dado encontra.\n");
    }

    /* Deleting all nodes of tree */
    deltree(root);
}
