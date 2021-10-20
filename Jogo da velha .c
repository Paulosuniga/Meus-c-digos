#include <stdio.h>

#define pecaX 'X'
#define pecaY 'O'
#define espacoVazio ' '

#define true 1
#define false 0

typedef int bool;


/*
	Jogo da Velha - programa para verificar o status de um jogo.

	Lista de Status calculado:
    0 - Jogo nao iniciado: o tabuleiro esta 'vazio', i.e., sem pecas X e O;
    1 - Jogo encerrado1: o primeiro jogador (que usa as pecas X) ganhou;
    2 - Jogo encerrado2: o segundo jogador (que usa as pecas O) ganhou;
    3 - Jogo encerrado3: empate - todas as casas do tabuleiro estao preenchidas com X e O, mas nenhum dos jogadores ganhou;
    4 - Jogo ja iniciado e em andamento: nenhuma das alternativas anteriores.	
 */

/*
	Determina o status de um partida de Jogo da Valha

	Entrada:
		tabuleiro - matriz 3x3 de caracteres representando uma partida valida de Jogo da Velha

	Saida:
		um inteiro contendo o status da partida (valores validos de zero a quatro)
 */


int verificaStatus(char tabuleiro[][3]) {
    int lin; //definindo variavel 
    int col; //definindo variavel
    if  ((tabuleiro[0][0]==' '&&tabuleiro[0][1]==' '&&tabuleiro[0][2]==' ')    //condicionando o codigo para que se em todas as posições da matriz não houver X ou O , retornar status 0 (jogo nao iniciado)
    &&    (tabuleiro[1][0]==' '&&tabuleiro[1][1]==' '&&tabuleiro[1][2]==' ')
    &&    (tabuleiro[2][0]==' '&&tabuleiro[2][1]==' '&&tabuleiro[2][2]==' ')
    &&    (tabuleiro[0][0]==' '&&tabuleiro[1][0]==' '&&tabuleiro[2][0]==' ')
    &&    (tabuleiro[0][1]==' '&&tabuleiro[1][1]==' '&&tabuleiro[2][1]==' ')
    &&    (tabuleiro[0][2]==' '&&tabuleiro[1][2]==' '&&tabuleiro[2][2]==' ')
    &&    (tabuleiro[0][0]==' '&&tabuleiro[1][1]==' '&&tabuleiro[2][2]==' ')
    &&    (tabuleiro[0][2]==' '&&tabuleiro[1][1]==' '&&tabuleiro[2][0]==' '))
        return 0;
    else {
        if    ((tabuleiro[0][0]=='X'&&tabuleiro[0][1]=='X'&&tabuleiro[0][2]=='X') //condicionando o codigo para possibilidades de quem esta com as peças X vencer(status 1 ), seja em linhas,colunas o diagonais a sucessao da letra X tres vezes 
        ||   (tabuleiro[1][0]=='X'&&tabuleiro[1][1]=='X'&&tabuleiro[1][2]=='X')
        ||     (tabuleiro[2][0]=='X'&&tabuleiro[2][1]=='X'&&tabuleiro[2][2]=='X')
        ||     (tabuleiro[0][0]=='X'&&tabuleiro[1][0]=='X'&&tabuleiro[2][0]=='X')
        ||     (tabuleiro[0][1]=='X'&&tabuleiro[1][1]=='X'&&tabuleiro[2][1]=='X')
        ||     (tabuleiro[0][2]=='X'&&tabuleiro[1][2]=='X'&&tabuleiro[2][2]=='X')
        ||     (tabuleiro[0][0]=='X'&&tabuleiro[1][1]=='X'&&tabuleiro[2][2]=='X')
        ||     (tabuleiro[0][2]=='X'&&tabuleiro[1][1]=='X'&&tabuleiro[2][0]=='X'))
            return 1;
        else {
            if  ((tabuleiro[0][0]=='O'&&tabuleiro[0][1]=='O'&&tabuleiro[0][2]=='O') //condicionando o codigo para possibilidades de quem esta com as peças O vencer (status 2) , seja em linhas ,colunas e diagonias a sucessao da letra O tres vezes 
            ||   (tabuleiro[1][0]=='O'&&tabuleiro[1][1]=='O'&&tabuleiro[1][2]=='O')
            ||     (tabuleiro[2][0]=='O'&&tabuleiro[2][1]=='O'&&tabuleiro[2][2]=='O')
            ||     (tabuleiro[0][0]=='O'&&tabuleiro[1][0]=='O'&&tabuleiro[2][0]=='O')
            ||     (tabuleiro[0][1]=='O'&&tabuleiro[1][1]=='O'&&tabuleiro[2][1]=='O')
            ||     (tabuleiro[0][2]=='O'&&tabuleiro[1][2]=='O'&&tabuleiro[2][2]=='O')
            ||     (tabuleiro[0][0]=='O'&&tabuleiro[1][1]=='O'&&tabuleiro[2][2]=='O')
            ||     (tabuleiro[0][2]=='O'&&tabuleiro[1][1]=='O'&&tabuleiro[2][0]=='O'))
                return 2;
            else {												//condicionando o codigo para o jogo em andamento 
                    for (lin=0;lin<3;lin++){					
                        for(col=0;col<3;col++){					//criação de um laço para percorrer todas as posições da matriz 
                            if((tabuleiro[lin][col] == ' '))	//caso seja encontrada uma posição em que nao ha X nem O , sendo as condições anteriores verificadas o codigo retorna jogo em andamento (status 4)
                                return 4;						
                    }
                }
            }
        }
        return 3; //caso nem uma das condições anteriores forem satisfeitas , a unica possibilidade é de empate (status 3 )
    }
}

int main(){
    char tab0[][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char tab1[][3] = {{'X','X','X'},{'O','O',' '},{' ',' ',' '}};
    char tab2[][3] = {{'O','X','X'},{'X','O','O'},{' ',' ','O'}};
    char tab3[][3] = {{'O','X','X'},{'X','O','O'},{'O','X','X'}};
    char tab4[][3] = {{' ',' ',' '},{'X','O','X'},{' ',' ',' '}};

    printf("Status calculado: %i\n", verificaStatus(tab0));
    printf("Status esperado para o tabuleiro0: 0\n\n");

    printf("Status calculado: %i\n", verificaStatus(tab1));
    printf("Status esperado para o tabuleiro1: 1\n\n");

    printf("Status calculado: %i\n", verificaStatus(tab2));
    printf("Status esperado para o tabuleiro2: 2\n\n");
    
    printf("Status calculado: %i\n", verificaStatus(tab3));
    printf("Status esperado para o tabuleiro1: 3\n\n");
    
    printf("Status calculado: %i\n", verificaStatus(tab4));
    printf("Status esperado para o tabuleiro4: 4\n\n");
    
    return 0;
}



