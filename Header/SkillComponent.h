#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H

#include "AllReference.h"

enum SKILLS {HEALTH = 0, MELEE, RANGE, ENDURANCE};
class SkillComponent{
    private:
       class Skill{
            private:
                int type;
                int level;
                int levelCap;
                int exp;
                int expNext;
            
            public:
                Skill();
                Skill(int type){
                    this->type = type;
                    this->level = 1;
                    this->levelCap = 99;
                    this->exp = 0;
                    this->expNext = 100;
                }

                ~Skill(){}

                //Accessors
                inline int getType() const { return this->type; }
                inline int& getLevel(){ return this->level;}
                inline int& getExp(){ return this->exp;}
                inline int& getExpNext(){ return this->expNext;}

                //Modifiers
                void setLevel(int level){ this->level = level;}
                void setLevelCap(int levelCap){this->levelCap = levelCap;}

                //Functions
                void gainExp(int exp){
                    this->exp += exp;
                    this->updateLevel();
                }

                void loseExp(int exp){
                    this->exp -= exp;
                }

                void updateLevel(bool up = true){
                    if(up){
                        if(this->level < this->levelCap){
                            while(this->exp >= this->expNext){
                                if(this->level < this->levelCap){
                                    this->level++;
                                    this->expNext = pow(this->level, 2) + this->level * 10 + this->level * 2;                             
                                }
                            }
                        }
                    } else {
                        if (this->level > 0){
                            while (this->exp < 0){
                                if (this->level > 0){
                                    this->level--;
                                    this->expNext = pow(this->level, 2) + this->level * 10 + this->level * 2;
                                }
                            }
                        }
                    }
                }

                void update(){

                }
       };
        vector<Skill> skills;
    public:
    
        SkillComponent();
        virtual ~SkillComponent();
        int getSkill(string key);
        int getSkill(int skill);
	    void gainExp(int skill, int exp);
};
#endif