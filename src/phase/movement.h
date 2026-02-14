#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "general.h"

void Game_RunMovementPhase(Game *game); //assign a player to make a move, until no player can make a move
bool Game_CanPlayerMove(Game *game, int playernum);//checks if any of the player's penguin can make a legal move
void Game_PlayMovementTurn(Game *game, int playernum);// allows player to make an input to make a move, calls the Game_IsValidMovement function 
bool Game_IsValidMovement(Game *game, int r1, int c1, int r2, int c2, int playerNum);// checks if a move is valid (starting row and columns, final rown and column), calls Game_IsPathClear function
bool Game_IsPathClear(Game *game, int r1, int c1, int r2, int c2); // checks if from (starting row and column) to (final row and column) is clean path - no gap or other penguin

#endif