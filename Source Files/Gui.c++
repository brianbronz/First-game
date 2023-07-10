#include "../Header/Gui.h"

gui::Button::Button(float x, float y, float width, float height, 
    Font* font, string text, unsigned character_size,
	Color text_idle_color, Color text_hover_color, Color text_active_color,
	Color idle_color, Color hover_color, Color active_color){
        
        this->buttonState = BTN_IDLE;
        this->shape.setPosition(Vector2f(x, y));
        this->shape.setSize(Vector2f(width, height));
        this->shape.setFillColor(idle_color);

        this->font = font;
        this->text.setFont(*this->font);
        this->text.setString(text);
        this->text.setFillColor(text_idle_color);
	    this->text.setCharacterSize(character_size);
        this->text.setPosition(
            this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width /2.f,
            this->shape.getPosition().y
        );

        this->textIdleColor = text_idle_color;
	    this->textHoverColor = text_hover_color;
	    this->textActiveColor = text_active_color;
        this->idleColor = idle_color;
        this->hoverColor = hover_color;
        this->activeColor = active_color;
}

gui::Button::~Button(){
    
}

bool gui::Button::isPressed(){
    return this->buttonState == BTN_ACTIVE;
}

 const string gui::Button::getText(){
    return this->text.getString();
}

short unsigned & gui::Button::getId(){
    return this->id;
}

void gui::Button::setText(string text){
    this->text.setString(text);
}

void gui::Button::setId( short unsigned id){
    this->id = id;
}

void gui::Button::update(Vector2i& mousePosWindow){
    //update the booleans for hover and pressed
    //Idle
    this->buttonState = BTN_IDLE;
    
    //hover
    if(this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))){
        this->buttonState = BTN_HOVER;
        //pressed
        if (Mouse::isButtonPressed(Mouse::Left)){
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch(this->buttonState){
        case BTN_IDLE:
            this->shape.setFillColor(this->idleColor);
            this->text.setFillColor(this->textIdleColor);
            break;
        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            this->text.setFillColor(this->textHoverColor);
            break;
        case BTN_ACTIVE:
            this->shape.setFillColor(this->activeColor);
            this->text.setFillColor(this->textActiveColor);
            break;
        default:
            this->shape.setFillColor(Color::Red);
            this->text.setFillColor(Color::Blue);
            break;
    }
}

void gui::Button::render(RenderTarget& target){
    target.draw(this->shape);
    target.draw(this->text);
}

//Drop Down List

gui::DropDownList::DropDownList(float x, float y, float width, float height, Font& font, string list[], unsigned nrOfElements, unsigned default_index):
    font(font){
    this->showList = false;
    this->keytimeMax = 1.f;
    this->keytime = 0.f;
    for (int i = 0; i < nrOfElements; i++){
        this->list.push_back(new gui::Button(x, y + ( i * height), width, height, &this->font,
            list[i], 12, Color::Black, Color::Black, Color::Black, Color::Blue, Color::Green, Color::Red));
    }
    this->activeElement = new Button(*this->list[default_index]);
}

gui::DropDownList::~DropDownList(){
    delete this->activeElement;
    for (int i = 0; i < this->list.size(); i++){
        delete this->list[i];
    }
}

bool gui::DropDownList::getKeytime(){
    if(this->keytime >= this->keytimeMax){
        this->keytime = 0.f;
        return true;
    }
    return false;
}

void gui::DropDownList::updateKeytime(float& dt){
    if (this->keytime < this->keytimeMax){
        this->keytime += 10.f * dt;
    }
}

void gui::DropDownList::update(Vector2i & mousePosWindow, float& dt){
    this->updateKeytime(dt);
    this->activeElement->update(mousePosWindow);

    //Show and hide the list
    if(this->activeElement->isPressed() && this->getKeytime()){
        (this->showList)?
            this->showList = false:
            this->showList = true;
    }
    if(this->showList){
        for (int i = 0; i < this->list.size(); i++){
            this->list[i]->update(mousePosWindow);
        }
    }
}

unsigned short & gui::DropDownList::getActiveElementId(){
    return this->activeElement->getId();
}

void gui::DropDownList::render(RenderTarget & target){
    this->activeElement->render(target);
    if(this->showList){
        for (int i = 0; i < this->list.size(); i++){
            this->list[i]->render(target);
        }
    }
}

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize,  Texture* texture_sheet,
    Font& font, string text){
    this->keytime = 0.f;
    this->keytimeMax = 1.f;
    this->gridSize = gridSize;
    float offset = 100.f;
	this->active = false;
    this->hidden = false;
	this->bounds.setSize(Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width){
		this->sheet.setTextureRect(IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	}

	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height){
		this->sheet.setTextureRect(IntRect(0, 0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
	}

    this->selector.setPosition(x, y);
	this->selector.setSize(Vector2f(gridSize, gridSize));
	this->selector.setFillColor(Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(Color::Red);

    this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);
	this->hide_btn = new gui::Button(
		y, x, 50.f, 50.f,
		&font, text, 16,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50)
	);
}

 bool& gui::TextureSelector::getActive(){
	return this->active;
}

IntRect& gui::TextureSelector::getTextureRect(){
	return this->textureRect;
}

bool gui::TextureSelector::getKeytime(){
	if (this->keytime >= this->keytimeMax){
		this->keytime = 0.f;
		return true;
	}
	return false;
}

gui::TextureSelector::~TextureSelector(){
    delete this->hide_btn;
}

//Functions
void gui::TextureSelector::updateKeytime(float& dt){
    if (this->keytime < this->keytimeMax){
            this->keytime += 10.f * dt;
    }
}

void gui::TextureSelector::update( Vector2i& mousePosWindow, float& dt){
	this->updateKeytime(dt);
	this->hide_btn->update(mousePosWindow);

	if (this->hide_btn->isPressed() && this->getKeytime()){
		(this->hidden)?
			this->hidden = false:
			this->hidden = true;
	}

	if (!this->hidden){
		this->active = false;
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))){
			this->active = true;
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);
			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
			);
			//Update texture rectangle
			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

void gui::TextureSelector::render(RenderTarget& target){
    if (!this->hidden){
        target.draw(this->bounds);
        target.draw(this->sheet);
        if(this->active){
            target.draw(this->selector);
        }
    }
    this->hide_btn->render(target);
}