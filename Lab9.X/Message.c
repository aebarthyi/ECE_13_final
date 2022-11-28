#include "Message.h"

#define START_DELIMITER '$'
#define CHECKSUM_DELIMITER '*'
#define END_DELIMITER '\n'

typedef enum DecodeState{
    DECODE_WAIT_FOR_START,
    DECODE_RECORDING_PAYLOAD,
    DECODE_RECORDING_CHECKSUM
};

typedef struct DecodeStatus{
    DecodeState decodeState;
    char checksum_string[82];
    int messageIndex;
};

static DecodeStatus decodeStatus = {DECODE_WAIT_FOR_START, {0}, 0};
/**
 * Given a payload string, calculate its checksum
 * 
 * @param payload       //the string whose checksum we wish to calculate
 * @return   //The resulting 8-bit checksum 
 */
uint8_t Message_CalculateChecksum(const char* payload){
    
}

/**
 * ParseMessage() converts a message string into a BB_Event.  The payload and
 * checksum of a message are passed into ParseMessage(), and it modifies a
 * BB_Event struct in place to reflect the contents of the message.
 * 
 * @param payload       //the payload of a message
 * @param checksum      //the checksum (in string form) of  a message,
 *                          should be exactly 2 chars long, plus a null char
 * @param message_event //A BB_Event which will be modified by this function.
 *                      //If the message could be parsed successfully,
 *                          message_event's type will correspond to the message type and 
 *                          its parameters will match the message's data fields.
 *                      //If the message could not be parsed,
 *                          message_events type will be BB_EVENT_ERROR
 * 
 * @return STANDARD_ERROR if:
 *              the payload does not match the checksum
 *              the checksum string is not two characters long
 *              the message does not match any message template
 *          SUCCESS otherwise
 * 
 * Please note!  sscanf() has a couple compiler bugs that make it a very
 * unreliable tool for implementing this function. * 
 */
int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event){
    
}

/**
 * Encodes the coordinate data for a guess into the string `message`. This string must be big
 * enough to contain all of the necessary data. The format is specified in PAYLOAD_TEMPLATE_COO,
 * which is then wrapped within the message as defined by MESSAGE_TEMPLATE. 
 * 
 * The final length of this
 * message is then returned. There is no failure mode for this function as there is no checking
 * for NULL pointers.
 * 
 * @param message            The character array used for storing the output. 
 *                              Must be long enough to store the entire string,
 *                              see MESSAGE_MAX_LEN.
 * @param message_to_encode  A message to encode
 * @return                   The length of the string stored into 'message_string'.
                             Return 0 if message type is MESSAGE_NONE.
 */
int Message_Encode(char *message_string, Message message_to_encode){
    
}

/**
 * Message_Decode reads one character at a time.  If it detects a full NMEA message,
 * it translates that message into a BB_Event struct, which can be passed to other 
 * services.
 * 
 * @param char_in - The next character in the NMEA0183 message to be decoded.
 * @param decoded_message - a pointer to a message struct, used to "return" a message
 *                          if char_in is the last character of a valid message, 
 *                              then decoded_message
 *                              should have the appropriate message type.
 *                          if char_in is the last character of an invalid message,
 *                              then decoded_message should have an ERROR type.
 *                          otherwise, it should have type NO_EVENT.
 * @return SUCCESS if no error was detected
 *         STANDARD_ERROR if an error was detected
 * 
 * note that ANY call to Message_Decode may modify decoded_message.
 */
int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event){
    while(decoded_message_event.type != BB_EVENT_ERROR){
        switch(decodeStatus.decodeState){
            case DECODE_WAIT_FOR_START: {
                if(char_in == START_DELIMITER)
                    decodeStatus.decodeState = DECODE_RECORDING_PAYLOAD;
                break;
            }
            case DECODE_RECORDING_PAYLOAD:{
                if(char_in == CHECKSUM_DELIMITER)
                    decodeStatus.decodeState = DECODE_RECORDING_CHECKSUM;
                else{
                    //check for stuff to return errors
                    decodeStatus.checksum_string[decodeStatus.messageIndex++] = char_in;
                }
          
                break;
            }
            case DECODE_RECORDING_CHECKSUM:{
                if(char_in == END_DELIMITER){
                    //do stuff here
                }
                else{
                    //only record HEX CHARs
                }
                    
                break;
            }
        }
    }
    
    
    
    
    return SUCCESS;
}