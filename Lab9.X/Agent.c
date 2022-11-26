#include "Agent.h"


typedef struct Agent{
    AgentState state;
    int turnCounter;
};

static Agent agentState;

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
            
        }
        case AGENT_STATE_CHALLENGING:{
            
        }
        case AGENT_STATE_ACCEPTING:{
            
        }
        case AGENT_STATE_ATTACKING:{
            
        }
        case AGENT_STATE_DEFENDING:{
            
        }
        case AGENT_STATE_WAITING_TO_SEND:{
            
        }
        case AGENT_STATE_END_SCREEN:{
            
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
