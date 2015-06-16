#ifndef PROTOTYPE_H
#define PROTOTYPE_H
#include"creational_pattern.h"


namespace prototype
{
	
	class RoomWithPrototypeSupport: public Room {
	public:
		RoomWithPrototypeSupport() {}
		RoomWithPrototypeSupport(int n): Room(n) {}
		virtual ~RoomWithPrototypeSupport() {}
		void Initialize(int n) {
			_roomNumber = n;
		}
		virtual RoomWithPrototypeSupport* Clone() const { return(new RoomWithPrototypeSupport(*this));}
	};

	
	class WallWithPrototypeSupport: public Wall {
	public:
		WallWithPrototypeSupport() {}
		virtual ~WallWithPrototypeSupport() {}	
		virtual WallWithPrototypeSupport* Clone() const { return (new WallWithPrototypeSupport(*this));}
	};


	class DoorWithPrototypeSupport: public Door {
	public:
		DoorWithPrototypeSupport() {}
		DoorWithPrototypeSupport(Room* r1, Room* r2): Door(r1, r2) {}
		virtual ~DoorWithPrototypeSupport() {}
		virtual void Initialize(Room* r1, Room* r2) {
			_room1 = r1;
			_room2 = r2;
		}
		virtual DoorWithPrototypeSupport* Clone() const { return (new DoorWithPrototypeSupport(*this));}
	};


	class MazePrototypeSupport: public Maze {
	public:
		MazePrototypeSupport() {}
		virtual ~MazePrototypeSupport() {}
		virtual MazePrototypeSupport* Clone() const { return (new MazePrototypeSupport(*this)); }		
	};


	// Base Class
	class MazeFactory {
	public:
		MazeFactory() {}
		virtual MazePrototypeSupport*      MakeMaze() const { return new MazePrototypeSupport; }
		virtual WallWithPrototypeSupport*  MakeWall() const { return new WallWithPrototypeSupport; }
		virtual RoomWithPrototypeSupport*  MakeRoom(int n) const { return new RoomWithPrototypeSupport(n); }
		virtual DoorWithPrototypeSupport*  MakeDoor(Room* r1, Room* r2) const { return new DoorWithPrototypeSupport(r1, r2); }
	};


	// Derived Class
	class MazePrototypeFactory: public MazeFactory {
	public:
		MazePrototypeFactory(MazePrototypeSupport*, 
							WallWithPrototypeSupport*, 
							RoomWithPrototypeSupport*, 
							DoorWithPrototypeSupport*);
		virtual ~MazePrototypeFactory() {}
		virtual MazePrototypeSupport*     MakeMaze() const;
		virtual WallWithPrototypeSupport* MakeWall() const;
		virtual RoomWithPrototypeSupport* MakeRoom(int) const;
		virtual DoorWithPrototypeSupport* MakeDoor(Room*, Room*) const;
	private:
		MazePrototypeSupport*	    _prototypeMaze;
		WallWithPrototypeSupport*	_prototypeWall;
		RoomWithPrototypeSupport*	_prototypeRoom;
		DoorWithPrototypeSupport*	_prototypeDoor;
	};


	MazePrototypeFactory::MazePrototypeFactory(MazePrototypeSupport* m, 
											   WallWithPrototypeSupport* w, 
											   RoomWithPrototypeSupport* r, 
											   DoorWithPrototypeSupport* d)
	:_prototypeMaze(m),
	 _prototypeWall(w),
	 _prototypeRoom(r),
	 _prototypeDoor(d)
	{
	}

	MazePrototypeSupport* MazePrototypeFactory::MakeMaze() const {
		return (_prototypeMaze->Clone());
	}

	WallWithPrototypeSupport* MazePrototypeFactory::MakeWall() const {
		return (_prototypeWall->Clone());
	}

	RoomWithPrototypeSupport* MazePrototypeFactory::MakeRoom(int n) const {
		RoomWithPrototypeSupport* room =_prototypeRoom->Clone();
		room->Initialize(n);
		return room;
	}

	DoorWithPrototypeSupport* MazePrototypeFactory::MakeDoor(Room* r1, Room* r2) const {
		DoorWithPrototypeSupport* door = _prototypeDoor->Clone();
		door->Initialize(r1, r2);
		return door;
	}


	class MazeGame {
	public:
		MazeGame() {}
		~MazeGame() {}
		MazePrototypeSupport* CreateMaze(MazePrototypeFactory& factory);
	};


	MazePrototypeSupport* MazeGame::CreateMaze(MazePrototypeFactory& factory) {
		MazePrototypeSupport* aMaze = factory.MakeMaze();

		RoomWithPrototypeSupport* r1 = factory.MakeRoom(1);
		RoomWithPrototypeSupport* r2 = factory.MakeRoom(2);
		DoorWithPrototypeSupport* aDoor = factory.MakeDoor(r1,r2);

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
	void creational_prototype_approach()
	{
		MazePrototypeFactory simpleMazeFactory(new MazePrototypeSupport,
											   new WallWithPrototypeSupport, 
											   new RoomWithPrototypeSupport,
											   new DoorWithPrototypeSupport);

		MazeGame game;
		MazePrototypeSupport* maze = game.CreateMaze(simpleMazeFactory);
		maze->DisplayAllComponent();
		return;
	}

}
#endif
