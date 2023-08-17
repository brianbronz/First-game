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
        virtual void update(const Vector2f& mouse_pos_view, const Vector2f center);
	    virtual void render(RenderTarget& target, Shader* shader = nullptr);
};

#endif