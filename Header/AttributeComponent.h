#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H
#include "AllReference.h"

class AttributeComponent{
public:
	//Leveling
	int level;
	int exp;
	int expNext;
	int attributePoints;

	//Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

	//Con / Des
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	//Functions
	void loseHP(int hp);
	void gainHP(int hp);
	void loseEXP(int exp);
	void gainExp(int exp);

 	bool isDead();
	void updateStats(bool reset);
	void updateLevel();

	void update();
};
#endif