//placement.h
#ifndef PLACEMENT_H
#define PLACEMENT_H
#include "general.h"

void Game_RunPlacementPhase(Game *game); //starts a placement phase
bool Game_IsValidMove(Game *game, int r, int c); // checks the validity in the placement phase (row, column)
void Game_PlayTurn(Game *game, int playerNum); // assigns a player to make a move and updates number of fishes and the state of the board, calls Game_IsValidMove function
void clear_input_buffer(); // clears input in the buffer
#endif