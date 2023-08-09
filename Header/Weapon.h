#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item{
private:
	void initVariables();

protected:
	Texture weapon_texture;
	Sprite weapon_sprite;

	int damageMin;
	int damageMax;
	unsigned range;

public:
	Weapon(unsigned value, std::string texture_file);
	virtual ~Weapon();

	//Accessors
	const unsigned& getRange() const;

	//Function
	virtual Item* clone() = 0;

	virtual void update(const Vector2f& mouse_pos_view, const Vector2f center) = 0;
	virtual void render(RenderTarget& target, Shader* shader = nullptr) = 0;
};

#endif