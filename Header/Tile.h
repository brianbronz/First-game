#ifndef TILE_H
#define TILE_H
#include "AllReference.h"

static const short DEFAULT_TYPE = 0;
enum TileTypes {DEFAULT = 0, DAMAGING, DOODAD};

class Tile{
    private:
    protected:
        RectangleShape shape;
        bool collision;
        short type;
    public:
        //Tile();
        Tile(int grid_x, int grid_y, float gridSizeF, Texture& texture, IntRect& texture_rect, bool collision = false, short type = DEFAULT_TYPE);
        virtual ~Tile();

        bool & getCollision();
	    const Vector2f& getPosition();
        const FloatRect getGlobalBounds();
	    bool intersects(FloatRect bounds);

        short& getType();
        //Functions
        string getAsString();
        void update();
	    void render(RenderTarget& target);
};

#endif