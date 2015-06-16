#ifndef CREATIONAL_CONVENTIONAL_H
#define CREATIONAL_CONVENTIONAL_H

#include"creational_pattern.h"
/*
*
Now create the game simulation with a scenario of two rooms seprated by a wall.
room1 || room2

N		N          
_______________
W|    E ||W		|E
|______||______|
S		S
*
*/


namespace creational_conventional
{
	class MazeGame {
	public:
		MazeGame() {}
		~MazeGame() {}
		Maze* CreateMaze();
	};

	Maze*	MazeGame::CreateMaze() {
		Maze* aMaze = new Maze;
		Room* r1 = new Room(1);
		Room* r2 = new Room(2);
		Door* theDoor = new Door(r1, r2);

		aMaze->AddRoom(r1);
		aMaze->AddRoom(r2);

		r1->SetSide(North,new Wall);
		r1->SetSide(East, theDoor);
		r1->SetSide(South,new Wall);
		r1->SetSide(West, new Wall);

		r2->SetSide(North,new Wall);
		r2->SetSide(East, new Wall);
		r2->SetSide(South,new Wall);
		r2->SetSide(West, theDoor);
		return aMaze;
	}


	//Client API
	void creational_conventional_approach()
	{
		MazeGame game;
		Maze* mz = game.CreateMaze();
		mz->DisplayAllComponent();
		delete mz;
	}
}

#endif
