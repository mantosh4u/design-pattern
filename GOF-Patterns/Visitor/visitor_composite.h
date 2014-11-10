#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include<algorithm>

//Forward Declaration
class EquipmentVisitor;


/********************************************************/
using Watt = double;
using Currency = double;

class Equipment {
public:
	using EquipmentSmartPtr = std::shared_ptr<Equipment>;
	virtual ~Equipment() = default;
	std::string Name() { return _name; }
	virtual Watt Power() { return _power; }
	virtual Currency NetPrice() { return _price; }
	// fixed 20% percent discount
	virtual Currency DiscountPrice() { return (0.8*NetPrice()); }
	
	virtual void   Accept(EquipmentVisitor* visitor) {}
	virtual size_t GetSize() const { return size_t(1); }
	virtual void Add(EquipmentSmartPtr x) { }
	virtual void Remove(EquipmentSmartPtr x) { }
protected:
	Equipment(std::string n) :_name(n){ }
private:
	std::string _name;
	Watt        _power{ 440 };
	Currency    _price{ 200 };
};




/*****************************************************************/
class FloopyDisk : public Equipment {
public:
	FloopyDisk(std::string n) :Equipment(n) {}
	virtual ~FloopyDisk() = default;
	virtual void Accept(EquipmentVisitor* visitor);
};


/*****************************************************************/
class Card : public Equipment {
public:
	Card(std::string n) :Equipment(n) {}
	virtual ~Card() = default;
	virtual void Accept(EquipmentVisitor* visitor);
};




/******************************************************************/
//To find out whether items are in the composite objects
class Name_Equal {
private:
	Equipment::EquipmentSmartPtr val;
public:
	Name_Equal(const Equipment::EquipmentSmartPtr& v) :val(v) { }
	bool operator()(const Equipment::EquipmentSmartPtr& x) const {
		return (x->Name() == val->Name());
	}
};




/*****************************************************************/
class  CompositeEquipment : public Equipment {
public:
	virtual ~CompositeEquipment() = default;
	virtual Watt Power() override;
	virtual Currency NetPrice() override;
	virtual void Add(EquipmentSmartPtr) override;
	virtual void Remove(EquipmentSmartPtr) override;

	virtual void Accept(EquipmentVisitor* visitor);
	virtual size_t GetSize() const { return _equipment.size(); }
protected:
	CompositeEquipment(std::string n) : Equipment(n) { }
private:
	std::vector<EquipmentSmartPtr>  _equipment;
};



/*****************************************************************/
class Chassis : public CompositeEquipment {
public:
	Chassis(std::string n) : CompositeEquipment(n) {}
	virtual ~Chassis() = default;
	virtual void Accept(EquipmentVisitor* visitor);

};



/*****************************************************************/
class Cabinet : public CompositeEquipment {
public:
	Cabinet(std::string n) : CompositeEquipment(n) {}
	virtual ~Cabinet() = default;
	virtual void Accept(EquipmentVisitor* visitor);
};



/*****************************************************************/
class Bus : public CompositeEquipment {
public:
	Bus(std::string n) : CompositeEquipment(n) {}
	virtual ~Bus() = default;
	virtual void Accept(EquipmentVisitor* visitor);
};







/************************************************************************/
class EquipmentVisitor {
public:
	virtual ~EquipmentVisitor() = default;
	virtual void VisitFloppyDisk(FloopyDisk*) {}
	virtual void VisitCard(Card*) {}
	virtual void VisitChassis(Chassis*) {}
	virtual void VisitBus(Bus*) {}
	virtual void VisitCabinet(Cabinet*) {}
//protected:
	EquipmentVisitor() = default;
};


/*******************************************************/
class PricingVisitor : public EquipmentVisitor {
public:
	PricingVisitor() :_total(Currency{}) { }
	virtual ~PricingVisitor() = default;
	Currency& GetTotalPrice() { return _total; }

	virtual void VisitFloppyDisk(FloopyDisk*);
	virtual void VisitCard(Card*);
	virtual void VisitChassis(Chassis*);
	virtual void VisitBus(Bus*);
	virtual void VisitCabinet(Cabinet*);
private:
	Currency _total;
};






/*******************************************************/
class  Inventory
{
public:
	void Accumulate(Equipment*);
	int  GetTotalCount() const { return count; }
private:
	int count = 0;
};



/*******************************************************/
class InventoryVisitor : public EquipmentVisitor {
public:
	InventoryVisitor() :_inventory(Inventory{}) { }
	virtual ~InventoryVisitor() = default;
	Inventory& GetInventory() { return _inventory; }

	virtual void VisitFloppyDisk(FloopyDisk*);
	virtual void VisitCard(Card*);
	virtual void VisitChassis(Chassis*);
	virtual void VisitBus(Bus*);
	virtual void VisitCabinet(Cabinet*);
private:
	Inventory _inventory;
};

