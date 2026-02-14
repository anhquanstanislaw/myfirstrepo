//general.h
#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct{
    int fish;
    int owner;
}Tile; // state of each tile (number of fish and owner)

typedef struct{
    int rows;
    int columns;
    int penguins_per_player;

    Tile board[50][50];
    int score1;
    int score2;
    int penguins_placed1;
    int penguins_placed2;
    char typeofgame; //value r is regular, value b is against bot;
}Game; // state of the game

#endif