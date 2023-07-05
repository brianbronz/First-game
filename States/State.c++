#include "../Header/State.h"

State::State(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states){
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->quit = false;
    this->states = states;
    this->paused = false;
}

State::~State(){
    
}

const bool & State::getQuit(){
    return this->quit;
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
void State::updateMousePositions(){
    this->mousePosScreen = Mouse::getPosition();
    this->mousePosWindow = Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
}