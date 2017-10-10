//????NewLine
//****Inicío do arquivo: calculadora5.cpp
//****Ultima Modificação: 5/6/2011
//==============================================================================
//++Calculadora
//Programa: Calculadora versão 5
//Autor: PedroHLC::InfoTec
//Data: 17-05-11 16:20
//==============================================================================
//++Descrição
//Desenvolva um programa em linguagem C\C++ que funcione como uma calculadora
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
#include <math.h> //inclui a biblioteca MATH
//-----------------------------------------------------------------------------
//Declara utilidades
    using namespace std;
//Declara variaveis globais
    float x, y, r; //declara as variáveis como reais: x, y, r
    wchar_t choose;
//-----------------------------------------------------------------------------
//Função: somar(v1, v2)
float somar(float v1, float v2){ return(v1 + v2); } //declara as variáveis como reais: somar(float v1, float v2){ return(v1 + v2)
//-----------------------------------------------------------------------------
//Função: subtrair(v1, v2)
float subtrair(float v1, float v2){ return(v1 - v2); } //declara as variáveis como reais: subtrair(float v1, float v2){ return(v1 - v2)
//-----------------------------------------------------------------------------
//Função: dividir(v1, v2)
float dividir(float v1, float v2){ return(v1 / v2); } //declara as variáveis como reais: dividir(float v1, float v2){ return(v1 / v2)
//-----------------------------------------------------------------------------
//Função: multiplicar(v1, v2)
float multiplicar(float v1, float v2){ return(v1 * v2); } //declara as variáveis como reais: multiplicar(float v1, float v2){ return(v1 * v2)
//-----------------------------------------------------------------------------
//Função: raiz(v1, v2)
float raiz(float v1, float v2){ return(pow(v1, (1/v2))); } //declara as variáveis como reais: raiz(float v1, float v2){ return(pow(v1, (1/v2)))
//-----------------------------------------------------------------------------
//Função: calculadora()
void calculadora(){
    //printf("Digite o primeiro valor: ");
    //scanf("%f", &x);
    //printf("Opera\207\344es:\n\t+ Soma\n\t- Subtra\207\306o\n\t* Multiplica\207\306o\n\t/ Divis\306o\n\tE Elevar\n\tR Raiz\n\tS Sair\nDigite a opera\207\306o:");
    //scanf("%s", &choose);
    //printf("Digite o segundo valor: ");
    printf("\tCALCULADORA\n\n"); //exibe uma mensagem na tela
    printf("Calculo: "); //exibe uma mensagem na tela
    scanf("%f%c%f", &x, &choose, &y); //captura a variável y
    switch(choose){
      case('+'): r = somar(x, y); break;
      case('-'): r = subtrair(x, y); break;
      case('*'): r = multiplicar(x, y); break;
      case('#'): r = pow(x, y); break;
      case('!'): r = raiz(x, y); break;
      case('/'): 
        if(y != 0) r = dividir(x, y);
        else{
          printf("Impossivel de dividir por 0\n"); //exibe uma mensagem na tela
          r = 0;
        }
        break;
      default:
        printf("Opera\207\306o desconhecida!\n"); //exibe uma mensagem na tela
        return; //retorna ""
        break;
    }
    printf("Resultado: %lf\n", r); //exibe uma mensagem na tela
    return; //retorna ""
}
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
    system("cls");
    //Persoanliza a Janela
    system("color f9");
    system("title Calculadora");
    //Roda o programa
    while(true){
         //Limpa a tela, caso o programa esteja retornando o loop
         system("cls");
         calculadora();
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
    return(0); //retorna "(0)"
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//????NewLine
//****Inicío do arquivo: for1.cpp
//****Ultima Modificação: 20/5/2011
#include<stdio.h> //inclui a biblioteca STDIO
#include<conio.h> //inclui a biblioteca CONIO
#include<windows.h> //inclui a biblioteca WINDOWS

main(){ //função principal
       for(int i=1; i <= 10; i++) //declara as variáveis como inteiros: i=1; i <= 10
       {
               Beep(i *1000, 500);
               printf("%d\n", i); //exibe uma mensagem na tela
       }
       for(int i=10; i >= 1; i--) //declara as variáveis como inteiros: i=10; i >= 1
       {
               Beep(i *1000, 500);
               printf("%d\n", i); //exibe uma mensagem na tela
       }
       for(int i=1; i <= 10; i += 3) //declara as variáveis como inteiros: i=1; i <= 10
       {
               Beep(i *1000, 500);
               printf("%d\n", i); //exibe uma mensagem na tela
       }
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//????NewLine
//****Inicío do arquivo: funcao(soma_valores).cpp
//****Ultima Modificação: 17/5/2011
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO

void mudacor();
int soma_valores(int a, int b); //declara as variáveis como inteiros: soma_valores(int a, int b)
void cor_pb();

main(){ //função principal
       int valor1, valor2; //declara as variáveis como inteiros: valor1, valor2
       
       printf("Digite um valor: "); //exibe uma mensagem na tela
       scanf("%d", &valor1); //captura a variável valor1
       printf("Digite outro valor: "); //exibe uma mensagem na tela
       scanf("%d", &valor2); //captura a variável valor2
       
       mudacor();
       
       printf("O resultado foi: %d\n", soma_valores(valor1, valor2)); //exibe uma mensagem na tela
       
       cor_pb();
}

void cor_pb(){
     system("color 0f");
     printf("finalizando o sistema"); //exibe uma mensagem na tela
     getch(); //espera o usuario pressionar ENTER
}



void mudacor(){
     system("color 1E");
}

int soma_valores(int a, int b){
    int total; //declara as variáveis como inteiros: total
    total = a + b;
    return(total); //retorna "(total)"
}
//****Fim do arquivo

//????NewLine
//****Inicío do arquivo: funcao(soma_valores)_fast.cpp
//****Ultima Modificação: 17/5/2011
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO

int soma_valores(int a, int b){
    return(a + b); //retorna "(a + b)"
}

main(){ //função principal
       int vA, vB; //declara as variáveis como inteiros: vA, vB
       
       printf("Digite um valor: "); //exibe uma mensagem na tela
       scanf("%i", &vA); //captura a variável vA
       printf("Digite outro valor: "); //exibe uma mensagem na tela
       scanf("%i", &vB); //captura a variável vB
       
       printf("O resultado foi: %i\n", soma_valores(vA, vB)); //exibe uma mensagem na tela
       
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//????NewLine
//****Inicío do arquivo: idades.cpp
//****Ultima Modificação: 20/5/2011
#include <stdio.h> //inclui a biblioteca STDIO
#include <conio.h> //inclui a biblioteca CONIO

main(){ //função principal
       int idade[27]; //declara as variáveis como inteiros: idade[27]
       int somaidade=0; //declara as variáveis como inteiros: somaidade=0
       for(int i=0; i < 27; i++){ //declara as variáveis como inteiros: i=0; i < 27
         scanf("%i", &idade[i]); //captura a variável idade[i]
         somaidade += idade[i];
       }
       printf("Total: %i\nM\202dia: %i\n", somaidade, (somaidade / 27)); //exibe uma mensagem na tela
       getch(); //espera o usuario pressionar ENTER
}
//****Fim do arquivo

//????NewLine
//****Inicío do arquivo: mm.cpp
//****Ultima Modificação: 25/5/2011
//==============================================================================
//++Maior e Menor-
//Programa: Maior e Menor-
//Autor: PedroHLC::InfoTec
//Data: 24-05-11 17:10
//==============================================================================
//++Descrição
// Elaborar um programa que efetue a leitura de valores positivos inteiro até
//que um valor negativo seja informado. Ao final deverão ser apresentados o Maior
//e o Menor valores informados pelo usuario.
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//-----------------------------------------------------------------------------
//Declara variaveis globais
    char choose; //declara as variáveis como caracter: choose
    int valor, valor_min, valor_max; //declara as variáveis como inteiros: valor, valor_min, valor_max
//-----------------------------------------------------------------------------
//Função: clean_values()
void clean_values(){
    valor=1;
    valor_min = 999999999;
    valor_max = 0;
}
//-----------------------------------------------------------------------------
//Função: mm()
void mm(){
    for(clean_values(); valor >= 0;){
        system("cls");
        scanf("%i", &valor); //captura a variável valor
        if(valor < 0) break;
        if(valor < valor_min) valor_min = valor;
        if(valor > valor_max) valor_max = valor;
    }
    printf("Número negativo detectado!\nValor menor: %i\nValor maior: %i", valor_min, valor_max); //exibe uma mensagem na tela
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
    system("cls");
    //Persoanliza a Janela
    system("color f9");
    system("title MM");
    //Roda o programa
    while(true){
         //Limpa a tela, caso o programa esteja retornando o loop
         system("cls");
         mm();
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
    return(0); //retorna "(0)"
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//????NewLine
//****Inicío do arquivo: numerorespondoes.cpp
//****Ultima Modificação: 27/4/2011
//==============================================================================
//++Switch
//Programa: Números que respondem
//Autor: PedroHLC::InfoTec
//Data: 27-04-11 16:50
//==============================================================================
//++Descrição
//Desenvolva um programa em linguagem C\C++ que responda conforme o número que
//for digitado.
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//-----------------------------------------------------------------------------
//Declara variaveis globais
    int numero; //declara as variáveis como inteiros: numero
    char choose; //declara as variáveis como caracter: choose
//-----------------------------------------------------------------------------
//Função: number_reader()
void number_reader(){
     printf("Digite o valor: "); //exibe uma mensagem na tela
     scanf("%i", &numero); //captura a variável numero
     printf("Voc%c digitou: ", 136); //exibe uma mensagem na tela
     switch(numero){
       case(0): puts("0"); break;
       case(1): puts("1"); break;
       case(2): puts("2"); break;
       case(3): puts("3"); break;
       case(4): puts("4"); break;
       default: puts("Desconhecido!"); break;
     }
}
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
    system("cls");
    //Persoanliza a Janela
    system("color f9");
    system("title Calculadora");
    //Roda o programa
    while(true){
         //Limpa a tela, caso o programa esteja retornando o loop
         system("cls");
         number_reader();
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
    return(0); //retorna "(0)"
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//????NewLine
//****Inicío do arquivo: randomico.cpp
//****Ultima Modificação: 25/5/2011
//==============================================================================
//++Advinha
//Programa: Advinha
//Autor: PedroHLC::InfoTec
//Data: 25-05-11 16:10
//==============================================================================
//++Descrição
// .
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
#include <time.h> //inclui a biblioteca TIME
//-----------------------------------------------------------------------------
//Declara variaveis globais
    char choose; //declara as variáveis como caracter: choose
    int valor, aleatorio, max, tentativas; //declara as variáveis como inteiros: valor, aleatorio, max, tentativas
//-----------------------------------------------------------------------------
//Função: randInt(valor_min, valor_max)
int randInt(int va,int vb){
   return (va + rand() % (vb - va + 1)); //retorna "(va + rand() % (vb - va + 1))"
}
void getValor(){
    printf("Digite um n\243mero de 0 a 30: "); //exibe uma mensagem na tela
    scanf("%i", &valor); //captura a variável valor
    while(valor < 0 or valor > 30){
          printf("Eu disse de 0 a 30! Vamos tentar denovo: "); //exibe uma mensagem na tela
          scanf("%i", &valor);     //captura a variável valor
    } 
}
//-----------------------------------------------------------------------------
//Função: guesss()
void guesss(){
    aleatorio = randInt(0, 30);
    valor = (aleatorio - 1);
    tentativas = 0;
    for(;valor!=aleatorio; tentativas++){
      getValor();
      if(valor < aleatorio) puts("Tente um mais alto!");
      else if(valor > aleatorio) puts("Tente um mais baixo!");
    }
    if(aleatorio == valor) puts("Parab\202ns! Voc\210 acertou!");
    printf("Tentativas: %d\n", tentativas); //exibe uma mensagem na tela
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Corrige o rand
    srand(unsigned(time(NULL)));
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
    system("cls");
    //Persoanliza a Janela
    system("color f9");
    system("title Advinha");
    //Roda o programa
    while(true){
         //Limpa a tela, caso o programa esteja retornando o loop
         guesss();
         system("cls");
         //Pergunta se o usuario quer fazer novamente.
         printf("Gostaria de tentar outra vez?(s/n): "); //exibe uma mensagem na tela
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
    return(0); //retorna "(0)"
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//????NewLine
//****Inicío do arquivo: tabuada2.cpp
//****Ultima Modificação: 24/5/2011
//==============================================================================
//++Tabuada
//Programa: Tabuada
//Autor: PedroHLC::InfoTec
//Data: 24-05-11 16:10
//==============================================================================
//++Descrição
//Desenvolva um programa em linguagem C\C++ que mostre a tabuada de 0 a 10 e
//apenas use 2 variaveis
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//-----------------------------------------------------------------------------
//Declara variaveis globais
    char choose; //declara as variáveis como caracter: choose
//-----------------------------------------------------------------------------
//Função: tabuada()
void tabuada(){
    for(int x=1; x <= 10; x++) for(int y=0; y <= 11; y++) //declara as variáveis como inteiros: x=1; x <= 10; x++) for(int y=0; y <= 11
      if(y==11)printf("\n"); //exibe uma mensagem na tela
      else printf("%i\t*\t%i\t=\t%i\n", x, y, (x*y)); //exibe uma mensagem na tela
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
    return(0); //retorna "(0)"
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//????NewLine
//****Inicío do arquivo: vectores.cpp
//****Ultima Modificação: 1/6/2011
//==============================================================================
//++Vectores
//Programa: Vectores
//Autor: PedroHLC::InfoTec
//Data: 1-06-11 16:30
//==============================================================================
//++Descrição
// Desenvolva os seguintes programas em linguagem C:
// 1- Criar um vetor de 5 posições e alimentar esse vetor com valores que serão
//    digitados pelo usuario(não utilize estrutura de repetição)C
// 2- Continuando o exercicio anterior, faça a exibição dos valores do vetor na
//    tela(não utilize estrutura de repetição)C
// 3- Refazer o mesmo exercícios anterior utilizando for
// 4- Refazer o mesmo exercício utilizando while
// 5- Criar um vetor com 10 poisções e ordinar esse vetor em ordem crescente
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//-----------------------------------------------------------------------------
//Declara variaveis globais
    char choose; //declara as variáveis como caracter: choose
    int valor, aleatorio, max, tentativas; //declara as variáveis como inteiros: valor, aleatorio, max, tentativas
//-----------------------------------------------------------------------------
//Função: vectorexample1()
void vectorexample1(){
    int valor[5]={0}; //declara as variáveis como inteiros: valor[5]={0}
    printf("Digite um valor:"); //exibe uma mensagem na tela
    scanf("%i", &valor[0]); //captura a variável valor[0]
    printf("Digite mais um valor:"); //exibe uma mensagem na tela
    scanf("%i", &valor[1]); //captura a variável valor[1]
    printf("Digite mais um valor:"); //exibe uma mensagem na tela
    scanf("%i", &valor[2]); //captura a variável valor[2]
    printf("Digite mais um valor:"); //exibe uma mensagem na tela
    scanf("%i", &valor[3]); //captura a variável valor[3]
    printf("Digite mais um valor:"); //exibe uma mensagem na tela
    scanf("%i", &valor[4]); //captura a variável valor[4]
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: vectorexample2()
void vectorexample2(){
    int valor[5]={0}; //declara as variáveis como inteiros: valor[5]={0}
    printf("Digite um valor:"); //exibe uma mensagem na tela
    scanf("%i", &valor[0]); //captura a variável valor[0]
    printf("Digite mais um valor:"); //exibe uma mensagem na tela
    scanf("%i", &valor[1]); //captura a variável valor[1]
    printf("Digite mais um valor:"); //exibe uma mensagem na tela
    scanf("%i", &valor[2]); //captura a variável valor[2]
    printf("Digite mais um valor:"); //exibe uma mensagem na tela
    scanf("%i", &valor[3]); //captura a variável valor[3]
    printf("Digite mais um valor:"); //exibe uma mensagem na tela
    scanf("%i", &valor[4]); //captura a variável valor[4]
    printf("Primeiro valor digitado: %i\n", valor[0]); //exibe uma mensagem na tela
    printf("Segundo valor digitado: %i\n", valor[1]); //exibe uma mensagem na tela
    printf("Terceiro valor digitado: %i\n", valor[2]); //exibe uma mensagem na tela
    printf("Quarto valor digitado: %i\n", valor[3]); //exibe uma mensagem na tela
    printf("Quinto valor digitado: %i\n", valor[4]); //exibe uma mensagem na tela
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: vectorexample3()
void vectorexample3(){
    int valor[5]={0}, x=0; //declara as variáveis como inteiros: valor[5]={0}, x=0
    for(x=0; x < 5; x++){
      printf("Digite um valor:"); //exibe uma mensagem na tela
      scanf("%i", &valor[x]); //captura a variável valor[x]
    }
    for(x=0; x < 5; x++){
      printf("%io. valor digitado: %i\n", x, valor[x]); //exibe uma mensagem na tela
    }
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: vectorexample4()
void vectorexample4(){
    int valor[5]={0}, x=0; //declara as variáveis como inteiros: valor[5]={0}, x=0
    while(x < 5){
      printf("Digite um valor:"); //exibe uma mensagem na tela
      scanf("%i", &valor[x]); //captura a variável valor[x]
      x++;
    }
    x = 0;
    while(x < 5){
      printf("%io. valor digitado: %i\n", x, valor[x]); //exibe uma mensagem na tela
      x++;
    }
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: vectorexample5()
void vectorexample5(){
    int valor[10], x=0, maior=-999999999, falta=10, jaforam[10], atualmaior=0, final[10]; //declara as variáveis como inteiros: valor[10], x=0, maior=-999999999, falta=10, jaforam[10], atualmaior=0, final[10]
    for(x=0; x < 10; x++){
      printf("Digite um valor:"); //exibe uma mensagem na tela
      scanf("%i", &valor[x]); //captura a variável valor[x]
    }
    for(falta=10; falta > 0; falta--){
      maior=(-999999999);
      for(x=0; x < 10; x++){
        if((valor[x] > maior) & (jaforam[x] != 1)){ //se ((VALOR[X] > MAIOR) & (JAFORAM[X] != 1))
                    atualmaior = x;
                    maior = valor[x];
        }
      }
      if(maior <= (-999999999)) printf("O programa falhou em %i que seria %io. maior!\n", valor[atualmaior], falta); //exibe uma mensagem na tela
      jaforam[atualmaior] = 1;
      final[falta-1] = maior;
    }
    for(x=0; x < 10; x++){
      printf("%io. valor (crescente): %i\n", x+1, final[x]); //exibe uma mensagem na tela
    }
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: getexercicio()
int getexercicio(){
    int cmd=0; //declara as variáveis como inteiros: cmd=0
    while(cmd==0){
                  printf("Digite o exercicio desejado: "); //exibe uma mensagem na tela
                  scanf("%i", &cmd); //captura a variável cmd
                  if(cmd<=0 or cmd >= 6){ //se (CMD<=0 OR CMD >= 6)
                            printf("Exercicio desconhecido!\n"); //exibe uma mensagem na tela
                            cmd = 0;
                  }
    }
    return(cmd);     //retorna "(cmd)"
}
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
    system("cls");
    //Persoanliza a Janela
    system("color f9");
    system("title Vetores");
    //Cria a variavel do exercicio desejado
    int exercicio; //declara as variáveis como inteiros: exercicio
    //Roda o programa
    while(true){
         //Limpa a tela, caso o programa esteja retornando o loop, e roda a funcao
         system("cls");
         exercicio=getexercicio();
         switch(exercicio){
           case(1):
                  system("cls");
                  vectorexample1();
                  break;
           case(2):
                  system("cls");
                  vectorexample2();
                  break;
           case(3):
                  system("cls");
                  vectorexample3();
                  break;
           case(4):
                  system("cls");
                  vectorexample4();
                  break;
           case(5):
                  system("cls");
                  vectorexample5();
                  break;
         }
         system("cls");
         //Pergunta se o usuario quer fazer novamente.
         printf("Gostaria de tentar outra vez?(s/n): "); //exibe uma mensagem na tela
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
    return(0); //retorna "(0)"
}
//------------------------------------------------------------------------------
//****Fim do arquivo

//????NewLine
//****Inicío do arquivo: while.cpp
//****Ultima Modificação: 1/6/2011
//==============================================================================
//++Exemplo While
//Programa: While
//Autor: PedroHLC::InfoTec
//Data: 30-05-11 16:10
//==============================================================================
//++Descrição
// .
//==============================================================================
//Bibliotecas
#include <stdio.h> //inclui a biblioteca STDIO
#include <stdlib.h> //inclui a biblioteca STDLIB
#include <conio.h> //inclui a biblioteca CONIO
//-----------------------------------------------------------------------------
//Declara variaveis globais
    char choose; //declara as variáveis como caracter: choose
    int valor, aleatorio, max, tentativas; //declara as variáveis como inteiros: valor, aleatorio, max, tentativas
//-----------------------------------------------------------------------------
//Função: whilexample1()
void whilexample1(){
    int i = 0; //declara as variáveis como inteiros: i = 0
    while(i <= 10){
            printf("%i\n", i); //exibe uma mensagem na tela
            i++;
    }
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: whilexample2()
void whilexample2(){
    int i = 0; //declara as variáveis como inteiros: i = 0
    while(i <= 100){
            printf("%i\n", i); //exibe uma mensagem na tela
            i += 2;
    }
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: whilexample3()
void whilexample3(){
    int i = 10; //declara as variáveis como inteiros: i = 10
    while(i >= 0){
            printf("%i\n", i); //exibe uma mensagem na tela
            i--;
    }
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: whilexample4()
void whilexample4(){
    int x, y, ymin, ymax; //declara as variáveis como inteiros: x, y, ymin, ymax
    printf("Digite o multiplicando:"); //exibe uma mensagem na tela
    scanf("%i", &x); //captura a variável x
    printf("Digite o valor minimo a ser multiplicado:"); //exibe uma mensagem na tela
    scanf("%i", &ymin); //captura a variável ymin
    printf("Digite o valor maximo a ser multiplicado(maior que o minimo):"); //exibe uma mensagem na tela
    scanf("%i", &ymax); //captura a variável ymax
    y = ymin;
    while(y <= ymax){
            printf("%i x %i = %i\n", x, y, (x*y)); //exibe uma mensagem na tela
            y++;
    }
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: whilexample5()
void whilexample5(){
    int x=0, y=0; //declara as variáveis como inteiros: x=0, y=0
    while(x <= 10){
            y = 0;
            while(y <= 10){
              printf("%i x %i = %i\n", x, y, (x*y)); //exibe uma mensagem na tela
              y++;
            }
            x++;
    }
    getch(); //espera o usuario pressionar ENTER
}
//-----------------------------------------------------------------------------
//Função: whilexample6()
char whilexample6(){
    fflush(stdin);
    int cmd=-1; //declara as variáveis como inteiros: cmd=-1
    while(cmd == -1){
            printf("Escolha uma opcao:\n1\tRecomecar o programa\n2\t Sair corretamente\n3\tSair bruscamente\nDigite sua escolha:"); //exibe uma mensagem na tela
            scanf("%i", &cmd); //captura a variável cmd
            if(cmd < 1 or cmd > 3) { //se (CMD < 1 OR CMD > 3)
                   printf("Operacao desconhecida!\n"); //exibe uma mensagem na tela
                   cmd = -1;
            }
    }
    switch(cmd){
                case(1):
                        return('s'); //retorna "('s')"
                        break;
                case(2):
                        return('n'); //retorna "('n')"
                        break;
                case(3):
                        exit(0);
                        break;
    }
    //return('s');
}
//-----------------------------------------------------------------------------
//Função: main()
main(){ //função principal
    //Limpa a tela, caso o programa tenha sido iniciado pelo DOS
    system("cls");
    //Persoanliza a Janela
    system("color f9");
    system("title Examplos While");
    //Roda o programa
    while(true){
         //Limpa a tela, caso o programa esteja retornando o loop, e roda a funcao
         system("cls");
         whilexample1();
         system("cls");
         whilexample2();
         system("cls");
         whilexample3();
         system("cls");
         whilexample4();
         system("cls");
         whilexample5();
         system("cls");
         choose = whilexample6();
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
    return(0); //retorna "(0)"
}
//------------------------------------------------------------------------------
//****Fim do arquivo

