#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include "AllReference.h"

class HitboxComponent
{
private:
    Sprite& sprite;
	RectangleShape hitbox;
	float offsetX;
	float offsetY;
public: 
    HitboxComponent(Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();
    bool isIntersect(FloatRect& frect);
	void update();
	void render(RenderTarget& target);

};
#endif