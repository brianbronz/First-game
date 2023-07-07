#ifndef GUI_H
#define GUI_H

#include "AllReference.h"
enum button_states{ 
                    BTN_IDLE = 0,
                    BTN_HOVER,
                    BTN_ACTIVE
    };
namespace gui{
    class Button{
        private:
            short unsigned buttonState;
            short unsigned id;
            RectangleShape shape;
            Font* font;
            Text text;

            Color textIdleColor;
            Color textHoverColor;
            Color textActiveColor;

            Color idleColor;
            Color hoverColor;
            Color activeColor;


        public:

            Button(float x, float y, float width, float height, 
                Font* font, string text, unsigned character_size,
                Color text_idle_color, Color text_hover_color, Color text_active_color,
                Color idle_color, Color hover_color, Color active_color);
            virtual ~Button();

            //Accessors
            bool isPressed();
            const string& getText();
            short unsigned& getId();
            //Modifiers
            void setText( string text);
            void setId( short unsigned id);
            //Function
            void update( Vector2f& mousePos);
            void render(RenderTarget& target);
    };
    class DropDownList{
        private:
            float keytime;
            float keytimeMax;
            Font& font;
            gui::Button* activeElement;
            vector<gui::Button*> list;
            bool showList;
        public:
            DropDownList(float x, float y, float width, float height, Font& font, string list[], unsigned nrOfElements, unsigned default_index = 0);
            ~DropDownList();
            //Accessors
            unsigned short& getActiveElementId();
            //Functions
            bool getKeytime();
            void updateKeytime( float& dt);
            void update(Vector2f& mousePos,  float& dt);
            void render(RenderTarget& target);
    };

    class TextureSelector
	{
	private:
		float gridSize;
		bool active;
		RectangleShape bounds;
		Sprite sheet;
		RectangleShape selector;
		Vector2u mousePosGrid;
		IntRect textureRect;

	public:
		TextureSelector(float x, float y, float width, float height, float gridSize,  Texture* texture_sheet);
        ~TextureSelector();
        //Accessors
         bool& getActive() ;
		//Functions
		void update( Vector2i& mousePosWindow);
		void render(RenderTarget& target);
	};
}
#endif