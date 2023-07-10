#include "../Header/Tile.h"

Tile::Tile(){
	this->collision = false;
	this->type = 0;
}

Tile::Tile(float x, float y, float gridSizeF, Texture& texture, bool collision, short type){
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(Color::Green);
	this->shape.setPosition(x, y);
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