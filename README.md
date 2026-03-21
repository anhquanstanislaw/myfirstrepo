# Penguins Game

## About the Game
Penguins is a turn-based strategy board game for 1 or 2 players. Players control penguins on a board, moving them to collect fish and block opponents. The game supports regular two-player mode and single-player mode against a bot (including a random-move bot).

## How to Compile
1. Open a terminal and navigate to the `src/io` directory:
	```sh
	cd src/io
	```
2. Run the following command to compile the game:
	```sh
	make
	```
	This will produce an executable named `game`.
3. To run the game:
	```sh
	./game
	```
4. To clean up compiled files:
	```sh
	make clean
	```

## Flowchart
The flowchart describing the game logic and phases can be found in the file:
* `flowcharts Jan Kraiński.pdf`

## Game Modes
- **Regular Game**: 2 players
- **Bot Game**: 1 player vs computer
- **Random Bot Game**: 1 player vs random-move bot

Enjoy playing Penguins!
 
## Game Rules (Brief)
- The game is played on a board of tiles, each with 1 or more fish.
- Players take turns placing their penguins on tiles with exactly 1 fish (placement phase).
- After all penguins are placed, players take turns moving their penguins in straight lines (no jumping over gaps or other penguins).
- When a penguin moves, it collects the fish from its starting tile, which is then removed from the board.
- The goal is to collect as many fish as possible. The game ends when no player can make a move.
- The player with the most fish at the end wins.
