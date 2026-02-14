#ifndef FILE_IO_H
#define FILE_IO_H
#include "general.h"

void Game_SaveBoard(Game *game, char *filename);
bool Game_LoadBoard(Game *game, char *filename);

#endif