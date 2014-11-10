#include"factory-pattern.h"

int main() {

	MazeGame Game;
	auto maze = Game.CreateMaze();

	BombedMazeGame bGame;
	auto bmaze = bGame.CreateMaze();

	return 0;
}
