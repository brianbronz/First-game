#include "../Header/AnimationComponent.h"

AnimationComponent::AnimationComponent(Sprite& sprite, Texture& textureSheet):sprite(sprite), textureSheet(textureSheet){
}

AnimationComponent::~AnimationComponent(){
    for (map<std::string, Animation*>::iterator it = this->animations.begin(); it != this->animations.end(); ++it){
        delete it->second;
    }
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

void AnimationComponent::reseAnimation(string animation){

}

void AnimationComponent::play(string key, const float& dt){
    this->animations[key]->play(dt);
}