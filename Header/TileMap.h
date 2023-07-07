#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
class TileMap{
	private:
		float gridSizeF;
		unsigned gridSizeU;
		Vector2u maxSize;
		unsigned layers;
		vector< vector< vector<Tile*> > > map;
		Texture tileTextureSheet;

	public:
		TileMap();
		TileMap(float gridSize, unsigned width, unsigned height);
		virtual ~TileMap();
		void update();
		void render(RenderTarget& target);

		void addTile(const unsigned x, const unsigned y, const unsigned z);
		void removeTile(const unsigned x, const unsigned y, const unsigned z);
};
#endif