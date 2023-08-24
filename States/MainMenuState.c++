#include "../Header/MainMenuState.h"
#include "../Source Files/Gui.c++"
#include "GameStates.c++"
#include "../States/SettingsState.c++"
//Initializer functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initFonts(){
    if(!this->font.loadFromFile("../Fonts/Dosis-Light.ttf")){
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initKeybinds(){
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

void MainMenuState::initGui(){
    
    VideoMode& vm = this->stateData->gfxSettings->resolution;
    //Background
    this->background.setSize(
		Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height))
	);
	if (!this->backgroundTexture.loadFromFile("../Source Files/Resources/Images/Backgrounds/bg2.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

    //Button background
	this->btnBackground.setSize(
		Vector2f(
			static_cast<float>(vm.width / 5), 
			static_cast<float>(vm.height)
		)
	);

	this->btnBackground.setPosition(gui::p2pX(11.5f, vm), 0.f);
	this->btnBackground.setFillColor(Color(10, 10, 10, 220));

    //Buttons
    this->buttons["GAME_STATE"] = new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(44.4f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
        &this->font, "New Game", gui::calcCharSize(vm),
        Color::Black, Color::Black, Color::Black,
        Color::Red, Color::Green, Color::Blue);

    this->buttons["SETTINGS_STATE"] = new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(53.7f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), 
        &this->font, "Settings", gui::calcCharSize(vm),
        Color::Black, Color::Black, Color::Black,
        Color::Red, Color::Green, Color::Blue);

    this->buttons["EXIT_STATE"] = new gui::Button(gui::p2pX(15.6f, vm), gui::p2pY(63.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), 
        &this->font, "QUIT", gui::calcCharSize(vm),
        Color::Black, Color::Black, Color::Black,
        Color::Red, Color::Green, Color::Blue);
}

void MainMenuState::resetGui()
{
	/*
	 * Clears the GUI elements and re-initialises the GUI.
	 */
	for (std::map<string, gui::Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it){
		delete it->second;
	}
	this->buttons.clear();
	this->initGui();
}


MainMenuState::MainMenuState(StateData* state_data): State(state_data){
    this->initVariables();
    this->initFonts();
    this->initKeybinds();
	this->initGui();
	this->resetGui();
}

MainMenuState::~MainMenuState(){
    for (std::map<string, gui::Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it){
        delete it->second;
    }
}


void MainMenuState::updateInput( float & dt){

}

void MainMenuState::updateButtons(){
    //Update all the buttons in the state and handles their functionality
    for (std::map<string, gui::Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        it->second->update(this->mousePosWindow);
    }

    //New game
    if(this->buttons["GAME_STATE"]->isPressed()){
        this->states->push(new GameState(this->stateData));
    }
    //Quit the game
    if(this->buttons["EXIT_STATE"]->isPressed()){
        this->endState();
    }

    //Quit the game
    if(this->buttons["SETTINGS_STATE"]->isPressed()){
         this->states->push(new SettingsState(this->stateData));
    } 
}

void MainMenuState::update(float& dt){
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
}

void MainMenuState::renderButtons(RenderTarget& target){
    for (std::map<string, gui::Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        it->second->render(target);
    }
}

void MainMenuState::render(RenderTarget* target){
    if (!target){
        target = this->window;
    }
    target->draw(this->background);
    target->draw(this->btnBackground);
    this->renderButtons(*target);
   	//REMOVE LATER!!! for debugging positions
/* 	Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText); */
}