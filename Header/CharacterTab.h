#pragma once

#include "Tab.h"

class CharacterTab : public Tab
{
private:
	RectangleShape back;
	Text infoText;

    void initText();
public:
	CharacterTab(VideoMode& vm, Font& font, Player& player);
	~CharacterTab();

	void update();
	void render(RenderTarget& target);
};

