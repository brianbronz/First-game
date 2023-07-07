#include "../Header/TileMap.h"
#include "Tile.c++"

TileMap::TileMap(){
	
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height){
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

	this->map.resize(this->maxSize.x, vector< std::vector<Tile*> >());
	for (int x = 0; x < this->maxSize.x; x++){
		for (int y = 0; y < this->maxSize.y; y++){
			this->map[x].resize(this->maxSize.y, vector<Tile*>());
			for (int z = 0; z < this->layers; z++){
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}
    if (!this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/grass1.png"))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET." << "\n";
}

TileMap::~TileMap(){
    for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z)
{
	/* Take two indicies from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it. */

	if (x < this->maxSize.x && x >= 0 && 
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			/* OK To add tile. */
			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileTextureSheet);
			std::cout << "DEGBUG: ADDED TILE!" << "\n";
		}	
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/* Take three indicies from the mouse position in the grid and remove a tile at that position if the internal tilemap array allows it. */

	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != NULL)
		{
			/* OK To remove tile. */
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
		}
	}
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget & target)
{	
	for (int i = 0; i < this->map.size(); i++){
		for (int j = 0; j <this->map[i].size(); j++){
			for (int k = 0; k < this->map[i][j].size(); k++){
				this->map[i][j][k]->render(target);
			}
		}
	}
}