#include "../Header/Tab.h"

Tab::Tab(VideoMode& vm, Font& font, Player& player,  bool hidden)
	: vm(vm), font(font), player(player), hidden(hidden){

}

Tab::~Tab(){

}

bool& Tab::getHidden()
{
	return this->hidden;
}

bool Tab::getOpen() const{	
	return !this->hidden;
}


void Tab::hide()
{
	this->hidden = true;
}

void Tab::toggle(){
	(this->hidden)?
		this->hidden = false:
		this->hidden = true;
}

void Tab::show()
{
	this->hidden = false;
}