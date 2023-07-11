#ifndef STATE_H
#define STATE_H
#include "Player.h"
#include "GraphicsSettings.h"
//keep resources
class Player;
class GraphicsSettings;
class State;
class StateData
{
public:
	StateData() {};
	//Variables
	float gridSize;
	RenderWindow* window;
	GraphicsSettings* gfxSettings;
	::map<string, int>* supportedKeys;
	stack<State*>* states;
};
class State{
    protected:
        StateData* stateData;
        stack<State*>* states;
        RenderWindow* window; //DA GUARDARE
        map<string, int>* supportedKeys;
        map<string, int> keybinds;
        bool quit;
        bool paused;
        float keytime;
        float keytimeMax;
        float gridSize;

        Vector2i mousePosScreen;
        Vector2i mousePosWindow;
        Vector2f mousePosView;
        Vector2u mousePosGrid;
        //resources
        map<string, Texture> textures;

        //function
        virtual void initKeybinds() = 0;
    public:
        State(StateData* state_data);
        virtual ~State();

        bool& getQuit();
        bool getKeytime();
        void endState();
        void pauseState();
        void unpauseState();
        
        void updateMousePositions(View* view = NULL);
        virtual void updateKeytime( float& dt);
        virtual void updateInput( float& dt) = 0;
        virtual void update( float& dt) = 0;//implement in the subclass for the inherit
        virtual void render(RenderTarget* target = NULL) = 0;
};

#endif