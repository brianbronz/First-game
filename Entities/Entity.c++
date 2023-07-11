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
		if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();
	return this->sprite.getPosition();
}

const Vector2u Entity::getGridPosition(unsigned gridSizeU)
{
	if (this->hitboxComponent)
		return sf::Vector2u(
			static_cast<unsigned>(this->hitboxComponent->getPosition().x) / gridSizeU,
			static_cast<unsigned>(this->hitboxComponent->getPosition().y) / gridSizeU
		);

	return sf::Vector2u(
		static_cast<unsigned>(this->sprite.getPosition().x) / gridSizeU,
		static_cast<unsigned>(this->sprite.getPosition().y) / gridSizeU
	);
}

const FloatRect Entity::getGlobalBounds(){
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}


const sf::FloatRect Entity::getNextPositionBounds(float& dt){
	if (this->hitboxComponent && this->movementComponent)
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

void Entity::setPosition( float x,  float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
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
void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();

}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}


void Entity::update( float & dt){

}

void Entity::render(RenderTarget& target){
    target.draw(this->sprite);
	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}