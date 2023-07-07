#ifndef TILE_H
#define TILE_H
#include "AllReference.h"

class Tile{
    private:
    protected:
        RectangleShape shape;
    public:
        Tile();
        Tile(float x, float y, float gridSizeF, Texture& texture);
        virtual ~Tile();

        void update();
	    void render(sf::RenderTarget& target);
};

#endif