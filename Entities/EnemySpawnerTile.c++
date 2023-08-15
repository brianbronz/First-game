#include "../Header/EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, 
	Texture& texture, IntRect& texture_rect,
		int enemy_type, int enemy_amount, Int32 enemy_time_to_spawn, float enemy_max_distance)
		: Tile(ENEMYSPAWNER, grid_x, grid_y, gridSizeF, texture, texture_rect, false){
    this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyCounter = 0;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->firstSpawn = true;
}

EnemySpawnerTile::~EnemySpawnerTile()
{

}

//Functions
void EnemySpawnerTile::update(){
}

int & EnemySpawnerTile::getEnemyAmount(){
	return this->enemyAmount;
}

int & EnemySpawnerTile::getEnemyCounter(){
	return this->enemyCounter;
}

string EnemySpawnerTile::getAsString() {
	stringstream ss;

	/*
	x, y, z (done in tilemap save)
	type,
	rect x, rect y,
	enemy type,
	enemy amount
	enemy time to spawn
	enemy max distance
	*/

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
		<< this->enemyType << " "  << this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemyMaxDistance;
	return ss.str();
}

bool EnemySpawnerTile::getSpawnTimer(){
	if(this->enemySpawnTimer.getElapsedTime().asSeconds() >= this->enemyTimeToSpawn || this->firstSpawn){
		this->enemySpawnTimer.restart();
		this->firstSpawn = false;
		return true;
	} else {
		return false;
	}
}

int& EnemySpawnerTile::getEnemyType()
{
	return this->enemyType;
}

float& EnemySpawnerTile::getEnemyMaxDistance()
{
	return this->enemyMaxDistance;
}

void EnemySpawnerTile::increaseEnemyCounter(){
	if (this->enemyCounter < this->enemyAmount)
		++this->enemyCounter;
}

void EnemySpawnerTile::decreaseEnemyCounter(){
	if (this->enemyCounter > 0)
		--this->enemyCounter;
}

void EnemySpawnerTile::render(RenderTarget & target, Shader* shader, Vector2f playerPosition){
	if (shader){
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPosition);
		target.draw(this->shape, shader);
	}else{
		target.draw(this->shape);
    }
}