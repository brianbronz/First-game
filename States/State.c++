#include "../Header/State.h"

State::State(StateData* state_data){
    this->stateData = state_data;
    this->window = state_data->window;
    this->supportedKeys = state_data->supportedKeys;
    this->states = state_data->states;
    this->quit = false;
    this->paused = false;
    this->keytime = 0.f;
    this->keytimeMax = 10.f;
    this->gridSize = state_data->gridSize;
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
    this->mousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
    if (this->gridSize == 0){this->gridSize = 64.f;}
	this->mousePosGrid = Vector2i(
			static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
			static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize)
		);
	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime( float& dt){
    if(this->keytime < this->keytimeMax){
        this->keytime += 100.f * dt;
    }
}