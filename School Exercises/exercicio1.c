#include<stdio.h> //Importa as funcoes: printf, sscanf, gets
#include<stdlib.h> //Importa as funcoes: system
#include<math.h> //Importa as funcoes: floor
#include<time.h> //Importa a estutura TIME e as funções mktime, asctime

// Strings estáticas que vão se repetir pelo programa
const char limpar[] = "cls";
const char msg_invalido[] = "::: \"%s\" nao e uma resposta valida!\n";

// ****************************************
// * Subprograma 1
// ****************************************

// Retorna o ajuste que será feito ao preço
double pegaAjuste(int parcelas) {
	if(parcelas == 1)
		return 0.9;
	else if(parcelas <= 3)
		return 1;
	else
		return 1.0175;
}

// Retorna o preço final com ajuste
double calculaPrecoTotal(double preco_inicial, double ajuste) {
	return preco_inicial * ajuste;
}

// Chamado pelo menu
void exercicio1() {
	// Buffer para o "gets"
	char resposta[60];

	// Variaveis para armazenar os precos e parcelas
	double preco_inicial = 0;
	int parcelas = 0;

	// Cabeçalho no inicio do programa
	system(limpar);
	printf("===[ CALCULADORA DE PRECO ]===\n");

	// Requista o valor inicial para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira o valor da venda sem descontos: ");
		gets(resposta);

		// Processa resposta (como um decimal) e condiciona existencia (deve ter valor maior que 0)
		if(sscanf(resposta,"%lf",&preco_inicial) == 1 && preco_inicial > 0)
			break;
		else
			printf(msg_invalido, resposta);
	}

	// Requista a quantidade de parcelas para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira a quantidade de parcelas [1-24]: ");
		gets(resposta);

		// Processa resposta (como um inteiro) e condiciona existencia (deve ter valor maior que 0 e menor/igual a 24)
		if(sscanf(resposta,"%d",&parcelas) == 1 && parcelas > 0 && parcelas <= 24)
			break;
		else
			printf(msg_invalido, resposta);
	}

	// Ajusta o juros conforme a quantidade de parcelas
	double ajuste = pegaAjuste(parcelas);

	// Calula o valor total
	double preco_final = calculaPrecoTotal(preco_inicial, ajuste);

	// Calcula o valor por parcelas
	double por_parcela = (preco_final / parcelas);

	// Exibe a resposta ao usuário
	printf("CALCULO CONCLUIDO:\n\tPreco por parcela: R$%.2lf\n\tPreco total: R$%.2lf\n\n", por_parcela, preco_final);
}

// ****************************************
// * Subprograma 2
// ****************************************

// Adiciona dias a uma data
void somaDias(int dia0, int mes0, int ano0, int dias_asomar, int *dia1, int *mes1, int *ano1) {
	// Transforma a data inicial em uma data do C
	struct tm t = {
		.tm_year=ano0-1900,
		.tm_mon=mes0-1,
		.tm_mday=dia0
	};

	// Soma a quantidade de dias
	t.tm_mday += dias_asomar;
	mktime(&t);

	// Destransforma a data do C para a data final
	*ano1 = t.tm_year+1900;
	*mes1 = t.tm_mon+1;
	*dia1 = t.tm_mday;

}

// Chamado pelo menu
void exercicio2() {
	// Buffer para o "gets"
	char resposta[60];

	// Variaveis para armazenar os dias e as datas (0 = Incial, 1 = Final)
	int dia0 = 0,
		mes0 = 0,
		ano0 = 0,
		dias_asomar = 0,
		dia1 = 0,
		mes1 = 0,
		ano1 = 0;

	// Cabeçalho no inicio do programa
	system(limpar);
	printf("===[ SOMA DATAS ]===\n");

	// Requista a data inicial para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira a data inicial [DD/MM/YYYY]: ");
		gets(resposta);

		// Processa resposta (como quatro decimais) e verifica suas validades
		if(sscanf(resposta,"%d/%d/%d",&dia0, &mes0, &ano0) == 3 &&
				dia0 > 0 && dia0 <= 31 &&
				mes0 > 0 && mes0 <= 12 &&
				ano0 >= 0
			)
			break;
		else
			printf(msg_invalido, resposta);
	}

	// Requista a quantidade de dias a somar para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira a quantidade de dias a somar: ");
		gets(resposta);

		// Processa resposta (como um inteiro) e condiciona existencia (deve ter valor maior que 0)
		if(sscanf(resposta, "%d", &dias_asomar) == 1 && dias_asomar > 0)
			break;
		else
			printf(msg_invalido, resposta);
	}

	// Faz o calculo
	somaDias(dia0, mes0, ano0, dias_asomar, &dia1, &mes1, &ano1);

	// Exibe a resposta ao usuário
	printf("CALCULO CONCLUIDO:\n\tData Final: %02d/%02d/%04d\n\n", dia1, mes1, ano1);
}

// ****************************************
// * Subprograma 3
// ****************************************

