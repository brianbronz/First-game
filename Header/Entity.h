//Base for the characters
#ifndef ENTITY_H
#define ENTITY_H

#include "AllReference.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "HitBoxComponent.h"
#include "MovementComponent.h"
#include "SkillComponent.h"

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
        SkillComponent* skillComponent;

    public:
        Entity();
        virtual ~Entity();

        //Component functions
        void setTexture(Texture& texture);
        void createHitboxComponent(Sprite& sprite, float offset_x, float offset_y,float width, float height);
        void createMovementComponent(float maxVelocity, float acceleration, float deceleration);
        void createAnimationComponent(Texture& textureSheet);
        void createAttributeComponent(unsigned level);
        void createSkillComponent();
        void createAIComponent();
        //Functions
        virtual MovementComponent* getMovementComponent();
        virtual AnimationComponent* getAnimationComponent();
        virtual AttributeComponent* getAttributeComponent();
        virtual SkillComponent* getSkillComponent();

        virtual const Vector2f& getPosition();
        virtual sf::Vector2f& getSpritePosition();
        virtual Vector2f getCenter();
        virtual sf::Vector2f getSpriteCenter();
        virtual Vector2i getGridPosition(int gridSizeI);
        virtual FloatRect getGlobalBounds();
        virtual FloatRect getNextPositionBounds(float& dt);
        virtual void setPosition(float x, float y);
	    virtual void move(float x, float y, float & dt);
        virtual void stopVelocity();
        virtual void stopVelocityX();
        virtual void stopVelocityY();
        virtual float getDistance(const Entity& entity);
        virtual float getSpriteDistance(const Entity& entity);
        virtual void update(float& dt, sf::Vector2f& mouse_pos_view, sf::View& view) = 0;
	    virtual void render(RenderTarget& target, Shader* shader, Vector2f lightPosition, bool show_hitbox) = 0;
};
#endif