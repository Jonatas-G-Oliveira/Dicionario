//Nome:Jonatas Garcia de OLiveira TIA:42181232

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void alocaVetor(char ***pp,int qtd_palavras,int tam_palavras){
	int j;
	*pp =(char **)malloc(qtd_palavras * sizeof(char *));
	for(j = 0;j < qtd_palavras; j++){
		(*pp)[j]= (char *)malloc(tam_palavras * sizeof(char));
	}		
}

void liberaVetor(char ***pp,int linha){
	int j;
	for(j =0;j < linha;j++){
		free((*pp)[j]);
	}
	free(*pp);
	*pp = NULL;
}


int buscaBinaria(char **matriz,char *palavra,int inicio,int fim){
	int m = (inicio + fim)/2;
	
	if(inicio > fim){
		return -1;//Item esta não esta na matriz
	}
	
	if(strcmp(matriz[m],palavra) == 0){
		return 1; //Achei o item
	} 
	
	if(strcmp(palavra,matriz[m]) == 1 ){
		return buscaBinaria(matriz,palavra,inicio,m-1);//O item esta a esquerda
	}	
	else{
		return buscaBinaria(matriz,palavra,m+1,fim);//O item esta a direta
	}
	
	return 0;
}


void transformaMinuscula(char *palavra){			
		int i= 0;										//Transforma cada caractere em minusculo
		for(i;i < strlen(palavra);i++){
			palavra[i] = tolower(palavra[i]);			
		}
		palavra[i] = '\0';								//Retorna a palavra em minuscula
}


char **ordenacaoRecursiva(char **palavras,int n){
	int j =0;
	char *aux;
	if(n==1){
		return palavras;
	}
	int count = 0;
	for(j =0;j < n;j++){
		if((strcmp(palavras[j],palavras[j+1])) == -1){ 	
			aux = palavras[j];
			palavras[j] = palavras[j+1];
			palavras[j+1] = aux;
			count++;
		}
	}
		if(count == 0){
			return palavras;
		}
		
	return ordenacaoRecursiva(palavras,n-1);
}


void imprimeArquivo(char **palavras,int tamanho){
	int j = 0 ;
	FILE *file = fopen("dicionario.txt","w");
	if(file){
		for(j = 0;j< tamanho;j++){
			fprintf(file, "%s\n",palavras[j]);
		}
		fprintf(file,"\n\nQUANTIDADE DE PALAVRAS: %d",tamanho);
	}else{
		printf("Não foi possível abrir o arquvivo\n");
	}
}


void main(){
	char **palavras,texto[30];
	alocaVetor(&palavras,100,30);
	FILE *arquivo = fopen("textoSamuel.txt","r");
	int tam = 0;
	while(fscanf(arquivo," %s",texto) != EOF) {
		transformaMinuscula(texto);
		
		if(strcmp(texto,".") == 0){			//Verifica se chegou no ponto final
			break;
		}
		
		if(tam > 1 && buscaBinaria(palavras,texto,0,tam) == 1){ //Se a palavra ja estiver no vetor eu travo a
			tam = tam;											//posição que ela esta,para substitui-la na próxima iteração
		}else{		
			strcpy(palavras[tam],texto);						//Se a palavras não estiver eu eu insiro ela no vetor			
			ordenacaoRecursiva(palavras,tam);					//Ordeno e aumento o contador
			tam++;
		}
		
	}
	imprimeArquivo(palavras,tam);
	liberaVetor(&palavras,100);
	fclose(arquivo);
	printf("Programa Finalizado");
	
}
	

