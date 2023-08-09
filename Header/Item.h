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
        unsigned value;

    public:
        Item(unsigned value);
        virtual ~Item();
        virtual Item* Clone() = 0;
};

#endif 
