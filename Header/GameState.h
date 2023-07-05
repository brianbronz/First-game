#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"

class GameState : public State{
    private: 
        Font font;
        PauseMenu* pMenu;
        Player* player;
	    Texture texture;

        //functions
        void initKeybinds();
        void initFonts();
        void initTextures();
        void initPauseMenu();
	    void initPlayers();
    public:
        GameState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
	    virtual ~GameState();

        //Functions
        void updateInput(const float& dt);
        void uodatePlayerInput(float& dt);
        void updatePauseMenuButtons();
        void update(const float& dt);
        void render(RenderTarget* target = NULL);
};

#endif