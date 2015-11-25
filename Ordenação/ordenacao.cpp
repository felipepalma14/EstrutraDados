#include <stdio.h>
#include <stdlib.h>

void ordenacaoPorSelecao(int notas[],int tamanho){
	int i,j,min,temp;
	for(i=0;i < tamanho-1;i++){
		min = i;// aguarda o indice minimo
		for(j=i+1; j <tamanho;j++){
			//verifica se o posterior eh maior que o minimo
			if(notas[j]>notas[min]){
				min=j;
			}
		}
		// troca as possicoes
		temp = notas[i];
		notas[i] = notas[min];
		notas[min] = temp;
	}
}

int main(){
	int notas[3] = {3,4,1};
	ordenacaoPorSelecao(notas,3);
	int k;
	for(k=0;k<3;k++){
		printf("%d\n",notas[k]);
	}
}
