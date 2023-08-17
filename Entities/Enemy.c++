#include "../Header/Enemy.h"
#include "../Source Files/VectorMath.c++"

void Enemy::initVariables(){
    this->gainExp =10;
	this->damageTimerMax = 1000;
	this->despawnTimerMax = 1000;
}

void Enemy::initAnimations(){

}

bool Enemy::getDamageTimerDone(){
	return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

bool Enemy::getDespawnTimerDone(){
	return this->despawnTimer.getElapsedTime().asMilliseconds() >= this->despawnTimerMax;
}


void Enemy::resetDamageTimer(){
	this->damageTimer.restart();
}

Enemy::Enemy(EnemySpawnerTile& enemy_spawner_tile): enemySpawnerTile(enemy_spawner_tile){
    this->initVariables();
	this->initAnimations();
}

Enemy::~Enemy(){}


unsigned & Enemy::getGainExp(){
	return this->gainExp;
}

EnemySpawnerTile & Enemy::getEnemySpawnerTile(){
	return this->enemySpawnerTile;
}

void Enemy::generateAttributes(const unsigned level){
	this->gainExp = level * (rand() % 5 + 1);
}

void Enemy::loseHP(const int hp){
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);
	}
}

bool Enemy::isDead(){
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();
	}

	return false;
}

AttributeComponent * Enemy::getAttributeComp() {
	if (this->attributeComponent)
		return this->attributeComponent;
	else
	{
		cout << "ERROR::ENEMY::ATTRIBUTECOMPONENT IS NOT INITIALIZED" << "\n";
		return nullptr;
	}
}

void Enemy::update(float& dt, Vector2f& mouse_pos_view, View& view){
	if(vectorDistance(this->getPosition(), view.getCenter()) < 1500.f)
		this->despawnTimer.restart();
}