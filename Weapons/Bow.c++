#include "../Header/Bow.h"

Bow::Bow(unsigned value, string texture_file) :RangedWeapon(value, texture_file){

}

Bow::~Bow(){
    
}

Bow * Bow::Clone(){
    return new Bow(*this);
}

void Bow::update(const sf::Vector2f & mouse_pos_view, const sf::Vector2f center)
{

}

void Bow::render(sf::RenderTarget & target, sf::Shader * shader)
{

}