#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include "AllReference.h"

class HitboxComponent
{
private:
    Sprite& sprite;
	RectangleShape hitbox;
	FloatRect nextPosition;
	float offsetX;
	float offsetY;
public: 
    HitboxComponent(Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();
	//Accessors
	const Vector2f& getPosition();
	FloatRect getGlobalBounds();
	const FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Modifiers
	void setPosition(Vector2f& position);
	void setPosition(float x, float y);

	//Functions
	bool intersects(FloatRect& frect);


	void update();
	void render(RenderTarget& target);

};
#endif