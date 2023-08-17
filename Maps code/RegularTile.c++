#include "../Header/AllReference.h"
#include "../Header/RegularTile.h"

RegularTile::RegularTile(short type, int grid_x, int grid_y, float gridSizeF,
	Texture& texture, IntRect& texture_rect,
	bool collision)
	: Tile(type, grid_x, grid_y, gridSizeF, texture, texture_rect, collision)
{

}

RegularTile::~RegularTile()
{

}

//Functions
string RegularTile::getAsString()
{
	stringstream ss;

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision;

	cout << ss.str() << "\n";

	return ss.str();
}

void RegularTile::update()
{

}

void RegularTile::render(RenderTarget & target, Shader * shader, const Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);

		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}