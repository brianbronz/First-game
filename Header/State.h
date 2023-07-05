#ifndef STATE_H
#define STATE_H
#include "Player.h"
//keep resources
class State{
    protected:
        stack<State*>* states;
        RenderWindow* window;
        map<string, int>* supportedKeys;
        map<string, int> keybinds;
        bool quit;
        bool paused;

        Vector2i mousePosScreen;
        Vector2i mousePosWindow;
        Vector2f mousePosView;
        //resources
        map<string, Texture> textures;

        //function
        virtual void initKeybinds() = 0;
    public:
        State(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
        virtual ~State();

        const bool& getQuit();
        void endState();
        void pauseState();
        void unpauseState();
        
        void updateMousePositions();
        virtual void updateInput(const float& dt) = 0;
        virtual void update(const float& dt) = 0;//implement in the subclass for the inherit
        virtual void render(RenderTarget* target = NULL) = 0;
};

#endif