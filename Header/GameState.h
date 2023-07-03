#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
class GameState : public State{
    private: 
        Player* player;
	    Texture texture;

        //functions
        void initKeybinds();
        void initTextures();
	    void initPlayers();
    public:
        GameState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
	    virtual ~GameState();

        //Functions
        void updateInput(const float& dt);
        void update(const float& dt);
        void render(RenderTarget* target = NULL);
};

#endif