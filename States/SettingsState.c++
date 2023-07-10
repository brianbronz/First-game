#include "../Header/SettingsState.h"

void SettingsState::initVariables(){
    this->modes = VideoMode::getFullscreenModes();
}

void SettingsState::initBackground(){
    this->background.setSize(Vector2f(
        static_cast<float>(this->window->getSize().x),
        static_cast<float>(this->window->getSize().y)
    ));
    if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg2.png")){
        throw("ERROR::FAILED_TO_LOAD_BACKGROUND"); 
    }
    this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts(){
    if(!this->font.loadFromFile("../Fonts/Dosis-Light.ttf")){
        throw("ERROR::NOT LOAD FONT");
    }
}

void SettingsState::initKeybinds(){
    ifstream ifs("../Config/MainMenuStateKeybinds.ini");
    if(ifs.is_open()){
        string key = "";
        string key2 = "";
        while(ifs >> key >> key2){
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

void SettingsState::initButtons(){
    this->buttons["BACK"] = new gui::Button(1500.f, 880.f, 250.f, 65.f,
                                            &this->font, "Back", 50, 
                                            Color::Black, Color::Black, Color::Black,
                                            Color::Blue, Color::Green, Color::Red);
    
    this->buttons["APPLY"] = new gui::Button(1300.f, 880.f, 250.f, 65.f,
                                            &this->font, "Apply", 50, 
                                            Color::Black, Color::Black, Color::Black,
                                            Color::Blue, Color::Green, Color::Red);
    
    vector<string> modes_str;
    for (int i = 0; i < this->modes.size(); i++){
        modes_str.push_back(to_string(this->modes[i].width)+ 'x' + to_string(this->modes[i].height));
    }
    this->ddl["RESOLUTION"] = new gui::DropDownList(800, 450, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText(){
    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(Vector2f(100.f, 450.f));
    this->optionsText.setCharacterSize(30);
    this->optionsText.setFillColor(Color::Black);
    this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing\n\n");
}

SettingsState::SettingsState(RenderWindow* window, GraphicsSettings& gfxSettings, map<string, int>* supportedKeys, stack<State*>* states):State(window, supportedKeys, states), gfxSettings(gfxSettings) {
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
    this->initText();
}

SettingsState::~SettingsState(){
    for (map<string, gui::Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it){
        delete it->second;
    }

    for (map<string, gui::DropDownList*>::iterator it = this->ddl.begin(); it != this->ddl.end(); ++it){
        delete it->second;
    }
}

void SettingsState::updateInput( float & dt){

}

void SettingsState::updateButtons( float& dt){
    for (map<string, gui::Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second->update(this->mousePosWindow);
    }
    //Quit the game
    if (this->buttons["BACK"]->isPressed()){
        this->endState();
    }

    if (this->buttons["APPLY"]->isPressed()){
        this->gfxSettings.resolution = this->modes[this->ddl["RESOLUTION"]->getActiveElementId()];
		this->window->create(this->gfxSettings.resolution, this->gfxSettings.title, Style::Default);
	}

    for(map<string, gui::DropDownList*>::iterator it= this->ddl.begin(); it != this->ddl.end(); ++it){
        it->second->update(this->mousePosWindow, dt);
    }
}

void SettingsState::update( float& dt){
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons(dt);
}

void SettingsState::renderButtons(RenderTarget& target){
    for (map<string, gui::Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it){
        it->second->render(target);
    }

    for (map<string, gui::DropDownList*>::iterator it = this->ddl.begin(); it != this->ddl.end(); ++it){
        it->second->render(target);
    }
}

void SettingsState::render(RenderTarget* target){
    if(!target){
        target = this->window;
    }
    target->draw(this->background);
    this->renderButtons(*target);
    target->draw(this->optionsText);
}