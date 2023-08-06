#ifndef DEFAULTEDITORMODE_H
#define DEFAULTEDITORMODE_H

#include "EditorMode.h"
#include "AllReference.h"

class DefaultEditorMode :
	public EditorMode
{
private:
	Text cursorText;
	RectangleShape sidebar;
	RectangleShape selectorRect;
	gui::TextureSelector* textureSelector;
	IntRect textureRect;
	bool collision;
	short type;
	int layer;
	bool tileAddLock;

	void initVariables();
	void initGui();

public:
	DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~DefaultEditorMode();

	void updateInput(float& dt);
	void updateGui(float& dt);
	void update(float& dt);

	void renderGui(RenderTarget& target);
	void render(RenderTarget& target);
};

#endif //!DEFAULTEDITORMODE_H