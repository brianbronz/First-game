#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapon.h"

class MeleeWeapon : public Weapon {
    protected:
        Texture weaponTexture;
        Sprite weaponSprite;

        int damageMin;
        int damageMax;

    public:
        MeleeWeapon(unsigned value, string texture_file);
        virtual ~MeleeWeapon();
        virtual MeleeWeapon* Clone() = 0;
        virtual void update(Vector2f & mousePosView, Vector2f center) = 0;
        virtual void render(RenderTarget & target, Shader * shader) = 0;
};

#endif