#include "../Header/MeleeWeapon.h"
#include "../Source Files/Item.c++"
#include "Weapon.c++"
MeleeWeapon::MeleeWeapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range,
	unsigned value, string texture_file): Weapon(level, damageMin, damageMax, range, value, texture_file)
{
	this->type = IT_MELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon(){

}

void MeleeWeapon::generate(const unsigned levelMin, const unsigned levelMax){
	this->level = rand() % (levelMax - levelMin + 1) + levelMin;
	this->damageMin = this->level * (rand() % 2 + 1);
	this->damageMax = this->level * (rand() % 2 + 1) + this->damageMin;
	this->range = this->level + rand() % 10 + 70;
	this->value = this->level + this->damageMin + this->damageMax + this->range + (rand() % level * 10);
	//cout << this->level << " " << this->damageMin << " " << this->damageMax << " " << this->range << " " << this->value << "\n";
}