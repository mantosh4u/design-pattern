#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include<algorithm>



using Watt = double;
using Currency = double;

/*****************************************/
class Equipment {
public:
	using EquipmentSmartPtr = std::shared_ptr<Equipment>;
	virtual ~Equipment() = default;
	std::string Name() { return _name; }
	virtual Watt Power() { return _power; }
	virtual Currency NetPrice() { return _price; }
	// fixed 20% percent discount
	virtual Currency DiscountPrice() { return (0.8*NetPrice()); }
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
};


/*****************************************************************/
class Card : public Equipment {
public:
	Card(std::string n) :Equipment(n) {}
	virtual ~Card() = default;
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
};



/*****************************************************************/
class Cabinet : public CompositeEquipment {
public:
	Cabinet(std::string n) : CompositeEquipment(n) {}
	virtual ~Cabinet() = default;
};



/*****************************************************************/
class Bus : public CompositeEquipment {
public:
	Bus(std::string n) : CompositeEquipment(n) {}
	virtual ~Bus() = default;
};


