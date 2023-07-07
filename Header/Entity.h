//Base for the characters
#ifndef ENTITY_H
#define ENTITY_H

#include "AllReference.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitBoxComponent.h"

class Entity{
    private:
        void initVariables();
    protected:
        Sprite sprite;
        HitboxComponent* hitboxComponent;
        MovementComponent* movementComponent;
        AnimationComponent* animationComponent;
    public:
        Entity();
        virtual ~Entity();

        //Component functions
        void setTexture(Texture& texture);
        void createHitboxComponent(Sprite& sprite, float offset_x, float offset_y,float width, float height);
        void createMovementComponent( float maxVelocity,  float acceleration,  float deceleration);
        void createAnimationComponent(Texture& textureSheet);
        //Functions
        virtual void setPosition( float x,  float y);
	    virtual void move( float x,  float y,  float & dt);
        virtual void update( float & dt);
        virtual void render(RenderTarget& target);

};
#endif