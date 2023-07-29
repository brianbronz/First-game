#include "../Header/Sword.h"
#include "MeleeWeapon.c++"
Sword::Sword(){
    //Visual Weapon
	if (!this->weaponTexture.loadFromFile("../Source Files/Resources/Images/Sprites/Player/sword.png"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE." << "\n";
	this->weaponSprite.setTexture(this->weaponTexture);
	this->weaponSprite.setOrigin(this->weaponSprite.getGlobalBounds().width / 2.f,this->weaponSprite.getGlobalBounds().height);
}

Sword::~Sword(){
    
}

void Sword::update(Vector2f & mousePosView, Vector2f center){
    //Update visual weapon
	this->weaponSprite.setPosition(center);
	float dX = mousePosView.x - this->weaponSprite.getPosition().x;
	float dY = mousePosView.y - this->weaponSprite.getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;
	this->weaponSprite.setRotation(deg + 90.f);

}

void Sword::render(RenderTarget & target, Shader * shader){
    (shader)? target.draw(this->weaponSprite, shader):
              target.draw(this->weaponSprite);
}