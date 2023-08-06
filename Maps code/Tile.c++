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

string Tile::getAsString(){
	stringstream ss;
	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision;
	return ss.str();
}


void Tile::update(){

}

void Tile::render(RenderTarget & target, Shader* shader, Vector2f playerPosition){
	if (shader){
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPosition);
		target.draw(this->shape, shader);
	} else{
		target.draw(this->shape);
	}
}