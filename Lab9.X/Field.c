
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Field.h"
#include "BOARD.h"


//#define MAX_BOAT_ON_FIELD 1

void FieldPrint_Helper(Field *field, int currentRow);
void FieldPrint_Helper(Field *field, int currentRow){
    int initial;
    for(initial = 0; initial < FIELD_COLS; initial++){
        switch(FieldGetSquareStatus(field, currentRow, initial)){
            case FIELD_SQUARE_EMPTY:
                printf(" .");
                break;
            case FIELD_SQUARE_SMALL_BOAT:
                printf(" 3");
                break;
            case FIELD_SQUARE_MEDIUM_BOAT:
                printf(" 4");
                break;
            case FIELD_SQUARE_LARGE_BOAT:
                printf(" 5");
                break;
            case FIELD_SQUARE_HUGE_BOAT:
                printf(" 6");
                break;
            case FIELD_SQUARE_HIT:
                printf(" X");
                break;
            case FIELD_SQUARE_MISS:
                printf(" O");
                break;
            default:
                printf(" .");
        }
    }
}


void FieldPrint_UART(Field *own_field, Field * opp_field){
    
    int initial;
    int currentRow = 0;
    printf("Your own Field:\n    0 1 2 3 4 5 6 7 8 9\n    ---------------------\n");
    printf(" 0[");
    FieldPrint_Helper(own_field, currentRow);
    currentRow++;
    printf(" ]\n");
    printf(" 1[");
    FieldPrint_Helper(own_field, currentRow);
    currentRow++;
    printf(" ]\n");
    printf(" 2[");
    FieldPrint_Helper(own_field, currentRow);
    currentRow++;
    printf(" ]\n");
    printf(" 3[");
    FieldPrint_Helper(own_field, currentRow);
    currentRow++;
    printf(" ]\n");
    printf(" 4[");
    FieldPrint_Helper(own_field, currentRow);
    currentRow++;
    printf(" ]\n");
    printf(" 5[");
    FieldPrint_Helper(own_field, currentRow);
    printf(" ]\n\n\nOpponent's Field:\n");
    currentRow = 0;
    
    printf("    0 1 2 3 4 5 6 7 8 9\n    ---------------------\n");
    printf(" 0[");
    FieldPrint_Helper(opp_field, currentRow);
    currentRow++;
    printf(" ]\n");
    printf(" 1[");
    FieldPrint_Helper(opp_field, currentRow);
    currentRow++;
    printf(" ]\n");
    printf(" 2[");
    FieldPrint_Helper(opp_field, currentRow);
    currentRow++;
    printf(" ]\n");
    printf(" 3[");
    FieldPrint_Helper(opp_field, currentRow);
    currentRow++;
    printf(" ]\n");
    printf(" 4[");
    FieldPrint_Helper(opp_field, currentRow);
    currentRow++;
    printf(" ]\n");
    printf(" 5[");
    FieldPrint_Helper(opp_field, currentRow);
    printf(" ]\n");
    
    
    
    
    
        
    
    
   

}

