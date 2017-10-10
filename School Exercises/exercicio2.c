#include<stdio.h> //Importa as funcoes: printf, sscanf, gets
#include<stdlib.h> //Importa as funcoes: system
#include<math.h> //Importa as funcoes: sqrt, exp

// Strings estáticas que vão se repetir pelo programa
const char limpar[] = "cls";
const char msg_invalido[] = "::: \"%s\" nao e uma resposta valida!\n";

// ****************************************
// * Subprograma 1
// ****************************************

// Chamado pelo menu
void subprograma1() {
	// Buffer para o "gets"
	char resposta[60];

	// Cabeçalho no inicio do programa
	system(limpar);
	printf("===[ VALIDA ENSAIO ]===\n");

	// Variaveis
	double deformidade, extensao, temp_variacao;

	// Para cada teste...
	int ensaio_i;
	for(ensaio_i=1; ensaio_i <= 500; ensaio_i++) {
		printf("* ENSAIO %d\n", ensaio_i);

		// Requista o valor da deformidade para o usuario
		while(1) {
			// Pergunta e captura resposta
			printf("Insira o valor da deformidade [mm]: ");
			gets(resposta);

			// Processa resposta (como um decimal)
			if(sscanf(resposta,"%lf",&deformidade) == 1)
				break;
			else
				printf(msg_invalido, resposta);
		}

		// Requista o valor da extensao para o usuario
		while(1) {
			// Pergunta e captura resposta
			printf("Insira o valor da extensao [mm]: ");
			gets(resposta);

			// Processa resposta (como um decimal)
			if(sscanf(resposta,"%lf",&extensao) == 1)
				break;
			else
				printf(msg_invalido, resposta);
		}

		// Requista o valor da variacao causada pelo aumento da temperatura para o usuario
		while(1) {
			// Pergunta e captura resposta
			printf("Insira o valor da variacao causada pelo aumento da temperatura [mm³]: ");
			gets(resposta);

			// Processa resposta (como um decimal)
			if(sscanf(resposta,"%lf",&temp_variacao) == 1)
				break;
			else
				printf(msg_invalido, resposta);
		}

		// Valida
		if(deformidade >= sqrt(temp_variacao) && extensao <= (deformidade / 3) && temp_variacao <= pow(deformidade * extensao, 2)) {
			printf("TESTE VÁLIDO\n\n");
		} else {
			printf("TESTE INVÁLIDO, DIGITE TODOS OS DADOS NOVAMENTE\n\n");
			ensaio_i -= 1;
		}
	}
}

// ****************************************
// * Subprograma 2
// ****************************************

// Chamado pelo menu
void subprograma2() {
	// Buffer para o "gets"
	char resposta[60];

	// Cabeçalho no inicio do programa
	system(limpar);
	printf("===[ MEDIA DE UM VETOR ]===\n");

	double media = 0, item = 0;

	// Requista o valor  para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira o primeiro valor: ");
		gets(resposta);

		// Processa resposta (como um decimal)
		if(sscanf(resposta,"%lf",&media) == 1)
			break;
		else
			printf(msg_invalido, resposta);
	}

	// Requista o valor da extensao para o usuario
	int saiu_do_loop = 0;
	while(!saiu_do_loop) {
		// Pergunta e captura resposta
		printf("Insira o proximo valor ou 'S' para sair: ");
		gets(resposta);

		// Este IF verifica se no 2º caracter da resposta termina o texto, ou  há uma quebra de linha.
		if(resposta[1] == 0 || resposta[1] == '\n') {
			// Para cada diferente valor do 1º caracter da resposta
			switch(resposta[0]) {
				case 's':
				case 'S':
					saiu_do_loop = 1;
					break;
			}
		}

		// Se saiu nao rodar o proximo codigo
		if(saiu_do_loop)
			break;

		// Processa resposta (como um decimal)
		if(sscanf(resposta,"%lf",&item) == 1) {
			media = (media + item) / 2;
		} else
			printf(msg_invalido, resposta);
	}

	// Exibe resultado
	printf("MEDIA: %lf\n", media);
}

// ****************************************
// * Subprograma 3
// ****************************************

// Chamado pelo menu
void subprograma3() {
	// Buffer para o "gets"
	char resposta[60];

	// Cabeçalho no inicio do programa
	system(limpar);
	printf("===[ MEDIA DE UM VETOR ]===\n");

	int item_i, item_qtd;
	double media = 0, itens[1024] = {0};

	// Requista o valor da extensao para o usuario
	item_i = 0;
	int saiu_do_loop = 0;
	while(!saiu_do_loop) {
		// Pergunta e captura resposta
		printf("Insira o proximo valor ou 'S' para sair: ");
		gets(resposta);

		// Este IF verifica se no 2º caracter da resposta termina o texto, ou  há uma quebra de linha.
		if(resposta[1] == 0 || resposta[1] == '\n') {
			// Para cada diferente valor do 1º caracter da resposta
			switch(resposta[0]) {
				case 's':
				case 'S':
					saiu_do_loop = 1;
					break;
			}
		}

		// Se saiu nao rodar o proximo codigo
		if(saiu_do_loop)
			break;

		// Processa resposta (como um decimal)
		if(sscanf(resposta,"%lf",&itens[item_i]) == 1) {
			// Ja ajusta a media
			if(item_i == 0)
				media = itens[item_i];
			else
				media = (media + itens[item_i]) / 2;

			// Avança um item
			item_i += 1;
		} else
			printf(msg_invalido, resposta);
	}

	// Salva a quantidade de itens
	item_qtd = item_i;

	// Variavel de desvio
	double desvio;

	// Para cada valor que tivemos de itens
	for(item_i=0; item_i < item_qtd; item_i++) {
		desvio += itens[item_i] - media;
	}

	// Transforma a soma dos desvios em sua media
	desvio /= item_qtd;

	printf("RESULTADOS:\n\tMEDIA: %lf\n\tDESVIO PADRAO: %lf\n\n", media, desvio);
}

// ****************************************
// * MENU PRINCIPAL
// ****************************************

int main() {
	// Buffer para o "gets"
	char resposta[60];

	// Pergunta ao usuario o que fazer em seguida
	int saiu_do_programa = 0;
	while(!saiu_do_programa) {
		// Cabeçalho no inicio do programa
		system(limpar);
		printf("===[ PROGRAMA DE LABORATORIO ]===\n");

		// Pergunta e captura resposta
		printf("Comandos disponiveis:\n\t1. Subprograma de validação de testes\n\t2. Subprograma de medias\n\t3. Subprograma de desvio\n\tQ. Sair\nEscolha um comando [1-3,Q]:");
		gets(resposta);

		// Este IF verifica se no 2º caracter da resposta termina o texto, ou  há uma quebra de linha.
		if(resposta[1] == 0 || resposta[1] == '\n') {
			// Para cada diferente valor do 1º caracter da resposta
			switch(resposta[0]) {
				case '1':
					subprograma1();
					break;
				case '2':
					subprograma2();
					break;
				case '3':
					subprograma3();
					break;
				case 'q':
				case 'Q':
					saiu_do_programa = 1;
					break;
				default:
					printf(msg_invalido, resposta);
			}
		} else
			printf(msg_invalido, resposta);

		// Espera o usuário pressionar ENTER antes de reiniciar ou fechar o aplicativo
		printf("Pressione ENTER para continuar...");
		gets(resposta);
	}

	return 1;
}
