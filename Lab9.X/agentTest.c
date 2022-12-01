#include <stdio.h>
#include "BOARD.h"
#include "Agent.h"
#include "Message.h"
#include "Negotiation.h"
#include "Field.h"


int main(void){
    Message testMessage;
    BB_Event testEvent = {BB_EVENT_NO_EVENT, 0,0,0};
    AgentState testState = AGENT_STATE_START;
    AgentInit();
    
    testMessage = AgentRun(testEvent);
    
    testEvent.type = BB_EVENT_START_BUTTON;
    
    testMessage = AgentRun(testEvent);
    
    if(AgentGetState() == AGENT_STATE_CHALLENGING){
        printf("PASSED\n");
        
    }
    else{
        printf("FAILED\n");
    }
    while(1);
    return 0;
}
