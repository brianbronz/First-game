#include "../Header/Tile.h"

 Tile::Tile(){
	this->collision = false;
	this->type = 0;
}
 
Tile::Tile(short type, int grid_x, int grid_y, float gridSizeF, Texture& texture, IntRect& texture_rect, bool collision){
	//this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	//this->shape.setFillColor(Color::Green);
	this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
    this->shape.setTexture(texture);
	this->collision = collision;
	this->type = type;
}

Tile::~Tile(){

}

short & Tile::getType(){
	return this->type;
}

bool & Tile::getCollision(){
	return this->collision;
}

const Vector2f & Tile::getPosition(){
	return this->shape.getPosition();
}

FloatRect Tile::getGlobalBounds(){
	return this->shape.getGlobalBounds();
}

//Functions
bool Tile::intersects(FloatRect bounds){
	return this->shape.getGlobalBounds().intersects(bounds);
}
