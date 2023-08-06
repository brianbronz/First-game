#include "../Header/HitBoxComponent.h"

HitboxComponent::HitboxComponent(Sprite& sprite, float offset_x, float offset_y, float width, float height): sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
    this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;
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

const Vector2f & HitboxComponent::getPosition(){
	return this->hitbox.getPosition();
}

FloatRect HitboxComponent::getGlobalBounds(){
	return this->hitbox.getGlobalBounds();
}

FloatRect & HitboxComponent::getNextPosition(Vector2f & velocity)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;

	return this->nextPosition;
}

//Modifiers
void HitboxComponent::setPosition(Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void HitboxComponent::setPosition(float x, float y)
{
	this->hitbox.setPosition(x, y);
	this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}

//Functions
bool HitboxComponent::intersects(FloatRect& frect){
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