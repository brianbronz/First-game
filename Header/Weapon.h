#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item{
private:
	void initVariables();

protected:
	Texture weapon_texture;
	Sprite weapon_sprite;

	unsigned damageMin;
	unsigned damageMax;
	unsigned range;

	Clock attackTimer;
	Int32 attackTimerMax;

public:
	Weapon(unsigned level, unsigned value, string texture_file);
	Weapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, string texture_file);
	virtual ~Weapon();

	//Accessors
	unsigned getDamage() const;
	const unsigned& getDamageMin() const;
	const unsigned& getDamageMax() const;
	const unsigned& getRange() const;
	bool getAttackTimer();
	//Function
	virtual Item* clone() = 0;
	virtual void generate(const unsigned levelMin, const unsigned levelMax) = 0;

	virtual void update(const Vector2f& mouse_pos_view, const Vector2f center) = 0;
	virtual void render(RenderTarget& target, Shader* shader = nullptr) = 0;
};

#endif