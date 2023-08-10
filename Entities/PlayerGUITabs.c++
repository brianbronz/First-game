#include "stdafx.h"
#include "PlayerGUITabs.h"


void PlayerGUITabs::initTabs()
{
	this->tabs.push_back(new CharacterTab(vm, font, player));
}

void PlayerGUITabs::initKeyTime()
{
	this->keyTimeMax = 0.3f;
	this->keyTimer.restart();
}

PlayerGUITabs::PlayerGUITabs(sf::VideoMode& vm, sf::Font& font, Player& player)
	: vm(vm), font(font), player(player){
	//this->initTabMenu();
	//this->initCharacterTab();
     	this->initTabs();
    this->initKeyTime();
}

PlayerGUITabs::~PlayerGUITabs()
{

}

bool PlayerGUITabs::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}

	return false;
}

bool PlayerGUITabs::tabsOpen()
{
    //Loop through tabs and check if any are open
	bool open = false;
	for (size_t i = 0; i < this->tabs.size() && !open; i++){
		if (this->tabs[i]->getOpen())
			return true;
	}
	return open;
}

void PlayerGUITabs::toggleTab(int tab_index)
{
	if(tab_index >= 0 || tab_index < this->tabs.size())
		this->tabs[tab_index]->toggle();
}


void PlayerGUITabs::update()
{
    for (size_t i = 0; i < this->tabs.size(); i++){
		if(this->tabs[i]->getOpen())
			this->tabs[i]->update();
	}
    /* if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && this->getKeyTime())
        {
            if(this->characterTab.getHidden())
                this->characterTab.show();
            else
                this->characterTab.hide();
        } */
}

void PlayerGUITabs::render(RenderTarget & target){
	for (size_t i = 0; i < this->tabs.size(); i++)
	{
		if (this->tabs[i]->getOpen())
			this->tabs[i]->render(target);
	}
}