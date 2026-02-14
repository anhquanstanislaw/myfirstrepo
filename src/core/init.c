//init.c
#include "init.h"

void Game_Init(Game *game){

    
    while(true){
        printf("--- GAME MODE ---\n");
        printf("r - Regular game(2 player)\n");
        printf("b - With Bot game(1 player)\n");
        printf("B - With Bot game(1 player), random plays\n");
        printf("Choose: ");
        scanf(" %c", &game->typeofgame); // b (bot) or r (regular)   
        printf("Enter rows: ");
        scanf("%d", &game->rows);
        printf("Enter columns: ");
        scanf("%d", &game->columns);
        printf("Penguins per player: ");
        scanf("%d", &game->penguins_per_player);
        
        if (game->rows * game->columns < game->penguins_per_player * 4) {// there was a modification from 2 to 4 so oval can be done
            printf("Warning: Board is too small for this many penguins!\n");

        }
        else{
            break;
        }
    }
    game->score1 = 0;
    game->score2 = 0;
    game->penguins_placed1 = 0;
    game->penguins_placed2 = 0;

    srand(time(NULL));
    printf("Generating board......\n");
    
    int ones_count = 0;
    int total_penguins_needed = game->penguins_per_player * 2;
    double a = game->rows / 2.0;  // semi-major axis (horizontal)
    double b = game->columns / 2.0;  // semi-minor axis (vertical)
    double cx = a-1;       // center x
    double cy = b-1;       // center y
    for (int r=0; r < game->rows; r++){
        for (int c=0; c < game->columns; c++){ 
            double xnorm = (r - 1 - cx) / a;
            double ynorm = (c - 1 - cy) / b;
            if (xnorm * xnorm + ynorm * ynorm < 1.0){
                game->board[r][c].fish = rand()%4;
                game->board[r][c].owner = 0;
                
                if (game->board[r][c].fish == 1) {
                    ones_count++;
                }                
            }
            else {
                game->board[r][c].fish = 0;  
                game->board[r][c].owner = 0; 
            }
        }
    }

    while (ones_count < total_penguins_needed) {
        int r = rand() % game->rows;
        int c = rand() % game->columns;

        if (game->board[r][c].fish != 1) {
            game->board[r][c].fish = 1;
            ones_count++;
        }
    }
    printf("Board Generated");
}

