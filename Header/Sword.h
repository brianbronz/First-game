#ifndef SWORD_H
#define SWORD_H

#include "MeleeWeapon.h"
#include "AllReference.h"

class Sword : public MeleeWeapon{
    private:

    public:
        Sword();
	    virtual ~Sword();

        virtual void update(Vector2f & mousePosView, Vector2f center);
        virtual void render(RenderTarget & target, Shader * shader = nullptr);
};

#endif