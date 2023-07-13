#include "../Header/SettingsState.h"

void SettingsState::initVariables(){
    this->modes = VideoMode::getFullscreenModes();
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

void SettingsState::initButtons(){//init the gui
    const VideoMode& vm = this->stateData->gfxSettings->resolution;
    //Background
	this->background.setSize(Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height))
	);

	if (!this->backgroundTexture.loadFromFile("../Source Files/Resources/Images/Backgrounds/bg2.png")){
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Buttons
    this->buttons["BACK"] = new gui::Button(gui::p2pX(72.f, vm), gui::p2pY(81.5f, vm),
		                                    gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		                                    &this->font, "Back", gui::calcCharSize(vm),
                                            Color::Black, Color::Black, Color::Black,
                                            Color::Blue, Color::Green, Color::Red);
    
    this->buttons["APPLY"] = new gui::Button(gui::p2pX(60.f, vm), gui::p2pY(81.5f, vm),
		                                    gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		                                    &this->font, "Apply", gui::calcCharSize(vm), 
                                            Color::Black, Color::Black, Color::Black,
                                            Color::Blue, Color::Green, Color::Red);
    
    //Modes
    vector<string> modes_str;
    for (int i = 0; i < this->modes.size(); i++){
        modes_str.push_back(to_string(this->modes[i].width)+ 'x' + to_string(this->modes[i].height));
    }
    //Drop down lists
    this->ddl["RESOLUTION"] = new gui::DropDownList(gui::p2pX(42.f, vm), gui::p2pY(42.f, vm),
		                                            gui::p2pX(10.4f, vm), gui::p2pY(4.5f, vm),
		                                            font, modes_str.data(), modes_str.size());

    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(Vector2f(gui::p2pX(5.2f, vm), gui::p2pY(41.7f, vm)));
	this->optionsText.setCharacterSize(gui::calcCharSize(vm, 70));
    this->optionsText.setFillColor(Color::Black);
    this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing\n\n");
}

void SettingsState::resetGui(){
	/*
	 * Clears the GUI elements and re-initialises the GUI.
	 *
	 * @return void
	 */
    for (map<string, gui::Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it){
        delete it->second;
    }

	this->buttons.clear();

    for (map<string, gui::DropDownList*>::iterator it = this->ddl.begin(); it != this->ddl.end(); ++it){
        delete it->second;
    }

	this->ddl.clear();
	this->initButtons();
}

SettingsState::SettingsState(StateData* state_data): State(state_data) {
    this->initVariables();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
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
        this->stateData->gfxSettings->resolution = this->modes[this->ddl["RESOLUTION"]->getActiveElementId()];
		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, Style::Default);
        this->resetGui();
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