// Chamado pelo menu
void exercicio3() {
	// Buffer para o "gets"
	char resposta[60];

	// Variaveis para armazenar os precos, parcelas e a data da compra
	double preco_inicial = 0;
	int parcelas = 0;
	int compra_dia = 0,
		compra_mes = 0,
		compra_ano = 0;

	// Cabeçalho no inicio do programa
	system(limpar);
	printf("===[ PARCELAS ]===\n");

	// Requista a data inicial para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira a data da compra [DD/MM/YYYY]: ");
		gets(resposta);

		// Processa resposta (como quatro decimais) e verifica suas validades
		if(sscanf(resposta,"%d/%d/%d",&compra_dia, &compra_mes, &compra_ano) == 3 &&
				compra_dia > 0 && compra_dia <= 31 &&
				compra_mes > 0 && compra_mes <= 12 &&
				compra_ano >= 0
			)
			break;
		else
			printf(msg_invalido, resposta);
	}

	// Requista o valor inicial para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira o valor da venda sem descontos: ");
		gets(resposta);

		// Processa resposta (como um decimal) e condiciona existencia (deve ter valor maior que 0)
		if(sscanf(resposta,"%lf",&preco_inicial) == 1 && preco_inicial > 0)
			break;
		else
			printf(msg_invalido, resposta);
	}
;
	// Requista a quantidade de parcelas para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira a quantidade de parcelas [1-24]: ");
		gets(resposta);

		// Processa resposta (como um inteiro) e condiciona existencia (deve ter valor maior que 0 e menor/igual a 24)
		if(sscanf(resposta,"%d",&parcelas) == 1 && parcelas > 0 && parcelas <= 24)
			break;
		else
			printf(msg_invalido, resposta);
	}

	// Ajusta o juros conforme a quantidade de parcelas
	double ajuste = pegaAjuste(parcelas);

	// Transforma a data inicial em uma data do C
	struct tm t = {
		.tm_year=compra_ano-1900,
		.tm_mon=compra_mes-1,
		.tm_mday=compra_dia
	};

	// Calula o valor total
	double preco_final = calculaPrecoTotal(preco_inicial, ajuste);

	// Calcula o valor por parcelas
	double por_parcela = (preco_final / parcelas);

	// Exibe já o valor final e de cada parcela
	printf("RESULTADOS:\n\tPreco total: R$%.2lf\n\tPreco por parcela R$%.2lf\n", preco_final, por_parcela);

	// Para cada percela
	int parcela_i;
	for(parcela_i=1; parcela_i <= parcelas; parcela_i++) {
		// Acrescenta 1 mês na data de validade
		t.tm_mon += 1;
		mktime(&t);

		// Destransforma a data do C para a data final
		int ano1 = t.tm_year+1900,
			mes1 = t.tm_mon+1,
			dia1 = t.tm_mday;

		// Exibe a resposta ao usuário
		printf("\tData da parcela %d: %02d/%02d/%04d\n", parcela_i, dia1, mes1, ano1);
	}
}

// ****************************************
// * Subprograma 4
// ****************************************

// Chamado pelo menu
void exercicio4() {
	// Buffer para o "gets"
	char resposta[60];

	// Variaveis para armazenar os dias e as datas (0 = Incial, 1 = Final)
	int dia0 = 0,
		mes0 = 0,
		ano0 = 0,
		dia1 = 0,
		mes1 = 0,
		ano1 = 0;

	// Cabeçalho no inicio do programa
	system(limpar);
	printf("===[ VALIDA DATA ]===\n");

	// Requista a data inicial para o usuario
	while(1) {
		// Pergunta e captura resposta
		printf("Insira a data inicial [DD/MM/YYYY]: ");
		gets(resposta);

		// Processa resposta (como quatro decimais) e verifica suas validades
		if(sscanf(resposta,"%d/%d/%d",&dia0, &mes0, &ano0) == 3 &&
				dia0 > 0 && dia0 <= 31 &&
				mes0 > 0 && mes0 <= 12 &&
				ano0 >= 0
			)
			break;
		else
			printf(msg_invalido, resposta);
	}

	// Transforma a data inicial em uma data do C
	struct tm t = {
		.tm_year=ano0-1900,
		.tm_mon=mes0-1,
		.tm_mday=dia0
	};

	// Deixa a biblioteca corrigir a data
	mktime(&t);

	// Destransforma a data do C para a data final
	ano1 = t.tm_year+1900;
	mes1 = t.tm_mon+1;
	dia1 = t.tm_mday;

	// Exibe a resposta ao usuário
	printf("RESULTADO:\n\t");
	if(ano0 == ano1 && mes1 == mes0 && dia0 == dia1)
		printf("A data inserida EXISTE no calendario!\n");
	else
		printf("A data inserida NAO EXISTE no calendario!\n");
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
		printf("===[ PROGRAMA DE JUROS ]===\n");

		// Pergunta e captura resposta
		printf("Comandos disponiveis:\n\t1. Subprograma de calculo de precos\n\t2. Subprograma de somar dias\n\t3. Subprograma de previsao de parcelas\n\t4. Subprogram de validas datas\n\tQ. Sair\nEscolha um comando [1-4,Q]:");
		gets(resposta);

		// Este IF verifica se no 2º caracter da resposta termina o texto, ou  há uma quebra de linha.
		if(resposta[1] == 0 || resposta[1] == '\n') {
			// Para cada diferente valor do 1º caracter da resposta
			switch(resposta[0]) {
				case '1':
					exercicio1();
					break;
				case '2':
					exercicio2();
					break;
				case '3':
					exercicio3();
					break;
				case '4':
					exercicio4();
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
