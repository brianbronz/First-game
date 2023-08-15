#include "../Header/Entity.h"
#include "../Animation code/MovementComponent.c++"
#include "../Source Files/HitBoxComponent.c++"
#include "AttributeComponent.c++"
#include "SkillComponent.c++"

void Entity:: initVariables(){
	this->hitboxComponent = NULL;
    this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->attributeComponent = NULL;
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

void Entity::createAttributeComponent(unsigned level){
	this->attributeComponent = new AttributeComponent(level);
}

void Entity::createSkillComponent(){
	this->skillComponent = new SkillComponent();
}

//Functions

MovementComponent* Entity::getMovementComponent()
{
	return this->movementComponent;
}

AnimationComponent* Entity::getAnimationComponent()
{
	return this->animationComponent;
}

AttributeComponent* Entity::getAttributeComponent()
{
	return this->attributeComponent;
}

SkillComponent* Entity::getSkillComponent()
{
	return this->skillComponent;
}

const Vector2f & Entity::getPosition(){
	if (this->hitboxComponent){
		return this->hitboxComponent->getPosition();
	}
	return this->sprite.getPosition();
}

void Entity::createAIComponent()
{

}

const Vector2f& Entity::getSpritePosition(){
	return this->sprite.getPosition();
}

Vector2f Entity::getCenter() const{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition() + Vector2f(this->hitboxComponent->getGlobalBounds().width / 2.f, this->hitboxComponent->getGlobalBounds().height / 2.f);
	return this->sprite.getPosition() + Vector2f(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
}

Vector2f Entity::getSpriteCenter() const{
	return this->sprite.getPosition() +
		Vector2f
		(
			this->sprite.getGlobalBounds().width / 2.f,
			this->sprite.getGlobalBounds().height / 2.f
		);;
}

Vector2i Entity::getGridPosition(int gridSizeI){
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

FloatRect Entity::getGlobalBounds(){
	if (this->hitboxComponent){
		return this->hitboxComponent->getGlobalBounds();
	}
	return this->sprite.getGlobalBounds();
}


FloatRect Entity::getNextPositionBounds(const float& dt){
	if (this->hitboxComponent && this->movementComponent){
		Vector2f velocity = this->movementComponent->getVelocity() * dt;
		return this->hitboxComponent->getNextPosition(velocity);
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

	if (this->skillComponent){
		this->skillComponent->gainExp(ENDURANCE, 1);
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

float Entity::getDistance(const Entity& entity){
	return sqrt(pow(this->getCenter().x - entity.getCenter().x, 2) + pow(this->getCenter().y - entity.getCenter().y, 2));
}

float Entity::getSpriteDistance(const Entity& entity)
{
	return sqrt(pow(this->getSpriteCenter().x - entity.getSpriteCenter().x, 2) + pow(this->getSpriteCenter().y - entity.getSpriteCenter().y, 2));
}