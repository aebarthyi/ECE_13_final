
#include <stdio.h>
#include <stdlib.h>
#include "Negotiation.h"
#include "BOARD.h"


NegotiationData NegotiationHash(NegotiationData secret){
    uint64_t square = secret * secret;
    NegotiationData result = square % PUBLIC_KEY;
    return result;
}

int NegotiationVerify(NegotiationData secret, NegotiationData commitment){
    if(NegotiationHash(secret) == commitment){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

NegotiationOutcome NegotiateCoinFlip(NegotiationData A, NegotiationData B){ // Finding a parity of 
    NegotiationData xored = A ^ B;
    xored = xored^(xored>>1);
    xored = xored^(xored>>2);
    xored = xored^(xored>>4);
    xored = xored^(xored>>8);
    
    if(xored & 1 == 1){
        return HEADS;
    }
    else{
        return TAILS;
    }
}

/*int i, counter;
    static uint16_t bitPosition = 0001;
    for(i = 0; i < 16; i++){
        if(xored & bitPosition){
            counter++;
        }
        bitPosition << 1;
    }
    if(counter % 2 == 0){
        return TAILS;
    }
    else{
        return HEADS;*/