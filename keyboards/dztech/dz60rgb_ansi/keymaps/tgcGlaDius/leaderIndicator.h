#include "print.h"

#pragma once

#define INDIC_ROWS MATRIX_ROWS
#define INDIC_COLLS MATRIX_COLS

#define CODESIZE sizeof(uint16_t)
#define ROW_SIZE (MATRIX_COLS*CODESIZE)
#define LAYER_SIZE (MATRIX_COLS*ROW_SIZE)

uint16_t readCodeAt(uint8_t layer, uint8_t row, uint8_t column){
    return pgm_read_word(&(keymaps[layer][row][column]));
}

const uint8_t rowStarts[INDIC_ROWS] = {0, INDIC_COLLS, INDIC_COLLS*2, (INDIC_COLLS*3)-1, (INDIC_COLLS*4)-3};
uint8_t keymapPosToRGBIndex(uint8_t row, uint8_t column){
    uint8_t offset = 0;
    if(row ==2 && column < 12){
        offset = 1;
    }
    else if( row == 3 && column < 12){
        offset = 2;
    }
    else if(row == 4){
        if(column<12){
            offset = 1;
        }
        if(column < 6){
            offset += 3;
        }
        if(column < 3){
            offset += 2;
        }
    }
    return rowStarts[row]+(INDIC_COLLS-offset-column-1);
}

bool leaderIndicator[DRIVER_LED_TOTAL] ={false,};

void activateCode(uint16_t code){
    for(int r = 0; r<INDIC_ROWS; r++){
        for(int c = 0; c<INDIC_COLLS; c++){
            if(readCodeAt(0,r,c) == code){
                leaderIndicator[keymapPosToRGBIndex(r,c)] = true;
            }
        }
    }
}

void clearLeaderIndicator(void){
    for(int r = 0; r<INDIC_ROWS; r++){
        for(int c = 0; c<INDIC_COLLS; c++){
            leaderIndicator[keymapPosToRGBIndex(r,c)] = false;
        }
    }
}

void highlightLeaderIdicator(void){
    for(int i = 0; i<DRIVER_LED_TOTAL; i++){
        if(leaderIndicator[i]){
            rgb_matrix_set_color(i,255,255,255);
        }
    }
}
