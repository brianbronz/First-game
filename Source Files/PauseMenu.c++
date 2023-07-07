#include "../Header/PauseMenu.h"

PauseMenu::PauseMenu(RenderWindow& window, Font& font): font(font){
    //init background
    this->background.setSize(Vector2f(
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)
    ));
    this->background.setFillColor(Color::Black);
    //Init container
    this->container.setSize(Vector2f(
        static_cast<float>(window.getSize().x) / 4.f,
        static_cast<float>(window.getSize().y) - 60.f
    ));
    this->container.setFillColor(Color::Blue);
    this->container.setPosition( static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 30.f);

    //Init text
    this->menuText.setFont(font);
    this->menuText.setFillColor(Color::Black);
    this->menuText.setCharacterSize(60);
    this->menuText.setString("PAUSED");
    this->menuText.setPosition(
        this->container.getPosition().x + this->container.getPosition().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
        this->container.getPosition().y + 40.f
    );
}

PauseMenu::~PauseMenu(){
    for (map<string, gui::Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it){
        delete it->second;
    }
}

map<string, gui::Button*>& PauseMenu::getButtons(){
    return this->buttons;
}

bool PauseMenu::isButtonPressed(string key){
    return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(string key, float y, string text){
    float width = 250.f;
    float height = 50.f;
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
    this->buttons[key] = new gui::Button(x, y, width, height, &this->font, text, 50, 
    Color::Black, Color::Black, Color::Black,
    Color::Blue, Color::Green, Color::Red);
}

void PauseMenu::update(Vector2f& mousePos){
    for (map<string, gui::Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second->update(mousePos);    
    }
}

void PauseMenu::render(RenderTarget& target){
    target.draw(this->background);
    target.draw(this->container);
    for (map<string, gui::Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second->render(target);
    }
    target.draw(this->menuText);
}