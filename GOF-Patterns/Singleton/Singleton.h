#include<iostream>

class Singleton {
public:
	static Singleton* GetInstance();
	void DoSomething();
protected:
	Singleton() = default;
private:
	static Singleton* _instance;
};

Singleton* Singleton::_instance = nullptr;

void Singleton::DoSomething() {
	std::cout << "Singleton::DoSomething" << "\n";
}


Singleton* Singleton::GetInstance() {
	if (_instance == nullptr) {
		_instance = new Singleton;
	}
	return _instance;
}



