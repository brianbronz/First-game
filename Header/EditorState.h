#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "AllReference.h"
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorModes.h"

enum EditorModes {DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE};

class EditorState :
	public State
{
private:
	//Variables
	EditorStateData editorStateData;

	View view;
	float cameraSpeed;

	Font font;
	PauseMenu* pmenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	std::vector<EditorMode*> modes;
	unsigned activeMode;

	//Functions
	void initVariables();
	void initEditorStateData();
	void initView();
	void initFonts();
	void initKeybinds();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();
	void initModes();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	//Functions
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void updateModes(const float& dt);
	void update(const float& dt);
	void renderButtons(RenderTarget& target);
	void renderGui(RenderTarget& target);
	void renderModes(RenderTarget& target);
	void render(RenderTarget* target = NULL);
};

#endif

