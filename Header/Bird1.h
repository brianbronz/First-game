#pragma once

#include "Enemy.h"

class Bird1 :
    public Enemy
{
private:
	void initVariables();
	void initAnimations();
	void initAI();
	void initGUI();

	RectangleShape hpBar;

	AIFollow* follow;

public:
	Bird1(float x, float y, Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player);
	virtual ~Bird1();

	//Functions
	void updateAnimation(float& dt);
	void update(float& dt, Vector2f& mouse_pos_view, View& view);

	void render(RenderTarget& target, Shader* shader, const Vector2f light_position, const bool show_hitbox);
};