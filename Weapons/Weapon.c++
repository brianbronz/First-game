#include "../Header/AllReference.h"
#include "../Header/Weapon.h"

void Weapon::initVariables()
{
	this->range = 50;
	this->damageMin = 1;
	this->damageMax = 2;

	//Timer
	this->attackTimer.restart();
	this->attackTimerMax = 500;
}

Weapon::Weapon(unsigned level, unsigned value, string texture_file)
	: Item(level, value)
{
	this->initVariables();

	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE::"<< texture_file << "\n";

	this->weapon_sprite.setTexture(this->weapon_texture);
}


Weapon::Weapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file)
	: Item(level, value) {
	this->initVariables();

	this->damageMin = damageMin;
	this->damageMax = damageMax;
	this->range = range;

	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE::" << texture_file << "\n";

	this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapon::~Weapon()
{

}

//Accessors
unsigned & Weapon::getRange() const{
	return this->range;
}

unsigned Weapon::getDamage() const{
	return rand() % (this->damageMax - this->damageMin + 1) + (this->damageMin);
}

unsigned & Weapon::getDamageMin() const{
	return this->damageMin;
}

unsigned & Weapon::getDamageMax() const{
	return this->damageMax;
}

bool Weapon::getAttackTimer(){
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax){
		this->attackTimer.restart();
		return true;
	}
	return false;
}