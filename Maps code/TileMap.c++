#include "../Header/TileMap.h"
#include "Tile.c++"

void TileMap::clear(){
	if(!this->map.empty()){
		for (int i = 0; i < this->map.size(); i++){
			for (int j = 0; j < this->map[i].size(); j++){
				for (int k = 0; k < this->map[i][j].size(); k++){
					for (int l = 0; l < this->map[i][j][k].size(); l++){
						delete this->map[i][j][k][l];
						this->map[i][j][k][l] = NULL;
					}
					this->map[i][j][k].clear();
				}
				this->map[i][j].clear();
			}
			this->map[i].clear();
		}
		this->map.clear();
	}
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, string texture_file){
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->textureFile = texture_file;

	this->map.resize(this->maxSize.x, std::vector< std::vector<Tile*> >());
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}
	if (!this->tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";
}

TileMap::TileMap(string file_name){
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;
	this->loadFromFile(file_name);
	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap(){
    this->clear();
}
Texture * TileMap::getTileSheet(){
	return &this->tileSheet;
}

void TileMap::addTile( unsigned x,  unsigned y,  unsigned z, bool& collision, short& type)
{
	/* Take two indicies from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it. */

	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0){
		if (this->map[x][y][z] == NULL){
			/* OK To add tile. */
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileTextureSheet);
			cout << "DEGBUG: ADDED TILE!" << "\n";
		}	
	}
}

void TileMap::removeTile( unsigned x,  unsigned y,  unsigned z)
{
	/* Take three indicies from the mouse position in the grid and remove a tile at that position if the internal tilemap array allows it. */

	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0){
		if (this->map[x][y][z] != NULL){
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
		}
	}
}

void TileMap::update()
{

}

void TileMap::render(RenderTarget & target)
{	
	for (int i = 0; i < this->map.size(); i++){
		for (int j = 0; j <this->map[i].size(); j++){
			for (int k = 0; k < this->map[i][j].size(); k++){
				this->map[i][j][k]->render(target);
			}
		}
	}
}

void TileMap::loadFromFile(string file_name){
	ifstream in_file;
	in_file.open(file_name);
	if (in_file.is_open()){
		Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;
		this->clear();
		this->map.resize(this->maxSize.x, vector< vector<Tile*> >());
		for (int x = 0; x < this->maxSize.x; x++){
			for (int y = 0; y < this->maxSize.y; y++){
				this->map[x].resize(this->maxSize.y, vector<Tile*>());
				for (int z = 0; z < this->layers; z++){
					this->map[x][y].resize(this->layers, NULL);
				}
			}
		}
		if (!this->tileSheet.loadFromFile(texture_file))
			cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";
		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type){
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, IntRect(trX, trY, this->gridSizeU, this->gridSizeU), collision, type);
		}
	} else {
		cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}
	in_file.close();
}