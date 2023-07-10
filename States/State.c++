#include "../Header/State.h"

State::State(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states){
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->quit = false;
    this->states = states;
    this->paused = false;
    this->keytime = 0.f;
    this->keytimeMax = 10.f;
}

State::~State(){
    
}

 bool & State::getQuit(){
    return this->quit;
}

bool State::getKeytime(){
    if(this->keytime >= this->keytimeMax){
        this->keytime = 0.f;
        return true;
    }
    return false;
}

void State::endState(){
    this->quit = true;
}

void State::pauseState(){
    this->paused = true;
}

void State::unpauseState(){
    this->paused = false;
}
void State::updateMousePositions(View* view){
    this->mousePosScreen = Mouse::getPosition();
    this->mousePosWindow = Mouse::getPosition(*this->window);
    if(view){
		this->window->setView(*view);
    }
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = Vector2u(
			static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
			static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize)
		);
	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime( float& dt){
    if(this->keytime < this->keytimeMax){
        this->keytime += 100.f * dt;
    }
}