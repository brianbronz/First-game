#ifndef ENEMYEDITORMODE_H
#define ENEMYEDITORMODE_H

#include "EditorMode.h"
#include "EnemySpawner.h"
#include "AllReference.h"

class EnemyEditorMode :
	public EditorMode
{
private:
	Text cursorText;
	RectangleShape sidebar;
	RectangleShape selectorRect;

	void initVariables();
	void initGui();

public:
	EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~EnemyEditorMode();
	//Functions
	void updateInput(float& dt);
	void updateGui(float& dt);
	void update(float& dt);
	void renderGui(RenderTarget& target);
	void render(RenderTarget& target);
};
#endif //!ENEMYEDITORMODE_H