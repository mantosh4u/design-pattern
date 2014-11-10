#include"visitor_composite.h"


/*******************************************************************/
void FloopyDisk::Accept(EquipmentVisitor* visitor) {
	visitor->VisitFloppyDisk(this);
}


/*******************************************************************/
void Card::Accept(EquipmentVisitor* visitor) {
	visitor->VisitCard(this);
}



/********************************************************************/
void PricingVisitor::VisitFloppyDisk(FloopyDisk* e) {
	_total += e->NetPrice();
}


void PricingVisitor::VisitCard(Card* e) {
	_total += e->NetPrice();
}

void PricingVisitor::VisitChassis(Chassis* e) {
	_total += e->NetPrice();
}

void PricingVisitor::VisitBus(Bus* e) {
	_total += e->NetPrice();
}

void PricingVisitor::VisitCabinet(Cabinet* e) {
	_total += e->NetPrice();
}



/********************************************************************/
Watt CompositeEquipment::Power() {
	Watt total{};
	for (const auto& itr : _equipment)
		total += itr->Power();
	total += Equipment::Power();
	return total;
}


Currency CompositeEquipment::NetPrice() {
	Currency total{};
	for (const auto& itr : _equipment) {
		std::cout << itr->Name() << "\n";
		total += itr->NetPrice();
	}
	total += Equipment::NetPrice();
	return total;
}

void CompositeEquipment::Add(EquipmentSmartPtr entry) {
	_equipment.push_back(entry);
}

void CompositeEquipment::Remove(EquipmentSmartPtr entry) {
	std::vector<EquipmentSmartPtr>& vec = _equipment;
	Name_Equal eq(entry);
	auto itrpos = std::find_if(std::begin(vec), std::end(vec), eq);
	if (itrpos != std::end(vec)) {
		vec.erase(itrpos);
	}
	else {
		for (EquipmentSmartPtr sptr : vec) {
			sptr->Remove(entry);
		}
	}
}


void CompositeEquipment::Accept(EquipmentVisitor* visitor) {
	for (const auto& itr : _equipment) {
		itr->Accept(visitor);
	}
}



/********************************************************************/
void Chassis::Accept(EquipmentVisitor* visitor) {
	CompositeEquipment::Accept(visitor);
	visitor->VisitChassis(this);
}



/********************************************************************/
void Cabinet::Accept(EquipmentVisitor* visitor) {
	CompositeEquipment::Accept(visitor);
	visitor->VisitCabinet(this);
}



/********************************************************************/
void Bus::Accept(EquipmentVisitor* visitor) {
	CompositeEquipment::Accept(visitor);
	visitor->VisitBus(this);
}









/**********************************************************/
void Inventory::Accumulate(Equipment* e) {
	// How to count the number of inventory in a given Equipment structure??
	count = e->GetSize();	
}


/*******************************************************/
void InventoryVisitor::VisitFloppyDisk(FloopyDisk* e) {
	_inventory.Accumulate(e);
}


void InventoryVisitor::VisitCard(Card* e) {
	_inventory.Accumulate(e);
}

void InventoryVisitor::VisitChassis(Chassis* e) {
	_inventory.Accumulate(e);
}

void InventoryVisitor::VisitBus(Bus* e) {
	_inventory.Accumulate(e);
}

void InventoryVisitor::VisitCabinet(Cabinet* e) {
	_inventory.Accumulate(e);
}

