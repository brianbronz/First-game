#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Sword.h"

class Player :
	public Entity
{
private:
	//Variables
	bool attacking;
	Sword sword;
	//Initializer functions
	void initVariables();
	void initComponents();
	void initAnimation();

public:
	Player(float x, float y, Texture& textureSheet);
	virtual ~Player();
	//Accessors
	AttributeComponent* getAttributeComponent();

	//Functions
	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);

	void updateAttack();
	void updateAnimation( float& dt);
	void update(float& dt, Vector2f& mouse_pos_view);

	void render(RenderTarget& target, Shader* shader = NULL, Vector2f lightPosition = Vector2f(), bool show_hitbox = false);
};

#endif