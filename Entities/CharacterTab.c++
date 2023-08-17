#include "../Header/CharacterTab.h"

void CharacterTab::initText(){
	//Text
	this->infoText.setFont(this->font);
	this->infoText.setCharacterSize(gui::calcCharSize(this->vm, 50));
	this->infoText.setFillColor(Color::White);
	this->infoText.setPosition(this->back.getPosition().x + 20.f, this->back.getPosition().y + 20.f);
}

CharacterTab::CharacterTab(VideoMode& vm, Font& font, Player& player)
	: Tab(vm, font, player, false){
	//Background
	this->back.setFillColor(Color(50, 50, 50, 180));
	this->back.setSize(Vector2f(gui::p2pX(45.f, this->vm), static_cast<float>(this->vm.height)));

	//Text
    this->initText();
}

CharacterTab::~CharacterTab(){

}

void CharacterTab::update(){
    if (!this->hidden){
        //Update the character info
		this->infoText.setString(this->player.toStringCharacterTab());
	}
}

void CharacterTab::render(RenderTarget & target){
	if (!this->hidden){
		target.draw(back);
		target.draw(infoText);
	}
}