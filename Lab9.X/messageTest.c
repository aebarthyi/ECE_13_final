#include "Message.h"
#include <string.h>
#include <stdio.h>
#include "BOARD.h"

int main(){
    
    char * testPayload1 = "RES,1,0,3";
    char * testChecksum1 = "5A";
    char expectedChecksum1 = 0x5a;
    BB_Event testMessageEvent = {BB_EVENT_NO_EVENT,0,0,0};
    BB_Event testDecodeEvent = {BB_EVENT_NO_EVENT,0,0,0};
    char * decodeTestString = "$RES,1,0,3*5A\n";
    Message messageToEncode = {MESSAGE_RES, 1, 0, 3};
    char messageEncoded[MESSAGE_MAX_LEN] = {0};
    int expectedMessageLen = 14;
    
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
    
    printf("TESTING Message_Encode()\n");
    
    int messageLen = Message_Encode(messageEncoded, messageToEncode);
    printf("MESSAGE: %s", messageEncoded);
    printf("MESSAGE LEN: %d\n", messageLen);
    
    if(messageLen == expectedMessageLen){
        printf("PASSED\n");
    }
    else{
        printf("FAILED\n");
    }
    
    printf("TESTING Message_Decode()\n");
    for(int i = 0; i < strlen(decodeTestString); i++){
        errorCheck = Message_Decode(decodeTestString[i], &testDecodeEvent);
        if(!errorCheck){
            printf("ERROR\n");
            break;
        }
    }
    
    printf("MESSAGE TYPE: %d PARAM0: %d PARAM1: %d PARAM2: %d\n", testDecodeEvent.type, testDecodeEvent.param0, testDecodeEvent.param1, testDecodeEvent.param2);
    while(1);
    return 0;
}
