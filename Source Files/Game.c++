#include "../Header/Game.h"
#include "../Header/MainMenuState.h"
#include "../States/MainMenuState.c++"
using namespace std;

//static functions
void Game::initVariables(){
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.f;
}

//Initialize functions
void Game::initWindow(){
    //initialize the window from the window configuration
    ifstream ifs("../Config/window.ini");
    this->videoModes = VideoMode::getFullscreenModes();
    bool fullscreen = false;

    string title = "None";
    VideoMode windowBounds = VideoMode::getDesktopMode();
    unsigned framerateLimit = 120;
    bool verticalSync = false;
    unsigned antialiasingLevel = 0;

    if(ifs.is_open()){
        getline(ifs, title);
        ifs >> windowBounds.width >> windowBounds.height;
        ifs >> fullscreen;
        ifs >> framerateLimit;
        ifs >> verticalSync;
        ifs >> antialiasingLevel;
    }
    ifs.close();
    this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasingLevel;

	(this->fullscreen)?
		this->window = new RenderWindow(windowBounds, title, Style::Fullscreen, windowSettings):
		this->window = new RenderWindow(windowBounds, title, Style::Titlebar | Style::Close, windowSettings);	

    this->window->setFramerateLimit(framerateLimit);
    this->window->setVerticalSyncEnabled(verticalSync);
    
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

void Game::initStates(){
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

//constructors/destructors
Game::Game(){
    this->initWindow();
    this->initKeys();
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
        
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit()){
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    //Application end
    else{
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