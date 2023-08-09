
#ifndef ENEMYSPAWNERTILE_H
#define ENEMYSPAWNERTILE_H

#include "AllReference.h"
#include "Tile.h"
class EnemySpawnerTile : public Tile
{
private:
	int enemyType;
	int enemyAmount;
	int enemyCounter;
	int enemyTimeToSpawn;
	Clock enemySpawnTimer;
	Int32 enemyTimeToSpawn;
	float enemyMaxDistance;
	bool spawned;

public:
	EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, Texture& texture, IntRect& texture_rect,
		 int enemy_type, int enemy_amount, Int32 enemy_time_to_spawn, float enemy_max_distance);
    virtual ~EnemySpawnerTile();
	virtual string getAsString();
	bool& getSpawned();
	int& getEnemyAmount();
	int& getEnemyCounter();
	//Modifiers
	
	void setSpawned(bool spawned);
	bool canSpawn();
	void increaseEnemyCounter();
	void decreaseEnemyCounter();
	void update();
	void render(RenderTarget & target, Shader* shader = NULL, Vector2f player_position = Vector2f());
};

#endif