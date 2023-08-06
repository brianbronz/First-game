
#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "AllReference.h"
#include "Tile.h"
class EnemySpawner
{
private:
	int enemyType;
	int enemyAmount;
	int enemyTimeToSpawn;
	float enemyMaxDistance;

public:
	EnemySpawner(Vector2i grid_position, float grid_size, int type, int amount, int time_to_spawn, float max_distance);
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, Texture& texture, IntRect& texture_rect,
		float grid_size, int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance);
    virtual ~EnemySpawner();

	void update();
	void render(RenderTarget & target, Shader* shader = NULL, Vector2f player_position = Vector2f());
};

#endif