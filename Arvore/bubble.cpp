#include <stdio.h>
#include <stdlib.h>


void ordena_por_bolha(int vetor[],int tamanho){
	int i,j,aux;
	for(i=0;i<tamanho;i++){
		for(j=0;j<tamanho-1;j++){
			if(vetor[j] > vetor[j+1]){
				aux = vetor[j+1];
				vetor[j+1] = vetor[j];
				vetor[j] = aux;
				
			}
		}
	}
}


int main(){

	int vetor[3] = {3,2,1};
	
	/*
	int i,j,aux,tamanho=3;
	for(i=0;i<tamanho;i++){
		for(j=0;j<tamanho-1;j++){
			if(vetor[j] > vetor[j+1]){
				aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
				
			}
		}
	}
	*/
	
	ordena_por_bolha(vetor,3);
	int k;
	for(k=0;k<3;k++){
		printf("%d\n",vetor[k]);
	}
}
