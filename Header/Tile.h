#ifndef TILE_H
#define TILE_H
#include "AllReference.h"

static const short DEFAULT_TYPE = 0;
enum TileTypes {DEFAULT = 0, DAMAGING};

class Tile{
    private:
    protected:
        RectangleShape shape;
        bool collision;
        short type;
    public:
        //Tile();
        Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, Texture& texture, IntRect& texture_rect, bool collision = false, short type = DEFAULT_TYPE);
        virtual ~Tile();

        //Functions
        string getAsString();
        void update();
	    void render(RenderTarget& target);
};

#endif