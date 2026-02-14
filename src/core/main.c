#include "general.h"
#include "init.h"
#include "placement.h"
#include "print.h"
#include "movement.h"
#include "file_io.h" 

int main() {
    Game myGame = {0}; 
    char choice;

    printf("--- PENGUINS GAME ---\n");
    printf("n - New Game\n");
    printf("l - Load Game\n");
    printf("-1 -1 - Save Game\n");

    printf("Choose: ");
    scanf(" %c", &choice);

    bool loaded = false;

    if (choice == 'l') { //loading game
        char filename[100];
        printf("Enter filename: ");
        scanf("%s", filename);
        if (Game_LoadBoard(&myGame, filename)) {
            loaded = true;
        } else {
            printf("Load failed. Starting new game.\n");
        }
    }

    if (!loaded) {
        Game_Init(&myGame);
    }

    
    if (myGame.penguins_placed1 < myGame.penguins_per_player || 
        myGame.penguins_placed2 < myGame.penguins_per_player) {
            
        printf("\n--- PLACEMENT PHASE ---\n");
        Game_RunPlacementPhase(&myGame);
    } else {
        printf("Skipping placement phase (already done).\n");
    }
    
    Game_Print(&myGame);
    
    printf("\n--- MOVEMENT PHASE ---\n");
    Game_RunMovementPhase(&myGame);

    return 0;
}