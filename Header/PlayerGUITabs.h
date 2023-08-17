#pragma once

#include "CharacterTab.h"

enum PLAYER_TABS { CHARACTER_TAB = 0, INVENTORY_TAB };

class PlayerGUITabs
{
private:    
    vector<Tab*> tabs;
	//Core
	VideoMode& vm;
	Font& font;
	Player& player;

    Clock keyTimer;
	float keyTimeMax;
	//Tabs

	void initTabs();
    void initKeyTime();
public:
	PlayerGUITabs(VideoMode& vm, Font& font, Player& player);
	virtual ~PlayerGUITabs();

    bool getKeyTime();
    bool tabsOpen();
    void toggleTab(int tab_index);

	//Functions
	void update();
	void render(RenderTarget& target);
};