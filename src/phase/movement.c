#include "movement.h"
#include "print.h"
#include "placement.h"
#include "file_io.h"
#include "general.h"
void Game_RunMovementPhase(Game *game){

    printf("\n--- MOVEMENT PHASE START ---\n");
    
    int currentPlayer = 1;

    while (true) {
        bool canP1Move = Game_CanPlayerMove(game, 1);
        bool canP2Move = Game_CanPlayerMove(game, 2);

        // --- END GAME CHECK ---
        if (!canP1Move && !canP2Move) {
            printf("Both players are stuck! Game over.\n");
            break;
        }

        
        if (currentPlayer == 1) {
            if (canP1Move) {
                Game_Print(game);
                Game_PlayMovementTurn(game, 1);
            } else {
                printf("\nPlayer 1 has no available moves!\n");
            }
            currentPlayer = 2;
        }
        
        else {
            if (canP2Move) {
                Game_Print(game);
                Game_PlayMovementTurn(game, 2);
            } else {
                printf("\nPlayer 2 has no available moves!\n");
            }
            currentPlayer = 1;
        }
    }

    
    printf("\n--- MOVEMENT PHASE FINISHED ---\n");
    printf("Final Score:\n");
    printf("  Player 1: %d\n", game->score1);
    printf("  Player 2: %d\n", game->score2);

    if (game->score1 > game->score2) {
        printf("Player 1 WINS!\n");
    } else if (game->score2 > game->score1) {
        printf("Player 2 WINS!\n");
    } else {
        printf("It's a TIE!\n");
    }

}
bool Game_CanPlayerMove(Game *game, int playernum){

    // find a penguin to start from
    for (int r = 0; r < game->rows; r++) {
        for (int c = 0; c < game->columns; c++) {
            
            // Found one of the player's penguins
            if (game->board[r][c].owner == playernum) {
                
                // check the 4 directions
                if(game->board[r+1][c].fish != 0 && game->board[r+1][c].owner == 0){
                    return true;
                }
                if(game->board[r-1][c].fish != 0 && game->board[r-1][c].owner == 0){
                    return true;
                }
                if(game->board[r][c+1].fish != 0 && game->board[r][c+1].owner == 0){
                    return true;
                }    
                if(game->board[r][c-1].fish != 0 && game->board[r][c-1].owner == 0){
                    return true;
                }                                            
            }
        }
    }

    return false;
}
void Game_PlayMovementTurn(Game *game, int playernum){
    int r1, c1, r2, c2;
    bool valid = false;

    printf("\nPlayer %d's turn to MOVE.\n", playernum);
    if (game->typeofgame == 'B' && playernum == 2) // Random Bot B
    {
        typedef struct { int r1, c1, r2, c2; } Move;
        Move moves[1000]; // Array to store all possible legal moves
        int moveCount = 0;

        // 1. Scan the board to find all possible moves for all penguins
        for (int i = 0; i < game->rows; i++) {
            for (int j = 0; j < game->columns; j++) {
                if (game->board[i][j].owner == playernum) {
                    
                    // Directions: Down, Up, Right, Left
                    int dr[] = {1, -1, 0, 0};
                    int dc[] = {0, 0, 1, -1};

                    for (int dir = 0; dir < 4; dir++) {
                        int nr = i + dr[dir];
                        int nc = j + dc[dir];

                        // Slide in the direction as long as it's valid
                        while (nr >= 0 && nr < game->rows && nc >= 0 && nc < game->columns &&
                               game->board[nr][nc].fish > 0 && game->board[nr][nc].owner == 0) {
                            
                            moves[moveCount++] = (Move){i, j, nr, nc};
                            
                            nr += dr[dir];
                            nc += dc[dir];
                        }
                    }
                }
            }
        }

        // 2. If moves exist, pick one at random
        if (moveCount > 0) {
            int pick = rand() % moveCount;
            r1 = moves[pick].r1;
            c1 = moves[pick].c1;
            r2 = moves[pick].r2;
            c2 = moves[pick].c2;

            int points = game->board[r2][c2].fish;
            game->score2 += points;

            game->board[r2][c2].owner = playernum;
            game->board[r2][c2].fish = 0;
            game->board[r1][c1].owner = 0;
            game->board[r1][c1].fish = 0;

            printf("Bot B randomly moved from (%d,%d) to (%d,%d) and scored %d points.\n",
                   r1, c1, r2, c2, points);
        }
    }
    else if(game->typeofgame == 'b' && playernum == 2)// bot moving in movement phase
    {
        bool penguinandmovefound = 0;
        for(int i=0; i <game->rows; i++)
        {
            for(int j=0; j < game->columns; j++)
            {
                if(game->board[i][j].owner == playernum)
                {
                    r1 = i;
                    c1 = j;
                    bool movefound=0;
                    if(game->board[r1+1][c1].fish != 0 && game->board[r1+1][c1].owner == 0 && !movefound){
                        r2=r1+1;
                        c2=c1;
                        movefound=1;
                    }
                    if(game->board[r1-1][c1].fish != 0 && game->board[r1-1][c1].owner == 0 && !movefound){
                        r2=r1-1;
                        c2=c1;
                        movefound=1;
                    }
                    if(game->board[r1][c1+1].fish != 0 && game->board[r1][c1+1].owner == 0 && !movefound){
                        r2=r1;
                        c2=c1+1;
                        movefound=1;
                    }    
                    if(game->board[r1][c1-1].fish != 0 && game->board[r1][c1-1].owner == 0 && !movefound){
                        r2=r1;
                        c2=c1-1;
                        movefound=1;
                    }                  
                    if(movefound)
                    {
                        int points = game->board[r2][c2].fish; // update points
                        game->score2 += points;
                        
                        game->board[r2][c2].owner = playernum; //update new tile
                        game->board[r2][c2].fish = 0;

                        game->board[r1][c1].owner = 0; // update old tile
                        game->board[r1][c1].fish = 0;
                        printf("Move successful! Player %d moved from (%d,%d) to (%d,%d) and scored %d points.\n",
                            playernum, r1, c1, r2, c2, points);
                        penguinandmovefound = true;
                        break;
                    }
                }
            }
            if(penguinandmovefound) break;
        }
    }
    else// regular mode with not bot
    {
        while (!valid) {
            printf("Enter penguin to move (row col): ");
            if (scanf("%d %d", &r1, &c1) != 2) {
                printf("Error: Invalid input. Please enter numbers only.\n");
                clear_input_buffer();
                continue;
            }

            if (r1 == -1 && c1 == -1) {
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

                printf("Continue playing.\n");
                continue; 
            }

            printf("Enter destination (row col): ");
            if (scanf("%d %d", &r2, &c2) != 2) {
                printf("Error: Invalid input. Please enter numbers only.\n");
                clear_input_buffer();
                continue;
            }

            if (Game_IsValidMovement(game, r1, c1, r2, c2, playernum)) {
                
                int points = game->board[r2][c2].fish;
                
                game->board[r2][c2].owner = playernum;
                game->board[r2][c2].fish = 0;

                game->board[r1][c1].owner = 0;
                game->board[r1][c1].fish = 0; 
                
                if (playernum == 1) {
                    game->score1 += points;
                } else {
                    game->score2 += points;
                }

                printf("Move successful! Player %d moved from (%d,%d) to (%d,%d) and scored %d points.\n",
                    playernum, r1, c1, r2, c2, points);
                    
                valid = true;
            } else {
                printf("Please try your move again.\n");
            }
        }
    }
}


