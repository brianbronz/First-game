#ifndef ENEMY_H
#define ENEMY_H
#include "AllReference.h"
#include "Entity.h"
#include "EnemySpawner.h"

class Enemy : public Entity{
    private:
        //EnemySpawner& enemy_spawner;
        //initializer functions
        virtual void initVariables() = 0;
        virtual void initAnimations() = 0;

    public:
        Enemy();
        virtual ~Enemy();

        //Functions
        virtual void updateAnimation(float & dt) = 0;
        virtual void update(float & dt, Vector2f & mousePosView) = 0;
        virtual void render(RenderTarget & target, Shader* shader = NULL, Vector2f light_position = Vector2f(), bool show_hitbox = false) = 0;
}; 
#endif