#ifndef PLAYERGUI_H
#define PLAYERGUI_H
#include "PlayerGUITabs.h"

class PlayerGUI
{
private:
	Player* player;
    VideoMode& vm;
	Font font;

    //Level bar
	string levelBarString;
	Text levelBarText;
	RectangleShape levelBarBack;

	//EXP Bar
/* 	string expBarString;
	Text expBarText;
	float expBarMaxWidth;
	RectangleShape expBarBack;
	RectangleShape expBarInner; */
	gui::ProgressBar* expBar;

	//HP Bar
/* 	string hpBarString;
	Text hpBarText;

	float hpBarMaxWidth;
	RectangleShape hpBarBack;
	RectangleShape hpBarInner; */
	gui::ProgressBar* hpBar;

	PlayerGUITabs* playerTabs;
	
	void initFont();
    void initLevelBar();
	void initEXPBar();
	void initHPBar();
	void initPlayerTabs(VideoMode &vm, Font &font, Player &player);

public:
	PlayerGUI(Player* player, VideoMode& vm);
	virtual ~PlayerGUI();

	bool getTabsOpen();
	void toggleCharacterTab();
	//Functions
    void updateLevelBar();
	void updateEXPBar();
	void updateHPBar();
	void updatePlayerTabs();

	void update(float& dt);

    void renderLevelBar(RenderTarget & target);
	void renderEXPBar(RenderTarget & target);
	void renderHPBar(RenderTarget & target);
	void renderPlayerTabs(RenderTarget& target);
	void render(RenderTarget& target);
};
#endif