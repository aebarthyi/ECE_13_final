#include <stdio.h>
#include "Agent.h"
#include "Message.h"
#include "Negotiation.h"
#include "Field.h"


int main(void){
    printf("Testing Out AgentInit().\n");
    AgentInit();
    if(agentState.state == AGENT_STATE_START && agentState.turnCounter == 0){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    
    
    
    
    
    while(1);
    return 0;
}
