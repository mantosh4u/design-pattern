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
	std::cout << std::endl;
}


template<typename Message>
void display(const Message& str){
	std::cout << str;
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
	std::array<MapSite*, 4> _sides;
	int _roomNumber;
};

Room::Room(int roomNo) : _roomNumber(roomNo) {
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
	Door(Room*, Room*);
	virtual void Enter();
	Room* OtherSideFrom(Room*);
private:
	Room* _room1;
	Room* _room2;
	bool _isOpen;
};

Door::Door(Room* r1 = nullptr, Room* r2 = nullptr)
: _room1(r1), _room2(r2), _isOpen(false) {
}

void Door::Enter() {
	display("This is door and it is ");
	if (_isOpen) {
		display("Open");
	}
	else {
		display("Closed");
	}
	EnterLine();
}


Room* Door::OtherSideFrom(Room* r) {
	if (r == _room1) {
		return _room2;
	}
	else if (r == _room2) {
		return _room1;
	}
	else {
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
	if (index > _rooms.size()) {
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

int SingletonNumberGenerator::Instance() {
	if (_instance == nullptr) {
		_instance = new SingletonNumberGenerator;
	}
	initialnumber++;
	return initialnumber;
}


