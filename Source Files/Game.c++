#include "../Header/Game.h"
#include "../Header/MainMenuState.h"
#include "../States/MainMenuState.c++"
#include "../Graphics Setting/GraphicsSettings.c++"
//static functions
void Game::initVariables(){
	this->window = NULL;
	this->dt = 0.f;
    this->gridSize = 64.f;
}

//Initialize functions
void Game::initGraphicsSettings(){
    this->gfxSettings.loadFromFile("../Config/Graphics.ini");
}
void Game::initWindow(){
    //initialize the window from the window configuration
    if(this->gfxSettings.fullscreen){
        this->window = new RenderWindow(
        this->gfxSettings.resolution, 
        this->gfxSettings.title, 
        Style::Fullscreen, 
        this->gfxSettings.contextSettings);
    } else {
        this->window = new RenderWindow(
        this->gfxSettings.resolution,
        this->gfxSettings.title,
        Style::Titlebar | Style::Close, 
        this->gfxSettings.contextSettings);
    }
    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys(){
    //how to move using the keyboard
    ifstream ifs("../Config/SupportedKeys.ini");
    if(ifs.is_open()){
        string key = "";
        int key_value = 0;
        while(ifs >> key >> key_value){
            this->supportedKeys[key] = key_value;
        }
    } 
    ifs.close();
}

void Game::initStateData(){
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Game::initStates(){
    this->states.push(new MainMenuState(&this->stateData));
}

//ructors/destructors
Game::Game(){
    this->initVariables();
	this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Game::~Game(){
    delete this->window;
    while(!this->states.empty()){
        delete this->states.top(); //remove only the data
        this->states.pop();
    }
}

//Functions
void Game::endApplication(){
    
}

void Game::updateDt(){
    /*
        updates the dt variable with the time it takes
        to update and render one frame.
    */
    this->dt = this->dtClock.restart().asSeconds();   
}

void Game::updateSFMLEvents(){
    while(this->window->pollEvent(this->sfEvent)){
        if(this->sfEvent.type == Event::Closed){
            this->window->close();
        }
    }
}

void Game::update(){
    this->updateSFMLEvents();
     if(!this->states.empty()){
        if (this->window->hasFocus()){
            this->states.top()->update(this->dt);
            if (this->states.top()->getQuit()){
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
        }
    }//Application end
    else {
        this->endApplication();
        this->window->close();
    }
}



void Game::render(){
    this->window->clear();
    
    //Render items
    if(!this->states.empty()){
        this->states.top()->render();
    }
    this->window->display();
}

void Game::run(){
    while(this->window->isOpen()){
        this->updateDt();
        this->update();
        this->render();
    }
}