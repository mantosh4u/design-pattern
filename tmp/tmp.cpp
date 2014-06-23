#include<string>
#include<iostream>
#include<algorithm>
#include<utility>
#include<vector>
#include<array>


enum Direction 
{
	North, South, East, West
};


void EnterLine(){
	std::cout<<std::endl;
}


template<typename Message>
void display(const Message& str){
	std::cout<<str;
}





class MapSite {
public:
	virtual void Enter() = 0;
};



class Room : public MapSite {
public:
	Room(int roomNo);
	MapSite* GetSide(Direction) const;
	void SetSide(Direction, MapSite*);
	virtual void Enter();
private:
	std::array<MapSite*,4> _sides;
	int _roomNumber;
};

Room::Room(int roomNo): _roomNumber(roomNo) {
	_sides.fill(nullptr);
}

MapSite* Room::GetSide(Direction di) const {
	return _sides[di];
}

void Room::SetSide(Direction di, MapSite* site){
	_sides[di] = site;
}

void Room::Enter() {
	display("Welcome to Room: ");
	display(_roomNumber);
	EnterLine();
}






class Wall : public MapSite {
public:
	Wall();
	virtual void Enter();
};

Wall::Wall() {
}

void Wall::Enter() {
	display("This is Wall");
	EnterLine();
}




class Door : public MapSite {
public:
	Door(Room* , Room* );
	virtual void Enter();
	Room* OtherSideFrom(Room*);
private:
	Room* _room1;
	Room* _room2;
	bool _isOpen;
};

Door::Door(Room* r1 = nullptr, Room* r2 = nullptr)
	: _room1(r1),_room2(r2), _isOpen(false) {
}

void Door::Enter() {
	display("This is door and it is ");
	if(_isOpen) {
		display("Open");
	}else {
		display("Closed");
	}
	EnterLine();
}


Room* Door::OtherSideFrom(Room* r) {
	if(r == _room1) {
		return _room2;
	} else if(r == _room2) {
		return _room1;
	} else {
		return nullptr;
	}
}





// Maze class to represent collection of rooms 
class Maze {
public:
	Maze();
	void AddRoom(Room*);
	Room* RoomNo(int) const;
private:
	std::vector<Room*> _rooms;
};


Maze::Maze() {
}

void Maze::AddRoom(Room* r) {
	_rooms.push_back(r);
}

Room* Maze::RoomNo(int index) const{
	if(index > _rooms.size()) {
		_rooms[index];
	}
	return nullptr;
}








class SingletonNumberGenerator {
public:
	static int Instance();
protected:
	SingletonNumberGenerator();
private:
	static SingletonNumberGenerator* _instance;
	static int initialnumber;
};


SingletonNumberGenerator* SingletonNumberGenerator::_instance = nullptr;
int SingletonNumberGenerator::initialnumber = 0;

SingletonNumberGenerator::SingletonNumberGenerator(){
}

int SingletonNumberGenerator::Instance () {
	if (_instance == nullptr) {
		_instance = new SingletonNumberGenerator;
	}
	initialnumber++;
	return initialnumber;
}


class MazeGame {
public:
	MazeGame();
	Maze* CreateMaze();
};


MazeGame::MazeGame() {
}


Maze* MazeGame::CreateMaze() {
	Maze* aMaze = new Maze;
	Room* r1 = new Room(SingletonNumberGenerator::Instance());
	Room* r2 = new Room(SingletonNumberGenerator::Instance());
	Door* theDoor = new Door(r1, r2);

	aMaze->AddRoom(r1);
	aMaze->AddRoom(r2);

	r1->SetSide(North, new Wall);
	r1->SetSide(East, theDoor);
	r1->SetSide(South, new Wall);
	r1->SetSide(West, new Wall);

	r2->SetSide(North, new Wall);
	r2->SetSide(East, new Wall);
	r2->SetSide(South, new Wall);
	r2->SetSide(West, theDoor);

	return aMaze;
}




#include"Creational_Pattern.h"


int main() {
	MazeGame game;
	game.CreateMaze();
	return 0;
}




/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/
/**************************************************************************************************/
class MazeFactory {
public:
	static MazeFactory* GetInstance();
	virtual Maze* MakeMaze() const
	{ return new Maze; }
	virtual Wall* MakeWall() const
	{ return new Wall; }
	virtual Room* MakeRoom(int n) const
	{ return new Room(n); }
	virtual Door* MakeDoor(Room* r1, Room* r2) const
	{ return new Door(r1, r2); }
protected:
	MazeFactory();
private:
	static MazeFactory* _instance;
};

MazeFactory* MazeFactory::_instance = nullptr;


MazeFactory::MazeFactory(){
}

MazeFactory* MazeFactory::GetInstance () {
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

	r1->SetSide(North,factory.MakeWall());
	r1->SetSide(East,aDoor);
	r1->SetSide(South,factory.MakeWall());
	r1->SetSide(West,factory.MakeWall());

	r2->SetSide(North,factory.MakeWall());
	r2->SetSide(East,factory.MakeWall());
	r2->SetSide(South,factory.MakeWall());
	r2->SetSide(West, aDoor);

	return aMaze;
}




int main() {
	MazeGame game;
	game.CreateMaze(*MazeFactory::GetInstance());
	return 0;
}






/**************************************************************************/
/**************************************************************************/
#include"Creational_Pattern.h"

/*
class Creator {
public:
virtual MapSite* CreateProduct() = 0;
};

template <class TheProduct>
class StandardCreator: public Creator {
public:
	virtual MapSite* CreateProduct();
};

template <class TheProduct>
Product* StandardCreator<TheProduct>::CreateProduct () {
	return new TheProduct;
}
*/


class MazeGame {
public:
	MazeGame();
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


MazeGame::MazeGame() {
}

Maze* MazeGame::CreateMaze() {
	Maze* aMaze = MakeMaze();
	Room* r1 = MakeRoom(SingletonNumberGenerator::Instance());
	Room* r2 = MakeRoom(SingletonNumberGenerator::Instance());
	Door* aDoor = MakeDoor(r1, r2);

	aMaze->AddRoom(r1);
	aMaze->AddRoom(r2);

	r1->SetSide(North,MakeWall());
	r1->SetSide(East,aDoor);
	r1->SetSide(South,MakeWall());
	r1->SetSide(West,MakeWall());

	r2->SetSide(North,MakeWall());
	r2->SetSide(East,MakeWall());
	r2->SetSide(South,MakeWall());
	r2->SetSide(West, aDoor);

	return aMaze;
}




class BombedWall: public Wall {
};


class RoomWithABomb: public Room {
public:
	RoomWithABomb(int n): Room(n){
	}
};

class BombedMazeGame : public MazeGame {
public:
BombedMazeGame();
virtual Wall* MakeWall() const
{ return new BombedWall; }
virtual Room* MakeRoom(int n) const
{ return new RoomWithABomb(n); }
};


