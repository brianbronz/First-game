#include "../Header/Entity.h"
#include "../Source Files/MovementComponent.c++"

void Entity:: initVariables(){
    this->movementComponent = NULL;
}

Entity::Entity(){
    this->initVariables();
}

Entity::~Entity(){
    delete this->movementComponent;
	delete this->animationComponent;
}

//Component functions
void Entity::setTexture(Texture& texture){
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(Texture& textureSheet){
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

//Functions
void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float & dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt); //Sets velocity
	}
}

//Component functions

void Entity::update(const float & dt){

}

void Entity::render(RenderTarget* target){
    target->draw(this->sprite);
}