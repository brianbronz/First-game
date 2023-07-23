#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Item.h"

class MeleeWeapon : Item {
    protected:
        Texture weaponTexture;
        Sprite weaponSprite;

        int damageMin;
        int damageMax;

    public:
        MeleeWeapon();
        virtual ~MeleeWeapon();
        virtual void update(Vector2f & mousePosView, Vector2f center) = 0;
        virtual void render(RenderTarget & target, Shader * shader) = 0;
};

#endif