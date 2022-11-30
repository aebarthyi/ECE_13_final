#include "Agent.h"
#include "Field.h"
#include "Negotiation.h"
#include "Uart1.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct { //agent struct to track state of the agent
    AgentState state;
    int turnCounter;
    Field myField;
    Field oppField;
    NegotiationData secret_a;
    NegotiationData secret_b;
    NegotiationData hash_a;
    GuessData own_guess;
    GuessData opp_guess;
}Agent;

static Agent agentState; //static module level struct to hold persistent data

/**
 * The Init() function for an Agent sets up everything necessary for an agent before the game
 * starts.  At a minimum, this requires:
 *   -setting the start state of the Agent SM.
 *   -setting turn counter to 0
 * If you are using any other persistent data in Agent SM, that should be reset as well.
 * 
 * It is not advised to call srand() inside of AgentInit.  
 *  */
void AgentInit(void){
    agentState.state = AGENT_STATE_START;
    agentState.turnCounter = 0;
}

/**
 * AgentRun evolves the Agent state machine in response to an event.
 * 
 * @param  The most recently detected event
 * @return Message, a Message struct to send to the opponent. 
 * 
 * If the returned Message struct is a valid message
 * (that is, not of type MESSAGE_NONE), then it will be
 * passed to the transmission module and sent via UART.
 * This is handled at the top level! AgentRun is ONLY responsible 
 * for generating the Message struct, not for encoding or sending it.
 */
Message AgentRun(BB_Event event){
    Message message = {MESSAGE_NONE, 0, 0, 0}; //message to be returned
    char * messageString;
    switch(agentState.state){
        case AGENT_STATE_START:{
            if(event.type == BB_EVENT_START_BUTTON){
                agentState.state = AGENT_STATE_CHALLENGING;
                FieldInit(&agentState.myField, &agentState.oppField);
                srand(time(NULL));
                agentState.secret_a = rand();
                agentState.hash_a = NegotiationHash(agentState.secret_a);
                
                message.type = MESSAGE_CHA;
                message.param0 = agentState.hash_a;
                Message_Encode(messageString, message);
               
                //place boats
                Uart1WriteData(messageString, strlen(messageString));
            }
            else if(event.type == BB_EVENT_CHA_RECEIVED){
                agentState.state = AGENT_STATE_ACCEPTING;
                FieldInit(&agentState.myField, &agentState.oppField);
                srand(time(NULL));
                agentState.secret_b = rand();
                
                message.type = MESSAGE_ACC; 
                message.type = agentState.secret_b;
                Message_Encode(messageString, message);
                
                Uart1WriteData(messageString, strlen(messageString));
            }
            else if(event.type == BB_EVENT_RESET_BUTTON)
                agentState.state = AGENT_STATE_START;
            //DO other things here like generate the message
            break;
        }
        case AGENT_STATE_CHALLENGING:{
            if(event.type == BB_EVENT_ACC_RECEIVED){
                message.type = MESSAGE_REV;
                message.type = agentState.secret_a;
                Message_Encode(messageString, message);
                //SEND REV
                
                if(NegotiateCoinFlip(agentState.secret_a, agentState.secret_b) == HEADS){
                    agentState.state = AGENT_STATE_WAITING_TO_SEND;
                }
                else
                    agentState.state = AGENT_STATE_DEFENDING;
                
                Uart1WriteData(messageString, strlen(messageString));
            }
            else if(event.type == BB_EVENT_RESET_BUTTON)
                agentState.state = AGENT_STATE_START;
            break;
        }
        case AGENT_STATE_ACCEPTING:{
            if(event.type == BB_EVENT_REV_RECEIVED){
                //stuff here
                if(NegotiateCoinFlip(agentState.secret_a, agentState.secret_b) == HEADS){
                    agentState.state = AGENT_STATE_DEFENDING;
                }
                else if(NegotiateCoinFlip(agentState.secret_a, agentState.secret_b) == TAILS){
                    
                    message.type = MESSAGE_SHO; 
                    message.param0 = agentState.own_guess.row;
                    message.param1 = agentState.own_guess.col;
                    Message_Encode(messageString, message);
                    agentState.state = AGENT_STATE_ATTACKING;
                    Uart1WriteData(messageString, strlen(messageString));
                }
                else
                    agentState.state = AGENT_STATE_END_SCREEN;
            }
            else if(event.type == BB_EVENT_RESET_BUTTON)
                agentState.state = AGENT_STATE_START;
            break;
        }
        case AGENT_STATE_ATTACKING:{
            if(event.type == BB_EVENT_RES_RECEIVED){
                FieldUpdateKnowledge(&agentState.oppField, &agentState.own_guess);
                //check if something happened 
                //check for victory
                
                agentState.state = AGENT_STATE_DEFENDING;
            }
            else if(event.type == BB_EVENT_RESET_BUTTON)
                agentState.state = AGENT_STATE_START;
            break;
        }
        case AGENT_STATE_DEFENDING:{
            if(event.type == BB_EVENT_SHO_RECEIVED){
                //check something then go to waiting to sent
                FieldRegisterEnemyAttack(&agentState.myField, &agentState.opp_guess);
                message.type = MESSAGE_RES;
                message.param0 = agentState.opp_guess.row;
                message.param1 = agentState.opp_guess.col;
                message.param2 = agentState.opp_guess.result;
                Message_Encode(messageString, message);
                Uart1WriteData(messageString, strlen(messageString));
                
                //check for victory 
                
                agentState.state = AGENT_STATE_WAITING_TO_SEND;
            }
            else if(event.type == BB_EVENT_RESET_BUTTON)
                agentState.state = AGENT_STATE_START;
            break;
        }
        case AGENT_STATE_WAITING_TO_SEND:{
            if(event.type == BB_EVENT_MESSAGE_SENT){
                agentState.state = AGENT_STATE_ATTACKING;
                agentState.turnCounter++;
                //decide guess
                //send SHO
                message.type = MESSAGE_SHO; 
                message.param0 = agentState.own_guess.row;
                message.param1 = agentState.own_guess.col;
                Message_Encode(messageString, message);
                Uart1WriteData(messageString, strlen(messageString));
            }
            else if(event.type == BB_EVENT_RESET_BUTTON)
                agentState.state = AGENT_STATE_START;
            break;
        }
        case AGENT_STATE_END_SCREEN:{
            //end state game screen
            
            break;
        }
    }
    return message;
}

/** * 
 * @return Returns the current state that AgentGetState is in.  
 * 
 * This function is very useful for testing AgentRun.
 */
AgentState AgentGetState(void){
    return agentState.state;
}

/** * 
 * @param Force the agent into the state given by AgentState
 * 
 * This function is very useful for testing AgentRun.
 */
void AgentSetState(AgentState newState){
    agentState.state = newState;
}
