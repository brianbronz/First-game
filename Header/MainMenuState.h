#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Gui.h"
#include "SettingsState.h"
class MainMenuState:public State{
    private: 
        //Field variables
        Texture backgroundTexture;
        RectangleShape background;
        Font font;

        RectangleShape btnBackground;
        map<string, gui::Button*> buttons;

        //functions
        void initVariables();
        void initFonts();
        void initKeybinds();
        void initGui();
	    void resetGui();
    public:
        MainMenuState(StateData* state_data);
	    virtual ~MainMenuState();

        //Functions
        void updateInput( float& dt);
        void updateButtons();
        void update( float& dt);
        void renderButtons(RenderTarget& target);
        void render(RenderTarget* target = NULL);
};
#endif