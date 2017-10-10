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
#include <time.h>

char * file_read(char* file_path) {
  FILE * pFile;
  long lSize;
  char * buffer;

  pFile = fopen ( file_path , "rb" );

  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);

  buffer = (char*) malloc (sizeof(char)*lSize);

  fread (buffer,1,lSize,pFile);
  
  fclose (pFile);
  return buffer;
}

void file_write(char* file_path, char* file_content) {
  FILE * pFile;

  pFile = fopen ( file_path , "wb" );

  fwrite (file_content, 1, sizeof(file_content), pFile);

  fclose (pFile);
}

int main(){ 
    // Create user vars  
    char * poof;
    int subpass=268496;
    
    // Read File
    poof = file_read("./arquivo");
    printf("File Size: %i\n", sizeof(poof));
    printf("Char Size: %i\n", strlen(poof));
    
    // Print user vars
    printf("Subpassoword: %d\n", subpass);
    
    // Create passoword from subpassoword
    int ipass = (((strlen(poof) * 2) + subpass)/2);
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
    int i2 = 0;
    while(i <= strlen(poof)){
      i2 = 0;
      while(i2 <= strlen(pass)){
        poof[i] += pass[i2];
        i2 += 1;
        i += 1;
      }
    }
    
    // Get now time after encryption
    time(&after_encrypt);
    encrypt_time = difftime(after_encrypt, before_encrypt);
    
    // Write File
    file_write("./arquivo_enc", poof);
          
    // Create time vars - decrypt
    time_t before_decrypt, after_decrypt;
    double decrypt_time;
    
    // Get now time before decryption
    time(&before_decrypt);
    
    // Decrypt
    i = 0;
    i2 = 0;
    while(i <= strlen(poof)){
      i2 = 0;
      while(i2 <= strlen(pass)){
        poof[i] -= pass[i2];
        i += 1;
      }
    }
    
    // Get now time after decryption
    time(&after_decrypt);
    decrypt_time = difftime(after_decrypt, before_decrypt);
    
    // Write File
    file_write("./arquivo_dec", poof);
    
    // Print encrypt duration in seconds
    printf ("Encrypt time: %.2lf seconds\n", encrypt_time );
    
    // Print decrypt duration in seconds
    printf ("Decrypt time: %.2lf seconds\n", decrypt_time );
    
    // Wait any key to exit
    getch();
}
