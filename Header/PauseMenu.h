#ifndef PAUSEMENU_H 
#define PAUSEMENU_H
#include "AllReference.h"
#include "Button.h"

class PauseMenu{
    private:
        Font& font;
        Text menuText;
        RectangleShape background;
        RectangleShape container;
        map<string, Button*> buttons;

    public:
        PauseMenu(RenderWindow& window, Font& font);
        virtual ~PauseMenu();

        //Accessors
        map<string, Button*>& getButtons();
        //Functions
        bool isButtonPressed(string key);
        void addButton(string key, float y, string text);
        void update(Vector2f& mousePos);
        void render(RenderTarget& target);
};
#endif