#include "../Header/AllReference.h"
#include "../Header/EnemySystem.h"
#include "TypeEnemies/Bird1.c++"
#include "TypeEnemies/Rat.c++"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies,
	std::map<std::string, Texture>& textures, Entity& player)
	: textures(textures), activeEnemies(activeEnemies), player(player){

}

EnemySystem::~EnemySystem(){

}

void EnemySystem::createEnemy(const short type, const float xPos, const float yPos,  EnemySpawnerTile& enemy_spawner_tile){
	switch (type){
	case RAT:
		this->activeEnemies.push_back(new Rat(xPos, yPos, this->textures["RAT1_SHEET"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	case BIRD1:
		this->activeEnemies.push_back(new Bird1(xPos, yPos, this->textures["BIRD1_SHEET"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	default:
		cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOES NOT EXIST" << "\n";
		break;
	}
}

void EnemySystem::removeEnemy(const int index){
	this->activeEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();
	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::update(const float & dt){

}

void EnemySystem::render(RenderTarget * target)
{

}