#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "AllReference.h"

class Inventory
{
private:
	Item** itemArray;
	unsigned nrOfItems;
	unsigned capacity;

	//Private functions
	void initialize();
	void nullify(const unsigned from = 0);
	void freeMemory();

public:
	Inventory(unsigned capacity);
	virtual ~Inventory();

	//Accessors
	unsigned& size();
	unsigned& maxSize();

	//Modifiers

	//Functions
	void clear();
	bool empty();

	bool add(Item* item);
	bool remove(const unsigned index);

	bool saveToFile(const string fileName);
	bool loadFromFile(const string fileName);
};
#endif