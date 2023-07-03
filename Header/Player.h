#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player :
	public Entity
{
private:
	//Variables

	//Initializer functions
	void initVariables();
	void initComponents();

public:
	Player(float x, float y, Texture& textureSheet);
	virtual ~Player();

	//Functions
	virtual void update(float& dt);
};

#endif