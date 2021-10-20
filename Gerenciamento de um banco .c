#include <stdio.h>

#define dividaMaxima 30000
#define dividaMaximaEspecial 50000

#define true 1
#define false 0

typedef int bool;

typedef struct{
	char* nome;
	int cpf;
} PESSOA;


typedef struct{
	PESSOA pessoa;
	char tipo;
	int valorContaCorrente;
	int valorDaDivida;
} CLIENTE;


typedef struct{
	PESSOA pessoa;
	CLIENTE* clientes[20];
	int numClientes;
} GERENTE;


typedef struct{
	GERENTE* gerentes[10];
	int numGerentes;
} BANCO;


/********************** FUNCOES PARA CRIAR CLIENTES, GERENTES OU BANCOS ******/


/* Funcao para a criacao de um novo cliente.
   A funcao preenche todos os valores de seus campos e retorna esse novo cliente.
*/
CLIENTE novoCliente(char* nome, int cpf, int valorInicial){
	CLIENTE novo;
	novo.pessoa.nome = nome;
	novo.pessoa.cpf = cpf;
	novo.valorContaCorrente = valorInicial;
	novo.valorDaDivida = 0;
	novo.tipo = 'C';
	return novo;
}

/* Funcao para a criacao de um novo cliente especial.
   A funcao preenche todos os valores de seus campos (utilizando a funcao novoCliente)
   e retorna esse novo cliente especial.
*/
CLIENTE novoClienteEspecial(char* nome, int cpf, int valorInicial){
	CLIENTE novo = novoCliente(nome,cpf,valorInicial);
	novo.tipo = 'E';
	return novo;
}

/* Funcao para a criacao de um novo gerente.
   A funcao preenche os valores de seus campos e retorna esse novo gerente.
*/
GERENTE novoGerente(char* nome, int cpf){
	GERENTE novo;
	novo.pessoa.nome = nome;
	novo.pessoa.cpf = cpf;
	novo.numClientes = 0;
	return novo;
}

/* Funcao para a criacao de um novo banco.
   A funcao preenche os valores de seus campos e retorna esse novo banco.
*/
BANCO novoBanco(){
	BANCO novo;
	novo.numGerentes = 0;
	return novo;
}





/********************** FUNCOES DOS CLIENTES *********************************/


/* Funcao que retorna true caso valorContaCorrente seja menor do que valorDaDivida.
 * Caso contrario, retorna false.  */
bool negativado(CLIENTE* c1) {

	if (c1->valorContaCorrente < c1->valorDaDivida)						//condicionando para cliente negativado (saldo menor que a divida)
		return true;
	else{

		return false;
	}
}


/* Funcao para o cliente atual (referenciado por c1) obter um emprestimo de acordo com o valor passado por parametro
 *   Caso o valor do parametro seja menor ou igual a zero, a funcao deve retornar false
 *   Caso contrario ha duas situacoes:
 *     1a) se o valor do parametro mais o valor do campo valorDaDivida for maior do
 *         que o valor da constante dividaMaxima (para clientes regulares) ou 
 *         dividaMaximaEspecial (para clientes especiais), a funcao deve retornar false 
 *     2a) caso contrario, o campo valorDaDivida deve ser incrementado em valor, o campo
 *         valorContaCorrente deve ser incrementado em valor e a funcao deve retornar true
 */
bool obterEmprestimo(CLIENTE* c1, int valor) {
	if (valor <=0)																//condiçao para nao trabalhar com zero e valores negativos
		return false;

	if ((c1->tipo == 'C' && (valor+c1->valorDaDivida > dividaMaxima))|| (c1->tipo == 'E' && valor+c1->valorDaDivida > dividaMaximaEspecial)) // condicionando para acessar cliente e cliente especial e checar se o emprestimo somado ao que ele ja deve nao ultrapassa o valor de divida maxima
		return false;
	
	else{																
	
		c1->valorContaCorrente = valor + c1->valorContaCorrente;					//se a divida maxima para os dois tipos de clientes nao for ultrapassada , entao o valor solicitado é adicionado na conta corrente e na divvida do cliente
		c1->valorDaDivida = valor + c1->valorDaDivida;
		return true;
	}
}

	





