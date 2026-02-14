#include "file_io.h"
#include <stdio.h>

void Game_SaveBoard(Game *game, char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error: Could not save file.\n");
        return;
    }

    fprintf(f, "%d %d %d %c\n", game->rows, game->columns, game->penguins_per_player, game->typeofgame);
    
    fprintf(f, "%d %d %d %d\n", game->score1, game->score2, game->penguins_placed1, game->penguins_placed2);

    for (int r = 0; r < game->rows; r++) {
        for (int c = 0; c < game->columns; c++) {
            fprintf(f, "%d %d ", game->board[r][c].fish, game->board[r][c].owner);
        }
        fprintf(f, "\n"); 
    }

    fclose(f);
    printf("Game saved to %s!\n", filename);
}

bool Game_LoadBoard(Game *game, char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error: Could not open file.\n");
        return false;
    }

    if (fscanf(f, "%d %d %d %c", &game->rows, &game->columns, &game->penguins_per_player, &game->typeofgame) != 4) {
        fclose(f); return false;
    }

    if (fscanf(f, "%d %d %d %d", &game->score1, &game->score2, &game->penguins_placed1, &game->penguins_placed2) != 4) {
        fclose(f); return false;
    }

    for (int r = 0; r < game->rows; r++) {
        for (int c = 0; c < game->columns; c++) {
            fscanf(f, "%d %d", &game->board[r][c].fish, &game->board[r][c].owner);
        }
    }

    fclose(f);
    printf("Game loaded successfully!\n");
    return true;
}