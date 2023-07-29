#include "../Header/Enemy.h"

EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, 
	Texture& texture, IntRect& texture_rect,
	float grid_size, int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance)
	: Tile(grid_x, grid_y, gridSizeF, texture, texture_rect, false, TileTypes::ENEMYSPAWNER)
{
    	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
}

EnemySpawner::~EnemySpawner()
{

}

//Functions
void EnemySpawner::update()
{

}

void EnemySpawner::render(RenderTarget & target, Shader* shader, Vector2f playerPosition){
	if (shader){
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPosition);
		target.draw(this->shape, shader);
	}else{
		target.draw(this->shape);
    }
}