/* Funcao para o cliente atual (referenciado por c1) pagar parte de sua divida de acordo com o valor passado por parametro
 *   Caso o valor do parametro seja menor ou igual a zero, a funcao deve retornar false
 *   Caso contrario ha duas situacoes:
 *     1a) se o valor do parametro for maior do que o valorDaDivida ou for maior do que 
 *         valorContaCorrente, a funcao deve retornar false 
 *     2a) caso contrario, o campo valorDaDivida deve ser decrementado em valor, o campo
 *         valorContaCorrente deve ser decrementado em valor e a funcao deve retornar true
 */
bool pagarEmprestimo(CLIENTE* c1, int valor) {
	if (valor <=0)														//condicionando para nao trabalhar com valores negativos e zero.
		return false;

	if(valor > c1->valorDaDivida||valor > c1->valorContaCorrente)			//condicionando para fazer o pagamento do emprestimo 
		return false;
	
	else {
		c1->valorDaDivida = c1->valorDaDivida - valor;						//se o valor passado por parametro ser compativel com o saldo do cliente entao esse valor é descontado de sua conta para o pagamento do emprestimo e tambem abatido do valor de sua divida
		c1->valorContaCorrente = c1->valorContaCorrente - valor;
		return true;
	}
	

}



/* Funcao para o cliente atual (referenciado por c1) realizar um saque do valor passado por parametro
 *   Caso o valor do parametro seja menor ou igual a zero, a funcao deve retornar false
 *   Caso contrario ha duas situacoes:
 *     1a) se o valor do parametro for maior do que o valor do campo valorContaCorrente, a 
 *         funcao deve retornar false
 *     2a) caso contrario, o campo valorContaCorrente deve ser decrementado em valor e a
 *         funcao deve retornar true
 */
bool realizarSaque(CLIENTE* c1, int valor) {
	if (valor <=0)									//condicionando para nao trabalhar com valores negativos e o zero
		return false;
	
		if (valor>c1->valorContaCorrente)    		//condicionando para nao permitir saques maiores que o saldo da conta do cliente
			return false;
		else{
		c1->valorContaCorrente = c1->valorContaCorrente - valor;    //se o saldo do cliente possibilitar o saque do valor passado pelo paramentro entao esse valor sacado é descontando de sua conta
			return true;		
		}	
	
	
}




/********************** FUNCOES DOS GERENTES *********************************/


/* Funcao para adicionar um cliente no arranjo de clientes do gerente referenciado por g1.
 * Caso o numero de clientes seja igual a 20, nao deve adicionar e deve retornar false.
 * Caso contrario, ha duas situacoes: 
 *   1a: o cliente ja consta no arranjo de clientes (verifique isso usando o numero do cpf),
 *       neste caso o cliente nao deve ser reinserido e a funcao deve retornar false; 
 *   2a: o cliente passado como parametro nao consta no arranjo de clientes: o cliente 
 *       deve ser adicionado na posicao numClientes, o campo numClientes deve ser 
 *       incrementado em 1 e a funcao deve retornar true. 
 */
bool adicionarCliente(GERENTE* g1, CLIENTE* cliente) {
	if (g1->numClientes == 20) return false;
	int x;
	for (x=0;x<g1->numClientes;x++){
		if (g1->clientes[x]->pessoa.cpf == cliente->pessoa.cpf) return false;
	}
	g1->clientes[g1->numClientes] = cliente;
	g1->numClientes++;
	return true;
}



