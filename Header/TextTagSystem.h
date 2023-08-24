#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H
#include "AllReference.h"

enum TAGTYPES { DEFAULT_TAG, NEGATIVE_TAG, POSITIVE_TAG, EXPERIENCE_TAG, ENVIRONMETAL_TAG};

class TextTagSystem
{
private:
	class TextTag
	{
	private:
		Text text;
		float dirY;
		float dirX;
		float lifetime;
		float speed;
		float acceleration;
		Vector2f velocity;
		int fadeValue;
		bool reverse;

	public:
		TextTag(Font& font, string text, float pos_x, float pos_y,
			float dir_x, float dir_y, Color color, unsigned char_size,
			float lifetime, bool reverse, float speed, float acceleration, int fade_value)
		{
			this->text.setFont(font);
			this->text.setPosition(pos_x, pos_y);
			this->text.setFillColor(color);
			this->text.setCharacterSize(char_size);
			this->text.setString(text);

			this->dirX = dir_x;
			this->dirY = dir_y;
			this->lifetime = lifetime;
			this->speed = speed;
			this->acceleration = acceleration;
			this->fadeValue = fade_value;
			this->reverse	= reverse;

			if (this->reverse){
				this->velocity.x = this->dirX * this->speed;
				this->velocity.y = this->dirY * this->speed;
			}
		}

        TextTag(TextTag* tag, float pos_x, float pos_y, string str)
		{
			this->text = tag->text;
			this->text.setString(str);
			this->text.setPosition(pos_x, pos_y);

			this->dirX = tag->dirX;
			this->dirY = tag->dirY;
			this->lifetime = tag->lifetime;
			this->speed = tag->speed;
			this->acceleration = tag->acceleration;
			this->fadeValue = tag->fadeValue;
			this->reverse = tag->reverse;
			this->velocity = tag->velocity;
		}

		~TextTag()
		{

		}

		//Accessor
		inline const bool isExpired() const{ return this->lifetime <= 0.f; }

		//Function
		void update(const float& dt)
		{
			if (this->lifetime > 0.f)
			{
				//Update the lifetime
				this->lifetime -= 100.f * dt;
				//Accelerate
				if (this->acceleration > 0.f){
					if (this->reverse)
					{
						this->velocity.x -= this->dirX * this->acceleration * dt;
						this->velocity.y -= this->dirY * this->acceleration * dt;

						if (abs(this->velocity.x) < 0.f)
							this->velocity.x = 0.f;

						if (abs(this->velocity.y) < 0.f)
							this->velocity.y = 0.f;

						this->text.move(this->velocity * dt);
					}
					else
					{
						this->velocity.x += this->dirX * this->acceleration * dt;
						this->velocity.y += this->dirY * this->acceleration * dt;
					
						if (abs(this->velocity.x) > this->speed)
							this->velocity.x = this->dirX * this->speed;

						if (abs(this->velocity.y) > this->speed)
							this->velocity.y = this->dirY * this->speed;

						this->text.move(this->velocity * dt);
					}
				} else {
					//Move the tag
					this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);
				}

				if (this->fadeValue > 0 && this->text.getFillColor().a >= this->fadeValue) {
					this->text.setFillColor(
						Color(
							this->text.getFillColor().r,
							this->text.getFillColor().g,
							this->text.getFillColor().b,
							this->text.getFillColor().a - this->fadeValue)
					);
				}
			}
		}

		void render(RenderTarget& target)
		{
			target.draw(this->text);
		}
	};

    Font font;
	std::map<unsigned, TextTag*> tagTemplates;
	vector<TextTag*> tags;

	//Private functions
	void initVariables();
	void initFonts(string font_file);
	void initTagTemplates();

public:
	TextTagSystem(string font_file);
	virtual ~TextTagSystem();

	//Functions
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const string str, const string prefix, const string postfix);
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const int i, const string prefix, const string postfix);
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const float f, const string prefix, const string postfix);
	void update(const float &dt);
	void render(RenderTarget & target);
};

#endif // !TEXTTAGSYSTEM_H