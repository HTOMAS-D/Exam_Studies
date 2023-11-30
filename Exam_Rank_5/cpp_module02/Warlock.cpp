#include "Warlock.hpp"


Warlock::Warlock(const std::string &name, const std::string &title) : _name(name), _title(title){std::cout << name << ": This looks like another boring day." << std::endl;}

Warlock::~Warlock(){std::cout << this->getName() << ": My job here is done!" << std::endl;}

const std::string &Warlock::getName() const {return this->_name;}

const std::string &Warlock::getTitle() const {return this->_title;}

void Warlock::setTitle(const std::string &title){this->_title = title;}

void Warlock::introduce()const{std::cout << this->getName() << ": I am " << this->getName() << ", " << this->getTitle() << "!" << std::endl;}

void Warlock::learnSpell(ASpell* spell){
    if(_spells.find(spell->getName()) == _spells.end()){
        _spells[spell->getName()] = spell->clone();
    }
}

void Warlock::forgetSpell(std::string name){
    if(_spells.find(name) != _spells.end()){
        delete _spells[name];
        _spells.erase(name);
    }
}


void    Warlock::launchSpell(std::string spellName, const ATarget& target) {
    if (_spells.find(spellName) != _spells.end()) {
        _spells[spellName]->launch(target);
    }
}