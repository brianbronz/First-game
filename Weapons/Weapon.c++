#include "../Header/AllReference.h"
#include "../Header/Weapon.h"

void Weapon::initVariables(){
	//Timer
	this->attackTimer.restart();
	this->attackTimerMax = 500;
}

Weapon::Weapon(unsigned level, unsigned value, string texture_file)
	: Item(level, value), range(50), damageMin(1), damageMax(2){
	this->initVariables();

	if (!this->weapon_texture.loadFromFile(texture_file))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE::"<< texture_file << "\n";

	this->weapon_sprite.setTexture(this->weapon_texture);
}


Weapon::Weapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string texture_file)
	: Item(level, value), damageMin(damageMin), damageMax(damageMax), range(range) {
	this->initVariables();

	if (!this->weapon_texture.loadFromFile(texture_file))
		cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE::" << texture_file << "\n";

	this->weapon_sprite.setTexture(this->weapon_texture);
}

Weapon::~Weapon()
{

}

//Accessors
const unsigned & Weapon::getRange() const{
	return this->range;
}

unsigned Weapon::getDamage() const{
	return rand() % (this->damageMax - this->damageMin + 1) + (this->damageMin);
}

const unsigned & Weapon::getDamageMin() const{
	return this->damageMin;
}

const unsigned & Weapon::getDamageMax() const{
	return this->damageMax;
}

bool Weapon::getAttackTimer(){
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax){
		this->attackTimer.restart();
		return true;
	}
	return false;
}