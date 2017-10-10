/* Replace "dll.h" with the name of your header */
#include "dll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

extern "C" __declspec(dllexport) int test(){
       return 1;
}

extern "C" __declspec(dllexport) char * slower(char * poof, int size, int subpass){
    // Declare Temp Vars
    int i, i2;
    char * poof_fixed = (char*) malloc(size);
    // Prepare Passoword
    int ipass = (((sizeof(subpass) * 2) * subpass)/2) + 1023;
    char pass[] = "";
    itoa(ipass, pass, 10);
    // Text Encrypt
    i = 0;
    i2 = 0;
    while(i < size){
      i2 = 0;
      while(i2 < sizeof(pass)){
        poof[i] += pass[i2];
        i2 += 1;
        i += 1;
      }
    }
    // Text Fixer
    i = (-1);
    i2 = (-1);
    while(i2 <= size){
       i += 1;
       i2 += 1;
       if(poof[i2] == 0){
          poof_fixed[i] = 92;
          i += 1;
          poof_fixed[i] = 48;
       }else{
         poof_fixed[i] = poof[i2];
       }
    }
    poof_fixed[i+1] = 0;
    // Return Encrypted Text
    return(poof_fixed);
}

extern "C" __declspec(dllexport) char * faster(char * poof, int size, int subpass){
    // Declare Temp Vars
    int i, i2;
    char * poof_fixed = (char*) malloc(size);
    // Prepare Passoword
    int ipass = (((sizeof(subpass) * 2) * subpass)/2) + 1023;
    char pass[] = "";
    itoa(ipass, pass, 10);
    // Text Decrypt
    i = 0;
    i2 = 0;
    while(i < size){
      i2 = 0;
      while(i2 < sizeof(pass)){
        poof[i] -= pass[i2];
        i2 += 1;
        i += 1;
      }
    }
    // Text Fixer
    i = (-1);
    i2 = (-1);
    while(i2 <= size){
       i += 1;
       i2 += 1;
       if(poof[i2] == 0){
          poof_fixed[i] = 92;
          i += 1;
          poof_fixed[i] = 48;
       }else{
         poof_fixed[i] = poof[i2];
       }
    }
    poof_fixed[i+1] = 0;
    // Return Decrypted Text
    return(poof_fixed);
}
