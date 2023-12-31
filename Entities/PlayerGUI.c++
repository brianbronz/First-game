#include "../Header/PlayerGUI.h"
#include "PlayerGUITabs.c++"

void PlayerGUI::initFont(){
	this->font.loadFromFile("../Fonts/Dosis-Light.ttf");
}

void PlayerGUI::initLevelBar(){
	float width = gui::p2pX(1.6f, this->vm);
	float height = gui::p2pY(2.8f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(1.9f, this->vm);

	this->levelBarBack.setSize(Vector2f(width, height));
	this->levelBarBack.setFillColor(Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::calcCharSize(this->vm, 150));
	this->levelBarText.setPosition( this->levelBarBack.getPosition().x + gui::p2pX(0.53f, this->vm), this->levelBarBack.getPosition().y + gui::p2pY(0.5f, this->vm)
	);
}

void PlayerGUI::initEXPBar(){
	/* float width = gui::p2pX(10.4f, this->vm);
	float height = gui::p2pY(1.9f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(5.6f, this->vm);

	this->expBarMaxWidth = width;

	this->expBarBack.setSize(Vector2f(width, height));
	this->expBarBack.setFillColor(Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarInner.setSize(Vector2f(width, height));
	this->expBarInner.setFillColor(Color(20, 20, 250, 200));
	this->expBarInner.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(gui::calcCharSize(this->vm, 180));
	this->expBarText.setPosition(this->expBarInner.getPosition().x + gui::p2pX(0.53f, this->vm), this->expBarInner.getPosition().y + gui::p2pY(0.5f, this->vm)
	 */	
	this->expBar = new gui::ProgressBar(
		1.f, 5.6f, 10.4f, 1.9f, Color::Blue, 220,
		this->vm, &this->font);
}

void PlayerGUI::initHPBar(){
	this->hpBar = new gui::ProgressBar(
		1.f, 8.3f, 10.4f, 2.8f, Color::Red, 180,
		this->vm, &this->font);
	/* float width = gui::p2pX(10.4f, this->vm);
	float height = gui::p2pY(2.8f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(8.3f, this->vm);

	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(Vector2f(width, height));
	this->hpBarBack.setFillColor(Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(Vector2f(width, height));
	this->hpBarInner.setFillColor(Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());
    this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(gui::calcCharSize(this->vm, 200));
	this->hpBarText.setPosition(this->hpBarInner.getPosition().x + gui::p2pX(0.53f, this->vm), this->hpBarInner.getPosition().y + gui::p2pY(0.15f, this->vm)
	); */
}

void PlayerGUI::initPlayerTabs(VideoMode &vm, Font &font, Player &player)
{
	this->playerTabs = new PlayerGUITabs(vm, font, player);
}
/* 
void PlayerGUI::initCharacterTab()
{
	this->playerTabs = new PlayerGUITabs(vm, font, player);
	//Background
	 this->CharacterTabBack.setFillColor(Color(50, 50, 50, 180));
	this->CharacterTabBack.setSize(Vector2f(gui::p2pX(30.f, this->vm), static_cast<float>(this->vm.height)));

	//Text
	this->CharacterInfoText.setFont(this->font);
	this->CharacterInfoText.setCharacterSize(gui::calcCharSize(this->vm, 50));
	this->CharacterInfoText.setFillColor(Color::White);
	this->CharacterInfoText.setPosition(this->CharacterTabBack.getPosition().x + 20.f, this->CharacterTabBack.getPosition().y + 20.f);
} */

PlayerGUI::PlayerGUI(Player* player, VideoMode& vm): vm(vm){
	this->player = player;

	this->initFont();
    this->initLevelBar();
	this->initEXPBar();
	this->initHPBar();
	this->initPlayerTabs(vm, font, *player);
	//this->initTabMenu();
	//this->initCharacterTab();
}

PlayerGUI::~PlayerGUI(){
	delete this->hpBar;
	delete this->expBar;
	delete this->playerTabs;
}

bool PlayerGUI::getTabsOpen(){
	return this->playerTabs->tabsOpen();
}

void PlayerGUI::toggleCharacterTab(){
	this->playerTabs->toggleTab(CHARACTER_TAB);
}

//Functions
void PlayerGUI::updateLevelBar(){
	this->levelBarString = to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::updateEXPBar(){
	/* float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);

	this->expBarInner.setSize(
		Vector2f(
			static_cast<float>(floor(this->expBarMaxWidth * percent)),
			this->expBarInner.getSize().y
		)
	);

	this->expBarString = to_string(this->player->getAttributeComponent()->exp) + " / " + to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString); */
	this->expBar->update(this->player->getAttributeComponent()->exp, this->player->getAttributeComponent()->expNext);
}

void PlayerGUI::updateHPBar()
{
	/* float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);

	this->hpBarInner.setSize(
		Vector2f(
			static_cast<float>(floor(this->hpBarMaxWidth * percent)),
			this->hpBarInner.getSize().y
		)
	);
    this->hpBarString = to_string(this->player->getAttributeComponent()->hp) + " / " + to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString); */
	this->hpBar->update(this->player->getAttributeComponent()->hp, this->player->getAttributeComponent()->hpMax);
}

void PlayerGUI::updatePlayerTabs()
{
	this->playerTabs->update();
}

void PlayerGUI::update(float & dt)
{
    this->updateLevelBar();
	this->updateEXPBar();
	this->updateHPBar();
	this->updatePlayerTabs();
}

void PlayerGUI::renderLevelBar(RenderTarget & target){
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGUI::renderEXPBar(RenderTarget & target){
	// target.draw(this->expBarBack);
	// target.draw(this->expBarInner);
	// target.draw(this->expBarText);
	this->expBar->render(target);
}

void PlayerGUI::renderHPBar(RenderTarget & target)
{
	this->hpBar->render(target);
}

//Tabs
void PlayerGUI::renderPlayerTabs(RenderTarget& target)
{
	this->playerTabs->render(target);
}

void PlayerGUI::render(RenderTarget & target)
{
    this->renderLevelBar(target);
	this->renderEXPBar(target);
	this->renderHPBar(target);
	this->renderPlayerTabs(target);
}