#ifndef TILE_H
#define TILE_H
#include "AllReference.h"

enum TileTypes {DEFAULT = 0, DAMAGING};

class Tile{
    private:
    protected:
        RectangleShape shape;
        bool collision;
        short type;
    public:
        Tile();
        Tile(float x, float y, float gridSizeF, Texture& texture, bool collision = false, short type = TileTypes::DEFAULT);
        virtual ~Tile();

        //Functions
        string getAsString();
        void update();
	    void render(RenderTarget& target);
};

#endif