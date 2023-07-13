//Base for the characters
#ifndef ENTITY_H
#define ENTITY_H

#include "AllReference.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitBoxComponent.h"
#include "AttributeComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;

class Entity{
    private:
        void initVariables();
    protected:
        Sprite sprite;
        HitboxComponent* hitboxComponent;
        MovementComponent* movementComponent;
        AnimationComponent* animationComponent;
        AttributeComponent* attributeComponent;

    public:
        Entity();
        virtual ~Entity();

        //Component functions
        void setTexture(Texture& texture);
        void createHitboxComponent(Sprite& sprite, float offset_x, float offset_y,float width, float height);
        void createMovementComponent(float maxVelocity, float acceleration, float deceleration);
        void createAnimationComponent(Texture& textureSheet);
        void createAttributeComponent(const unsigned level);
        //Functions
        const virtual Vector2f& getPosition();
        virtual const Vector2i getGridPosition(int gridSizeI);
        virtual const FloatRect getGlobalBounds();
        virtual const FloatRect getNextPositionBounds(float& dt);
        virtual void setPosition(float x, float y);
	    virtual void move(float x, float y, float & dt);
        virtual void stopVelocity();
        virtual void stopVelocityX();
        virtual void stopVelocityY();
        virtual void update(float& dt) = 0;
	    virtual void render(RenderTarget& target) = 0;
};
#endif