#include "Message.h"
#include <stdio.h>
#include "BOARD.h"

int main(){
    
    char * testPayload1 = "RES,1,0,3";
    char * testChecksum1 = "5A";
    char expectedChecksum1 = 0x5a;
    BB_Event testMessageEvent = {BB_EVENT_NO_EVENT,0,0,0};
    
    printf("TESTING Message_CalculateChecksum()\n");
    
    char calculatedChecksum1 = Message_CalculateChecksum(testPayload1);
    
    if(expectedChecksum1 == calculatedChecksum1){
        printf("PASSED\n");
    }
    else{
        printf("FAILED\n");
    }
    
    
    printf("TESTING Message_ParseMessage()\n");
    
    int errorCheck = Message_ParseMessage(testPayload1, testChecksum1, &testMessageEvent);
    
    if(testMessageEvent.type == BB_EVENT_RES_RECEIVED && testMessageEvent.param0 == 1 && testMessageEvent.param1 == 0 && testMessageEvent.param2 == 3){
        printf("PASSED\n");
    }
    else{
        printf("FAILED\nMessageType: %d\n", testMessageEvent.type);
    }
    
    
    while(1);
    return 0;
}
