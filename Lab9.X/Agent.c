#include "Agent.h"
#include "Field.h"


typedef struct { //agent struct to track state of the agent
    AgentState state;
    int turnCounter;
    Field *myField;
    Field *oppField;
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
    switch(agentState.state){
        case AGENT_STATE_START:{
            if(event.type == BB_EVENT_START_BUTTON){
                agentState.state = AGENT_STATE_CHALLENGING;
                FieldInit(agentState.myField, agentState.oppField);
                //send CHA
                //place boats
                
            }
            else if(event.type == BB_EVENT_CHA_RECEIVED)
                agentState.state = AGENT_STATE_ACCEPTING;
            else if(event.type == BB_EVENT_RESET_BUTTON)
                agentState.state = AGENT_STATE_START;
            //DO other things here like generate the message
            break;
        }
        case AGENT_STATE_CHALLENGING:{
            if(event.type == BB_EVENT_ACC_RECEIVED){
                //SEND REV
            }
            else if(event.type == BB_EVENT_RESET_BUTTON)
                agentState.state = AGENT_STATE_START;
            break;
        }
        case AGENT_STATE_ACCEPTING:{
            if(event.type == BB_EVENT_REV_RECEIVED){
                //stuff here
            }
            else if(event.type == BB_EVENT_RESET_BUTTON)
                agentState.state = AGENT_STATE_START;
            break;
        }
        case AGENT_STATE_ATTACKING:{
            if(event.type == BB_EVENT_RES_RECEIVED){
                //check if something happened 
            }
            else if(event.type == BB_EVENT_RESET_BUTTON)
                agentState.state = AGENT_STATE_START;
            break;
        }
        case AGENT_STATE_DEFENDING:{
            if(event.type == BB_EVENT_SHO_RECEIVED){
                //check something then go to waiting to sent
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
            }
            else if(event.type == BB_EVENT_RESET_BUTTON)
                agentState.state = AGENT_STATE_START;
            break;
        }
        case AGENT_STATE_END_SCREEN:{
            break;
        }
    }
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
