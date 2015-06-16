#ifndef BUIILDER_H
#define BUIILDER_H
#include"creational_pattern.h"

namespace builder
{
	//Base Class
	class MazeBuilder {
	public:
		virtual ~MazeBuilder() {}
		virtual void BuildMaze() { }
		virtual void BuildRoom(int room) { }
		virtual void BuildDoor(int roomFrom, int roomTo) { }
		virtual Maze* GetMaze() { return 0; }
	protected:
		MazeBuilder() {}
	};


	//Derrive Class
	class StandardMazeBuilder : public MazeBuilder {
	public:
		StandardMazeBuilder():_currentMaze(NULL) {}
		virtual ~StandardMazeBuilder() {}
		virtual void BuildMaze();
		virtual void BuildRoom(int);
		virtual void BuildDoor(int, int);
		virtual Maze* GetMaze() { return _currentMaze; }
	private:
		Direction CommonWall(Room*, Room*);
		Maze* _currentMaze;
	};

	void StandardMazeBuilder::BuildMaze()
	{
		_currentMaze = new Maze;
	}

	void StandardMazeBuilder::BuildRoom(int n) 
	{
		if(!_currentMaze->RoomNo(n)) {
			Room* room = new Room(n);
			_currentMaze->AddRoom(room);

			room->SetSide(North, new Wall);
			room->SetSide(South, new Wall);
			room->SetSide(East, new Wall);
			room->SetSide(West, new Wall);
		}
	}


	void StandardMazeBuilder::BuildDoor(int n1,int n2)
	{
		Room* r1 = _currentMaze->RoomNo(n1);
		Room* r2 = _currentMaze->RoomNo(n2);
		Door* d = new Door(r1, r2);

		r1->SetSide(CommonWall(r1,r2), d);
		r2->SetSide(CommonWall(r2,r1), d);
	}

	// CommonWall is a utility operation that determines the direction of the common wall between two rooms.
	Direction StandardMazeBuilder::CommonWall(Room* r1, Room* r2)
	{
		//TBD: What does it means?
		return North;
	}



	class MazeGame {
	public:
		MazeGame() {}
		~MazeGame() {}
		Maze* CreateMaze(MazeBuilder& builder);
	};


	Maze*	MazeGame::CreateMaze(MazeBuilder& builder)
	{
		builder.BuildMaze();
		builder.BuildRoom(1);
		builder.BuildRoom(2);
		builder.BuildDoor(1,2);
		return (builder.GetMaze());
	}


	//Another Derived Class of Builder
	class CountingMazeBuilder : public MazeBuilder {
	public:
		CountingMazeBuilder():_doors(0),_rooms(0) {}
		virtual ~CountingMazeBuilder() {}
		virtual void BuildMaze() {}
		virtual void BuildRoom(int);
		virtual void BuildDoor(int, int);
		virtual void AddWall(int, Direction) {}
		void GetCounts(int&, int&) const;
	private:
		int _doors;
		int _rooms;
	};

	void CountingMazeBuilder::BuildRoom(int n) {
		_rooms++;
	}

	void CountingMazeBuilder::BuildDoor(int n1, int n2) {
		_doors++;
	}

	void CountingMazeBuilder::GetCounts(int& rooms, int& doors) const {
		rooms = _rooms;
		doors = _doors;
	}


	//Client API
	void creational_builder_approach()
	{

		//Maze* maze;
		//MazeGame game;
		//StandardMazeBuilder aBuilder;
		//game.CreateMaze(aBuilder);
		//maze = aBuilder.GetMaze();
		//maze->DisplayAllComponent();
		//delete maze;

		int rooms;
		int doors;
		MazeGame game;
		CountingMazeBuilder builder;
		game.CreateMaze(builder);
		builder.GetCounts(rooms, doors);
		std::cout << "The maze has " << rooms << " rooms and " << doors << " doors" << std::endl;
	}
}
#endif
