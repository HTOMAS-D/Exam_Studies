#include "ASpell.hpp"

ASpell::ASpell(const std::string &name, const std::string &effects): _name(name), _effects(effects){}
ASpell::~ASpell(){}


const std::string &ASpell::getName()const {return _name;}
const std::string &ASpell::getEffects()const{return _effects;}

void ASpell::launch(const ATarget &target)const{
    target.getHitBySpell(*this);
}