#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entity.h"
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
	virtual ~TileMap();

	//Accessors
	Texture* getTileSheet();
	int getLayerSize(int x, int y, int layer);
	//Functions
	void addTile(int x, int y, int z, IntRect& texture_rect, bool collision, short type);
	void removeTile(int x, int y, int z);
	void loadFromFile(string file_name);
	void updateCollision(Entity* entity, float& dt);
	void update();
	void render(RenderTarget& target, const Vector2i& gridPosition, bool show_collision = false);
	void renderDeferred(RenderTarget& target);
};
#endif