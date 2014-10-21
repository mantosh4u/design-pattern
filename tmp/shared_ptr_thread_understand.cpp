#include<iostream>
#include<memory>
#include<thread>
#include<vector>

class Equipment {
public:
	using Watt = double;
	using Currency = double;

   virtual ~Equipment() = default;
	std::string Name() { return _name; }
	Equipment(std::string n):_name(n){ }

private:
	std::string _name;
	Watt        _power{440};
	Currency    _price{999};
};


using SharedEquipmentCollection = std::vector<std::shared_ptr<Equipment>>;


void function_one(SharedEquipmentCollection* one) {
	auto e1 = std::make_shared<Equipment>("e1");
	one->push_back(e1);
	auto e2 = std::make_shared<Equipment>("e2");
	auto e3 = std::make_shared<Equipment>("e3");
	one->push_back(e2);
	one->push_back(e3);

	std::cout<<one->size()<<"\n";
}


void function_two(SharedEquipmentCollection* two) {
	auto l1 = std::make_shared<Equipment>("l1");
	two->push_back(l1);
	auto l2 = std::make_shared<Equipment>("l2");
	auto l3 = std::make_shared<Equipment>("l3");
	two->push_back(l2);
	two->push_back(l3);

	std::cout<<two->size()<<"\n";
}


void function_three(SharedEquipmentCollection* three) {
	auto collectioncopy{three->begin(),three->end()};
	
	for(const auto& itr: collectioncopy) {
//		std::cout<<itr.Name()<<"\n";
	}
	
	std::cout<<three->size()<<"\n";
}


int main() {
	
	SharedEquipmentCollection collection;	
	std::thread t1{function_one,&collection};
	std::thread t2{function_two, &collection};
	t1.join();
   t2.join();

	std::thread t3{function_three, &collection};
	t3.join();

	return 0;
}
