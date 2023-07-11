#include "../Header/TileMap.h"
#include "Tile.c++"

void TileMap::clear(){
	if(!this->map.empty()){
		for (int i = 0; i < this->maxSizeWorldGrid.x; i++){
			for (int j = 0; j < this->maxSizeWorldGrid.y; j++){
				for (int k = 0; k < this->layers; k++){
						delete this->map[i][j][k];
						this->map[i][j][k] = NULL;
				}
				this->map[i][j].clear();
			}
			this->map[i].clear();
		}
		this->map.clear();
	}
}

TileMap::TileMap(float gridSize, int width, int height, string texture_file){
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<Tile*> >());
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}
	if (!this->tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";
	this->collisionBox.setSize(Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}


TileMap::~TileMap(){
    this->clear();
}
Texture * TileMap::getTileSheet(){
	return &this->tileSheet;
}

void TileMap::addTile( int x,  int y,  int z, IntRect& texture_rect, bool collision, short type){
	if (x < this->maxSizeWorldGrid.x && x >= 0 && y < this->maxSizeWorldGrid.y && y >= 0 && z < this->layers && z >= 0){
		if (this->map[x][y][z] == NULL){
			/* OK To add tile. */
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type);
			cout << "DEGBUG: ADDED TILE!" << "\n";
		}	
	}
}

void TileMap::removeTile( int x,  int y,  int z)
{
	/* Take three indicies from the mouse position in the grid and remove a tile at that position if the internal tilemap array allows it. */

	if (x < this->maxSizeWorldGrid.x && x >= 0 && y < this->maxSizeWorldGrid.y && y >= 0 && z < this->layers && z >= 0){
		if (this->map[x][y][z] != NULL){
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;
		}
	}
}

void TileMap::update()
{

}

void TileMap::render(RenderTarget & target, Entity* entity)
{	
	if (entity)
	{
		this->layer = 0;

		this->fromX = entity->getGridPosition(this->gridSizeI).x - 5;
		if (this->fromX < 0)
			this->fromX = 0;
		else if (this->fromX > this->maxSizeWorldGrid.x)
			this->fromX = this->maxSizeWorldGrid.x;

		this->toX = entity->getGridPosition(this->gridSizeI).x + 8;
		if (this->toX < 0)
			this->toX = 0;
		else if (this->toX > this->maxSizeWorldGrid.x)
			this->toX = this->maxSizeWorldGrid.x;

		this->fromY = entity->getGridPosition(this->gridSizeI).y - 5;
		if (this->fromY < 0)
			this->fromY = 0;
		else if (this->fromY > this->maxSizeWorldGrid.y)
			this->fromY = this->maxSizeWorldGrid.y;

		this->toY = entity->getGridPosition(this->gridSizeI).y + 8;
		if (this->toY < 0)
			this->toY = 0;
		else if (this->toY > this->maxSizeWorldGrid.y)
			this->toY = this->maxSizeWorldGrid.y;

		for (size_t x = this->fromX; x < this->toX; x++)
		{
			for (size_t y = this->fromY; y < this->toY; y++)
			{
				this->map[x][y][this->layer]->render(target);
				if (this->map[x][y][this->layer]->getCollision())
				{
					this->collisionBox.setPosition(this->map[x][y][this->layer]->getPosition());
					target.draw(this->collisionBox);
				}
			}
		}
	}
	else{
	for (int i = 0; i < this->map.size(); i++){
		for (int j = 0; j <this->map[i].size(); j++){
			for (int k = 0; k < this->map[i][j].size(); k++){
				if (this->map[i][j][k] != NULL){
					this->map[i][j][k]->render(target);
					if (this->map[i][j][k]->getCollision()){
						this->collisionBox.setPosition(this->map[i][j][k]->getPosition());
						target.draw(this->collisionBox);
					}			
				}
			}
		}
	}
	}
}

void TileMap::loadFromFile(string file_name){
	ifstream in_file;
	in_file.open(file_name);
	if (in_file.is_open()){
		Vector2i size;
		int gridSize = 0;
		int layers = 0;
		string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;
		this->clear();
		this->map.resize(this->maxSizeWorldGrid.x, vector< vector<Tile*> >());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++){
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++){
				this->map[x].resize(this->maxSizeWorldGrid.y, vector<Tile*>());
				for (int z = 0; z < this->layers; z++){
					this->map[x][y].resize(this->layers, NULL);
				}
			}
		}
		if (!this->tileSheet.loadFromFile(texture_file))
			cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";
		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type){
			IntRect rect(trX, trY, this->gridSizeI, this->gridSizeI);
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, rect, collision, type);
		}
	} else {
		cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}
	in_file.close();
}

void TileMap::updateCollision(Entity * entity, float& dt)
{
	//WORLD BOUNDS
	if (entity->getPosition().x < 0.f){
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f){
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	} else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
	//TILES
		this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (size_t x = this->fromX; x < this->toX; x++)
	{
		for (size_t y = this->fromY; y < this->toY; y++)
		{	
			sf::FloatRect playerBounds = entity->getGlobalBounds();
			sf::FloatRect wallBounds = this->map[x][y][this->layer]->getGlobalBounds();
			sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

			if (this->map[x][y][this->layer]->getCollision() && 
				this->map[x][y][this->layer]->intersects(nextPositionBounds)
				)
			{
				//Bottom collision
				if (playerBounds.top < wallBounds.top
					&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{
					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height - 2.f);
				}

				//Top collision
				else if (playerBounds.top > wallBounds.top
					&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left
					)
				{
					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height + 2.f);
				}

				//Right collision
				if (playerBounds.left < wallBounds.left
					&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top
					)
				{
					entity->stopVelocityX();
					entity->setPosition(wallBounds.left - playerBounds.width - 2.f, playerBounds.top);
				}

				//Left collision
				else if (playerBounds.left > wallBounds.left
					&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top
					)
				{
					entity->stopVelocityX();
					entity->setPosition(wallBounds.left + wallBounds.width + 2.f, playerBounds.top);
				}
			}
		}
	}
}