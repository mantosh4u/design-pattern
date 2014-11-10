#include"Common.h"

class MazeFactory {
public:
	static MazeFactory* GetInstance();
	virtual Maze* MakeMaze() const
	{
		return new Maze;
	}
	virtual Wall* MakeWall() const
	{
		return new Wall;
	}
	virtual Room* MakeRoom(int n) const
	{
		return new Room(n);
	}
	virtual Door* MakeDoor(Room* r1, Room* r2) const
	{
		return new Door(r1, r2);
	}
protected:
	MazeFactory();
private:
	static MazeFactory* _instance;
};

MazeFactory* MazeFactory::_instance = nullptr;


MazeFactory::MazeFactory(){
}

MazeFactory* MazeFactory::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MazeFactory;
	}
	return _instance;
}







class MazeGame {
public:
	MazeGame();
	Maze* CreateMaze(MazeFactory& factory);
};


MazeGame::MazeGame() {
}


Maze* MazeGame::CreateMaze(MazeFactory& factory) {
	Maze* aMaze = factory.MakeMaze();
	Room* r1 = factory.MakeRoom(SingletonNumberGenerator::Instance());
	Room* r2 = factory.MakeRoom(SingletonNumberGenerator::Instance());
	Door* aDoor = factory.MakeDoor(r1, r2);

	aMaze->AddRoom(r1);
	aMaze->AddRoom(r2);

	r1->SetSide(North, factory.MakeWall());
	r1->SetSide(East, aDoor);
	r1->SetSide(South, factory.MakeWall());
	r1->SetSide(West, factory.MakeWall());

	r2->SetSide(North, factory.MakeWall());
	r2->SetSide(East, factory.MakeWall());
	r2->SetSide(South, factory.MakeWall());
	r2->SetSide(West, aDoor);

	return aMaze;
}

