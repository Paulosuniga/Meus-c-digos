#include <stdio.h>
#include <stdlib.h>

int contagem1(int* valores, int n, int x){
  int resposta = 0;
  int i;
  for (i=0;i<n;i++) //la�o para percorrer o arranjo
  if(valores[i]==x)  //condicionando para fazer a contagem 
  resposta=resposta+1;
  else resposta=resposta;
  

    
  return resposta;
}

int main() {
  int* x = (int*) malloc(sizeof(int)*10);
  x[0] = 3;
  x[1] = 4;
  x[2] = 5;
  x[3] = -1;
  x[4] = 7;
  x[5] = 3;
  x[6] = 4;
  x[7] = 3;
  x[8] = -1;
  x[9] = 3;
  
  printf("Resultado: %i\n", contagem1(x, 10, 3));

  return 0;
}
