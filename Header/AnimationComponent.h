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
                float timer;
                int width;
                int height;
                IntRect startRect;
                IntRect currentRect;
                IntRect endRect;
                Animation(Sprite& sprite, Texture& textureSheet,float speedAnimation, int start_frames_x, int start_frames_y, 
                int frames_x, int frames_y, int width, int height): sprite(sprite), textureSheet(textureSheet), speedAnimation(speedAnimation), width(width), height(height){

                    this->timer = 0.f;
                    this->startRect = IntRect(start_frames_x * width, start_frames_y * height, width, height);
                    this->currentRect = this->startRect;
                    this->endRect = IntRect(frames_x * width, frames_y * height, width, height);
                    this->sprite.setTexture(this->textureSheet, true);
                    this->sprite.setTextureRect(this->startRect);
                }
                
            //function
            void play(const float& dt){
                //update timer
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
                    }
                    this->sprite.setTextureRect(this->currentRect);
                }
            };
            void pause();
            void reset(){
                this->timer = 0.f;
                this->currentRect = this->startRect;
                
            };
        };
        Sprite& sprite;
        Texture& textureSheet;
        map<string, Animation*> animations;
        Animation* lastAnimation;

    public:
        AnimationComponent(Sprite& sprite, Texture& textureSheet);
        virtual ~AnimationComponent();

        //Function
        void addAnimation(string key, float speedAnimation, int start_frames_x, 
            int start_frames_y, int frames_x, int frames_y, int width, int height);
        void startAnimation(string animation);
        void pauseAnimation(string animation);
        void resetAnimation(string animation);
        void play(string key, const float& dt);
};
#endif