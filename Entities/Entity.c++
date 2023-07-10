#include "../Header/Entity.h"
#include "../Animation code/MovementComponent.c++"
#include "../Source Files/HitBoxComponent.c++"

void Entity:: initVariables(){
	this->hitboxComponent = NULL;
    this->movementComponent = NULL;
	this->animationComponent = NULL;
}

Entity::Entity(){
    this->initVariables();
}

Entity::~Entity(){
	delete this->hitboxComponent;
    delete this->movementComponent;
	delete this->animationComponent;
}

//Component functions
void Entity::setTexture(Texture& texture){
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(Sprite & sprite, float offset_x, float offset_y, float width, float height){
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent( float maxVelocity,  float acceleration,  float deceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(Texture& textureSheet){
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

//Functions
const Vector2f & Entity::getPosition(){
	return this->sprite.getPosition();
}


void Entity::setPosition( float x,  float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::move( float dir_x,  float dir_y,  float & dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt); //Sets velocity
	}
}

//Component functions

void Entity::update( float & dt){

}

void Entity::render(RenderTarget& target){
    target.draw(this->sprite);
	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}