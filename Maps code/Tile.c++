#include "../Header/Tile.h"

Tile::Tile(){

}

Tile::Tile(float x, float y, float gridSizeF, Texture& texture){
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(Color::Green);
	this->shape.setPosition(x, y);
    this->shape.setTexture(&texture);
}

Tile::~Tile(){

}

void Tile::update(){

}

void Tile::render(sf::RenderTarget & target){
	target.draw(this->shape);
}