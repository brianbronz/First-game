//Base for the characters
#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"

using namespace sf;
using namespace std;
class Entity{
    private:
        void initVariables();
    protected:
        Sprite sprite;
        MovementComponent* movementComponent;
        AnimationComponent* animationComponent;
    public:
        Entity();
        virtual ~Entity();

        //Component functions
        void setTexture(Texture& texture);
        void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
        void createAnimationComponent(Texture& textureSheet);
        //Functions
        virtual void setPosition(const float x, const float y);
	    virtual void move(const float x, const float y, const float& dt);
        virtual void update(const float& dt);
        virtual void render(RenderTarget* target);

};
#endif