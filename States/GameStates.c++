#include "../Header/GameState.h"
#include "../Entities/Enemy.c++"
#include "../Entities/Player.c++"
#include "../Entities/PlayerGUI.c++"
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
			static_cast<float>(this->stateData->gfxSettings->resolution.width / 2),
			static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)
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
	if (!this->textures["PLAYER_IDLE"].loadFromFile("../Source Files/Resources/Images/Sprites/Player/PLAYER_SHEET2.png")){//change test with name file for animation
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
	}
    if(!this->textures["RAT1_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/rat1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT1_TEXTURE";
	}
}

void GameState::initPauseMenu(){
    
    const VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pMenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);
    this->pMenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
    this->activeEnemies.push_back(new Enemy(200.f, 100.f, this->textures["RAT1_SHEET"]));
	this->activeEnemies.push_back(new Enemy(500.f, 200.f, this->textures["RAT1_SHEET"]));
	this->activeEnemies.push_back(new Enemy(600.f, 300.f, this->textures["RAT1_SHEET"]));
	this->activeEnemies.push_back(new Enemy(400.f, 500.f, this->textures["RAT1_SHEET"]));
	this->activeEnemies.push_back(new Enemy(200.f, 400.f, this->textures["RAT1_SHEET"]));
}

void GameState::initShaders(){
	if (!this->core_shader.loadFromFile("../States/vertex_shader.vert", "../States/fragment_shader.frag")){
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void GameState::initPlayers(){
	this->player = new Player(220, 220, this->textures["PLAYER_IDLE"]);
}

void GameState::initPlayerGUI(){
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initTileMap(){
    //this->map = new TileMap(this->stateData->gridSize, 1000, 1000, "../Source Files/Resources/Images/Tiles/tilesheet1.png");
    //this->map->loadFromFile("../Maps code/text.slmp");
    this->map = new TileMap("../Maps code/text.slmp");
}

//Constructors / Destructors
GameState::GameState(StateData* state_data): State(state_data){
    this->initDeferredRender();
    this->initView();
	this->initKeybinds();
    this->initFonts();
	this->initTextures();
    this->initPauseMenu();
    this->initShaders();
	this->initPlayers();
    this->initPlayerGUI();
    this->initTileMap();
}

GameState::~GameState(){
    delete this->pMenu;
    delete this->player;
    delete this->playerGUI;
    delete this->map;
    for (size_t i = 0; i < this->activeEnemies.size(); i++){
		delete this->activeEnemies[i];
	}
}

void GameState::updateView(const float & dt){
	this->view.setCenter(
        floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 10.f),
		floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
    );
    if (this->map->getMaxSizeF().x >= this->view.getSize().x){
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f){
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		} else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->map->getMaxSizeF().x){
			this->view.setCenter(this->map->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->map->getMaxSizeF().y >= this->view.getSize().y){
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f){
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		} else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->map->getMaxSizeF().y){
			this->view.setCenter(this->view.getCenter().x, this->map->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}

    this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void GameState::updateInput( float& dt){
    if(Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()){
        (this->paused)? this->unpauseState(): this->pauseState();
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

void GameState::updatePlayerGUI(float & dt){
	this->playerGUI->update(dt);
}

void GameState::updatePauseMenuButtons(){
    if(this->pMenu->isButtonPressed("QUIT")){
        this->endState();
    }
}

void GameState::updateTileMap(float & dt){
	this->map->update(this->player, dt);
    for (int i = 0; i < this->activeEnemies.size(); i++){
		this->map->update(this->activeEnemies[i], dt);
	}
}

void GameState::update(float& dt){
    this->updateMousePositions(&this->view);
    this->updateKeytime(dt);
    this->updateInput(dt);
    if(this->paused){
        this->pMenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();
    } else {
        this->updateView(dt);
        this->updatePlayerInput(dt);
        this->updateTileMap(dt);
        this->player->update(dt, this->mousePosView);
        this->playerGUI->update(dt);
        for (int i = 0;  i < this->activeEnemies.size(); i++){
			this->activeEnemies[i]->update(dt, this->mousePosView);
		}	
    }
}

void GameState::render(RenderTarget* target){
    if (!target){
        target = this->window;
    }
	this->renderTexture.clear();
	this->renderTexture.setView(this->view);
    this->map->render(this->renderTexture, this->viewGridPosition, &this->core_shader, this->player->getCenter(), false);
    for (int i = 0;  i < this->activeEnemies.size(); i++){
		this->activeEnemies[i]->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
	}
    this->player->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
    this->map->renderDeferred(this->renderTexture, &this->core_shader, this->player->getCenter());
    //Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);
    if(this->paused){
		this->pMenu->render(this->renderTexture);
	}
	//FINAL RENDER
	this->renderTexture.display();
	target->draw(this->renderSprite);
}