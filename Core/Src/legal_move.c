#include "legal_move.h"
#include <stdint.h>
#include "game.h"
#include "stm32h750b_discovery_lcd.h"
#include "display.h"

//player1: id: 0 ---> liveBoard: 1
//player2: id: 1 ---> liveBoard: 5


int liveBoard[3][3];
int squaresFilled = 0;

void MG_empty_square(int32_t x, int32_t y){

    if(liveBoard[y][x] != 0) return;

    if(playerOnMove == 0){
        liveBoard[y][x] = 1;
        squaresFilled++;

        MG_Playscreen_DrawX(x,y, LCD_COLOR_ARGB8888_RED);
        playerOnMove = 1;
    }else{
        liveBoard[y][x] = 5;
        squaresFilled++;

        MG_Playscreen_DrawCircle(x,y, LCD_COLOR_ARGB8888_BLUE);
        playerOnMove = 0;
    } 

    //TODO implemetiraj logiko:
    // preveri ce ima kateri igralec 3 v vrsto
    // ce so vsa polja zapolnjena in ni zmagovalca te vrze nazaj na homescreen in rece da je draw


}
