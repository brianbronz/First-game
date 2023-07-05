#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H
#include "AllReference.h"

class AnimationComponent{
    private:
        class Animation{
            public:
            //Fields variables
                Sprite& sprite;
                Texture& textureSheet;
                float speedAnimation;
                bool done;
                float timer;
                int width;
                int height;
                IntRect startRect;
                IntRect currentRect;
                IntRect endRect;
                Animation(Sprite& sprite, Texture& textureSheet,float speedAnimation, int start_frames_x, int start_frames_y, 
                int frames_x, int frames_y, int width, int height): sprite(sprite), textureSheet(textureSheet){

                    this->speedAnimation= speedAnimation;
                    this->timer = 0.f;
                    this->done = false;
                    this->width = width; 
                    this->height = height;
                    this->startRect = IntRect(start_frames_x * width, start_frames_y * height, width, height);
                    this->currentRect = this->startRect;
                    this->endRect = IntRect(frames_x * width, frames_y * height, width, height);
                    this->sprite.setTexture(this->textureSheet, true);
                    this->sprite.setTextureRect(this->startRect);
                }
                
            bool& isDone(){
                return this->done;
            }
            //function
            bool& play(const float& dt){
                //update timer
                this->done = false;
                this->timer += 100.f * dt; 
                if (this->timer >= this->speedAnimation){
                    //reset timer
                    this->timer = 0.f;
                    //animate
                    if(this->currentRect != this->endRect){
                        this->currentRect.left += this->width;
                    } else {
                        //reset
                        this->currentRect.left = this->startRect.left;
                        this->done = true;
                    }
                    this->sprite.setTextureRect(this->currentRect);
                }
                return this->done;
            };
            bool& play(const float& dt, float mod_percent){
                //update timer
                if (mod_percent < 0.5f){
                    mod_percent = 0.5f;
                }
                this->done = false;
                this->timer += mod_percent * 100.f * dt;
                if (this->timer >= this->speedAnimation){
                    //reset timer
                    this->timer = 0.f;
                    //animate
                    if(this->currentRect != this->endRect){
                        this->currentRect.left += this->width;
                    } else {
                        //reset
                        this->currentRect.left = this->startRect.left;
                        this->done = true;
                    }
                    this->sprite.setTextureRect(this->currentRect);
                }
                return this->done;
            };
            void pause();
            void reset(){
                this->timer = this->speedAnimation;
                this->currentRect = this->startRect;
                
            };
        };
        Sprite& sprite;
        Texture& textureSheet;
        map<string, Animation*> animations;
        Animation* lastAnimation;
        Animation* priorityAnimation;

    public:
        AnimationComponent(Sprite& sprite, Texture& textureSheet);
        virtual ~AnimationComponent();

        //Accessors
        bool& isDone(string key);
        //Function
        void addAnimation(string key, float speedAnimation, int start_frames_x, 
            int start_frames_y, int frames_x, int frames_y, int width, int height);
        void startAnimation(string animation);
        void pauseAnimation(string animation);
        void resetAnimation(string animation);
        bool& play(string key, const float& dt, bool priority = false);
        bool& play(string key, const float& dt, float& modifier, float& modifier_max, bool priority = false);
        
};
#endif