/* Funcao para cobrar os emprestimos de todos os clientes do gerente atual (referenciado por g1).
 * Para cada um dos clientes presentes no arranjo clientes, este metodo deve:
 *   - nao fazer nada para o cliente, caso seu valorDaDivida seja igual a zero
 *   - caso contrario, ha duas situacoes:
 *     1a) se o valorContaCorrente do cliente for maior ou igual ao valorDaDivida, deve
 *         fazer o cliente pagar a divida, isto e, o valorContaCorrente sera atualizado, 
 *         descontando-se o valor da divida e o valorDaDivida sera zerado.
 *     2a) se o valorContaCorrente do cliente for menor do que o valorDaDivida, deve
 *         fazer o cliente pagar parte da divida, isto e, o valorDaDivida sera atualizado,
 *         tendo seu valor diminuido pelo valorContaCorrente e o valorContaCorrente sera zerado.
 */
void cobrarTodosEmprestimos(GERENTE g1) {
	CLIENTE* atual;
	int c;
	for (c=0; c < g1.numClientes; c++){
		atual = g1.clientes[c];
		if (atual->valorDaDivida > 0){
			if (atual->valorContaCorrente >= atual->valorDaDivida){
				atual->valorContaCorrente -= atual->valorDaDivida;
				atual->valorDaDivida = 0;
			}else{
				atual->valorDaDivida -= atual->valorContaCorrente;
				atual->valorContaCorrente = 0;
			}
		}
	}
}



/* Funcao para imprimir informacoes sobre os clientes gerenciados por ger1 */
void imprimirClientes(GERENTE ger1){
	CLIENTE* atual;
	printf("\tNumero de clientes: %i\n", ger1.numClientes);
	for (int c=0; c < ger1.numClientes; c++){
		atual = ger1.clientes[c];
		printf("%4i %c %s\t%11i %8i %8i %i\n", c+1, atual->tipo, atual->pessoa.nome, atual->pessoa.cpf, atual->valorContaCorrente, atual->valorDaDivida, negativado(atual));
	}
}




/********************** FUNCOES DOS BANCOS ***********************************/

/* Funcao para adicionar um gerente no arranjo de gerentes do banco referenciado por b1.
 * Caso o numero de gerentes seja igual a 10, nao deve adicionar e deve retornar false.
 * Caso contrario, ha duas situacoes: 
 *   1a: o gerente ja consta no arranjo de gerentes (verifique isso usando o numero do cpf),
 *       neste caso o gerente nao deve ser reinserido e a funcao deve retornar false; 
 *   2a: o gerente passado como parametro nao consta no arranjo de gerentes: o gerente 
 *       deve ser adicionado na posicao numGerentes, o campo numGerentes deve ser 
 *       incrementado em 1 e a funcao deve retornar true. 
 */
bool adicionarGerente(BANCO* b1, GERENTE* gerente){
	if (b1->numGerentes==10)							//condicionando para verificar se o banco ja possui o numero maximo de gerentes
		return false;
	else {
		for (int y=0;y<b1->numGerentes;y++){							//laço para verificar se o gerente ja consta no banco 
			if(b1->gerentes[y]->pessoa.cpf == gerente->pessoa.cpf)
				return false;
	}
	b1->gerentes[b1->numGerentes] = gerente;							//se o gerente nao possuir ao banco ele é adicionado ao banco
	b1->numGerentes++;													//acrescentando uma unidade no numero de gerentes do banco 
	
	return true;
}
}



/* Funcao para imprimir informacoes gerais sobre o banco b1 (passado como parametro) */
void imprimirDadosBanco(BANCO b1){
	printf("#########################################################################\n");
	printf("Imprimindo informacoes do banco.\n");
	printf("Ha %i gerente(s) neste banco.\n",b1.numGerentes);
	GERENTE* ger;
	for (int g=0; g < b1.numGerentes; g++){
		ger = b1.gerentes[g];
		printf("Gerente: %s\tCPF: %i\n", ger->pessoa.nome, ger->pessoa.cpf);
		imprimirClientes(*ger);
	}
	printf("#########################################################################\n");
}





