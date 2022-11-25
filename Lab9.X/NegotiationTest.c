#include <stdio.h>
#include <stdlib.h>
#include "Negotiation.h"
#include "BOARD.h"


NegotiationData data1 = 0x143F;
NegotiationData data2 = 0x0003;

NegotiationData guess = 0x034F;
NegotiationData encryptedGuess;
NegotiationData changedGuess = 0x0344;

NegotiationData data_a = 0x1011000101101010;
NegotiationData data_b = 0x0101011010101100;
// 1110011111000110 // 10 1s' it is even therfore the parity is even.
NegotiationData data_bv2 = 0x0101011010101101;
//0x1011000101101010;
//0x0101011010101101;
//0x1110011111000111 11 1s, parity is odd.
int main(void){
    printf("Testing out NegotiationHash:\n");
   
    if(NegotiationHash(data1) == 0x70F6){ // Expanding data 1 into binary gives: 0001 0100 0011 1111
        printf("Test Passed.\n"); // When we are hexing it, we are squaring it and then moduloing it by 0xBEEF
    }
    else{
        printf("Test Failed.\n");
    }
    if(NegotiationHash(data2) == 0x0009){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    printf("Testing out NegotiationVerify\nSuppose a user gives a guess,\
 it ought to be encrypted, and sent first to the recipient. before\
 the recipient of the encrypted message sends their answer. Then verification must happen.\n");
    
    encryptedGuess = NegotiationHash(guess);
    if(NegotiationVerify(guess, encryptedGuess) == TRUE){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    if(NegotiationVerify(changedGuess, encryptedGuess) == FALSE){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    printf("Testing out NegotiateCoinFlip(). Suppose that data_a and data_b \
randomly generated data values.\n");
    
    if(NegotiateCoinFlip(data_a, data_b) == TAILS){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    if(NegotiateCoinFlip(data_a, data_bv2) == HEADS){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    
    
    
}