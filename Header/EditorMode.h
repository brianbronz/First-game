#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "State.h"
#include "TileMap.h"
#include "Gui.h"
#include "AllReference.h"

class EditorStateData
{
public:
	EditorStateData() {};

	//Variables
	View* view;
	
	Font* font;

	float* keytime;
	float* keytimeMax;

	std::map<string, int>* keybinds;

	Vector2i* mousePosScreen;
	Vector2i* mousePosWindow;
	Vector2f* mousePosView;
	Vector2i* mousePosGrid;
};

class EditorMode
{
private:

protected:
	StateData* stateData;
	EditorStateData* editorStateData;
	TileMap* tileMap;

public:
	EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~EditorMode();

	//Functions
	bool getKeytime();

	virtual void updateInput(float& dt) = 0;
	virtual void updateGui(float& dt) = 0;
	virtual void update(float& dt) = 0;

	virtual void renderGui(RenderTarget& target) = 0;
	virtual void render(RenderTarget& target) = 0;
};

#endif //!EDITORMODE_H