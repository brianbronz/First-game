#include "../Header/MainMenuState.h"
#include "../Source Files/Button.c++"
#include "GameStates.c++"
//#include "State.c++"

//Initializer functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
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

void MainMenuState::initButtons(){
    this->buttons["GAME_STATE"] = new Button(771.f, 826.f, 250.f, 70.f, 
        &this->font, "New Game", 50,
        Color::Black, Color::Black, Color::Black,
        Color::Red, Color::Green, Color::Blue);

    this->buttons["SETTINGS"] = new Button(771, 1012, 250, 70, &this->font, "Settings", 50,
        Color::Black, Color::Black, Color::Black,
        Color::Red, Color::Green, Color::Blue);

    this->buttons["EXIT_STATE"] = new Button(771, 1198, 250, 70, &this->font, "QUIT", 50,
        Color::Black, Color::Black, Color::Black,
        Color::Red, Color::Green, Color::Blue);
}

MainMenuState::MainMenuState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states){
    this->initVariables();
	this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

MainMenuState::~MainMenuState(){
    for (map<std::string, Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it){
        delete it->second;
    }
}


void MainMenuState::updateInput(const float & dt){

}

void MainMenuState::updateButtons(){
    //Update all the buttons in the state and handles their functionality
    for (map<std::string, Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        it->second->update(this->mousePosView);
    }

    //New game
    if(this->buttons["GAME_STATE"]->isPressed()){
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }
    //Quit the game
    if(this->buttons["EXIT_STATE"]->isPressed()){
        this->endState();
    }
}

void MainMenuState::update(const float& dt){
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
}

void MainMenuState::renderButtons(RenderTarget* target){
    for (map<std::string, Button*>::iterator it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        it->second->render(target);
    }
}

void MainMenuState::render(RenderTarget* target){
    if (!target){
        target = this->window;
    }
    target->draw(this->background);

   this->renderButtons(target);
   	//REMOVE LATER!!! for debugging positions
/* 	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText); */
}