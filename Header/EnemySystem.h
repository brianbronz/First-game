#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include "EnemySpawnerTile.h"
#include "Rat.h"
#include "Bird1.h"
#include "AllReference.h"

enum EnemyTypes {RAT = 0, BIRD1};

class EnemySystem
{
private:
	map<string, Texture>& textures;
	vector<Enemy*>& activeEnemies;
	Entity& player;

public:
	EnemySystem(vector<Enemy*>& activeEnemies, 
	map<string, Texture>& textures, Entity& player);
	virtual ~EnemySystem();

	//Accessors

	//Modifiers

	//Functions
	void createEnemy(const short type, const float xPos, const float yPos, EnemySpawnerTile& enemy_spawner_tile);
	void removeEnemy(const int index);
	void update(const float& dt);
	void render(RenderTarget* target);
};

#endif //!ENEMYSYSTEM_H 