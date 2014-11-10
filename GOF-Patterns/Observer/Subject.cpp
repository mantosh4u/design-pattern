#include"Subject.h"
#include<thread>

/****************************************************/
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


/***************************************************/
int ClockTimer::GetHour() {
	return _time.GetHour();
}

int ClockTimer::GetMinute() {
	return _time.GetMin();
}

int ClockTimer::GetSecond() {
	return _time.GetSecond();
}

int ClockTimer::GetDay() {
	return _time.GetDay();
}

int ClockTimer::GetMonth() {
	return _time.GetMonth();
}

int ClockTimer::GetYear() {
	return _time.GetYear();
}


void ClockTimer::Tick() {
	bool whetherToNotify = true;
	// update internal time-keeping state after 5 second
	while (1) {
		if (whetherToNotify)
		{
			Subject::Notify();
			whetherToNotify = false;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::seconds(50));
			whetherToNotify = true;
		}
	}
}









DigitalClock::DigitalClock(ClockTimer* s) {
	_subject = s;
	_subject->Attach(this);
}


DigitalClock::~DigitalClock() {
	_subject->Detach(this);
}


void DigitalClock::Update(Subject* theChangedSubject) {
	if (theChangedSubject == _subject) {
		Draw();
	}
}


void DigitalClock::Draw() {
	// get the new values from the subject
	auto hour = _subject->GetHour();
	auto minute = _subject->GetMinute();
	auto second = _subject->GetSecond();
	auto day = _subject->GetDay();
	auto month = _subject->GetMonth();
	auto year = _subject->GetYear();

	// Draw the digital clock	
	this->displayOnConsole(hour);
	this->displayOnConsole(minute);
	this->displayOnConsole(second);
	this->displayOnConsole(day);
	this->displayOnConsole(month);
	this->displayOnConsole(year);
}

