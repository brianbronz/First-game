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
	const unsigned& size() const;
	const unsigned& maxSize() const;

	//Modifiers

	//Functions
	void clear();
	const bool empty() const;

	const bool add(Item* item);
	const bool remove(const unsigned index);

	const bool saveToFile(const string fileName);
	const bool loadFromFile(const string fileName);
};
#endif