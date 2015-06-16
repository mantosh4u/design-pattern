#ifndef FACTORY_METHOD_H 
#define FACTORY_METHOD_H
#include"creational_pattern.h"


namespace factory_method
{

	//Base Class
	class MazeGame {
	public:
		Maze* CreateMaze();
		// factory methods:
		virtual Maze* MakeMaze() const
		{ return new Maze; }
		virtual Room* MakeRoom(int n) const
		{ return new Room(n); }
		virtual Wall* MakeWall() const
		{ return new Wall; }
		virtual Door* MakeDoor(Room* r1, Room* r2) const
		{ return new Door(r1, r2); }
	};

	Maze* MazeGame::CreateMaze() {
		Maze* aMaze = MakeMaze();

		Room* r1 = MakeRoom(1);
		Room* r2 = MakeRoom(2);
		Door* theDoor = MakeDoor(r1,r2);

		aMaze->AddRoom(r1);
		aMaze->AddRoom(r2);

		r1->SetSide(North, MakeWall());
		r1->SetSide(East, theDoor);
		r1->SetSide(South, MakeWall());
		r1->SetSide(West, MakeWall());

		r2->SetSide(North, MakeWall());
		r2->SetSide(East, MakeWall());
		r2->SetSide(South, MakeWall());
		r2->SetSide(West, theDoor);

		return aMaze;
	}


	//Derive Class which would create different type of room and door.
	class EnchantedMaze: public MazeGame {
	public:
		EnchantedMaze() {}
		virtual Room* MakeRoom(int n) const { return new EnchantedRoom(n);}
		virtual Door* MakeDoor(Room* r1, Room* r2) const { return new DoorNeedingSpell(r1, r2);}
	};



	//Client API
	void creational_factory_method_approach()
	{
		EnchantedMaze game;
		Maze* mz = game.CreateMaze();
		mz->DisplayAllComponent();
		delete mz;
	}

}


#endif
