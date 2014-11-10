#include"visitor_composite.h"



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

	//Now we can use PricingVisitor for calculating the price of total computer
	auto vprice = std::make_unique<PricingVisitor>();
	vprice->VisitCabinet(cabinet.get());
	auto price = vprice->GetTotalPrice();
	std::cout << "The PC Price Using Vistior Patterns Are : " << price << "\n";


	//Now we can use InventoryVisitor for calculating the total number in computer
	auto vcount = std::make_unique<InventoryVisitor>();
	vcount->VisitCabinet(cabinet.get());
	auto count = vcount->GetInventory().GetTotalCount();
	std::cout << "The PC Parts Counts Using InventoryVisitor : " << count << "\n";

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



