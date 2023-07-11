#include "../Header/GameState.h"
#include "../Entities/Player.c++"
#include "../Source Files/PauseMenu.c++"
#include "../Maps code/TileMap.c++"
#include "State.c++"

void GameState::initDeferredRender(){
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		IntRect(0, 0, this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height)
	);
}

void GameState::initView(){
    this->view.setSize(Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

    this->view.setCenter(Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width / 2.f),
			static_cast<float>(this->stateData->gfxSettings->resolution.height / 2.f)
		)
	);
}

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

void GameState::initTileMap(){
    	this->map = new TileMap(this->stateData->gridSize, 10, 10, "../Source Files/Resources/Images/Tiles/tilesheet1.png");
        this->map->loadFromFile("text.slmp");
}

//Constructors / Destructors
GameState::GameState(StateData* state_data): State(state_data){
    this->initDeferredRender();
    this->initView();
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

void GameState::updateView(const float & dt){
	this->view.setCenter(floor(this->player->getPosition().x),floor(this->player->getPosition().y));
}

void GameState::updateInput( float& dt){
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

void GameState::updateTileMap(float & dt){
	this->map->update();
	this->map->updateCollision(this->player, dt);
}

void GameState::update(float& dt){
    this->updateMousePositions(&this->view);
    this->updateKeytime(dt);
    this->updateInput(dt);
    if(!this->paused){
        this->updateView(dt);
        this->updateTileMap(dt);
        this->player->update(dt);
    } else {
        this->pMenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(RenderTarget* target){
    if (!target){
        target = this->window;
    }
	this->renderTexture.clear();
	this->renderTexture.setView(this->view);
	this->map->render(this->renderTexture, this->player);
    this->player->render(this->renderTexture);
    if(this->paused){
        target->setView(this->window->getDefaultView());
        this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pMenu->render(this->renderTexture);
	}
	//FINAL RENDER
	this->renderTexture.display();
	target->draw(this->renderSprite);
}