//****Inicío do arquivo: a soma b.cpp
//****Ultima Modificação: 1/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
main(){ //função principal
       int A, B, R; //declara as variáveis como inteiros: A, B, R;
       
       printf("Digite um valor: "); //exibe uma mensagem na tela
       scanf("%i", &A); //captura a variável A
       printf("Digite outro valor: "); //exibe uma mensagem na tela
       scanf("%i", &B); //captura a variável B
       
       R = (A + B); //soma e grava o resultado em R
       
       printf("O resultado foi: %i\n", R); //exibe uma mensagem na tela
       
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//****Inicío do arquivo: boletim.cpp
//****Ultima Modificação: 15/4/2011
//==============================================================================
//++Boletim
//Programa: Boletim
//Autor: PedroHLC::InfoTec
//Data: 12-04-11 16:30
//==============================================================================
//++Descrição
//Desenvolva um programa em linguagem C\C++ que leia os valores de quatro notas
//escolares, o nome do aluno, o seu numero de chamada.
//O programa deve calcular a média aritmédica;mostrar a mensagem "Reprovado" se
//for menor que 5; aprensenta a mensagem "Recuperação" caso a média seja menor
//que 7 e maior que 5; aprensentara mensagem "Aprovado" caso a média seja maior
//que 7.
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//-----------------------------------------------------------------------------
//Declara utilidades
    using namespace std; //corrige a captura de espaços
//Declara variaveis globais
    float notas[3], media, total=0; //declara as variáveis como reais: notas[3], media, total=0;
    int aluno_id, faltas; //declara as variáveis como inteiros: aluno_id, faltas;
    char choose; //declara as variáveis como texto: choose;
    char nome[255]; //declara as variáveis como texto: nome[255];
//-----------------------------------------------------------------------------
//Função: getsf(char[255])
char* getsf(char x[255]){
    fflush(stdin); //limpa a entrada
    return(gets(x)); //captura um texto
}
//-----------------------------------------------------------------------------
//Função: boletim()
void boletim(){
    //Cabeçalho
    printf("\t*\tBoletim\t*\n\n"); //exibe uma mensagem na tela
    //Lê os valores
    printf("Digite o seu nome: "); //exibe uma mensagem na tela
    getsf(nome); //captura texto para a variável nome);
    printf("Digite o seu n\243mero: "); //exibe uma mensagem na tela
    scanf("%i", &aluno_id); //captura a variável aluno_id
    printf("Digite o n\243mero de faltas: "); //exibe uma mensagem na tela
    scanf("%i", &faltas); //captura a variável faltas
    //Limpa o cache da variavel total
    total = 0;
    //Lê os valores em grande escala
    for(int i=0; i < 4; i++){
       printf("Digite a %i\246 nota: ", (i + 1)); //exibe uma mensagem na tela
       scanf("%f", &notas[i]); //captura a variável notas[i]
       total += notas[i]; //Acresenta essa nota para depois calcular a média
    }
    //Calcula a média
    media = total / 4;
    //Quebra linha
    puts("\0");
    //Exibe as informações coletadas
    printf("Nome: %s\n", nome); //exibe uma mensagem na tela
    printf("N\243mero: %i\n", aluno_id); //exibe uma mensagem na tela
    printf("M\202dia: %.2f\n", media); //exibe uma mensagem na tela
    //Exibe o estado do aluno
    printf("Situa\207\306o: "); //exibe uma mensagem na tela
    if(faltas >= 15) printf("Reprovado por faltas!\n"); //exibe uma mensagem na tela
    else if(media < 5) printf("Reprovado\n"); //exibe uma mensagem na tela
    else if(media >= 5 & media < 7) printf("Recupera\207\306o\n"); //exibe uma mensagem na tela
    else if(media >= 7) printf("Aprovado\n"); //exibe uma mensagem na tela
}
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
    system("cls");
    //Persoanliza a Janela
    system("color f9");
    system("title Boletim");
    //Roda o programa
    while(true){
         //Limpa a tela, caso o programa esteja retornando o loop
         system("cls");
         //Executa o comando principal
         boletim();
         //Quebra linha
         puts("\0");
         //Pergunta se o usuario quer fazer novamente.
         printf("Gostaria de calcular outra vez?(s/n): "); //exibe uma mensagem na tela
         scanf("%s", &choose); //captura a variável choose
         //Se o usuario não quiser, não repete
         if(choose == 'n' or choose == 'N') break;
    }
    //ESPERA O USUARIO FECHAR O PROGRAMA
    printf("Pressione qualquer tecla para continuar..."); //exibe uma mensagem na tela
    getch(); //espera o usuario pressionar ENTER
    //Limpa a tela e retorna a cor original, caso o programa voltará ao DOS
    system("cls");
    system("color 0F");
    //Retorna sucessivamente
    return(0);
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//****Inicío do arquivo: c para f e k.cpp
//****Ultima Modificação: 4/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB

main(){ //função principal
    float f, c, k; //declara as variáveis como reais: f, c, k;
    while(true){
                printf("Digite a temperatura em ºC: "); //exibe uma mensagem na tela
                scanf("%f", &c); //captura a variável c
                
                f = (9 * c + 160) / 5; //calcula em fahrenheit
                k = c + 273; //calcula em kelvin
                
                printf("Temperatura em ºF: %f\n", f); //exibe uma mensagem na tela
                printf("Temperatura em K: %f\n", k); //exibe uma mensagem na tela
                
                getch(); //espera o usuario pressionar ENTER
                system("cls"); //limpa a tela
    }
    return 0;
}
//****Fim do arquivo

//****Inicío do arquivo: diferenca quadrada.cpp
//****Ultima Modificação: 1/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
main(){ //função principal
       int A, B, R; //declara as variáveis como inteiros: A, B, R;
       
       printf("Digite um valor: "); //exibe uma mensagem na tela
       scanf("%i", &A); //captura a variável A
       printf("Digite outro valor: "); //exibe uma mensagem na tela
       scanf("%i", &B); //captura a variável B
       
       R = (A - B) * (A - B); //calcula primeiro a diferençã e depois o quadrado
       
       printf("O resultado foi: %i\n", R); //exibe uma mensagem na tela
       
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//****Inicío do arquivo: eleicao.cpp
//****Ultima Modificação: 22/3/2011
/*
Em uma eleição sindical concorreram ao cargo de presidente tres candidatos (Tíririca, Romário, Vampeta).
Durante a apuração dos votos nulos e votos em branco, alem dos votos validos para cada canditato.
Deve ser criado um progrma de computadores que faça a leitura da quantidade de votos nulos e votos em branco.
Ao final o programa desse aprensentar o número total de eleitore, considerando votos válidos emrelação à a quantidade de eleitores,
o porcentual correspondente de votos váludos o candidato.
A relação à quantidade de eleitores o porcentual corresponde de votos nulos em relação A quantidade de elitores,
e por ultimo o porcentual correspondente de votos em relação a quantidade de eleitores.
*/

#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
main(){ //função principal
       system("title Eleição");
       float total_eleitores, tiririca, romario, vampeta, brancos, nulos, total, total_validos; //declara as variáveis como reais: total_eleitores, tiririca, romario, vampeta, brancos, nulos, total, total_validos;
       float perc_validos, perc_tiririca, perc_romario, perc_vampeta, perc_brancos, perc_nulos; //declara as variáveis como reais: perc_validos, perc_tiririca, perc_romario, perc_vampeta, perc_brancos, perc_nulos;
       printf("Eleitores: "); //exibe uma mensagem na tela
       scanf("%f", &total_eleitores); //captura a variável total_eleitores
       printf("Tiririca: "); //exibe uma mensagem na tela
       scanf("%f", &tiririca); //captura a variável tiririca
       printf("Romario: "); //exibe uma mensagem na tela
       scanf("%f", &romario); //captura a variável romario
       printf("Vampeta: "); //exibe uma mensagem na tela
       scanf("%f", &vampeta); //captura a variável vampeta
       printf("Brancos: "); //exibe uma mensagem na tela
       scanf("%f", &brancos); //captura a variável brancos
       printf("Nulos: "); //exibe uma mensagem na tela
       scanf("%f", &nulos); //captura a variável nulos
       total_validos = tiririca + romario + vampeta; //calcula a quantidade de votos valido
       total = total_validos + brancos + nulos; //calcula a quantidade total de votos
       system("cls"); //limpa a tela
       //outros calculos
       perc_validos = total_validos / total_eleitores;
       perc_tiririca = tiririca / total;
       perc_romario = romario / total;
       perc_vampeta = vampeta / total;
       perc_brancos = brancos / total;
       perc_nulos = nulos / total;
       printf("Total:\t\t%0.f\n", total); //exibe uma mensagem na tela
       printf("Total Validos:\t%0.f\n", total_validos); //exibe uma mensagem na tela
       printf("Validos:\t%2.f\n", perc_validos * 100); //exibe uma mensagem na tela
       printf("Tirica:\t\t%2.f\n", perc_tiririca * 100); //exibe uma mensagem na tela
       printf("Romario:\t%2.f\n", perc_romario * 100); //exibe uma mensagem na tela
       printf("Vampeta:\t%2.f\n", perc_vampeta * 100); //exibe uma mensagem na tela
       printf("Brancos:\t%2.f\n", perc_brancos * 100); //exibe uma mensagem na tela
       printf("Nulos:\t\t%2.f\n", perc_nulos * 100); //exibe uma mensagem na tela
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//****Inicío do arquivo: f para c e k.cpp
//****Ultima Modificação: 4/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB

main(){ //função principal
    float f, c, k; //declara as variáveis como reais: f, c, k;
    while(true){
                printf("Digite a temperatura em ºF: "); //exibe uma mensagem na tela
                scanf("%f", &f); //captura a variável f
                
                c = (f - 32) / 9 * 5; //calcula em celsius
                k = c + 273; //calcula em kelvins
                
                printf("Temperatura em ºC: %f\n", c); //exibe uma mensagem na tela
                printf("Temperatura em K: %f\n", k); //exibe uma mensagem na tela
                
                getch(); //espera o usuario pressionar ENTER
                system("cls"); //limpa a tela
    }
    return 0;
}
//****Fim do arquivo

//****Inicío do arquivo: ilustríssimo.cpp
//****Ultima Modificação: 15/4/2011
//==============================================================================
//++Ilustríssimo
//Programa: Ilustríssimo
//Autor: PedroHLC::InfoTec
//Data: 13-04-11 16:20
//==============================================================================
//++Descrição
//Desenvolva um programa em linguagem C\C++ que leia o nome, de uma pessoa e
//apresente como a saída a seguintes mensagens:
//"Ilustríssimo Sr.", caso seja uma pessoa de sexo masculino, ou "Ilustríssima
// Sra.", caso seja uma pessoa do sexo feminino.
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
#include <string.h> //inclui a biblioteca STRING
//-----------------------------------------------------------------------------
//Declara utilidades
    using namespace std;
//Declara variaveis globais
    int name_size, sexo; //declara as variáveis como inteiros: name_size, sexo;
    char choose, nome[255], sobrenome[255], nome_fc, sexoc; //declara as variáveis como texto: choose, nome[255], sobrenome[255], nome_fc, sexoc;
//-----------------------------------------------------------------------------
//Função: getsf(char[255])
char* getsf(char x[255]){
    fflush(stdin); //limpa a entrada
    return(gets(x)); //captura um texto
}
//-----------------------------------------------------------------------------
//Função: ilustrissimo()
void ilustrissimo(){
    //Cabeçalho
    printf("\t*\tBoletim\t*\n\n"); //exibe uma mensagem na tela
    //Lê os valores
    printf("Digite o seu PRIMEIRO nome: "); //exibe uma mensagem na tela
    getsf(nome); //captura texto para a variável nome);
    printf("Digite o seu SOBREnome: "); //exibe uma mensagem na tela
    getsf(sobrenome); //captura texto para a variável sobrenome);
    //Quebra linha
    puts("\0");
    //Descobre a ultima letra do primeiro nome
    name_size = strlen(nome);
    nome_fc = nome[name_size - 1];
    //Mostra o resultado do calculo acima
    printf("Informa\207\344es sobre seu primeiro nome:\n"); //exibe uma mensagem na tela
    printf("N\243mero de letras: %i\n", name_size); //exibe uma mensagem na tela
    printf("\353ltima letra: '%c'\n", nome_fc); //exibe uma mensagem na tela
    //Calcula o sexo
    if(nome_fc == 'o' or nome_fc == 'O') sexo = 0;
    else if(nome_fc == 'a' or nome_fc == 'A') sexo = 1;
    else{
         printf("Digite seu sexo(M/F): "); //exibe uma mensagem na tela
         scanf("%s", &sexoc); //captura a variável sexoc
         if(sexoc == 'm' or sexoc == 'M') sexo = 0;
         else sexo = 1;
    }
    //Mostra o resultado do calculo acima
    printf("Seu sexo: "); //exibe uma mensagem na tela
    if(sexo == 1) printf("Feminino\n"); //exibe uma mensagem na tela
    else printf("Masculino\n"); //exibe uma mensagem na tela
    //Quebra linha
    puts("\0");
    //Mostra o sexo
    if(sexo == 1) printf("Obrigado Ilustr\241ssimo Sra. %s %s\n", nome, sobrenome); //exibe uma mensagem na tela
    else printf("Obrigado Ilustr\241ssimo Sr. %s %s\n", nome, sobrenome); //exibe uma mensagem na tela
}
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
    system("cls");
    //Persoanliza a Janela
    system("color f9");
    system("title Ilustríssimo");
    //Roda o programa
    while(true){
         //Limpa a tela, caso o programa esteja retornando o loop
         system("cls");
         //Executa o comando principal
         ilustrissimo();
         //Quebra linha
         puts("\0");
         //Pergunta se o usuario quer fazer novamente.
         printf("Gostaria de calcular outra vez?(s/n): "); //exibe uma mensagem na tela
         scanf("%s", &choose); //captura a variável choose
         //Se o usuario não quiser, não repete
         if(choose == 'n' or choose == 'N') break;
    }
    //ESPERA O USUARIO FECHAR O PROGRAMA
    printf("Pressione qualquer tecla para continuar..."); //exibe uma mensagem na tela
    getch(); //espera o usuario pressionar ENTER
    //Limpa a tela, caso o programa voltará ao DOS
    system("cls");
    system("color 0F");
    //Retorna sucessivamente
    return(0);
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//****Inicío do arquivo: imc.cpp
//****Ultima Modificação: 6/4/2011
//==============================================================================
//++Cabeçalho
//Programa: IMC - Índice de massa corporal
//Autor: PedroHLC::InfoTec
//Data: 09-04-11 16:10
//==============================================================================
//++Descrição
//O que é IMC?
//Qual a fórmula do IMC?
//Qual a faixa de classificação do IMC?
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//-----------------------------------------------------------------------------
using namespace std; //corrige a captura de espaços
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS ou esteja retornando
    system("cls");
    //Declara
    float altura, alturavc, massa, imc, pesoi; //declara as variáveis como reais: altura, alturavc, massa, imc, pesoi;
    int sexok; //declara as variáveis como inteiros: sexok;
    char choose, csexo; //declara as variáveis como texto: choose, csexo;
    //Persoanliza a Janela
    system("color f9");
    system("title IMC");
    //Cabeçalho
    printf("\t*\tIMC\t*\n\n"); //exibe uma mensagem na tela
    //Lê os valores
    printf("Digite o sexo(m,f): "); //exibe uma mensagem na tela
    scanf("%s", &csexo); //captura a variável csexo
    printf("\n"); //exibe uma mensagem na tela
    printf("Digite a altura: "); //exibe uma mensagem na tela
    scanf("%f", &altura); //captura a variável altura
    printf("Digite a massa:\t "); //exibe uma mensagem na tela
    scanf("%f", &massa); //captura a variável massa
    //Transforma o sexo de char para K
    if(csexo == 'm'){ //se (CSEXO == 'M')
          sexok = 4; 
    }else{
          sexok = 2;
    }
    //Calcula e mostra o IMC
    imc = massa / (altura * altura);
    printf("IMC:\t\t %.2f\n", imc); //exibe uma mensagem na tela
    //Calcula e mostra o peso ideal
    alturavc = (altura * 100);
    pesoi = alturavc - 100 - ((alturavc - 150) / sexok);
    printf("Peso Ideal:\t %.2f\n", pesoi); //exibe uma mensagem na tela
    //Mostra a classificação
    if(imc < 18.5){ //se (IMC < 18.5)
           printf("Classifica\207\306o:\t Magreza\n"); //exibe uma mensagem na tela
    }else if(imc >= 18.5 & imc < 25){ //se (IMC >= 18.5 & IMC < 25)
           printf("Classifica\207\306o:\t Saud%cvel\n"); //exibe uma mensagem na tela
    }else if(imc >= 25 & imc < 30){ //se (IMC >= 25 & IMC < 30)
           printf("Classifica\207\306o:\t Sobrepeso\n"); //exibe uma mensagem na tela
    }else if(imc >= 30 & imc < 35){ //se (IMC >= 30 & IMC < 35)
           printf("Classifica\207\306o:\t Obesidade Grau 1\n"); //exibe uma mensagem na tela
    }else if(imc >= 35 & imc < 40){ //se (IMC >= 35 & IMC < 40)
           printf("Classifica\207\306o:\t Obesidade Grau 2 (severa)\n"); //exibe uma mensagem na tela
    }else if(imc >= 40){ //se (IMC >= 40)
           printf("Classifica\207\306o:\t Obesidade Grau 3 (m\340rbida)\n"); //exibe uma mensagem na tela
    }
    //Pergunta se o usuario quer fazer novamente.
    printf("\n\nGostaria de calcular outra vez?(s/n): "); //exibe uma mensagem na tela
    scanf("%s", &choose); //captura a variável choose
    if(choose == 's'){ //se (CHOOSE == 'S')
           main(); //função principal
    }else{
          //ESPERA O USUARIO FECHAR O PROGRAMA
          printf("Pressione qualquer tecla para continuar..."); //exibe uma mensagem na tela
          getch(); //espera o usuario pressionar ENTER
          //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
          system("cls");
          system("color 0F");
    }
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//****Inicío do arquivo: imc2.cpp
//****Ultima Modificação: 6/4/2011
//==============================================================================
//++Cabeçalho
//Programa: IMC - Índice de massa corporal
//Autor: PedroHLC::InfoTec
//Data: 09-04-11 17:20
//==============================================================================
//++Descrição
//O que é IMC?
//Qual a fórmula do IMC?
//Qual a faixa de classificação do IMC?
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//-----------------------------------------------------------------------------
//Declara utilidades
    using namespace std;
//Declara variaveis globais
    float altura, alturavc, massa, imc, pesoi; //declara as variáveis como reais: altura, alturavc, massa, imc, pesoi;
    int sexok; //declara as variáveis como inteiros: sexok;
    char choose, csexo; //declara as variáveis como texto: choose, csexo;
    char nome[255]; //declara as variáveis como texto: nome[255];
//-----------------------------------------------------------------------------
//Função: calc_imc()
void calc_imc(){
    //Cabeçalho
    printf("\t*\tIMC\t*\n\n"); //exibe uma mensagem na tela
    //Lê os valores
    printf("Digite o seu nome: "); //exibe uma mensagem na tela
    gets(nome);
    printf("Digite o sexo(m,f): "); //exibe uma mensagem na tela
    scanf("%s", &csexo); //captura a variável csexo
    printf("\n"); //exibe uma mensagem na tela
    printf("Digite a altura: "); //exibe uma mensagem na tela
    scanf("%f", &altura); //captura a variável altura
    printf("Digite a massa:\t "); //exibe uma mensagem na tela
    scanf("%f", &massa); //captura a variável massa
    //Transforma o sexo de char para K
    if(csexo == 'm'){ //se (CSEXO == 'M')
          sexok = 4; 
    }else{
          sexok = 2;
    }
    //Calcula e mostra o IMC
    imc = massa / (altura * altura);
    printf("IMC:\t\t %.2f\n", imc); //exibe uma mensagem na tela
    //Calcula e mostra o peso ideal
    alturavc = (altura * 100);
    pesoi = alturavc - 100 - ((alturavc - 150) / sexok);
    printf("Peso Ideal:\t %.2f\n", pesoi); //exibe uma mensagem na tela
    //Mostra a classificação
    if(imc < 18.5){ //se (IMC < 18.5)
           printf("Classifica\207\306o:\t Magreza\n"); //exibe uma mensagem na tela
    }else if(imc >= 18.5 & imc < 25){ //se (IMC >= 18.5 & IMC < 25)
           printf("Classifica\207\306o:\t Saud%cvel\n"); //exibe uma mensagem na tela
    }else if(imc >= 25 & imc < 30){ //se (IMC >= 25 & IMC < 30)
           printf("Classifica\207\306o:\t Sobrepeso\n"); //exibe uma mensagem na tela
    }else if(imc >= 30 & imc < 35){ //se (IMC >= 30 & IMC < 35)
           printf("Classifica\207\306o:\t Obesidade Grau 1\n"); //exibe uma mensagem na tela
    }else if(imc >= 35 & imc < 40){ //se (IMC >= 35 & IMC < 40)
           printf("Classifica\207\306o:\t Obesidade Grau 2 (severa)\n"); //exibe uma mensagem na tela
    }else if(imc >= 40){ //se (IMC >= 40)
           printf("Classifica\207\306o:\t Obesidade Grau 3 (m\340rbida)\n"); //exibe uma mensagem na tela
    }
}
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
    system("cls");
    //Persoanliza a Janela
    system("color f9");
    system("title IMC");
    //Roda o programa
    while(true){
         //Limpa a tela, caso o programa esteja retornando o loop
         system("cls");
         //Executa o comando principal
         calc_imc();
         //Pergunta se o usuario quer fazer novamente.
         printf("\n\nGostaria de calcular outra vez?(s/n): "); //exibe uma mensagem na tela
         scanf("%s", &choose); //captura a variável choose
         //Se o usuario não quiser, não repete
         if(choose == 'n' or choose == 'N') break;
    }
    //ESPERA O USUARIO FECHAR O PROGRAMA
    printf("Pressione qualquer tecla para continuar..."); //exibe uma mensagem na tela
    getch(); //espera o usuario pressionar ENTER
    //Limpa a tela, caso o programa voltará ao DOS
    system("cls");
    system("color 0F");
    //Retorna sucessivamente
    return(0);
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//****Inicío do arquivo: prestacao.cpp
//****Ultima Modificação: 21/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB

main(){ //função principal
       float valor, tempo, prestacao, taxa; //declara as variáveis como reais: valor, tempo, prestacao, taxa;
       printf("Digite o preco: R$"); //exibe uma mensagem na tela
       scanf("%f", &valor); //captura a variável valor
       printf("Digite o tempo : "); //exibe uma mensagem na tela
       scanf("%f", &tempo); //captura a variável tempo
       printf("Digite a taxa : "); //exibe uma mensagem na tela
       scanf("%f", &taxa); //captura a variável taxa
       
       prestacao = valor + (valor * (taxa / 100) * tempo); //calcula valor da prestação
       
       printf("\t Valor da Prestacao: R$%.2f\n", prestacao); //exibe uma mensagem na tela
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//****Inicío do arquivo: primeiro programa.cpp
//****Ultima Modificação: 1/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
main(){ //função principal
    printf("Esse e o meu primeiro programa!\n"); //exibe uma mensagem na tela
    getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//****Inicío do arquivo: primeirose.cpp
//****Ultima Modificação: 29/3/2011
/*
================================================================================
++Cabeçalho
Programa: Soma Valores
Autor: PedroHLC::InfoTec
Data: 29-03-11 17:50
================================================================================
++Descrição
Desenvolva um diagrama de blocos e portugol de um programa que leia dois valores
numéricos e só apresente o resultado caso o valor somado seja maior que 10.
================================================================================
*/
//------------------------------------------------------------------------------
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//------------------------------------------------------------------------------
main(){ //função principal
    //Declara
    int valor1, valor2, R; //declara as variáveis como inteiros: valor1, valor2, R;
    //Persoanliza a Janela
    system("color f9");
    system("title Soma Valores");
    //Cabeçalho
    printf("\t*\tMEDIA ESCOLAR\t*\n\n"); //exibe uma mensagem na tela
    //Lê os valores
    printf("Digite o primeiro valor: "); //exibe uma mensagem na tela
    scanf("%i", &valor1); //captura a variável valor1
    printf("Digite o segundo valor: "); //exibe uma mensagem na tela
    scanf("%i", &valor2); //captura a variável valor2
    //Calcula a Soma
    R = valor1 + valor2;
    //SE(R>=10) ENTÃO MOSTRA(R)
    if(R >= 10){ //se (R >= 10)
         printf("Resultado de %i + %i = %i\n", valor1, valor2, R); //exibe uma mensagem na tela
    }else{
          printf("Resultado: JEGUE \245 SABE SOMAR ISSO?!!!\n"); //exibe uma mensagem na tela
    }
    //ESPERA O USUARIO FECHAR O PROGRAMA
    printf("Pressione qualquer tecla para continuar..."); //exibe uma mensagem na tela
    getch(); //espera o usuario pressionar ENTER
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//****Inicío do arquivo: quadro de 3.cpp
//****Ultima Modificação: 21/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB

main(){ //função principal
       int A, B, C, R; //declara as variáveis como inteiros: A, B, C, R;
       
       printf("Digite um valor: "); //exibe uma mensagem na tela
       scanf("%i", &A); //captura a variável A
       printf("Digite outro valor: "); //exibe uma mensagem na tela
       scanf("%i", &B); //captura a variável B
       printf("Digite mais uma vez outro valor: "); //exibe uma mensagem na tela
       scanf("%i", &C); //captura a variável C
       
       R = (A * A) + (B * B) + (C * C); //calcura o quadrado dos 3 valores e soma
       
       printf("O resultado foi: %i\n", R); //exibe uma mensagem na tela
       
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//****Inicío do arquivo: quadro dos 3.cpp
//****Ultima Modificação: 21/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB

main(){ //função principal
       int A, B, C, R; //declara as variáveis como inteiros: A, B, C, R;
       
       printf("Digite um valor: "); //exibe uma mensagem na tela
       scanf("%i", &A); //captura a variável A
       printf("Digite outro valor: "); //exibe uma mensagem na tela
       scanf("%i", &B); //captura a variável B
       printf("Digite mais uma vez outro valor: "); //exibe uma mensagem na tela
       scanf("%i", &C); //captura a variável C
       
       R = (A + B + C); //soma os 3 valores
       
       printf("O resultado foi: %i\n", (R * R)); //exibe uma mensagem na tela
       
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//****Inicío do arquivo: r para us.cpp
//****Ultima Modificação: 21/3/2011
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO

main(){ //função principal
       // Declara
       float dollar, real, cotacao; //declara as variáveis como reais: dollar, real, cotacao;
       int choosed; //declara as variáveis como inteiros: choosed;
       // Titula
       system("title U$ para R$");
       // ...
       printf("Digite o valor a cotacao u$ para R$: "); //exibe uma mensagem na tela
       scanf("%f", &cotacao); //captura a variável cotacao
       
       printf("Digite o valor em Real: R$"); //exibe uma mensagem na tela
       scanf("%f", &real); //captura a variável real
       
       dollar = real / cotacao; //calcular o valor do dollar
       
       printf("\t Valor em Dollars: U$%.2f\n", dollar); //exibe uma mensagem na tela
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//****Inicío do arquivo: salario.cpp
//****Ultima Modificação: 4/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB

main(){ //função principal
    int r, vh, ht; //declara as variáveis como inteiros: r, vh, ht;
    while(true){
                printf("Digite o valor da hora: "); //exibe uma mensagem na tela
                scanf("%i", &vh); //captura a variável vh
                printf("Digite a quantidade de horas: "); //exibe uma mensagem na tela
                scanf("%i", &ht); //captura a variável ht
                
                r = (vh * ht); //calcula o salario bruto
                
                printf("Salario bruto: %i\n", r); //exibe uma mensagem na tela
                
                getch(); //espera o usuario pressionar ENTER
                system("cls"); //limpa a tela
    }
    return 0;
}
//****Fim do arquivo

//****Inicío do arquivo: segundose.cpp
//****Ultima Modificação: 1/4/2011
/*
================================================================================
++Cabeçalho
Programa: Média Escolar
Autor: PedroHLC::InfoTec
Data: 29-03-11 18:20
================================================================================
++Descrição
Desenvolva um programa quue apresente a Média Escolar de um aluno.
O Programa deve pedir para o usuário difitar três notas, em seguida o programa
deve calcular a média na tela em seguida ele também deve verificiar se a média
é menor que 7, caso isso seja verdade, o programa deve mostrar a mensagem
"REPROVADO" automaticamente
Atenção: A mensagem deve ser exivida, caso a média for menor que 7.
================================================================================
*/
//------------------------------------------------------------------------------
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS ou esteja retornando
    system("cls");
    //Declara
    float nota1, nota2, nota3, media; //declara as variáveis como reais: nota1, nota2, nota3, media;
    char choose; //declara as variáveis como texto: choose;
    //Persoanliza a Janela
    system("color f9");
    system("title Média Escolar");
    //Cabeçalho
    printf("\t*\tMEDIA ESCOLAR\t*\n\n"); //exibe uma mensagem na tela
    //Lê os valores
    printf("Digite a primeira nota: "); //exibe uma mensagem na tela
    scanf("%f", &nota1); //captura a variável nota1
    printf("Digite o segunda nota: "); //exibe uma mensagem na tela
    scanf("%f", &nota2); //captura a variável nota2
    printf("Digite a tereira nota: "); //exibe uma mensagem na tela
    scanf("%f", &nota3); //captura a variável nota3
    //Calcula a Média
    media = ((nota1 + nota2 + nota3) / 3);
    //SE(MEDIA<7) ENTÃO MOSTRA("REPROVADO")
    if(media < 7.0){ //se (MEDIA < 7.0)
         printf("REPROVADO\n"); //exibe uma mensagem na tela
    }else{
         printf("Aprovado com media: %.2f\n", media); //exibe uma mensagem na tela
    }
    //Pergunta se o usuario quer fazer novamente.
    printf("Deseja calcular outra media?(s/n)"); //exibe uma mensagem na tela
    scanf("%s", &choose); //captura a variável choose
    if(choose == 's'){ //se (CHOOSE == 'S')
           main(); //função principal
    }else{
          //ESPERA O USUARIO FECHAR O PROGRAMA
          printf("Pressione qualquer tecla para continuar..."); //exibe uma mensagem na tela
          getch(); //espera o usuario pressionar ENTER
          //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
          system("cls");
          system("color 0F");
    }
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//****Inicío do arquivo: tabuada.cpp
//****Ultima Modificação: 15/4/2011
//==============================================================================
//++Tabuada
//Programa: Tabuada
//Autor: PedroHLC::InfoTec
//Data: 13-04-11 17:10
//==============================================================================
//++Descrição
//Desenvolva um programa em linguagem C\C++ que mostre a tabuada
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//-----------------------------------------------------------------------------
//Declara variaveis globais
    int x, y; //declara as variáveis como inteiros: x, y;
    char choose; //declara as variáveis como texto: choose;
//-----------------------------------------------------------------------------
//Função: tabuada()
void tabuada(){
    printf("Digite o valor da primeira variavel: "); //exibe uma mensagem na tela
    scanf("%i", &x); //captura a variável x
    printf("Digite o valor máximo do multiplicando: "); //exibe uma mensagem na tela
    scanf("%i", &y); //captura a variável y
    for(int i=0; i <= y; i++) printf("%i * %i = %i\n", x, i, (x*i)); //exibe uma mensagem na tela
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
    system("cls");
    //Persoanliza a Janela
    system("color f9");
    system("title Tabuada");
    //Roda o programa
    while(true){
         //Limpa a tela, caso o programa esteja retornando o loop
         system("cls");
         tabuada();
         //Quebra linha
         puts("\0");
         //Pergunta se o usuario quer fazer novamente.
         printf("Gostaria de calcular outra vez?(s/n): "); //exibe uma mensagem na tela
         scanf("%s", &choose); //captura a variável choose
         //Se o usuario não quiser, não repete
         if(choose == 'n' or choose == 'N') break;
    }
    //ESPERA O USUARIO FECHAR O PROGRAMA
    printf("Pressione qualquer tecla para continuar..."); //exibe uma mensagem na tela
    getch(); //espera o usuario pressionar ENTER
    //Limpa a tela, caso o programa voltará ao DOS
    system("cls");
    system("color 0F");
    //Retorna sucessivamente
    return(0);
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//****Inicío do arquivo: tereceitose.cpp
//****Ultima Modificação: 15/4/2011
/*
================================================================================
++Cabeçalho
Programa: Crescente
Autor: PedroHLC::InfoTec
Data: 30-03-11 17:15
================================================================================
++Descrição
Desenvolva um programa em C, que leia dois valores inteiros digitados pelo
usuario. O programa deve exibir na tela os valores que foram digitados em
ordem crescente.
================================================================================
*/
//------------------------------------------------------------------------------
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS ou esteja retornando
    system("cls");
    //Declara
    int valor1, valor2; //declara as variáveis como inteiros: valor1, valor2;
    char choose; //declara as variáveis como texto: choose;
    //Personaliza a Janela
    system("color f9");
    system("title Crescente");
    //Cabeçalho
    printf("\t*\tCRESCENTE\t*\n\n"); //exibe uma mensagem na tela
    //Lê os valores
    printf("Digite o primeiro valor: "); //exibe uma mensagem na tela
    scanf("%i", &valor1); //captura a variável valor1
    printf("Digite o segundo valor: "); //exibe uma mensagem na tela
    scanf("%i", &valor2); //captura a variável valor2
    //SE(VALOR1 > VALOR2) ENTÃO MOSTRA(VALOR1 e 2)
    if(valor1 < valor2){ //se (VALOR1 < VALOR2)
         printf("%i\n", valor1); //exibe uma mensagem na tela
         printf("%i\n", valor2); //exibe uma mensagem na tela
    }else{
         if(valor1 > valor2){ //se (VALOR1 > VALOR2)
            printf("%i\n", valor2); //exibe uma mensagem na tela
            printf("%i\n", valor1); //exibe uma mensagem na tela
         }else{
    
            printf("Os valores \255 s%co iguais!\n", 198); //exibe uma mensagem na tela
         }
    }
    //Pergunta se o usuario quer fazer novamente.
    printf("Deseja calcular outra media?(s/n)"); //exibe uma mensagem na tela
    scanf("%s", &choose); //captura a variável choose
    if(choose == 's'){ //se (CHOOSE == 'S')
           main(); //função principal
    }else{
          //ESPERA O USUARIO FECHAR O PROGRAMA
          printf("Pressione qualquer tecla para continuar..."); //exibe uma mensagem na tela
          getch(); //espera o usuario pressionar ENTER
          //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
          system("cls");
          system("color 0F");
    }
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//****Inicío do arquivo: troca de valores.cpp
//****Ultima Modificação: 4/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
main(){ //função principal
       system("title Troca de valores");
       
       int a, b, c; //declara as variáveis como inteiros: a, b, c;
       
       printf("Seus valores:\n\tA="); //exibe uma mensagem na tela
       scanf("%i", &a); //captura a variável a
       printf("\tB="); //exibe uma mensagem na tela
       scanf("%i", &b); //captura a variável b
            
       c = a; //C recebe de A
       a = b; //A receve de B
       b = c; //B recebe de C
       
       printf("Resultado:\n\tA=%i\n\tB=%i\n", a, b); //exibe uma mensagem na tela
       
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//****Inicío do arquivo: us para r.cpp
//****Ultima Modificação: 20/3/2011
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO

main(){ //função principal
       // Declara
       float dollar, real, cotacao; //declara as variáveis como reais: dollar, real, cotacao;
       int choosed; //declara as variáveis como inteiros: choosed;
       // Titula
       system("title U$ para R$");
       // ...
       printf("Digite o valor a cotacao u$ para R$: "); //exibe uma mensagem na tela
       scanf("%f", &cotacao); //captura a variável cotacao
              
       printf("Digite o valor em Dollars: U$"); //exibe uma mensagem na tela
       scanf("%f", &dollar); //captura a variável dollar
       
       real = dollar * cotacao; // calcula o valor do dollar
       
       printf("\t Valor em Real: R$%.2f\n", real); //exibe uma mensagem na tela
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//****Inicío do arquivo: volume - lata.cpp
//****Ultima Modificação: 4/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB

main(){ //função principal
    float volume, raio, altura; //declara as variáveis como reais: volume, raio, altura;
    while(true){
                printf("Digite o raio: "); //exibe uma mensagem na tela
                scanf("%f", &raio); //captura a variável raio
                printf("Digite a altura: "); //exibe uma mensagem na tela
                scanf("%f", &altura); //captura a variável altura
                
                volume = 3.14159 * (raio * raio) * altura; //calcula o volume
                
                printf("O volume e: %f\n", volume); //exibe uma mensagem na tela
                
                getch(); //espera o usuario pressionar ENTER
                system("cls"); //limpa a tela
    }
    return 0;
}
//****Fim do arquivo

//****Inicío do arquivo: volume.cpp
//****Ultima Modificação: 4/3/2011
#include <conio.h> //inclui a biblioteca CONIO
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB

main(){ //função principal
    float volume, altura, largura, comprimento; //declara as variáveis como reais: volume, altura, largura, comprimento;
    while(true){
                printf("Digite a altura: "); //exibe uma mensagem na tela
                scanf("%f", &altura); //captura a variável altura
                printf("Digite a largura: "); //exibe uma mensagem na tela
                scanf("%f", &largura); //captura a variável largura
                printf("Digite o comprimento: "); //exibe uma mensagem na tela
                scanf("%f", &comprimento); //captura a variável comprimento
                
                volume = altura * largura * comprimento; //calcula o valume
                
                printf("O volume e: %f\n", volume); //exibe uma mensagem na tela
                
                getch(); //espera o usuario pressionar ENTER
                system("cls"); //limpa a tela
    }
    return 0;
}
//****Fim do arquivo
