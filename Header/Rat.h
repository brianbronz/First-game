#ifndef RAT_H
#define RAT_H

#include "Enemy.h"

class Rat : public Enemy{
private:
	void initVariables();
	void initAnimations();
	void initAI();
	void initGUI();

	RectangleShape hpBar;
	AIFollow* follow;
public:
	Rat(const float x, const float y, Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player);
	virtual ~Rat();

	//Functions
	void updateAnimation(float & dt);
	void update(float & dt, Vector2f& mouse_pos_view, View& view);

	void render(RenderTarget & target, Shader* shader, Vector2f light_position, bool show_hitbox);
};

#endif //!RAT