void FieldInit(Field *own_field, Field *opp_field){
    int i, j;
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
    int addBoatSize;
    SquareStatus currentStatus;
    if(row < FIELD_ROWS && row > 0 && col < FIELD_COLS && col >= 0){ 
        switch(boat_type){
            case FIELD_BOAT_TYPE_SMALL:
                addBoatSize = FIELD_BOAT_SIZE_SMALL - 1;
                currentStatus = FIELD_SQUARE_SMALL_BOAT;
                break;
            case FIELD_BOAT_TYPE_MEDIUM:
                addBoatSize = FIELD_BOAT_SIZE_MEDIUM - 1;
                currentStatus = FIELD_SQUARE_MEDIUM_BOAT;
                break;
            case FIELD_BOAT_TYPE_LARGE:
                addBoatSize = FIELD_BOAT_SIZE_LARGE - 1;
                currentStatus = FIELD_SQUARE_LARGE_BOAT;
                break;
            case FIELD_BOAT_TYPE_HUGE:
                addBoatSize = FIELD_BOAT_SIZE_HUGE - 1;
                currentStatus = FIELD_SQUARE_HUGE_BOAT;
                break;
    }
    
        if(dir == FIELD_DIR_SOUTH){
            if(row + addBoatSize < FIELD_ROWS){
                int i;
                for(i = 0; i < addBoatSize + 1; i++){
                    own_field->grid[row + i][col] = currentStatus;
                }
                goto lives;
            }
            else{
                return STANDARD_ERROR;
            }
        }
        else{
            if(col + addBoatSize < FIELD_COLS){
                int l;
                for(l = 0; l < addBoatSize + 1; l++){
                    own_field->grid[row][col + l] = currentStatus;
                }
                goto lives;
            }
            else{
                return STANDARD_ERROR;
            }
        }
        lives:
                switch(boat_type){
                    case FIELD_BOAT_TYPE_SMALL:
                        own_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
                        break;
                    case FIELD_BOAT_TYPE_MEDIUM:
                        own_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
                        break;
                    case FIELD_BOAT_TYPE_LARGE:
                        own_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
                        break;
                    case FIELD_BOAT_TYPE_HUGE:
                        own_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
                        break;
                }
                return SUCCESS;
        
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
            opp_guess->result = FIELD_SQUARE_HIT;
            break;
        case FIELD_SQUARE_MEDIUM_BOAT:
            own_field->mediumBoatLives--;
            FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, FIELD_SQUARE_HIT);
            opp_guess->result = FIELD_SQUARE_HIT;
            break;
        case FIELD_SQUARE_LARGE_BOAT:
            own_field->largeBoatLives--;
            FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, FIELD_SQUARE_HIT);
            opp_guess->result = FIELD_SQUARE_HIT;
            break;
        case FIELD_SQUARE_HUGE_BOAT:
            own_field->hugeBoatLives--;
            FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, FIELD_SQUARE_HIT);
            opp_guess->result = FIELD_SQUARE_HIT;
            break;
        default:
            FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, FIELD_SQUARE_MISS);
            opp_guess->result = FIELD_SQUARE_MISS;
            
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
            opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_MISS;
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
        returnVar |= FIELD_BOAT_STATUS_SMALL;
    }
    if(f->mediumBoatLives > 0){
        returnVar |= FIELD_BOAT_STATUS_MEDIUM;
    }
    if(f->largeBoatLives > 0){
        returnVar |= FIELD_BOAT_STATUS_LARGE;
    }
    if(f->hugeBoatLives > 0){
        returnVar |= FIELD_BOAT_STATUS_HUGE;
    }
    return returnVar;
}

uint8_t FieldAIPlaceAllBoats(Field *own_field){
    int smallBoat = 1, sBoat = 1, mediumBoat = 1, mBoat = 2, largeBoat = 1, lBoat = 3, hugeBoat = 1, hBoat = 4;
    srand(time(NULL));
    int randomGen, randomRow, randomCol;
    BoatType currentBoatType;
    BoatDirection currentBoatDir = FIELD_DIR_EAST;
    randomGen = rand();
    randomGen &= (0x03);
    while(smallBoat + mediumBoat + largeBoat + hugeBoat > 0){
        if(randomGen == sBoat & smallBoat != 0){
            currentBoatType = FIELD_BOAT_TYPE_SMALL;
            smallBoat = 0;
        }
        else if(randomGen == mBoat & mediumBoat != 0){
            currentBoatType = FIELD_BOAT_TYPE_MEDIUM;
            mediumBoat = 0;
        }
        else if(randomGen == lBoat & largeBoat != 0){
            currentBoatType = FIELD_BOAT_TYPE_LARGE;
            largeBoat = 0;
        }
        else if(randomGen == hBoat & hugeBoat != 0){
            currentBoatType = FIELD_BOAT_TYPE_HUGE;
            hugeBoat = 0;
        }
        while(1){
            randomRow = rand() % 5;
            randomCol = rand() % 9;
            if(FieldAddBoat(own_field, randomRow, randomCol, FIELD_DIR_EAST, currentBoatType) + FieldAddBoat(own_field, randomRow, randomCol, FIELD_DIR_SOUTH, currentBoatType) == 0){
              continue;  
            }
            
        }
   
    
    }
    
    
    BoatDirection currentDir = FIELD_DIR_EAST;
    BoatType currentBoat;
        
   
    
    /*
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
    
    
        */
    

   
    
}
