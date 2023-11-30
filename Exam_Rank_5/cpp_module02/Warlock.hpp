#ifndef WARLOCK_HPP
#define WARLOCK_HPP
#include <string>
#include <iostream>
#include <map>
#include "ASpell.hpp"

class ASpell;

class Warlock{
    private:
        std::string _name;
        std::string _title;
        std::map <std::string, ASpell*> _spells;
    public:
        Warlock(const std::string &name, const std::string &title);
        ~Warlock();

        const std::string &getName() const;
        const std::string &getTitle() const;

        void setTitle(const std::string &title);
        void introduce()const;

        void learnSpell(ASpell *spell);
        void forgetSpell(std::string spell);
        // void launchSpell(std::string spell, ATarget &target);
        void launchSpell(std::string spellName, const ATarget& target);

};


#endif