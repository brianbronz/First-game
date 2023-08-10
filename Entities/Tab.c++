#include "stdafx.h"
#include "Tab.h"

Tab::Tab(sf::VideoMode& vm, sf::Font& font, Player& player,  bool hidden)
	: vm(vm), font(font), player(player), hidden(hidden)
{

}

Tab::~Tab()
{

}

bool& Tab::getHidden()
{
	return this->hidden;
}

bool& Tab::getOpen()
{
	return (this->hidden == false);
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