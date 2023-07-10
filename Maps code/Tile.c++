#include "../Header/Tile.h"

/* Tile::Tile(){
	this->collision = false;
	this->type = 0;
}
 */
Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, Texture& texture, IntRect& texture_rect, bool collision, short type){
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(Color::Green);
	this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
    this->shape.setTexture(&texture);
	this->collision = collision;
	this->type = type;
}

Tile::~Tile(){

}


//Functions
string Tile::getAsString(){
	std::stringstream ss;
	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;
	return ss.str();
}


void Tile::update(){

}

void Tile::render(RenderTarget & target){
	target.draw(this->shape);
}