#ifndef BOW_H
#define BOW_H

#include "RangeWeapon.h"
#include "AllReference.h"

class Bow : public RangeWeapon{
    private:

    public:
        Bow(unsigned level, unsigned value, string texture_file);
	    virtual ~Bow();
        virtual Bow* Clone();
        virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center);
	    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

#endif