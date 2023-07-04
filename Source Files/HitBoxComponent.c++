#include "../Header/HitBoxComponent.h"

HitboxComponent::HitboxComponent(Sprite& sprite, float offset_x, float offset_y, float width, float height): sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	float newX = this->sprite.getPosition().x + this->offsetX;
    float newY = this->sprite.getPosition().y + this->offsetY;
    this->hitbox.setPosition(newX, newY);
	this->hitbox.setSize(Vector2f(width, height));
	this->hitbox.setFillColor(Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(Color::Green);
}

HitboxComponent::~HitboxComponent(){

}

bool HitboxComponent::isIntersect(FloatRect& frect){
    return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update(){
    float newX = this->sprite.getPosition().x + this->offsetX;
    float newY = this->sprite.getPosition().y + this->offsetY;
    this->hitbox.setPosition(newX, newY);
}


void HitboxComponent::render(RenderTarget& target){
    target.draw(this->hitbox);
}