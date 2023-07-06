#include "../Header/GameState.h"
#include "../Source Files/Player.c++"
#include "../Source Files/PauseMenu.c++"
#include "State.c++"

void GameState::initFonts(){
    if(!this->font.loadFromFile("../Fonts/Dosis-Light.ttf")){
        throw("ERROR::MAINMENUSTATE:: NOT ABLE TO LOAD ANY FONTS");
    }
}

void GameState::initKeybinds(){
    ifstream ifs("../Config/gameStateKeybinds.ini");
    if(ifs.is_open()){
        string key = "";
        string key2 = "";
        while(ifs >> key >> key2){
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();}

void GameState::initTextures(){
	if (!this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET.png")){//change test with name file for animation
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
	}
}

void GameState::initPauseMenu(){
    this->pMenu = new PauseMenu(*this->window, this->font);
    this->pMenu->addButton("QUIT", 800.f, "Quit");
}

void GameState::initPlayers(){
	this->player = new Player(100, 100, this->textures["PLAYER_IDLE"]);
}

//Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states){
	this->initKeybinds();
    this->initFonts();
	this->initTextures();
    this->initPauseMenu();
	this->initPlayers();
}

GameState::~GameState(){
    delete this->pMenu;
    delete this->player;
}

void GameState::updateInput(const float& dt){
    if(Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()){
        (this->paused)?
            this->unpauseState():
            this->pauseState();
    }
}

void GameState::updatePlayerInput(float& dt){
    //update player input
    if(Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_LEFT")))){
        this->player->move(-1.f, 0.f, dt);
    }
    if(Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_UP")))){
        this->player->move(0.f, -1.f, dt);
    }
    if(Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_DOWN")))){
        this->player->move(0.f, 1.f, dt);
    }
    if(Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))){
        this->player->move(1.f, 0.f, dt);
    }
}

void GameState::updatePauseMenuButtons(){
    if(this->pMenu->isButtonPressed("QUIT")){
        this->endState();
    }
}

void GameState::update(const float& dt){
    this->updateMousePositions();
    this->updateKeytime(dt);
    this->updateInput(dt);
    if(!this->paused){
        this->player->update(dt);
    } else {
        this->pMenu->update(this->mousePosView);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(RenderTarget* target){
    if (!target){
        target = this->window;
    }
    this->player->render(*target);
    if(this->paused){this->pMenu->render(*target);}
}