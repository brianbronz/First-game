#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entity.h"
#include "EnemySpawner.h"
class TileMap{
	private:
	void clear();

	float gridSizeF;
	int gridSizeI;
	Vector2i maxSizeWorldGrid;
	Vector2f maxSizeWorldF;
	int layers;
	vector< vector< vector< vector<Tile*> > > > map;
	stack<Tile*> deferredRenderStack; 
	string textureFile;
	Texture tileSheet;
	RectangleShape collisionBox;

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

public:
	TileMap(float gridSize, int width, int height, string texture_file);
	TileMap(string filename);
	virtual ~TileMap();

	bool tileEmpty(int x, int y, int z);
	//Accessors
	Texture* getTileSheet();
	int getLayerSize(int x, int y, int layer);
	Vector2i& getMaxSizeGrid();
	Vector2f& getMaxSizeF();
	//Functions
	void addTile(int x, int y, int z, IntRect& texture_rect, bool collision, short type);
	void removeTile(int x, int y, int z, int type);
	void loadFromFile(string file_name);
	void update(Entity* entity, float& dt);
	void render(RenderTarget& target, Vector2i& gridPosition, Shader* shader = NULL, Vector2f playerPosition = Vector2f(), bool show_collision = false);
	void renderDeferred(RenderTarget& target, Shader* shader = NULL, Vector2f playerPosition = Vector2f());
};
#endif