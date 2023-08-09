#include "../Header/Enemy.h"

void Enemy::initVariables(){
    this->gainExp =10;
}

void Enemy::initAnimations(){

}

Enemy::Enemy(){
    this->initVariables();
	this->initAnimations();
}

Enemy::~Enemy(){}


unsigned & Enemy::getGainExp(){
	return this->gainExp;
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