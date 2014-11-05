#include<list>
#include<exception>
#include<iostream>
#include<algorithm>
#include<utility>



/* Wrapper class List based on STL std::list */
template<typename Item>
class List {
public:
    void Append(Item obj);
    void Remove(Item obj);
    void display(void);
    int  Count() const;
    Item Get(int index) const;
private:
    std::list<Item> _collection;
};



template<typename Item>
void List<Item>::Append(Item obj) {
    _collection.push_back(obj);
}



template<typename Item>
void List<Item>::Remove(Item obj) {
    auto pos = std::find(std::begin(_collection), std::end(_collection), obj);
    if (pos != std::end(_collection)) {
        _collection.erase(pos);
    }
}



template<typename Item>
void List<Item>::display(void) {
    for (const auto& itr : _collection) {
        std::cout << itr << "\t";
    }
    std::cout << std::endl;
}



template<typename Item>
int List<Item>::Count() const {
    _collection.size();
}



template<typename Item>
Item List<Item>::Get(int index) const {
    if (index < _collection.size()) {
        auto iter = _collection.begin();
        while (index--) {
            ++iter;
        }
        return *iter;
    }
    throw std::out_of_range("Out Of Range Error");
}



/* Iterator base class to get the items from the collection like List */
template <class Item>
class Iterator {
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone()= 0;
    virtual Item CurrentItem()= 0;
protected:
    Iterator(){
    }
};



/* Iterator concrete class to traverse the List container class */
template <typename Item>
class ListIterator : public Iterator<Item> {
public:
    ListIterator(const List<Item>*);
    void First();
    void Next();
    bool IsDone();
    Item CurrentItem();
private:
    const List<Item>* _list;
    int _current;
};


template<typename Item>
ListIterator<Item>::ListIterator(const List<Item>* aList) :
_list(aList), _current(0) {
}

template<typename Item>
void ListIterator<Item>::First() {
    _current = 0;
}

template<typename Item>
void ListIterator<Item>::Next() {
    _current++;
}

template<typename Item>
bool ListIterator<Item>::IsDone() {
    return (_current >= _list->Count());
}

template<typename Item>
Item ListIterator<Item>::CurrentItem() {
    if (IsDone()) {
        throw std::out_of_range("Out Of Range Error");
    }
    return _list->Get(_current);
}

