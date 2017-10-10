/*
Encriptação e decriptação com contra-senha
Por PedroHLC
:D Meu primeiro sistema em C++
--------------------------------------------
Encrypt and decrypt with subpassoword
By PedroHLC
:D My first C++ System
*/

//headers
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//#include <string.h>
//#include <ctype.h>
#include <time.h>

// Create a nil char
int nilchar(){
    char i[1];
    return(i[0]);
}

int main(){ 
    // Create user vars  
    char poof[]="PedroHLC will be the best!";
    int subpass=268496;
    
    // Scan text
    //printf("Digite aqui uma frase a ser encriptada: ");
    //gets(poof);
    
    // Print user vars
    printf("Normal: %s\n", poof);
    printf("Subpassoword: %d\n", subpass);
    
    // Create passoword from subpassoword
    int ipass = (((sizeof(poof) * 2) + subpass)/2);
    char pass[]="";
    itoa(ipass, pass, 10);
    
    // Print passoword
    printf("Passoword: %s\n", pass);
    
    // Create time vars - ecrypt
    time_t before_encrypt, after_encrypt;
    double encrypt_time;
    
    // Get now time before encryption
    time(&before_encrypt);
    
    // Encrypy
    int i = 0;
    while(i < sizeof(poof)){
      for(int i2 = 0; i2 < sizeof(pass); i2++){
        poof[i] += pass[i2];
        i += 1;
        if(poof[i] == nilchar()) { break; }
      }
    }
    
    // Get now time after encryption
    time(&after_encrypt);
    encrypt_time = difftime(before_encrypt, after_encrypt);
    
    // Print encrypt result
    printf("Encrypted: %s\n", poof);
       
    // Create time vars - decrypt
    time_t before_decrypt, after_decrypt;
    double decrypt_time;
    
    // Get now time before decryption
    time(&before_decrypt);
    
    // Decrypt
    i = 0;
    while(i < sizeof(poof)){
      for(int i2 = 0; i2 < sizeof(pass); i2++){
        poof[i] -= pass[i2];
        i += 1;
        if(poof[i] == nilchar()) { break; }
      }
    }
    
    // Get now time after decryption
    time(&after_decrypt);
    decrypt_time = difftime(before_decrypt, after_decrypt);
    
    // Print decrypt result
    printf("Decrypted: %s\n\n", poof);
    
    // Print encrypt duration in seconds
    printf ("Encrypt time: %.2lf seconds\n", encrypt_time );
    
    // Print decrypt duration in seconds
    printf ("Decrypt time: %.2lf seconds\n", decrypt_time );
    
    // Wait any key to exit
    getch();
}
