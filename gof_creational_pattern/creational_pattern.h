#ifndef CREATIONAL_PATTERN_H 
#define CREATIONAL_PATTERN_H

#include<string>
#include<iostream>
#include<algorithm>
#include<utility>
#include<vector>


enum Direction { North, South, East, West };


void EnterLine() {
	std::cout << std::endl;
}

template<typename Message>
void display(const Message& str) {
	std::cout << str;
}


class MapSite {
public:
	virtual ~MapSite() {}    
	virtual void Enter() = 0;
};


class Room : public MapSite {
public:
	Room();
	Room(int roomNo);
	~Room() {}
	MapSite* GetSide(Direction) const;
	void SetSide(Direction, MapSite*);
	virtual void Enter();
protected:
	std::vector<MapSite*> _sides;
	int _roomNumber;
};

Room::Room() {
	_sides.push_back(NULL);
	_sides.push_back(NULL);
	_sides.push_back(NULL);
	_sides.push_back(NULL);
}


Room::Room(int roomNo) : _roomNumber(roomNo) {
	_sides.push_back(NULL);
	_sides.push_back(NULL);
	_sides.push_back(NULL);
	_sides.push_back(NULL);
}

MapSite* Room::GetSide(Direction di) const {
	return _sides[di];
}

void Room::SetSide(Direction di, MapSite* site) {
	_sides[di] = site;
}

void Room::Enter() {
	display("Welcome to Room: ");
	display(_roomNumber);
	EnterLine();
}



class Wall : public MapSite {
public:
	Wall() {}
	~Wall() {}
	virtual void Enter();
};

void Wall::Enter() {
	display("This is Wall");
	EnterLine();
}



class Door : public MapSite {
public:
	Door():_room1(NULL), _room2(NULL) {}
	Door(Room* r1, Room* r2);
	virtual void Enter();
	~Door() {}
	Room* OtherSideFrom(Room*);
protected:
	Room* _room1;
	Room* _room2;
	bool _isOpen;
};

Door::Door(Room* r1, Room* r2)
	: _room1(r1), _room2(r2), _isOpen(false) {
}

void Door::Enter() {
	display("This is door and it is ");
	if (_isOpen) {
		display("Open");
	} else {
		display("Closed");
	}
	EnterLine();
}

Room* Door::OtherSideFrom(Room* r) {
	if (r == _room1) {
		return _room2;
	} else if (r == _room2) {
		return _room1;
	} else {
		return NULL;
	}
}



// Maze class to represent collection of rooms
class Maze {
public:
	Maze() {}
	~Maze() {}
	void AddRoom(Room*);
	Room* RoomNo(size_t) const;
	void  DisplayAllComponent();
private:
	std::vector<Room*> _rooms;
};


void Maze::AddRoom(Room* r) {
	_rooms.push_back(r);
}

Room* Maze::RoomNo(size_t index) const {
	size_t sz = _rooms.size();    
	if ((index-1) < sz) {
		return(_rooms[index-1]);
	}
	return NULL;
}

void Maze::DisplayAllComponent()  {
	for(std::vector<Room*>::iterator itr = _rooms.begin();
		itr != _rooms.end(); ++itr) {
			(*itr)->Enter();
	}
}




class EnchantedRoom: public Room{
public:
	EnchantedRoom(int n): Room(n) {}
	virtual ~EnchantedRoom() {}	
	virtual void Enter();
};

void EnchantedRoom::Enter() {
	display("This is EnchantedRoom");
	EnterLine();
	Room::Enter();
}


class DoorNeedingSpell: public Door{
public:
	DoorNeedingSpell(Room* r1, Room* r2): Door(r1,r2) {}
	virtual ~DoorNeedingSpell() {}	
	virtual void Enter();
};

void DoorNeedingSpell::Enter() {
	display("This is DoorNeedingSpell");
	EnterLine();
	Door::Enter();
}

#endif
