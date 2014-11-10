#include"Composite.h"


Equipment::EquipmentSmartPtr assemble_pc() {
	auto cabinet = std::make_shared<Cabinet>("PC Cabinet");
	auto chassis = std::make_shared<Chassis>("Chassis");
	cabinet->Add(chassis);

	auto bus = std::make_shared<Bus>("MCA Bus");
	auto card = std::make_shared<Card>("16Mbs Token Ring Card");
	bus->Add(card);
	chassis->Add(bus);
	auto floopy = std::make_shared<FloopyDisk>("3.5inch Floopy Disk");
	cabinet->Add(floopy);
	
	cabinet->Remove(bus);
	
	return cabinet;
}


int main() {
	auto pc = assemble_pc();
	std::cout << "The PC Name is: " << pc->Name() << "\n";
	std::cout << "The PC parts are: " << "\n";
	auto price = pc->NetPrice();
	std::cout << "The net price of PC is: " << price << "\n";

	return 0;
}

