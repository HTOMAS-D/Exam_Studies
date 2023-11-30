#include "ATarget.hpp"

ATarget::ATarget(const std::string &type): _type(type){}

ATarget::~ATarget(){}

const std::string &ATarget::getType()const {return _type;}

void ATarget::getHitBySpell(const ASpell &Spell)const{
    std::cout << this->getType() << " has been " << Spell.getEffects() << "!" <<  std::endl;
}
