#include "../Header/RangeWeapon.h"

RangeWeapon::RangeWeapon(unsigned value, std::string texture_file): Weapon(value, texture_file){
    this->type = ItemTypes::IT_RANGEDWEAPON;
}

RangeWeapon::~RangeWeapon(){
    
}