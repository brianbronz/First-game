#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H
#include "Gui.h"
#include "State.h"
class SettingsState: public State{
    private:
        GraphicsSettings& gfxSettings;
        Texture backgroundTexture;
        RectangleShape background;
        Font font;
        map<string, gui::Button*> buttons;
        map<string, gui::DropDownList*> ddl;
        Text optionsText;
        vector<VideoMode> modes;
        //functions
        void initVariables();
        void initBackground();
        void initFonts();
        void initKeybinds();
	    void initButtons();
        void initText();
    public:
        SettingsState(RenderWindow* window, GraphicsSettings& gfxSettings, map<string, int>* supportedKeys, stack<State*>* states);
        virtual ~SettingsState();

        void updateInput( float& dt);
        void updateButtons( float& dt);
        void update( float& dt);
        void renderButtons(RenderTarget& target);
        void render(RenderTarget* target = NULL);
};
#endif