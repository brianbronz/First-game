#include "../Header/AllReference.h"
#include "../Header/Weapon.h"

void Weapon::initVariables()
{
	this->range = 30;
	this->damageMin = 1;
	this->damageMax = 2;

	//Timer
	this->attackTimer.restart();
	this->attackTimerMax = 500;
}

Weapon::Weapon(unsigned value, std::string texture_file)
	: Item(value)
{
	this->initVariables();

	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE::"<< texture_file << "\n";

	this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapon::~Weapon()
{

}

//Accessors
unsigned & Weapon::getRange(){
	return this->range;
}

unsigned & Weapon::getDamageMin(){
	return this->damageMin;
}

unsigned & Weapon::getDamageMax(){
	return this->damageMax;
}

bool Weapon::getAttackTimer(){
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax){
		this->attackTimer.restart();
		return true;
	}
	return false;
}