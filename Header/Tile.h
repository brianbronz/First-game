#ifndef TILE_H
#define TILE_H
#include "AllReference.h"

static const short DEFAULT_TYPE = 0;
enum TileTypes {DEFAULT = 0, DAMAGING, DOODAD, ENEMYSPAWNER};

class Tile{
    private:
    protected:
        Sprite shape;
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
        virtual void update();
	    virtual void render(RenderTarget& target, Shader* shader = NULL, Vector2f playerPosition = Vector2f());
};

#endif