#include "../Header/Sword.h"
#include "MeleeWeapon.c++"
Sword::Sword(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, 
	unsigned value, string texture_file): MeleeWeapon(damageMin, damageMax, range, value, texture_file){
    //Visual Weapon
	this->weaponSprite.setOrigin(this->weaponSprite.getGlobalBounds().width / 2.f,this->weaponSprite.getGlobalBounds().height);
}

Sword::~Sword(){
    
}

void Sword::update(Vector2f & mousePosView, Vector2f center){
    //Update visual weapon
	this->weaponSprite.setPosition(center);
	float dX = mousePosView.x - this->weaponSprite.getPosition().x;
	float dY = mousePosView.y - this->weaponSprite.getPosition().y;
	float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;
	if (this->attackTimer.getElapsedTime().asMilliseconds() < this->attackTimerMax){
		float len = std::sqrt(pow(dX, 2) + pow(dY, 2));
		sf::Vector2f normVec(dX / len, dY / len);

		this->weapon_sprite.setPosition(center.x + normVec.x * 10.f, center.y + normVec.y * 10.f);
	} else
		this->weapon_sprite.setRotation(deg + 90.f);

}

void Sword::render(RenderTarget & target, Shader * shader){
    (shader)? target.draw(this->weaponSprite, shader):
              target.draw(this->weaponSprite);
}

Sword * Sword::Clone(){
	return new Sword(*this);
}