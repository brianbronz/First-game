#pragma once

#include "CharacterTab.h"

class PlayerGUITabs
{
private:    
    CharacterTab characterTab;
	//Core
	sf::VideoMode& vm;
	sf::Font& font;
	Player& player;

	//Tabs

public:
	PlayerGUITabs(sf::VideoMode& vm, sf::Font& font, Player& player);
	virtual ~PlayerGUITabs();

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};