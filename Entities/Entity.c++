#include "../Header/Entity.h"
#include "../Animation code/MovementComponent.c++"
#include "../Source Files/HitBoxComponent.c++"
#include "AttributeComponent.c++"

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
	delete this->attributeComponent;
}

//Component functions
void Entity::setTexture(Texture& texture){
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(Sprite & sprite, float offset_x, float offset_y, float width, float height){
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(float maxVelocity, float acceleration, float deceleration){
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(Texture& textureSheet){
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

void Entity::createAttributeComponent(const unsigned level){
	this->attributeComponent = new AttributeComponent(level);
}

//Functions
const Vector2f & Entity::getPosition(){
	if (this->hitboxComponent){
		return this->hitboxComponent->getPosition();
	}
	return this->sprite.getPosition();
}

const Vector2i Entity::getGridPosition(int gridSizeI){
	if (this->hitboxComponent){
		return Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
		);
	}
	return Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI
	);
}

const FloatRect Entity::getGlobalBounds(){
	if (this->hitboxComponent){
		return this->hitboxComponent->getGlobalBounds();
	}
	return this->sprite.getGlobalBounds();
}


const FloatRect Entity::getNextPositionBounds(float& dt){
	if (this->hitboxComponent && this->movementComponent){
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	}
	return FloatRect(-1.f, -1.f, -1.f, -1.f);
}

void Entity::setPosition(float x, float y)
{
	if (this->hitboxComponent){
		this->hitboxComponent->setPosition(x, y);
	} else {
		this->sprite.setPosition(x, y);
	}
}

void Entity::move(float dir_x, float dir_y, float & dt){
	if (this->movementComponent){
		this->movementComponent->move(dir_x, dir_y, dt); //Sets velocity
	}
}

//Component functions
void Entity::stopVelocity(){
	if (this->movementComponent){
		this->movementComponent->stopVelocity();
	}

}

void Entity::stopVelocityX(){
	if (this->movementComponent){
		this->movementComponent->stopVelocityX();
	}
}

void Entity::stopVelocityY(){
	if (this->movementComponent){
		this->movementComponent->stopVelocityY();
	}
}


void Entity::update( float & dt){

}

void Entity::render(RenderTarget& target){

}