#include <stdio.h>
#include <stdlib.h>
#include "Field.h"
#include "BOARD.h"

Field *myField, *oponentField, field1, field2;
GuessData *enemyGuess, guess1, *enemyGuess2, guess2;
GuessData *myGuess, myguess1, *myGuess2, myguess2;


int main(void){
    
    printf("Welcome to CRUZID's Lab09 (BattleShips).  Compiled on %s %s.\n", __TIME__, __DATE__);
    myField = &field1;
    oponentField = &field2;
    FieldInit(myField, oponentField);
    
    FieldPrint_UART(myField, oponentField);
    
    printf("Testing out FieldInit().\n");
    if(oponentField->hugeBoatLives == FIELD_BOAT_SIZE_HUGE && \
            oponentField->largeBoatLives == FIELD_BOAT_SIZE_LARGE &&\
            oponentField->mediumBoatLives == FIELD_BOAT_SIZE_MEDIUM &&\
            oponentField->smallBoatLives == FIELD_BOAT_SIZE_SMALL){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    if(oponentField->grid[3][2] == FIELD_SQUARE_UNKNOWN && myField->grid[2][5] == FIELD_SQUARE_EMPTY){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    printf("Testing out FieldGetSquareStatus().\n");
    if(FieldGetSquareStatus(oponentField, 3, 2) == FIELD_SQUARE_UNKNOWN){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    if(FieldGetSquareStatus(oponentField, 3, FIELD_COLS) == FIELD_SQUARE_INVALID){
        printf("Test Passed.\n");   
    }
    else{
        printf("Test Failed.\n");
    }
    
    printf("Testing out FieldSetSquareStatus().\n");
    SquareStatus squareVariable = FieldSetSquareStatus(oponentField, 3, 3, FIELD_SQUARE_SMALL_BOAT);
    if(squareVariable == FIELD_SQUARE_UNKNOWN && FieldGetSquareStatus(oponentField, 3, 3) == FIELD_SQUARE_SMALL_BOAT){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    if(FieldSetSquareStatus(myField, FIELD_ROWS, FIELD_COLS, FIELD_SQUARE_LARGE_BOAT) == FIELD_SQUARE_INVALID){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    printf("Testing out AddBoat().\n");
    FieldAddBoat(myField, 3, 1, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_SMALL);
    if(FieldGetSquareStatus(myField, 3, 1) == FIELD_SQUARE_SMALL_BOAT && FieldGetSquareStatus(myField, 5, 1) == FIELD_SQUARE_SMALL_BOAT && FieldGetSquareStatus(myField, 4, 1) == FIELD_SQUARE_SMALL_BOAT){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    FieldAddBoat(myField, 2, 1, FIELD_DIR_EAST, FIELD_BOAT_TYPE_HUGE);
    if(FieldGetSquareStatus(myField, 2, 5) == FIELD_SQUARE_HUGE_BOAT && FieldGetSquareStatus(myField,2,1) == FIELD_SQUARE_HUGE_BOAT){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    uint8_t errorReading = FieldAddBoat(myField, 3, 1, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_HUGE);
    if(errorReading == STANDARD_ERROR){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    printf("Now Testing out FieldRegisterEnemyAttack()\n");
    
    enemyGuess = &guess1;
    enemyGuess2 = &guess2;
    enemyGuess->col = 1;
    enemyGuess->row = 2;
    
    
    enemyGuess2->col = 6;
    enemyGuess2->row = 4;
    
  
    
 
    FieldRegisterEnemyAttack(myField, enemyGuess);
    if(FieldGetSquareStatus(myField, 2, 1) == FIELD_SQUARE_HIT){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    FieldRegisterEnemyAttack(myField, enemyGuess2);
    if(FieldGetSquareStatus(myField, 4, 6) == FIELD_SQUARE_MISS && myField->hugeBoatLives == 5 && myField->smallBoatLives == 3){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    
    printf("Testing out FieldUpdateKnowledge().\n");
    myGuess = &myguess1;
    myGuess2 = &myguess2;
    myGuess->col = 5;
    myGuess->row = 3;
    myGuess->result = RESULT_HIT;
    myGuess2->col = 6;
    myGuess2->row = 1;
    myGuess2->result = RESULT_MEDIUM_BOAT_SUNK;
    
    FieldUpdateKnowledge(oponentField, myGuess);
    if(FieldGetSquareStatus(oponentField, 3, 5) == FIELD_SQUARE_HIT){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    FieldUpdateKnowledge(oponentField, myGuess2);
    if(FieldGetSquareStatus(oponentField, 1, 6) == FIELD_SQUARE_HIT && oponentField->mediumBoatLives == 0){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Passed.\n");
    }
    
    printf("Testing out FieldGetBoatStates().\n");
 
    uint8_t boatStatus = FieldGetBoatStates(myField);
    if(boatStatus ^ (0x0F) == (0x09)){
        printf("Test Passed.\n");
    }
    else{
        printf("%u", boatStatus);
    }
    
    FieldAddBoat(myField, 0, 9, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_MEDIUM);
    uint8_t boatStatus2 = FieldGetBoatStates(myField);
    if(boatStatus ^ (0x0F) == (0x0B)){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
    FieldPrint_UART(myField, oponentField);
     
    
    
    
    
    
  
    
}