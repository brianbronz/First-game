#ifndef ENEMY_H
#define ENEMY_H
#include "AllReference.h"
#include "Entity.h"
#include "EnemySpawnerTile.h"
#include "AIFollow.h"

class Enemy : public Entity{
    protected:
        unsigned gainExp;
        EnemySpawnerTile& enemySpawnerTile;
        Clock damageTimer;
	    Int32 damageTimerMax;
        Clock despawnTimer;
	    Int32 despawnTimerMax;
        //initializer functions
        void initVariables();
        void initAnimations();

    public:
        Enemy(EnemySpawnerTile& enemy_spawner_tile);
        virtual ~Enemy();

        unsigned& getGainExp();
        EnemySpawnerTile& getEnemySpawnerTile();
        bool getDamageTimerDone();
        bool getDespawnTimerDone();

	    //Modifiers
	    void resetDamageTimer();
        //Functions
        virtual void generateAttributes(const unsigned level);
        
        virtual void loseHP(const int hp);
        virtual bool isDead();

        virtual AttributeComponent* getAttributeComp();
        virtual void updateAnimation(float & dt) = 0;
        virtual void update(float & dt, Vector2f& mouse_pos_view, View& view) = 0;
        virtual void render(RenderTarget & target, Shader* shader = NULL, Vector2f light_position = Vector2f(), bool show_hitbox = false) = 0;
}; 
#endif