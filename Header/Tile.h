#ifndef TILE_H
#define TILE_H
#include "AllReference.h"

static short DEFAULT_TYPE = 0;
enum TileTypes {DEFAULT = 0, DAMAGING, DOODAD, ENEMYSPAWNER};

class Tile{
    private:
    protected:
        Sprite shape;
        bool collision;
        short type;
    public:
        Tile();
        Tile(short type, int grid_x, int grid_y, float gridSizeF, Texture& texture, IntRect& texture_rect, bool collision);
        virtual ~Tile();

        virtual bool & getCollision();
        virtual const Vector2f& getPosition();
        virtual FloatRect getGlobalBounds();
        virtual bool intersects(FloatRect bounds);
        virtual string getAsString() = 0;
        virtual short & getType();
        virtual void update() = 0;
	    virtual void render(RenderTarget& target, Shader* shader = NULL, Vector2f playerPosition = Vector2f()) = 0;
};

#endif