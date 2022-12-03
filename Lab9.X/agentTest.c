#include <stdio.h>
#include "BOARD.h"
#include "Agent.h"
#include "Message.h"
#include "Negotiation.h"
#include "Field.h"

void resetString(char * message){
    for(int i = 0; i < MESSAGE_MAX_LEN; i++){
        message[i] = 0;
    }
}

int main(void){
    Message testMessage;\
    char messageString[MESSAGE_MAX_LEN] = {0};
    BB_Event testEvent = {BB_EVENT_NO_EVENT, 0,0,0};
    AgentState testState = AGENT_STATE_START;
    AgentInit();
    
    testMessage = AgentRun(testEvent);
    
    testEvent.type = BB_EVENT_START_BUTTON;
    
    testMessage = AgentRun(testEvent);
    
    printf("\n\nTESTING AGENT STATE MACHINE:\n\n");
    
    printf("MESSAGE_TYPE: %d\nMESSAGE_PARAM0: %d\nMESSAGE_PARAM1: %d\nMESSAGE_PARAM2: %d\n", testMessage.type, testMessage.param0, testMessage.param1, testMessage.param2);
    Message_Encode(messageString, testMessage);
    printf("MESSAGE: %s\n", messageString);
    resetString(messageString);
    if(AgentGetState() == AGENT_STATE_CHALLENGING && testMessage.type == MESSAGE_CHA){
        printf("PASSED\n");
        
    }
    else{
        printf("FAILED\n");
    }
    
    testState = AGENT_STATE_START;
    AgentSetState(testState);
    testEvent.type = BB_EVENT_CHA_RECEIVED;
    testMessage = AgentRun(testEvent);
    
    printf("MESSAGE_TYPE: %d\nMESSAGE_PARAM0: %d\nMESSAGE_PARAM1: %d\nMESSAGE_PARAM2: %d\n", testMessage.type, testMessage.param0, testMessage.param1, testMessage.param2);\
    Message_Encode(messageString, testMessage);
    printf("MESSAGE: %s\n", messageString);
    resetString(messageString);
    if(AgentGetState() == AGENT_STATE_ACCEPTING && testMessage.type == MESSAGE_ACC){
        printf("Passed.\n");
    }
    else{
        printf("Failed.\n");
    }
    
    testState =  AGENT_STATE_CHALLENGING;
    AgentSetState(testState);
    testEvent.type = BB_EVENT_ACC_RECEIVED;
    testMessage = AgentRun(testEvent);
    
    printf("MESSAGE_TYPE: %d\nMESSAGE_PARAM0: %d\nMESSAGE_PARAM1: %d\nMESSAGE_PARAM2: %d\n", testMessage.type, testMessage.param0, testMessage.param1, testMessage.param2);
    Message_Encode(messageString, testMessage);
    printf("MESSAGE: %s\n", messageString);
    resetString(messageString);
     if((AgentGetState() == AGENT_STATE_DEFENDING || AgentGetState() == AGENT_STATE_WAITING_TO_SEND) && testMessage.type == MESSAGE_REV){
        printf("Passed.\n");
    }
    else{
        printf("Failed.\n");
    }
    
    testState =  AGENT_STATE_ACCEPTING;
    AgentSetState(testState);
    testEvent.type = BB_EVENT_REV_RECEIVED;
    testMessage = AgentRun(testEvent);
    
    printf("MESSAGE_TYPE: %d\nMESSAGE_PARAM0: %d\nMESSAGE_PARAM1: %d\nMESSAGE_PARAM2: %d\n", testMessage.type, testMessage.param0, testMessage.param1, testMessage.param2);
    Message_Encode(messageString, testMessage);
    printf("MESSAGE: %s\n", messageString);
    resetString(messageString);
     if(AgentGetState() == AGENT_STATE_ATTACKING && testMessage.type == MESSAGE_SHO){
        printf("Passed.\n");
    }
    else{
        printf("Failed.\n");
    }
    
    testState =  AGENT_STATE_ATTACKING;
    AgentSetState(testState);
    testEvent.type = BB_EVENT_RES_RECEIVED;
    testMessage = AgentRun(testEvent);
    
    printf("MESSAGE_TYPE: %d\nMESSAGE_PARAM0: %d\nMESSAGE_PARAM1: %d\nMESSAGE_PARAM2: %d\n", testMessage.type, testMessage.param0, testMessage.param1, testMessage.param2);
    Message_Encode(messageString, testMessage);
    printf("MESSAGE: %s\n", messageString);
    resetString(messageString);
     if(AgentGetState() == AGENT_STATE_DEFENDING && testMessage.type == MESSAGE_NONE){
        printf("Passed.\n");
    }
    else{
        printf("Failed.\n");
    }
    
    testState =  AGENT_STATE_DEFENDING;
    AgentSetState(testState);
    testEvent.type = BB_EVENT_SHO_RECEIVED;
    testMessage = AgentRun(testEvent);
    
    printf("MESSAGE_TYPE: %d\nMESSAGE_PARAM0: %d\nMESSAGE_PARAM1: %d\nMESSAGE_PARAM2: %d\n", testMessage.type, testMessage.param0, testMessage.param1, testMessage.param2);
    Message_Encode(messageString, testMessage);
    printf("MESSAGE: %s\n", messageString);
    resetString(messageString);
     if(AgentGetState() == AGENT_STATE_WAITING_TO_SEND && testMessage.type == MESSAGE_RES){
        printf("Passed.\n");
    }
    else{
        printf("Failed.\n");
    }
    
    testState = AGENT_STATE_WAITING_TO_SEND;
    AgentSetState(testState);
    testEvent.type = BB_EVENT_MESSAGE_SENT;
    testMessage = AgentRun(testEvent);
    
    printf("MESSAGE_TYPE: %d\nMESSAGE_PARAM0: %d\nMESSAGE_PARAM1: %d\nMESSAGE_PARAM2: %d\n", testMessage.type, testMessage.param0, testMessage.param1, testMessage.param2);
    Message_Encode(messageString, testMessage);
    printf("MESSAGE: %s\n", messageString);
    resetString(messageString);
     if(AgentGetState() == AGENT_STATE_ATTACKING && testMessage.type == MESSAGE_SHO){
        printf("Passed.\n");
    }
    else{
        printf("Failed.\n");
    }

    
    
    while(1);
    return 0;
}
