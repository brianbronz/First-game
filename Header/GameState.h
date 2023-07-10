#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class PauseMenu;
class Player;
class TileMap;
class View;
class Font;
class RenderTexture;

class GameState : public State{
    private: 
        View view;
        RenderTexture renderTexture;
        Sprite renderSprite;
        Font font;
        PauseMenu* pMenu;
        Player* player;
	    Texture texture;
        TileMap map;
        //functions
        void initView();
        void initKeybinds();
        void initFonts();
        void initTextures();
        void initPauseMenu();
	    void initPlayers();
    public:
        GameState(RenderWindow* window, ::map<string, int>* supportedKeys, stack<State*>* states);
	    virtual ~GameState();

        //Functions
        void updateView(const float& dt);
        void updateInput( float& dt);
        void updatePlayerInput(float& dt);
        void updatePauseMenuButtons();
        void update( float& dt);
        void render(RenderTarget* target = NULL);
};

#endif