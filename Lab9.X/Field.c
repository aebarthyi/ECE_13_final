
#include <stdio.h>
#include <stdlib.h>
#include "Field.h"
#include "BOARD.h"


void FieldPrint_UART(Field *own_field, Field * opp_field){
   //
}

void FieldInit(Field *own_field, Field *opp_field){
    uint8_t i, j;
    for(i = 0; i < FIELD_ROWS; i++){
        for(j = 0; j < FIELD_COLS; j++)
        {
            own_field->grid[i][j] = FIELD_SQUARE_EMPTY;
            opp_field->grid[i][j] = FIELD_SQUARE_UNKNOWN;
        }    
    }
    
    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
}

SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col){
    if(row < FIELD_ROWS && row >= 0 && col < FIELD_COLS && col >= 0){
        return f->grid[row][col];
    }
    else{
        return FIELD_SQUARE_INVALID;
    }
}

SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p){
    if(row < FIELD_ROWS && row >= 0 && col < FIELD_COLS && col >= 0){
        uint8_t returnValue = f->grid[row][col];
        f->grid[row][col] = p;
        return returnValue;
    }
    else{
        return FIELD_SQUARE_INVALID;
    }
}

uint8_t FieldAddBoat(Field *own_field, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type){
    BoatSize addBoatSize;
    switch(boat_type){
        case FIELD_BOAT_TYPE_SMALL:
            addBoatSize = FIELD_BOAT_SIZE_SMALL;
            break;
        case FIELD_BOAT_TYPE_MEDIUM:
            addBoatSize = FIELD_BOAT_SIZE_MEDIUM;
            break;
        case FIELD_BOAT_TYPE_LARGE:
            addBoatSize = FIELD_BOAT_SIZE_LARGE;
            break;
        case FIELD_BOAT_TYPE_HUGE:
            addBoatSize = FIELD_BOAT_SIZE_HUGE;
            break;
    }
    
    if(row < FIELD_ROWS && row >= 0 && col < FIELD_COLS && col >= 0){   
        if(dir == FIELD_DIR_EAST){
            if(row + boat_type < FIELD_ROWS){
                int i;
                for(i = 0; i < addBoatSize; i++){
                    own_field->grid[row + i][col] = boat_type;
                }
                return SUCCESS;
            }
            else{
                return STANDARD_ERROR;
            }
        }
        else{
            if(col + boat_type < FIELD_COLS){
                int l;
                for(l = 0; l < addBoatSize; l++){
                    own_field->grid[row][col + l] = boat_type;
                    return SUCCESS;
                }
            }
            else{
                return STANDARD_ERROR;
            }
        }
    }
    else{
        return STANDARD_ERROR;
    }
}

SquareStatus FieldRegisterEnemyAttack(Field *own_field, GuessData *opp_guess){
    SquareStatus returnVar = FieldGetSquareStatus(own_field, opp_guess->row, opp_guess->col);
    switch(FieldGetSquareStatus(own_field, opp_guess->row, opp_guess->col)){
        case FIELD_SQUARE_SMALL_BOAT:
            own_field->smallBoatLives--;
            FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, FIELD_SQUARE_HIT);
            break;
        case FIELD_SQUARE_MEDIUM_BOAT:
            own_field->mediumBoatLives--;
            FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, FIELD_SQUARE_HIT);
            break;
        case FIELD_SQUARE_LARGE_BOAT:
            own_field->largeBoatLives--;
            FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, FIELD_SQUARE_HIT);
            break;
        case FIELD_SQUARE_HUGE_BOAT:
            own_field->hugeBoatLives--;
            FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, FIELD_SQUARE_HIT);
            break;
        default:
            FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, FIELD_SQUARE_MISS);
    }
    return returnVar;

}

SquareStatus FieldUpdateKnowledge(Field *opp_field, const GuessData *own_guess){
    SquareStatus returnVar = FieldGetSquareStatus(opp_field, own_guess->row, own_guess->col);
    switch(own_guess->result){
        case RESULT_HIT:
            opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
            break;
            
        case RESULT_MISS:
            opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_EMPTY;
            break;
            
        case RESULT_SMALL_BOAT_SUNK:
            opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
            opp_field->smallBoatLives = 0;
            break;
            
        case RESULT_MEDIUM_BOAT_SUNK:
            opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
            opp_field->mediumBoatLives = 0;
            break;
            
        case RESULT_LARGE_BOAT_SUNK:
            opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
            opp_field->largeBoatLives = 0;
            break;
            
        case RESULT_HUGE_BOAT_SUNK:
            opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
            opp_field->hugeBoatLives = 0;
            break;
            
    }
    return returnVar;
}

uint8_t FieldGetBoatStates(const Field *f){
    uint8_t returnVar = 0x00;
    if(f->smallBoatLives > 0){
        returnVar | FIELD_BOAT_STATUS_SMALL;
    }
    if(f->mediumBoatLives > 0){
        returnVar | FIELD_BOAT_STATUS_MEDIUM;
    }
    if(f->largeBoatLives > 0){
        returnVar | FIELD_BOAT_STATUS_LARGE;
    }
    if(f->hugeBoatLives > 0){
        returnVar | FIELD_BOAT_STATUS_HUGE;
    }
    return returnVar;
}

uint8_t FieldAIPlaceAllBoats(Field *own_field){
    static uint8_t smallBoat = TRUE, mediumBoat = TRUE, largeBoat = TRUE, hugeBoat = TRUE;
    int i, j, k;
    BoatDirection currentDir = FIELD_DIR_EAST;
    BoatType currentBoat;
        
    start:
        if(hugeBoat = TRUE){
        currentBoat = FIELD_BOAT_TYPE_HUGE; 
        }
        else if(largeBoat = TRUE){
            currentBoat = FIELD_BOAT_TYPE_LARGE; 
        }
        else if(mediumBoat = TRUE){
            currentBoat = FIELD_BOAT_TYPE_MEDIUM; 
        }
        else{
            currentBoat = FIELD_BOAT_TYPE_SMALL; 
        }
        for(i = 0; i < FIELD_ROWS; i++){
            for(j = 0; j < FIELD_COLS; j++){
                currentDir = FIELD_DIR_EAST;
                goto mid;
                mid:
                    if(FieldAddBoat(own_field, i, j, currentDir, currentBoat) != STANDARD_ERROR){
                        FieldAddBoat(own_field, i, j, currentDir, currentBoat);
                        goto intermediary;
                    }
                    else{
                        if(currentDir == FIELD_DIR_EAST){
                            currentDir = FIELD_DIR_SOUTH;
                            goto mid;
                        }
                        else{
                            continue;
                        }
                    }
            }   
        }
    goto decision;
         
    intermediary:
        if(currentBoat == FIELD_BOAT_TYPE_HUGE){
            hugeBoat = FALSE;
        }
        else if(currentBoat == FIELD_BOAT_TYPE_LARGE){
            largeBoat = FALSE;
        }
        else if(currentBoat == FIELD_BOAT_TYPE_MEDIUM){
            mediumBoat = FALSE;
        }
        else{
            smallBoat = FALSE;
            goto decision;
        }
        currentDir = FIELD_DIR_EAST;
        goto start;
    
    decision:
        if(smallBoat == TRUE | mediumBoat == TRUE | largeBoat == TRUE | hugeBoat == TRUE){
            return STANDARD_ERROR;
        }
        else{
            return SUCCESS;
        }
    
    
        
    

   
    
}
