#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game{
    private:
        //fields variable
        GraphicsSettings gfxSettings;
        StateData stateData;
        RenderWindow *window;
        Event sfEvent;

        Clock dtClock;
        float dt;

        stack<State*> states;//State* because it is an abstract class
        std::map<string, int> supportedKeys;
        float gridSize;
        //initialization
        void initVariables();
        void initGraphicsSettings();
        void initWindow();
        void initKeys();
        void initStateData();
        void initStates();
    public:
        //ructor and destructor
        Game();
        virtual ~Game();

        //Functions

        //Regular
        void endApplication();
        //update
        void updateDt();
        void updateSFMLEvents();
        void update();

        //render
        void render();

        //core
        void run();
};

#endif