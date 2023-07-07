#include "../Header/AnimationComponent.h"

AnimationComponent::AnimationComponent(Sprite& sprite, Texture& textureSheet): sprite(sprite), textureSheet(textureSheet){
    this->lastAnimation = NULL; 
    this->priorityAnimation = NULL;
}

AnimationComponent::~AnimationComponent(){
    for (map<std::string, Animation*>::iterator it = this->animations.begin(); it != this->animations.end(); ++it){
        delete it->second;
    }
}

bool& AnimationComponent::isDone(string key){
    return this->animations[key]->isDone();
}

//Functions
void AnimationComponent::addAnimation(string key, 
    float speedAnimation, int start_frames_x, int start_frames_y, 
    int frames_x, int frames_y, int width, int height){
    this->animations[key] = new Animation(this->sprite, this->textureSheet, 
    speedAnimation, start_frames_x, start_frames_y,
    frames_x, frames_y, width, height);
}

void AnimationComponent::startAnimation(string animation){

}

void AnimationComponent::pauseAnimation(string animation){

}

void AnimationComponent::resetAnimation(string animation){

}

bool& AnimationComponent::play(string key, const float& dt, bool priority){
    if (this->priorityAnimation){
        if(this->priorityAnimation == this->animations[key]){
            if(this->lastAnimation != this->animations[key] ){
                if (this->lastAnimation != NULL){
                    this->lastAnimation->reset();
                }
                this->lastAnimation = this->animations[key];
            }
            //remove the priority animation if it is executed
            if(this->animations[key]->play(dt)){
                this->priorityAnimation = NULL;
            }
        }
    } else{
        //play the animation with no priority
        if (priority){
            this->priorityAnimation = this->animations[key];
        }
        if(this->lastAnimation != this->animations[key] ){
            if (this->lastAnimation != NULL){
                this->lastAnimation->reset();
            }
            this->lastAnimation = this->animations[key];
        }
        this->animations[key]->play(dt);
    }
    return this->animations[key]->isDone();
}

bool& AnimationComponent::play(string key, const float& dt, float& modifier, float& modifier_max, bool priority){
    if (this->priorityAnimation){//check for a priority animation
        if(this->priorityAnimation == this->animations[key]){
            if(this->lastAnimation != this->animations[key] ){
                if (this->lastAnimation != NULL){
                    this->lastAnimation->reset();
                }
                this->lastAnimation = this->animations[key];
            }
            //remove the priority animation if it is executed
            if(this->animations[key]->play(dt, abs(modifier/modifier_max))){
                this->priorityAnimation = NULL;
            }
        }
    } else{
        //play the animation with no priority
        if (priority){
            this->priorityAnimation = this->animations[key];
        }
        if(this->lastAnimation != this->animations[key] ){
            if (this->lastAnimation != NULL){
                this->lastAnimation->reset();
            }
            this->lastAnimation = this->animations[key];
        }
        this->animations[key]->play(dt, abs(modifier/modifier_max));
    }
    return this->animations[key]->isDone();
}