#ifndef ENEMY_H
#define ENEMY_H
#include "AllReference.h"
#include "Entity.h"
#include "EnemySpawner.h"

class Enemy : public Entity{
    private:
        //EnemySpawner& enemy_spawner;
        //initializer functions
        void initVariables();
        void initAnimations();

    public:
        Enemy(float x, float y, Texture & texture_sheet);
        virtual ~Enemy();

        //Functions
        void updateAnimation(float & dt);
        void update(float & dt, Vector2f & mousePosView);
        void render(RenderTarget & target, Shader* shader = NULL, Vector2f light_position = Vector2f(), bool show_hitbox = false);
}; 
#endif