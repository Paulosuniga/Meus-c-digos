#include <stdio.h>



/*
	Calcula a raiz quadrada de um valor, com uma determinada
	precisao. Retorna esse valor, ou -1 quando:
	
	* a < 0
	* epsilon <= 0
	* epsilon >= 1
	
	Parametro:
		a - valor cuja raiz quadrada sera calculada
		epsilon - precisao do calculo
*/



double raizQuadrada(double a, double epsilon) {
	double resposta;        			//declarando variaveis
	double penultimaresposta; 
	double mod;							
	resposta = a/2;							 //primeiro iteração para começar se aproximar da raiz
	if (epsilon>1 || epsilon<=0	||	a<0) 	//condicionando o codigo para nao operar com valores de a negativos e nem com epsilon diferente do intervalo 0 e 1 
	return -1;
	if(a==0) 								//condicionando o codigo para retornar 0 quando a for 0 , ja que raiz de 0 é 0
	return 0;
	
	
	do {										//criando um laço , para que seja feito n operações com o objetivo de se aproximar da raiz quadrada solicitada
		penultimaresposta=resposta;
		resposta = (penultimaresposta+(a/penultimaresposta))/2;  //operações proposta por Newton para aproximação da raiz
		mod =  resposta-penultimaresposta;				
		if(mod < 0)								//operação para calcular o valor absoluto da diferença da linha anterior
		mod *=-1;
		
		
		
		
		
	}while (mod >= epsilon);					//condicionado a parada do laço , quando essa condição nao for mais satisfeita o codigo para de loopar , ja que a raiz de a estara bem proximo da exatidao





	return resposta;
}




int main() {



	/* Exemplo de teste: */
	double valor =850;
	double precisao = 0.001;
	printf("Raiz aproximada de %f = %f\n", valor, raizQuadrada(valor, precisao));

	return 0;
}
