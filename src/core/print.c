//print.c
#include "print.h"

void Game_Print(Game *game){ // printing the board
    printf("\n");
    printf("    ");
    for(int c=0; c < game->columns; c++){
        printf(" %-2d ", c);
    }
    printf("\n");
    printf("   +");
    for(int c=0; c < game->columns; c++){
        printf("----");
    }
    printf("\n");

    for (int r =0; r < game->rows; r++){
        printf("%2d |", r);

        for (int c=0; c < game->columns; c++){ 
            Tile t=game->board[r][c];
            if (t.owner!=0){//some penguin is on this tile
                printf(" P%d ", t.owner);
            }else if(t.fish==0){
                printf("    ");
            }else {
                printf(" %d  ", t.fish);
            }
        }
        printf("|\n");
    }
    printf("\n   Scores -> Player 1: %d | Player 2: %d\n", game->score1, game->score2);
}