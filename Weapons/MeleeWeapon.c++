#include "../Header/MeleeWeapon.h"
#include "../Source Files/Item.c++"
MeleeWeapon::MeleeWeapon(unsigned value, string texture_file):Weapon(value, texture_file){
	this->type = ItemTypes::IT_MELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon(){

}
