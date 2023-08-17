#include "../Header/Bow.h"

Bow::Bow(unsigned level, unsigned value, string texture_file):RangeWeapon(level, value, texture_file){

}

Bow::~Bow(){
    
}

Bow * Bow::Clone(){
    return new Bow(*this);
}

void Bow::update(const Vector2f & mouse_pos_view, const Vector2f center)
{

}

void Bow::render(RenderTarget & target, Shader * shader)
{

}