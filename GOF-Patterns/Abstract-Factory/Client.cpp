#include"abstract_factory.h"

int main() {

	MazeGame Game;
	MazeFactory* factory = MazeFactory::GetInstance();
	auto maze = Game.CreateMaze(*factory);

	return 0;
}
