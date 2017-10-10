/*
Encriptação e decriptação de arquivos com contra-senha
Por PedroHLC
:D Meu segundo sistema em C++
--------------------------------------------
Encrypt and decrypt of files with subpassoword
By PedroHLC
:D My second C++ System
*/

//headers
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
//#include <ctype.h>
#include <time.h>

// Create a nil char
int nilchar(){
    char i[1];
    return(i[0]);
}

int main(){ 
    puts("Por favor espere, dependendo do tamanho, vai demorar muito!");
    
    // Create user vars  
    char * poof;
    int subpass=268496;
    FILE * original_file;
    
    // Open File
    original_file = fopen ("./arquivo" , "rb");
    // Define File End
    long file_size;
    fseek(original_file, 0 , SEEK_END);
    file_size = ftell(original_file);
    rewind(original_file);
    poof = (char*) malloc(sizeof(char)*file_size);
    // Read File
    fread (poof, 1, file_size, original_file);
    // Close File
    fclose(original_file);
    
    // Print user vars
    //printf("Normal: %s\n", poof);
    //printf("Subpassoword: %d\n", subpass);
    
    // Create passoword from subpassoword
    int ipass = (((strlen(poof) * 2) + subpass)/2);
    char pass[]="";
    itoa(ipass, pass, 10);
    
    // Print passoword
    //printf("Passoword: %s\n", pass);
    
    // Create time vars - ecrypt
    time_t before_encrypt, after_encrypt;
    double encrypt_time;
    
    //
    puts("Praparacao completa ! Inciando...");
    
    // Get now time before encryption
    time(&before_encrypt);
    
    // Encrypy
    int i = 0;
    while(i < strlen(poof)){
      for(int i2 = 0; i2 < sizeof(pass); i2++){
        poof[i] += pass[i2];
        i += 1;
        if(poof[i] == nilchar()) { break; }
      }
    }
    
    // Get now time after encryption
    time(&after_encrypt);
    encrypt_time = difftime(after_encrypt, before_encrypt);
    
    // Print encrypt result
    //printf("Encrypted: %s\n", poof);
       
    // Create time vars - decrypt
    time_t before_decrypt, after_decrypt;
    double decrypt_time;
    
    // Get now time before decryption
    time(&before_decrypt);
    
    // Decrypt
    i = 0;
    while(i < strlen(poof)){
      for(int i2 = 0; i2 < sizeof(pass); i2++){
        poof[i] -= pass[i2];
        i += 1;
        if(poof[i] == nilchar()) { break; }
      }
    }
    
    // Get now time after decryption
    time(&after_decrypt);
    decrypt_time = difftime(after_decrypt, before_decrypt);
    
    // Print decrypt result
    //printf("Decrypted: %s\n\n", poof);
    
    // Print encrypt duration in seconds
    printf ("Encrypt time: %.2lf seconds\n", encrypt_time );
    
    // Print decrypt duration in seconds
    printf ("Decrypt time: %.2lf seconds\n", decrypt_time );
    
    // Wait any key to exit
    getch();
}
