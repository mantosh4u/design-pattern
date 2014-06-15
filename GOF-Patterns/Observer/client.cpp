#include"Observer.hpp"


ClockTimer*	timer = nullptr;
DigitalClock* digtalClock1 = nullptr;
DigitalClock* digtalClock2 = nullptr;	


void subjectFunction() {
	timer = new ClockTimer;
	while(1) {
		timer->Tick();
	}
}


void observerFunctionOne() {
   while(timer == nullptr) {
		 std::this_thread::sleep_for(std::chrono::seconds(1));
   }
   digtalClock1 = new DigitalClock(timer);
	while(1) {
		digtalClock1->Draw();
	}
}


void observerFunctionTwo() {
   while(timer == nullptr) {
		 std::this_thread::sleep_for(std::chrono::seconds(1));
   }
   digtalClock2 = new DigitalClock(timer);
	while(1) {
		digtalClock2->Draw();
	}
}



int main() {
	// Create the one thread for subject and another thread for observer
	//  Main thread should wait for the all these child thread.
	// Whenever the timer ticks, the two clocks will be updated and will 
	// redisplay themselves appropriately.
	
	std::thread subjectId {subjectFunction};
	std::thread observerIdOne {observerFunctionOne};
	std::thread observerIdTwo {observerFunctionTwo};
	subjectId.join();
	observerIdOne.join();
	observerIdTwo.join(); 
	
	delete timer;
	delete digtalClock1;
	delete digtalClock2;

}


