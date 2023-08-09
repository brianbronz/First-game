#ifndef RAT_H
#define RAT_H

#include "Enemy.h"

class Rat : public Enemy{
private:
	void initVariables();
	void initAnimations();
	void initGUI();

	RectangleShape hpBar;
public:
	Rat(float x, float y, Texture& texture_sheet);
	virtual ~Rat();

	//Functions
	void updateAnimation(float & dt);
	void update(float & dt, Vector2f& mouse_pos_view);

	void render(RenderTarget & target, Shader* shader, Vector2f light_position, bool show_hitbox);
};

#endif //!RAT