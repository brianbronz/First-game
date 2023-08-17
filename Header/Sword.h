#ifndef SWORD_H
#define SWORD_H

#include "MeleeWeapon.h"
#include "AllReference.h"

class Sword : public MeleeWeapon{
    private:

    public:
        Sword(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, string texture_file);
	    virtual ~Sword();
        virtual Sword* clone();
        virtual void update(const Vector2f & mousePosView, const  Vector2f center);
        virtual void render(RenderTarget & target, Shader * shader = nullptr);
};

#endif