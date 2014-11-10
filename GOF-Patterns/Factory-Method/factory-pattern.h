#include"Common.h"

class MazeGame {
public:
	MazeGame();
	Maze* CreateMaze();
	// factory methods:
	virtual Maze* MakeMaze() const
	{
		return new Maze;
	}
	virtual Room* MakeRoom(int n) const
	{
		return new Room(n);
	}
	virtual Wall* MakeWall() const
	{
		return new Wall;
	}
	virtual Door* MakeDoor(Room* r1, Room* r2) const
	{
		return new Door(r1, r2);
	}
};



MazeGame::MazeGame() {
}

Maze* MazeGame::CreateMaze() {
	Maze* aMaze = MakeMaze();
	Room* r1 = MakeRoom(SingletonNumberGenerator::Instance());
	Room* r2 = MakeRoom(SingletonNumberGenerator::Instance());
	Door* aDoor = MakeDoor(r1, r2);

	aMaze->AddRoom(r1);
	aMaze->AddRoom(r2);

	r1->SetSide(North, MakeWall());
	r1->SetSide(East, aDoor);
	r1->SetSide(South, MakeWall());
	r1->SetSide(West, MakeWall());

	r2->SetSide(North, MakeWall());
	r2->SetSide(East, MakeWall());
	r2->SetSide(South, MakeWall());
	r2->SetSide(West, aDoor);

	return aMaze;
}




class BombedWall : public Wall {
};


class RoomWithABomb : public Room {
public:
	RoomWithABomb(int n) : Room(n){
	}
};


class BombedMazeGame : public MazeGame {
public:
	BombedMazeGame();
	Maze* CreateMaze();
	virtual Wall* MakeWall() const
	{
		return new BombedWall;
	}
	virtual Room* MakeRoom(int n) const
	{
		return new RoomWithABomb(n);
	}

};


BombedMazeGame::BombedMazeGame() {
}


Maze* BombedMazeGame::CreateMaze() {

	Maze* aMaze = MakeMaze();
	Room* r1 = MakeRoom(SingletonNumberGenerator::Instance());
	Room* r2 = MakeRoom(SingletonNumberGenerator::Instance());
	Door* aDoor = MakeDoor(r1, r2);

	aMaze->AddRoom(r1);
	aMaze->AddRoom(r2);

	r1->SetSide(North, MakeWall());
	r1->SetSide(East, aDoor);
	r1->SetSide(South, MakeWall());
	r1->SetSide(West, MakeWall());

	r2->SetSide(North, MakeWall());
	r2->SetSide(East, MakeWall());
	r2->SetSide(South, MakeWall());
	r2->SetSide(West, aDoor);

	return aMaze;
}


