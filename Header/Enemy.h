#ifndef ENEMY_H
#define ENEMY_H
#include "AllReference.h"
#include "Entity.h"
#include "EnemySpawnerTile.h"

class Enemy : public Entity{
    protected:
        unsigned gainExp;
        EnemySpawnerTile& enemySpawnerTile;
        Clock damageTimer;
	    Int32 damageTimerMax;
        //initializer functions
        virtual void initVariables() = 0;
        virtual void initAnimations() = 0;

    public:
        Enemy(EnemySpawnerTile& enemy_spawner_tile);
        virtual ~Enemy();

        unsigned& getGainExp();
        EnemySpawnerTile& getEnemySpawnerTile();
        bool getDamageTimerDone();

	    //Modifiers
	    void resetDamageTimer();
        //Functions
        virtual void generateAttributes(const unsigned level);
        
        virtual void loseHP(const int hp);
        virtual bool isDead();

        virtual AttributeComponent* getAttributeComp();
        virtual void updateAnimation(float & dt) = 0;
        virtual void update(float & dt, Vector2f & mousePosView) = 0;
        virtual void render(RenderTarget & target, Shader* shader = NULL, Vector2f light_position = Vector2f(), bool show_hitbox = false) = 0;
}; 
#endif