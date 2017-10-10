#include<stdio.h> //Importa as funcoes: printf, sscanf, gets
#include<stdlib.h> //Importa as funcoes: system

// Strings estáticas que vão se repetir pelo programa
const char limpar[] = "cls";
const char msg_invalido[] = "::: \"%s\" nao e uma resposta valida!\n";

// TABELA DE CARACTERES
char codex[][2] = {
	{'a', 'X'},
	{'b', 'Y'},
	{'c', 'H'},
	{'d', 'L'},
	{'e', 'F'},
	{'A', 'x'},
	{'B', 'y'},
	{'C', 'h'},
	{'D', 'l'},
	{'E', 'f'}
};

// ****************************************
// * Subprograma 1
// ****************************************

// Chamado pelo menu
void subprograma1() {
	// Buffer para o "gets"
	char resposta[60];

	// Cabeçalho no inicio do programa
	system(limpar);
	printf("===[ CARACTER CORRESPONDENTE ]===\n");

	// Variaveis
	char caracter_entrada, caracter_saida;

	// Requista o valor da extensao para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira um unico caracter: ");
		gets(resposta);

		// Processa resposta como apenas um caracter, verificando se a linha acaba no segundo
		if(resposta[1] == 0 || resposta[1] == '\n') {
			// Salva o caracter e inicialmente o poem como o de saida
			caracter_entrada = caracter_saida = resposta[0];
			// Para cada item da tabela
			int c_i;
			for(c_i = 0; c_i < sizeof(codex); c_i++) {
				// Se o caracter estiver na primeira coluna da table, sera codificado igual ao valor da segunda coluna
				if(caracter_entrada == codex[c_i][0]) {
					caracter_saida = codex[c_i][1];
					break;
				}
			}
			break;
		} else
			printf(msg_invalido, resposta);
	}

	printf("RESULTADO: codificar('%c') = '%c'\n", caracter_entrada, caracter_saida);
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
	printf("===[ CARACTER CORRESPONDENTE ]===\n");

	// Variaveis
	char caracter_entrada, caracter_saida;

	// Requista o valor da extensao para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira um unico caracter: ");
		gets(resposta);

		// Processa resposta como apenas um caracter, verificando se a linha acaba no segundo
		if(resposta[1] == 0 || resposta[1] == '\n') {
			// Salva o caracter e inicialmente o poem como o de saida
			caracter_entrada = caracter_saida = resposta[0];
			// Para cada item da tabela
			int c_i;
			for(c_i = 0; c_i < sizeof(codex); c_i++) {
				// Se o caracter estiver na segunda coluna da table, sera descodificado igual ao valor da primeira coluna
				if(caracter_entrada == codex[c_i][1]) {
					caracter_saida = codex[c_i][0];
					break;
				}
			}
			break;
		} else
			printf(msg_invalido, resposta);
	}

	printf("RESULTADO: descodificar('%c') = '%c'\n", caracter_entrada, caracter_saida);
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
	printf("===[ PROCURA ]===\n");

	// Variaveis
	char caracter;
	char frase[160];
	int busca;

	// Requista o valor da extensao para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira um unico caracter: ");
		gets(resposta);

		// Processa resposta como apenas um caracter, verificando se a linha acaba no segundo
		if(resposta[1] == 0 || resposta[1] == '\n') {
			caracter = resposta[0];
			break;
		} else
			printf(msg_invalido, resposta);
	}

	// Pergunta e captura resposta
	printf("Insira a frase: ");
	gets(frase);

	// Procura o caracter
	busca = -1;
	int c_i;
	for(c_i = 0; c_i < sizeof(frase); c_i++)
		if(caracter == frase[c_i]) {
			busca = c_i+1;
			break;
		}
	if(busca >= 0) {
		printf("O CARACTER FOI ENCONTRADO NA %dª POSICAO.\n", busca);
	} else
		printf("O CARACTER NAO FOI ENCONTRADO!\n");
}

// ****************************************
// * Subprograma 4
// ****************************************

// Chamado pelo menu
void subprograma4() {
	// Variavel da frase
	char frase[80], caracter_entrada, caracter_saida;

	// Cabeçalho no inicio do programa
	system(limpar);
	printf("===[ CODIFICA ]===\n");

	// Pergunta e captura re4sposta
	printf("Insira a frase: ");
	gets(frase);

	printf("CODIFICADO: ");
	int c_i;
	for(c_i=0; c_i < sizeof(frase); c_i++) {
		caracter_saida = caracter_entrada = frase[c_i];

		// Se a frase acabou, ou tiver uma quebra de linha, para
		if(caracter_entrada == 0 || caracter_entrada == '\n')
			break;

		// Para cada item da tabela
		int z_i;
		for(z_i = 0; z_i < sizeof(codex); z_i++) {
			// Se o caracter estiver na primeira coluna da table, sera codificado igual ao valor da segunda coluna
			if(caracter_entrada == codex[z_i][0]) {
				caracter_saida = codex[z_i][1];
				break;
			}
		}

		printf("%c", caracter_saida);
	}
	printf("\n");
}

// ****************************************
// * Subprograma 5
// ****************************************

// Chamado pelo menu
void subprograma5() {
	// Variavel da frase
	char frase[80], caracter_entrada, caracter_saida;

	// Cabeçalho no inicio do programa
	system(limpar);
	printf("===[ DESCODIFICA ]===\n");

	// Pergunta e captura resposta
	printf("Insira a frase: ");
	gets(frase);

	printf("DESCODIFICADO: ");
	int c_i;
	for(c_i=0; c_i < sizeof(frase); c_i++) {
		caracter_saida = caracter_entrada = frase[c_i];

		// Se a frase acabou, ou tiver uma quebra de linha, para
		if(caracter_entrada == 0 || caracter_entrada == '\n')
			break;

		// Para cada item da tabela
		int z_i;
		for(z_i = 0; z_i < sizeof(codex); z_i++) {
			// Se o caracter estiver na segunda coluna da table, sera codificado igual ao valor da primeira coluna
			if(caracter_entrada == codex[z_i][1]) {
				caracter_saida = codex[z_i][0];
				break;
			}
		}

		printf("%c", caracter_saida);
	}
	printf("\n");
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
		printf("===[ PROGRAMA DE CESAR ]===\n");

		// Pergunta e captura resposta
		printf("Comandos disponiveis:\n\t1. Subprograma que codifica caracter\n\t2. Subprograma que descodifica caracter\n\t3. Subprograma de procura caracter\n\t4. Subprograma que codifica frase\n\t5. Subprograma que descodifica frase\n\tQ. Sair\nEscolha um comando [1-5,Q]:");
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
				case '4':
					subprograma4();
					break;
				case '5':
					subprograma5();
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
