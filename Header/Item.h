#ifndef ITEM_H
#define ITEM_H  
#include "AllReference.h"

enum ItemTypes {IT_DEFAULT = 0, IT_RANGEDWEAPON, IT_MELEEWEAPON};
enum ItemRarities {COMMON = 0, UNCOMMON, RARE, EPIC, LEGENDARY, MYTHIC};

class Item {
    private:
        void initVariables();

    protected:
        //Variables
        short unsigned type;
        unsigned level;
        unsigned value;

    public:
        Item(unsigned level, unsigned value);
        virtual ~Item();

        //Accessors
        short unsigned getType() const{return this->type;}
        unsigned getLevel() const{return this->level;}
        unsigned getValue() const{return this->value;}

        virtual Item* clone() = 0;
};

#endif 
