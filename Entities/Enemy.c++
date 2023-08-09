#include "../Header/Enemy.h"

void Enemy::initVariables(){
    this->gainExp =10;
}

void Enemy::initAnimations(){

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