#ifndef TAB_H
#define TAB_H

#include "Player.h"
#include "Gui.h"

class Tab
{
protected:
	VideoMode& vm;
	Font& font;
	Player& player;
    bool hidden;

public:
	Tab(VideoMode& vm, Font& font, Player& player, bool hidden);
	virtual ~Tab();

    //Accessor
	bool& getHidden();
    bool getOpen() const;
	void toggle();
	//Functions
	void hide();
	void show();

	virtual void update() = 0;
	virtual void render(RenderTarget& target) = 0;
};
#endif