#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"
#include "SettingsState.h"
class MainMenuState:public State{
    private: 
        //Field variables
        Texture backgroundTexture;
        RectangleShape background;
        Font font;

        map<string, Button*> buttons;

        //functions
        void initVariables();
	    void initBackground();
        void initFonts();
        void initKeybinds();
        void initButtons();
    public:
        MainMenuState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
	    virtual ~MainMenuState();

        //Functions
        void updateInput(const float& dt);
        void updateButtons();
        void update(const float& dt);
        void renderButtons(RenderTarget& target);
        void render(RenderTarget* target = NULL);
};
#endif