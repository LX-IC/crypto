#include "sm4.h"

int main() {

    int i;
    unsigned int key[4] = { 
        0x01234567,
        0x89abcdef,
        0xfedcba98,
        0x76543210 
    };
    unsigned int plaintext[4] = {
        0x01234567,
        0x89abcdef,
        0xfedcba98,
        0x76543210 
    };
    unsigned int rk_output[32];
    unsigned int En_output[4];
    unsigned int De_output[4];
    
    SM4_KeyExp(key, rk_output);
    SM4_Encrypt(rk_output, plaintext, En_output);
    SM4_Decrypt(rk_output, En_output, De_output);
   
    for(i = 0; i < 4; i++) {
        if(De_output[i] != plaintext[i]) {
            printf("Self-check error ! \n");
            return 1;
        }
    }

    printf("Encry data is:   %x_%x_%x_%x \n", plaintext[0], plaintext[1], plaintext[2], plaintext[3]);
    printf("Encry result is: %x_%x_%x_%x \n", En_output[0], En_output[1], En_output[2], En_output[3]);
    printf("Decry data is:   %x_%x_%x_%x \n", En_output[0], En_output[1], En_output[2], En_output[3]);
    printf("Decry result is: %x_%x_%x_%x \n", De_output[0], De_output[1], De_output[2], De_output[3]);
    
    printf("\n");
    printf("Self-check success ! \n");
    
    return 0;
    
}	
	
