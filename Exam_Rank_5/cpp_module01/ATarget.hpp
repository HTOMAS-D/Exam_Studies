#ifndef ATARGET_HPP
#define ATARGET_HPP
#include <string>
#include <iostream>
#include "ASpell.hpp"

class ASpell;

class ATarget{
    private:
        std::string _type;
    public:
        ATarget(const std::string &type);
        virtual ~ATarget();

        const std::string &getType()const;
        virtual ATarget *clone()const = 0;

        void getHitBySpell(const ASpell &Spell) const;
};


#endif