bool Game_IsValidMovement(Game *game, int r1, int c1, int r2, int c2, int playerNum){
    
    if (r1 < 0 || r1 >= game->rows || c1 < 0 || c1 >= game->columns ||
        r2 < 0 || r2 >= game->rows || c2 < 0 || c2 >= game->columns) {
        printf("Error: Coordinates are off the board.\n");
        return false;
    }
    if (game->board[r1][c1].owner != playerNum) {
        printf("Error: You do not have a penguin at (%d, %d).\n", r1, c1);
        return false;
    }
    if (game->board[r2][c2].owner != 0) {
        printf("Error: Destination (%d, %d) is already occupied.\n", r2, c2);
        return false;
    }
    if (game->board[r2][c2].fish == 0) {
        printf("Error: Destination (%d, %d) is water (no fish).\n", r2, c2);
        return false;
    }
    if (r1 != r2 && c1 != c2) {
        printf("Error: Move must be in a straight line (not diagonal).\n");
        return false;
    }
    if (r1 == r2 && c1 == c2) {
        printf("Error: You must move to a different tile.\n");
        return false;
    }
    if (!Game_IsPathClear(game, r1, c1, r2, c2)) {
        printf("Error: Path is blocked by another penguin or a gap.\n");
        return false;
    }
    return true;

}

bool Game_IsPathClear(Game *game, int r1, int c1, int r2, int c2){
    
    if (c1 == c2) {
        if (r1 < r2) { //Down
            for (int r = r1 + 1; r < r2; r++) {
                if (game->board[r][c1].fish == 0 || game->board[r][c1].owner != 0) {
                    return false;
                }
            }
        } else { //UP
            for (int r = r1 - 1; r > r2; r--) {
                if (game->board[r][c1].fish == 0 || game->board[r][c1].owner != 0) {
                    return false;
                }
            }
        }
    }
    else if (r1 == r2) {
        if (c1 < c2) { //Right
            for (int c = c1 + 1; c < c2; c++) {
                if (game->board[r1][c].fish == 0 || game->board[r1][c].owner != 0) {
                    return false;
                }
            }
        } else { //Left
            for (int c = c1 - 1; c > c2; c--) {
                if (game->board[r1][c].fish == 0 || game->board[r1][c].owner != 0) {
                    return false;
                }
            }
        }
    }
    

    return true;
}
