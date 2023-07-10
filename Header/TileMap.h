#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
class TileMap{
	private:
	void clear();

	float gridSizeF;
	unsigned gridSizeU;
	Vector2u maxSize;
	unsigned layers;
	vector< vector< vector< Tile* > > > map;
	string textureFile;
	Texture tileSheet;

public:
	TileMap(string file_name);
	TileMap(float gridSize, unsigned width, unsigned height, string texture_file);
	virtual ~TileMap();

	//Accessors
	Texture* getTileSheet() ;

	//Functions
	void addTile(unsigned x, unsigned y, unsigned z, IntRect& texture_rect, bool& collision, short& type);
	void removeTile(unsigned x, unsigned y, unsigned z);
	void loadFromFile(string file_name);

	void update();
	void render(RenderTarget& target);
};
#endif