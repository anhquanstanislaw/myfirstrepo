
// placement.c
#include "placement.h"
#include "print.h"
#include "file_io.h" 
#include "general.h"
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool Game_IsValidMove(Game *game, int r, int c){ // for placement phase
    if (r < 0 || r >= game->rows || c < 0 || c >= game->columns) { 
        printf("Error: Out of bounds.\n");
        return false;
    }
    if (game->board[r][c].fish != 1) {
        printf("Error: You must choose a tile with exactly 1 fish.\n");
        return false;
    }
    if (game->board[r][c].owner != 0) {
        printf("Error: Tile is already occupied.\n");
        return false;
    }
    return true;
}

void Game_PlayTurn(Game *game, int playerNum) { 
    int r, c;
    bool valid = false;

    printf("\nPlayer %d's turn. Enter row and column: ", playerNum);
    


    if (game->typeofgame == 'B' && playerNum == 2) // case when the random bot moves
    {
        printf("Random Bot is thinking...\n");
        int r, c;
        bool found = false;

        // Keep generating random coordinates until a valid 1-fish tile is found
        while (!found) {
            r = rand() % game->rows;
            c = rand() % game->columns;

            // Use your existing validation logic
            if (game->board[r][c].fish == 1 && game->board[r][c].owner == 0) {
                game->board[r][c].owner = playerNum; 
                int points = game->board[r][c].fish;
                game->board[r][c].fish = 0;
                game->score2 += points;
                game->penguins_placed2++;
                
                printf("Bot B placed a penguin at (%d, %d)\n", r, c);
                found = true;
            }
        }
    }  
    else if(game->typeofgame == 'b' && playerNum == 2) // case when the bot moves
    {
        bool found = 0;
        for(int i=0; i < game->rows; i++)
        {
            for(int j=0; j < game->columns; j++)
            {
                if(game->board[i][j].fish==1 && game->board[i][j].owner==0)
                {
                    game->board[i][j].owner = playerNum; 
                    int points = game->board[i][j].fish;
                    game->board[i][j].fish = 0;
                    game->score2 += points;
                    game->penguins_placed2++;
                    found = 1;
                    break;                    
                }
            }
            if(found) break;            
        }
    } else {// case when typeofgame is normal (without bot)
        while(!valid){
            if (scanf("%d %d", &r, &c) == 2){ 
                
                if (r == -1 && c == -1) {
                    char filename[100];
                    printf("Enter filename to save: ");
                    scanf("%s", filename);
                    Game_SaveBoard(game, filename);
                    
                    printf("Game saved! Do you want to exit? (y/n): ");
                    char choice;
                    scanf(" %c", &choice); 
                    
                    if (choice == 'y' || choice == 'Y') {
                        printf("Exiting game. Bye!\n");
                        exit(0); 
                    }

                    printf("Continue playing. Enter row and column: ");
                    continue; 
                }

                if(Game_IsValidMove(game, r, c)){ 
                    
                    game->board[r][c].owner = playerNum; 
                    int points = game->board[r][c].fish;
                    game->board[r][c].fish = 0;
                    
                    if (playerNum == 1) {
                        game->score1 += points;
                        game->penguins_placed1++;
                    } else {
                        game->score2 += points;
                        game->penguins_placed2++;
                    }
                    valid = true;
                } else {
                    printf("Try Again: ");
                }
            } else {
                printf("Error: Invalid input. Please enter numbers only.\n");
                clear_input_buffer();
                printf("Try again: ");
            }
        }        
    }

}
void Game_RunPlacementPhase(Game *Game){
    while (Game->penguins_placed1 < Game->penguins_per_player || Game->penguins_placed2 < Game->penguins_per_player) {// placing penguin until the right amount of penguin is placed
        
        Game_Print(Game);
        
        if (Game->penguins_placed1 < Game->penguins_per_player) {
            Game_PlayTurn(Game, 1);
            
        }
        
        if (Game->penguins_placed2 < Game->penguins_per_player) {
            Game_Print(Game); 
            Game_PlayTurn(Game, 2);
        }
    }   
}