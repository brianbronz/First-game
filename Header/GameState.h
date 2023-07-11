#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"


class GameState : public State{
    private: 
        View view;
        RenderTexture renderTexture;
        Sprite renderSprite;
        Font font;
        PauseMenu* pMenu;
        Player* player;
	    Texture texture;
        TileMap* map;
        //functions
        void initDeferredRender();
        void initView();
        void initKeybinds();
        void initFonts();
        void initTextures();
        void initPauseMenu();
	    void initPlayers();
        void initTileMap();
    public:
        GameState(StateData* state_data);
	    virtual ~GameState();

        //Functions
        void updateView(const float& dt);
        void updateInput( float& dt);
        void updatePlayerInput(float& dt);
        void updatePauseMenuButtons();
        void updateTileMap(float& dt);
        void update( float& dt);
        void render(RenderTarget* target = NULL);
};

#endif