#include "legal_move.h"
#include <stdint.h>
#include "game.h"
#include "stm32h750b_discovery_lcd.h"
#include "display.h"
#include <stdlib.h>

//player1: id: 0 ---> liveBoard: 1
//player2: id: 1 ---> liveBoard: 5

#define PLAYER0_COLOR LCD_COLOR_ARGB8888_RED
#define PLAYER1_COLOR LCD_COLOR_ARGB8888_BLUE


int liveBoard[4][4];
int diagonala_00_22 = 0;
int diagonala_02_20 = 0;
int squaresFilled = 0;

void MG_empty_square(int32_t x, int32_t y){

    if(liveBoard[y][x] != 0) return;

    uint32_t player_color;
    uint8_t player_num;

    if(playerOnMove == 0){
        player_color = PLAYER0_COLOR;
        player_num = 1;
        playerOnMove = 1;
    }else{
        player_color = PLAYER1_COLOR;
        player_num = 5;
        playerOnMove = 0;
    }

    liveBoard[y][x] = player_num;
    squaresFilled++;

    liveBoard[y][3] += player_num;
    liveBoard[3][x] += player_num;
    if(x == y) diagonala_00_22 += player_num;
    if((x == 1 && x == y) || abs(x-y) == 2) diagonala_02_20 += player_num;

    if(playerOnMove == 1) MG_Playscreen_DrawX(x,y, player_color);
    else  MG_Playscreen_DrawCircle(x,y, player_color);

    //TODO implemetiraj logiko:
    // preveri ce ima kateri igralec 3 v vrsto
    // ce so vsa polja zapolnjena in ni zmagovalca te vrze nazaj na homescreen in rece da je draw
    //ne pozabi clear-at liveBoard-a in squaresFilled nazaj na 0 za novo igro

    for(int i = 0; i < 4; i++){

        if(i != 3 && liveBoard[i][3] == 3) gameStatus = PLAYER1_WIN;
        else if(i != 3 && liveBoard[i][3] == 15) gameStatus = PLAYER2_WIN;

        if(i == 3){
            for(int j = 0; j < 3; j++){
                if(liveBoard[i][j] == 3) gameStatus = PLAYER1_WIN;
                else if(liveBoard[i][j] == 15) gameStatus = PLAYER2_WIN;
            }
        }
    }

    if(diagonala_00_22 == 3) gameStatus = PLAYER1_WIN;
    else if(diagonala_00_22 == 15) gameStatus = PLAYER2_WIN;

    if(diagonala_02_20 == 3) gameStatus = PLAYER1_WIN;
    else if(diagonala_02_20 == 15) gameStatus = PLAYER2_WIN;

    if(squaresFilled == 9 && gameStatus == ONGOING) gameStatus = DRAW;

    if(gameStatus != ONGOING){

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                liveBoard[i][j] = 0;
            }
        }

        squaresFilled = 0;
        diagonala_00_22 = 0;
        diagonala_02_20 = 0;
    }


}
