#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class GameState : public State{
    private: 
        Font font;
        PauseMenu* pMenu;
        Player* player;
	    Texture texture;
        TileMap map;
        //functions
        void initKeybinds();
        void initFonts();
        void initTextures();
        void initPauseMenu();
	    void initPlayers();
    public:
        GameState(RenderWindow* window, ::map<string, int>* supportedKeys, stack<State*>* states);
	    virtual ~GameState();

        //Functions
        void updateInput( float& dt);
        void updatePlayerInput(float& dt);
        void updatePauseMenuButtons();
        void update( float& dt);
        void render(RenderTarget* target = NULL);
};

#endif