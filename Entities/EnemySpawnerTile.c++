#include "../Header/EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, 
	Texture& texture, IntRect& texture_rect,
		int enemy_type, int enemy_amount, Int32 enemy_time_to_spawn, float enemy_max_distance)
		: Tile(TileTypes::ENEMYSPAWNER, grid_x, grid_y, gridSizeF, texture, texture_rect, false){
    this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyCounter = 0;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->spawned = false;
}

EnemySpawnerTile::~EnemySpawnerTile()
{

}

//Functions
void EnemySpawnerTile::update(){
	if (this->canSpawn())
		this->spawned = false;
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

bool & EnemySpawnerTile::getSpawned() {
	return this->spawned;
}

void EnemySpawnerTile::setSpawned(bool spawned){
	this->spawned = spawned;
	this->enemySpawnTimer.restart();
}

bool EnemySpawnerTile::canSpawn(){
	(this->enemySpawnTimer.getElapsedTime().asSeconds() >= this->enemyTimeToSpawn)? 
		return true:
		return false;
}

void EnemySpawnerTile::increaseEnemyCounter(){
	if (this->enemyCounter > this->enemyAmount)
		this->enemyCounter = this->enemyAmount;
	else
		++this->enemyCounter;
}

void EnemySpawnerTile::decreaseEnemyCounter(){
	if (this->enemyCounter < 0)
		this->enemyCounter = 0;
	else
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