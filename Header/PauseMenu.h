#ifndef PAUSEMENU_H 
#define PAUSEMENU_H
#include "AllReference.h"
#include "Gui.h"

class PauseMenu{
    private:
        Font& font;
        Text menuText;
        RectangleShape background;
        RectangleShape container;
        map<string, gui::Button*> buttons;

    public:
        PauseMenu(VideoMode& vm, Font& font);
        virtual ~PauseMenu();

        //Accessors
        map<string, gui::Button*>& getButtons();
        //Functions
        bool isButtonPressed(string key);
        void addButton(const string key, const float y, const float width, const float height, const unsigned char_size, const string text);
        void update(Vector2i& mousePosWindow);
        void render(RenderTarget& target);
};
#endif