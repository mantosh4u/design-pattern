#include"Singleton.h"

int main()
{
	auto sobject = Singleton::GetInstance();
	sobject->DoSomething();
	return 0;
}
