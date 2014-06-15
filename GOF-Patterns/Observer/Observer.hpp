#include"../List.hpp"
#include<string>
#include<chrono>
#include<ctime>
#include<thread>


/* Actual Observer Pattern Implementation */

/* forward declaration */
class Subject;

class Observer {
public:
    virtual ~Observer() {
    }
    virtual void Update(Subject* theChangedSubject) = 0;
protected:
    Observer() {
    }
};




class Subject {
public:
    virtual ~Subject() {
    	delete _observers;
    }
    virtual void Attach(Observer* obj);
    virtual void Detach(Observer* obj);
    virtual void Notify();
protected:
    Subject() {
    	_observers = new List<Observer*>;
    }
private:
    List<Observer*> *_observers;
};


void Subject::Attach(Observer* o) {
    _observers->Append(o);
}

void Subject::Detach(Observer* o) {
    _observers->Remove(o);
}

void Subject::Notify() {
    ListIterator<Observer*> i(_observers);
    for (i.First(); !i.IsDone(); i.Next()) {
        i.CurrentItem()->Update(this);
    }
}



/*
ClockTimer is a concrete subject for storing and maintaining the time of day.
It notifies its observers every second. ClockTimer provides the interface for
retrieving individual time units such as the hour, minute, and second.
 */

class ClockTimer : public Subject {
public:
    ClockTimer();
    virtual int GetHour();
    virtual int GetMinute();
    virtual int GetSecond();
    void Tick();
private:
    std::string _time;
};


std::string  get_ctime_to_ltime(const time_t* tp) {
    char* tmp = ::ctime(tp);
    std::string output{tmp};
    return output;
}

std::string  calculate_date_time(void) {
    auto tp = std::chrono::system_clock::now();
    time_t cstyle_t = std::chrono::system_clock::to_time_t(tp);
    return(get_ctime_to_ltime(&cstyle_t));
}


/* Thu Jun 12 21:20:48 2014 */
ClockTimer::ClockTimer() {
	_time = calculate_date_time();
}


int ClockTimer::GetHour() {
    size_t hr_pos = 11;
    std::string hour = _time.substr(hr_pos,2);
    return std::stoi(hour);
}


int ClockTimer::GetMinute() {
    size_t min_pos = 14;
    std::string minute = _time.substr(min_pos,2);
    return std::stoi(minute);
}


int ClockTimer::GetSecond() {
    size_t sec_pos = 17;
    std::string second = _time.substr(sec_pos,2);
    return std::stoi(second);
}


void ClockTimer::Tick() {
    std::string _timetmp;
    // update internal time-keeping state after 10 second
    while(1) {
        _timetmp = calculate_date_time();
         size_t min_pos = 14;
    		std::string minute = _timetmp.substr(min_pos,2);
    		int min = std::stoi(minute);
         if(min > GetMinute()) {
        		Subject::Notify();
        }
        else {
        	std::this_thread::sleep_for(std::chrono::seconds(10));
        	}
    }
}




class FileWidget {
public:
	FileWidget(){}
	~FileWidget() {}
	template<typename T>
	void displayOnConsole(T& input) {
		std::cout<<input<<std::endl;		
	}
private:
 /* std::ostream _output;*/
};



/* concrete observer implementation */
class DigitalClock: public FileWidget, public Observer {
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


DigitalClock::DigitalClock (ClockTimer* s) {
	_subject = s;
	_subject->Attach(this);
}


DigitalClock::~DigitalClock () {
	_subject->Detach(this);
}



void DigitalClock::Update (Subject* theChangedSubject) {
	if (theChangedSubject == _subject) {
		Draw();
	}
}


void DigitalClock::Draw () {
	// get the new values from the subject
	int hour 		= _subject->GetHour();
	int minute = _subject->GetMinute();
	int second = _subject->GetSecond();

	// Draw the digital clock	
	this->displayOnConsole(hour);
	this->displayOnConsole(minute);
	this->displayOnConsole(second);
}



