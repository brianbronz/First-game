#include "../Header/Item.h"

void Item::initVariables(){

}

Item::Item(unsigned level, unsigned value){
    this->initVariables();

	this->level = level;
	this->value = value;
	this->type = IT_DEFAULT;
}

Item::~Item(){
    
}