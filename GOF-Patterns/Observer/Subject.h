#include"List.h"
#include"DateTime.h"


/* Forward Declaration */
class Observer;

/*Base Subject Class*/
class Subject {
public:
	virtual ~Subject() { delete _observers; }
	virtual void Attach(Observer* obj);
	virtual void Detach(Observer* obj);
	virtual void Notify();
protected:
	Subject() = default;
private:
	List<Observer*> *_observers = new List<Observer*>;
};


/*
ClockTimer is a concrete subject for storing and maintaining the time of day.
It notifies its observers every second. ClockTimer provides the interface for
retrieving individual time units such as the hour, minute, and second.
*/
class ClockTimer : public Subject {
public:
	ClockTimer() = default;
	virtual int GetHour();
	virtual int GetMinute();
	virtual int GetSecond();
	virtual int GetDay();
	virtual int GetMonth();
	virtual int GetYear();
	void Tick();
private:
	CurrentDateTime _time;
};





class Observer {
public:
	virtual ~Observer() = default;
	virtual void Update(Subject* theChangedSubject) = 0;
protected:
	Observer() = default;
};



/**********************************************************/
class FileWidget {
public:
	FileWidget() = default;
	~FileWidget() = default;
	template<typename T>
	void displayOnConsole(const T& input) {
		std::cout << input << "\n";
	}
};



/*Forward Declaration */
class ClockTimer;

/* concrete observer implementation */
class DigitalClock : public FileWidget, public Observer {
public:
	DigitalClock(ClockTimer*);
	virtual ~DigitalClock();
	virtual void Update(Subject*);
	// overrides Observer operation
	virtual void Draw();
	// overrides FileWidget operation;
	// defines how to draw the digital clock
private:
	ClockTimer* _subject;
};

