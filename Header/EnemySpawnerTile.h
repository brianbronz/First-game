
#ifndef ENEMYSPAWNERTILE_H
#define ENEMYSPAWNERTILE_H

#include "AllReference.h"
#include "Tile.h"
class EnemySpawnerTile : public Tile
{
private:
	int enemyType;
	int enemyAmount;
	int enemyTimeToSpawn;
	float enemyMaxDistance;
	bool spawned;

public:
	EnemySpawnerTile(Vector2i grid_position, float grid_size, int type, int amount, int time_to_spawn, float max_distance);
	EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, Texture& texture, IntRect& texture_rect,
		 int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance);
    virtual ~EnemySpawnerTile();
	virtual string getAsString();
	bool& getSpawned();
	//Modifiers
	
	void setSpawned(bool spawned);
	void update();
	void render(RenderTarget & target, Shader* shader = NULL, Vector2f player_position = Vector2f());
};

#endif