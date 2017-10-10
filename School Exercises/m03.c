#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>
#define gets(x) fgets(x, sizeof(x), stdin)

const char limpar[] = "clear";
const char msg_invalido[] = "::: \"%s\" não é uma resposta válida!\n";
const char nomearquivo_numeros[] = "numeros.txt",
		nomearquivo_pares[] = "pares.txt",
		nomearquivo_impares[] = "impares.txt",
		nomearquivo_pessoas[] = "pessoas.dat";

void programa1();
void programa2();

typedef struct {
	char nome[30];
	int idade;
} PESSOA;

int main() {
	setlocale(LC_ALL, "Portuguese");

	char resposta[3];

	bool saiu_do_programa = 0;
	while(!saiu_do_programa) {
		system(limpar);
		printf("===[ PROBLEMA 3: Arquivos ]===\n");

		printf("Comandos disponiveis:\n\t1. Entrada de dados\n\t2. Manipulador Binário\n\tQ. Sair\nEscolha um comando [1-2,Q]:");
		gets(resposta);

		if(resposta[1] == 0 || resposta[1] == '\n') {
			switch(resposta[0]) {
				case '1':
					programa1();
					break;
				case '2':
					programa2();
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

		printf("Pressione ENTER para continuar...");
		gets(resposta);
	}

	return 1;
}

void imprimir_numeros() {
	FILE *arquivo_impares, *arquivo_pares;

	char * linha = NULL;
	size_t len = 0;
	ssize_t qtd_byteslidos;
	int num_inteiro;

	arquivo_impares = fopen(nomearquivo_impares, "r");
	arquivo_pares = fopen(nomearquivo_pares, "r");

	if(arquivo_impares == NULL && arquivo_pares == NULL) {
		printf("Arquivo de pares e impares não foram encontrados.\n");
		return;
	}

	if(arquivo_impares != NULL) {
		printf("Ímpares:\n");
		while ((qtd_byteslidos = getline(&linha, &len, arquivo_impares)) != -1) {
			if(sscanf(linha, "%d", &num_inteiro) == 1) {
				printf("\t%d\n", num_inteiro);
			}

			free(linha);
			linha = NULL;
		}
		fclose(arquivo_impares);
	}

	if(arquivo_pares != NULL) {
		printf("Pares:\n");
		while ((qtd_byteslidos = getline(&linha, &len, arquivo_pares)) != -1) {
			if(sscanf(linha, "%d", &num_inteiro) == 1) {
				printf("\t%d\n", num_inteiro);
			}

			free(linha);
			linha = NULL;
		}
		fclose(arquivo_pares);
	}

	free(linha);
}

void programa1() {
	system(limpar);
	printf("===[ PROBLEMA 3: PROGRAMA 1 ]===\n");

	FILE *arquivo_numeros, *arquivo_impares, *arquivo_pares;

	char * linha = NULL;
	size_t len = 0;
	ssize_t qtd_byteslidos;
	int num_inteiro;

	arquivo_numeros = fopen(nomearquivo_numeros, "r");

	if(arquivo_numeros == NULL) {
		printf("Arquivo \"%s\" não foi encontrado.\n", nomearquivo_numeros);
		return;
	}

	arquivo_impares = fopen(nomearquivo_impares, "w");
	arquivo_pares = fopen(nomearquivo_pares, "w");

	while ((qtd_byteslidos = getline(&linha, &len, arquivo_numeros)) != -1) {
		printf(linha);
		fflush(stdout);

		if(sscanf(linha, "%d", &num_inteiro) == 1) {
			if(num_inteiro % 2 == 0) 
				fprintf(arquivo_pares, "%d\n", num_inteiro);
			else
				fprintf(arquivo_impares, "%d\n", num_inteiro);
		}

		free(linha);
		linha = NULL;
	}

	fclose(arquivo_numeros);
	fclose(arquivo_impares);
	fclose(arquivo_pares);
	free(linha);

	printf("RESULTADOS:\n");
	imprimir_numeros();
}

void programa2_item1();
void programa2_item2();
void programa2_item3();
void programa2_item4();

void programa2() {
	setlocale(LC_ALL, "Portuguese");

	char resposta[3];

	bool saiu_do_programa = 0;
	while(!saiu_do_programa) {
		system(limpar);
		printf("===[ PROBLEMA 3: PROGRAMA 2 ]===\n");

		printf("Comandos disponiveis:\n\t1. Entrada de dados\n\t2. Todos os registros\n\t3. Maiores de 18\n\t4. Idade média\n\tQ. Voltar ao menu principal\nEscolha um comando [1-4,Q]:");
		gets(resposta);

		if(resposta[1] == 0 || resposta[1] == '\n') {
			switch(resposta[0]) {
				case '1':
					programa2_item1();
					break;
				case '2':
					programa2_item2();
					break;
				case '3':
					programa2_item3();
					break;
				case '4':
					programa2_item4();
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

		if(!saiu_do_programa){
			printf("Pressione ENTER para continuar...");
			gets(resposta);
		}
	}
}

void programa2_item1() {
	system(limpar);
	printf("===[ PROBLEMA 3: PROGRAMA 2: ITEM 1 ]===\n");

	char resposta[10];

	FILE *arquivo_pesoas;
	arquivo_pesoas = fopen("pessoas.dat", "wb+");

	bool adicionando_pessoas = true;
	while(adicionando_pessoas) {
		PESSOA nova = {"", 0};

		while(strlen(nova.nome) < 3) {
			printf("Entre com nome (min. 3 caracteres): ");
			gets(nova.nome);
		}

		while(nova.idade <= 0 || nova.idade > 200) {
			printf("Entre com a idade: ");
			gets(resposta);

			sscanf(resposta, "%d", &nova.idade);
		}

		fwrite(&nova, sizeof(PESSOA), 1, arquivo_pesoas);

		while(1) {
			printf("Adicionar outro? [S,N]: ");
			gets(resposta);

			if(resposta[1] == 0 || resposta[1] == '\n') {
				if(resposta[0] == 'S' || resposta[0] == 's') {
					break;
				} else if(resposta[0] == 'N' || resposta[0] == 'n') {
					adicionando_pessoas = false;
					break;
				}
			}

			printf(msg_invalido, resposta);
		}
	}

	fclose(arquivo_pesoas);
}

void programa2_item2() {
	system(limpar);
	printf("===[ PROBLEMA 3: PROGRAMA 2: ITEM 2 ]===\n");

	FILE *arquivo_pesoas;
	arquivo_pesoas = fopen("pessoas.dat", "rb");

	printf("CADASTROS:\n");

	PESSOA buffer;
	while(fread(&buffer, sizeof(PESSOA), 1, arquivo_pesoas) > 0) {
		printf("\t%s - %d ano(s)\n", buffer.nome, buffer.idade);
	}
}

void programa2_item3() {
	system(limpar);
	printf("===[ PROBLEMA 3: PROGRAMA 2: ITEM 3 ]===\n");

	FILE *arquivo_pesoas;
	arquivo_pesoas = fopen("pessoas.dat", "rb");

	printf("CADASTROS MAIORES DE 18:\n");

	PESSOA buffer;
	while(fread(&buffer, sizeof(PESSOA), 1, arquivo_pesoas) > 0)
		if(buffer.idade >= 18)
			printf("\t%s - %d anos\n", buffer.nome, buffer.idade);
}

void programa2_item4() {
	system(limpar);
	printf("===[ PROBLEMA 3: PROGRAMA 2: ITEM 4 ]===\n");

	FILE *arquivo_pesoas;
	arquivo_pesoas = fopen("pessoas.dat", "rb");

	PESSOA buffer;
	double idade_media = -1;
	while(fread(&buffer, sizeof(PESSOA), 1, arquivo_pesoas) > 0) {
		if(idade_media == -1)
			idade_media = buffer.idade;
		else 
			idade_media = (idade_media + buffer.idade) / 2;
	}

	printf("IDADE MÉDIA: %.2f\n", idade_media);
}