#include "../../Header/AllReference.h"
#include "../../Header/Rat.h"


//Initializer functions
void Rat::initVariables(){

}

void Rat::initAnimations(){
	this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 3, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 60, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 60, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 60, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 4, 3, 4, 60, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);
}


void Rat::initAI(){

}

void Rat::initGUI(){
	this->hpBar.setFillColor(Color::Red);
	this->hpBar.setSize(Vector2f(60.f, 10.f));
	this->hpBar.setPosition(this->sprite.getPosition());
}

//ructors / Destructors
Rat::Rat(const float x, const float y, Texture& texture_sheet,  EnemySpawnerTile& enemy_spawner_tile, Entity& player)
	: Enemy(enemy_spawner_tile){
	this->initVariables();
	this->initGUI();

	this->createHitboxComponent(this->sprite, 13.f, 39.f, 30.f, 30.f);
	this->createMovementComponent(70.f, 800.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->generateAttributes(this->attributeComponent->level);
	this->setPosition(x, y);
	this->initAnimations();

	this->follow = new AIFollow(*this, player);
}


Rat::~Rat(){
 	delete this->follow;
}

void Rat::updateAnimation(float & dt){
	if (this->movementComponent->getState(IDLE)){
		this->animationComponent->play("IDLE", dt);
	} else if (this->movementComponent->getState(MOVING_LEFT)){
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	} else if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	} else if (this->movementComponent->getState(MOVING_UP)){
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	} else if (this->movementComponent->getState(MOVING_DOWN)){
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax){
		this->sprite.setColor(Color::Red);
	}else{
		this->sprite.setColor(Color::White);
	}
}

void Rat::update(float & dt, Vector2f& mouse_pos_view, View& view){
	Enemy::update(dt, mouse_pos_view, view);
	this->movementComponent->update(dt);

	//Update GUI REMOVE THIS!!!!
	this->hpBar.setSize(Vector2f(60.f * (static_cast<float>(this->attributeComponent->hp) / this->attributeComponent->hpMax), 10.f));
	this->hpBar.setPosition(this->sprite.getPosition());

	this->updateAnimation(dt);
	this->hitboxComponent->update();

	this->follow->update(dt);
}

void Rat::render(RenderTarget & target, Shader* shader, Vector2f light_position, bool show_hitbox){
	if (shader){
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);
	} else {
		target.draw(this->sprite);
	}

	target.draw(this->hpBar);
	if (show_hitbox)
		this->hitboxComponent->render(target);
}