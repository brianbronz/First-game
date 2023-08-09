#ifndef RANGEWEAPON_H
#define RANGEWEAPON_H

#include "Weapon.h"

class RangeWeapon : public Weapon {
    private:

    public:
        RangeWeapon(unsigned value, string texture_file);
        virtual ~RangeWeapon();
        virtual RangedWeapon* Clone() = 0;
        virtual void update(const Vector2f& mouse_pos_view, const Vector2f center) = 0;
	    virtual void render(RenderTarget& target, Shader* shader = nullptr) = 0;
};

#endif