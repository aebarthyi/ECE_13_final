
#include <stdio.h>
#include <stdlib.h>
#include "Negotiation.h"


NegotiationData NegotiationHash(NegotiationData secret){
    NegotiationData square = secret * secret;
    return square % PUBLIC_KEY;
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
    int i, counter;
    uint16_t bitPosition = 0001;
    for(i = 0; i < 16; i++){
        if(xored & bitPosition){
            counter++;
        }
        bitPosition << 1;
    }
    if(counter % 2 == 0){
        NegotiationOutcome = TAILS;
    }
    else{
        NegotiationOutcome = HEADS;
    }
}