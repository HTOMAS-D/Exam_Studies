#include "SpellBook.hpp"

SpellBook::SpellBook(){}

SpellBook::~SpellBook(){}

void SpellBook::learnSpell(ASpell *spell){
    if(_spells.find(spell->getName()) == _spells.end()){
        _spells[spell->getName()] = spell->clone();
    }
}

void SpellBook::forgetSpell(const std::string &name){
    if(_spells.find(name) != _spells.end()){
        delete _spells[name];
        _spells.erase(name);
    }
}


ASpell* SpellBook::createSpell(const std::string& name) {
    if (_spells.find(name) != _spells.end())
        return (_spells[name]->clone());
    return (NULL);
}