int main(){
	
	printf("ATENCAO: Nem todas as caracteristicas do enunciado sao testadas neste exemplo.\n");
	printf("         Cabe a cada aluno(a) testar cuidadosamente seu EP.\n\n");
	
	printf("*** Criando Clientes **************************************\n");
	CLIENTE c1 = novoCliente("Cliente A\0", 22222, 10000);
	CLIENTE c2 = novoClienteEspecial("Cliente B\0", 33333, 2000);
	CLIENTE c3 = novoCliente("Cliente C\0", 44444, 30000);
	CLIENTE c4 = novoCliente("Cliente D\0", 55555, 10);


	printf("*** Criando Gerentes **************************************\n");
	GERENTE ger1 = novoGerente("Gerente 1\0", 12345);
	GERENTE ger2 = novoGerente("Gerente 2\0", 12121);



	printf("*** Criando um Banco **************************************\n");
	BANCO meuBanco = novoBanco();
	
	

	printf("*** Adicionando clientes ao Gerente 1 **************************\n");
	
	if (adicionarCliente(&ger1, &c1)) printf("Cliente '%s' adicionado corretamente.\n", c1.pessoa.nome);
	else printf("Cliente '%s' nao pode ser adicionado.\n", c1.pessoa.nome);
	
	if (adicionarCliente(&ger1, &c2)) printf("Cliente '%s' adicionado corretamente.\n", c2.pessoa.nome);
	else printf("Cliente '%s' nao pode ser adicionado.\n", c2.pessoa.nome);
	
	if (adicionarCliente(&ger1, &c2)) printf("Cliente '%s' adicionado corretamente.\n", c2.pessoa.nome);
	else printf("Cliente '%s' nao pode ser adicionado.\n", c2.pessoa.nome);
	
	if (adicionarCliente(&ger1, &c3)) printf("Cliente '%s' adicionado corretamente.\n", c3.pessoa.nome);
	else printf("Cliente '%s' nao pode ser adicionado.\n", c3.pessoa.nome);
	
	printf("*** Adicionando clientes ao Gerente 2 **************************\n");
	
	if (adicionarCliente(&ger2, &c3)) printf("Cliente '%s' adicionado corretamente.\n", c3.pessoa.nome);
	else printf("Cliente '%s' nao pode ser adicionado.\n", c3.pessoa.nome);
	
	if (adicionarCliente(&ger2, &c4)) printf("Cliente '%s' adicionado corretamente.\n", c4.pessoa.nome);
	else printf("Cliente '%s' nao pode ser adicionado.\n", c4.pessoa.nome);
	
	printf("*** Adicionando Gerentes ao Banco ******************************\n");
	
	adicionarGerente(&meuBanco,&ger1);
	adicionarGerente(&meuBanco,&ger2);
	
	imprimirDadosBanco(meuBanco);


	printf("*** Testando a funcao obterEmprestimo **************************\n");
	
	if (obterEmprestimo(&c4, 20000))  printf("Cliente '%s' obteve o emprestimo solicitado.\n", c4.pessoa.nome);
	else  printf("Cliente '%s' nao obteve o emprestimo solicitado.\n", c4.pessoa.nome);
	

	if (obterEmprestimo(&c4,20000))  printf("Cliente '%s' obteve o emprestimo solicitado.\n", c4.pessoa.nome);
	else  printf("Cliente '%s' nao obteve o emprestimo solicitado.\n", c4.pessoa.nome);

	
	if (obterEmprestimo(&c2,20000))  printf("Cliente '%s' obteve o emprestimo solicitado.\n", c2.pessoa.nome);
	else  printf("Cliente '%s' nao obteve o emprestimo solicitado.\n", c2.pessoa.nome);


	if (obterEmprestimo(&c2,20000))  printf("Cliente '%s' obteve o emprestimo solicitado.\n", c2.pessoa.nome);
	else  printf("Cliente '%s' nao obteve o emprestimo solicitado.\n", c2.pessoa.nome);

	
	imprimirDadosBanco(meuBanco);

	printf("*** Testando a funcao realizarSaque ****************************\n");
	
	if (realizarSaque(&c2, 12345))  printf("Cliente '%s' realizou o saque solicitado.\n", c2.pessoa.nome);
	else  printf("Cliente '%s' nao pode realizar o saque solicitado.\n", c2.pessoa.nome);

	if (realizarSaque(&c2, 12345))  printf("Cliente '%s' realizou o saque solicitado.\n", c2.pessoa.nome);
	else  printf("Cliente '%s' nao pode realizar o saque solicitado.\n", c2.pessoa.nome);

	if (realizarSaque(&c1, 10000))  printf("Cliente '%s' realizou o saque solicitado.\n", c1.pessoa.nome);
	else  printf("Cliente '%s' nao pode realizar o saque solicitado.\n", c1.pessoa.nome);


	if (realizarSaque(&c1, 1))  printf("Cliente '%s' realizou o saque solicitado.\n", c1.pessoa.nome);
	else  printf("Cliente '%s' nao pode realizar o saque solicitado.\n", c1.pessoa.nome);

	
	imprimirDadosBanco(meuBanco);
	

	printf("*** Testando a funcao pagarEmprestimo **************************\n");
	if (pagarEmprestimo(&c1, 100))  printf("Cliente '%s' pagou (parte de) sua divida.\n", c1.pessoa.nome);
	else  printf("Cliente '%s' nao pode pagar (parte de) sua divida.\n", c1.pessoa.nome);

	if (pagarEmprestimo(&c2, 100))  printf("Cliente '%s' pagou (parte de) sua divida.\n", c2.pessoa.nome);
	else  printf("Cliente '%s' nao pode pagar (parte de) sua divida.\n", c2.pessoa.nome);
	
	if (pagarEmprestimo(&c3, 100))  printf("Cliente '%s' pagou (parte de) sua divida.\n", c3.pessoa.nome);
	else  printf("Cliente '%s' nao pode pagar (parte de) sua divida.\n", c3.pessoa.nome);

	if (pagarEmprestimo(&c4, 100))  printf("Cliente '%s' pagou (parte de) sua divida.\n", c4.pessoa.nome);
	else  printf("Cliente '%s' nao pode pagar (parte de) sua divida.\n", c4.pessoa.nome);

	
	imprimirDadosBanco(meuBanco);


	printf("*** Testando a funcao cobrarTodosEmprestimos *******************\n");
	
	cobrarTodosEmprestimos(ger1);
	imprimirDadosBanco(meuBanco);
	
	cobrarTodosEmprestimos(ger2);
	imprimirDadosBanco(meuBanco);
	
	
	printf("\nATENCAO: Nem todas as caracteristicas do enunciado sao testadas neste exemplo.\n");
	printf("         Cabe a cada aluno testar cuidadosamente seu EP.\n\n");
	
	printf("* Testando a funcao negativados *******\n");
    if(negativado(&c1)) printf("Cliente '%s' esta negativado\n", c1.pessoa.nome);
    else printf("Cliente '%s' nao esta negativado\n", c1.pessoa.nome);

    if(negativado(&c2)) printf("Cliente '%s' esta negativado\n", c2.pessoa.nome);
    else printf("Cliente '%s' nao esta negativado\n", c2.pessoa.nome);

    if(negativado(&c3)) printf("Cliente '%s' esta negativado\n", c3.pessoa.nome);
    else printf("Cliente '%s' nao esta negativado\n", c3.pessoa.nome);

    if(negativado(&c4)) printf("Cliente '%s' esta negativado\n", c4.pessoa.nome);
    else printf("Cliente '%s' nao esta negativado\n", c1.pessoa.nome);

    imprimirDadosBanco(meuBanco);

	return 0;	
}
