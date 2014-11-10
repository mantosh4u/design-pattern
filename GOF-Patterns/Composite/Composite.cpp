#include"Composite.h"


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
		display(itr->Name());
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
