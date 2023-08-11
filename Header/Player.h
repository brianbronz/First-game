#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Items.h"
#include "Inventory.h"

class Player :
	public Entity
{
private:
	//Variables
	Inventory* inventory;

	bool initAttack;
	bool attacking;
	Weapon* weapon;

	Clock damageTimer;
	Int32 damageTimerMax;

	//Initializer functions
	void initVariables();
	void initComponents();
	void initAnimation();
	void initInventory();

public:
	Player(float x, float y, Texture& textureSheet);
	virtual ~Player();
	//Accessors
	AttributeComponent* getAttributeComponent();
	Weapon* getWeapon();

	string toStringCharacterTab();
	bool& getInitAttack();

	bool getDamageTimer();
	unsigned getDamage();

	//Modifier
	void setInitAttack(bool initAttack);
	//Functions
	void loseHP(int hp);
	void gainHP(int hp);
	void loseEXP(int exp);
	void gainEXP(int exp);

	void updateAnimation( float& dt);
	void update(float& dt, Vector2f& mouse_pos_view);

	void render(RenderTarget& target, Shader* shader = NULL, Vector2f lightPosition = Vector2f(), bool show_hitbox = false);
};

#endif