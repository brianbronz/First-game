#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Bow.h"
#include "Sword.h"
#include "Enemy.h"
#include "TextTagSystem.h"

class GameState : public State{
    private: 
        View view;
        Vector2i viewGridPosition;
        RenderTexture renderTexture;
        Sprite renderSprite;
        Font font;
        PauseMenu* pMenu;
        Shader core_shader;

        Clock keyTimer;
    	float keyTimeMax;

        Player* player;
        PlayerGUI* playerGUI;
	    Texture texture;
        TileMap* map;
        
        //Systems
        TextTagSystem* tts;

        vector<Enemy*> activeEnemies;
        EnemySystem *enemySystem;
        //functions
        void initDeferredRender();
        void initView();
        void initKeybinds();
        void initFonts();
        void initTextures();
        void initPauseMenu();
        void initKeyTime();
        void initShaders();
	    void initPlayers();
        void initPlayerGUI();
        void initEnemySystem();
        void initTileMap();
        void initSystems();
    public:
        GameState(StateData* state_data);
	    virtual ~GameState();

        //Accessors
        bool getKeyTime();
        //Functions
        void updateView(float& dt);
        void updateInput( float& dt);
        void updatePlayerInput(float& dt);
        void updatePlayerGUI(float& dt);
        void updatePauseMenuButtons();
        void updateTileMap(float& dt);
        void update( float& dt);
        void updatePlayer(float& dt);
	    void updateCombatAndEnemies(Enemy* enemy, int index, float& dt);
        void render(RenderTarget* target = NULL);
        void updateCombat(const float & dt)
};

#endif