#include "../Header/SkillComponent.h"

SkillComponent::SkillComponent(){
    this->skills.push_back(HEALTH);
	this->skills.push_back(MELEE);
	this->skills.push_back(RANGE);
	this->skills.push_back(ENDURANCE);
}

SkillComponent::~SkillComponent(){

}

int SkillComponent::getSkill(int skill){
    if (skills.empty() || skill < 0 || skill >= this->skills.size())
		throw("ERROR::SKILLCOMPONENT::GETSKILL::SKILL DOES NOT EXIST");
	else
		return this->skills[skill].getLevel();
}

void SkillComponent::gainExp(int skill, int exp){
    if (skills.empty() || skill < 0 || skill >= this->skills.size())
		throw("ERROR::SKILLCOMPONENT::GAINEXP::SKILL DOES NOT EXIST");
    else
        this->skills[skill].gainExp(exp);
}