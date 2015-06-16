#ifndef ABSTRACT_FACTORY_H 
#define ABSTRACT_FACTORY_H

#include"creational_pattern.h"

namespace abstract_factory
{
	//Base Class
	class MazeFactory {
	public:
		static MazeFactory* GetInstance();
		virtual Maze* MakeMaze() const { return new Maze;}
		virtual Wall* MakeWall() const { return new Wall;}
		virtual Room* MakeRoom(int n) const { return new Room(n);}
		virtual Door* MakeDoor(Room* r1, Room* r2) const { return new Door(r1, r2);}
	protected:
		MazeFactory() {}
	private:
		static MazeFactory* _instance;
	};

	MazeFactory* MazeFactory::_instance = NULL;

	MazeFactory* MazeFactory::GetInstance () {
		if (_instance == NULL) {
			_instance = new MazeFactory;
		}
		return _instance;
	}

	//Derive Class
	class EnchantedMazeFactory: public MazeFactory {
	public:
		EnchantedMazeFactory() {}
		virtual Maze* MakeMaze() const { return new Maze;}
		virtual Wall* MakeWall() const { return new Wall;}
		virtual Room* MakeRoom(int n) const { return new EnchantedRoom(n);}
		virtual Door* MakeDoor(Room* r1, Room* r2) const { return new DoorNeedingSpell(r1, r2);}
	};

	
	//MazeGame Creation Class
	class MazeGame {
	public:
		MazeGame() {}
		~MazeGame() {}
		Maze* CreateMaze(MazeFactory& factory);
	};

	/*
	*
	// Does Not Make Sense if we compare this code with above conventional code
	// However this method is parameterized with MazeFactory instance which means
	// if you want to change/replace with some other type of factory, the below code
	// would produce totaly different type of product without changing a single bit
	// of the below code.
	*
	*/

	Maze*	MazeGame::CreateMaze(MazeFactory& factory) {
		Maze* aMaze = factory.MakeMaze();

		Room* r1 = factory.MakeRoom(1);
		Room* r2 = factory.MakeRoom(2);
		Door* aDoor = factory.MakeDoor(r1,r2);

		aMaze->AddRoom(r1);
		aMaze->AddRoom(r2);

		r1->SetSide(North, factory.MakeWall());
		r1->SetSide(East, aDoor);
		r1->SetSide(South, factory.MakeWall());
		r1->SetSide(West, factory.MakeWall());

		r2->SetSide(North,factory.MakeWall());
		r2->SetSide(East, factory.MakeWall());
		r2->SetSide(South,factory.MakeWall());
		r2->SetSide(West, aDoor);

		return aMaze;	
	}

	//Client API
	void creational_abstract_factory_approach()
	{
		abstract_factory::EnchantedMazeFactory aFactory;
		abstract_factory::MazeGame game;
		Maze* mz = game.CreateMaze(aFactory);
		mz->DisplayAllComponent();

		// Now do some additional stuff which and fetch the room number 
		Room* r = mz->RoomNo(1);
		if(r) 
		{
			MapSite* nsite = r->GetSide(North);
			MapSite* ssite = r->GetSide(South);
			MapSite* esite = r->GetSide(East);
			MapSite* wsite = r->GetSide(West);

			nsite->Enter();
			ssite->Enter();
			esite->Enter();
			wsite->Enter();			
		}
		delete mz;		
	}
}


#endif
