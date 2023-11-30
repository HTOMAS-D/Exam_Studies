#ifndef POLYMORPH_HPPP
#define POLYMORPH_HPPP
#include "ASpell.hpp"

class ASpell;

class Polymorph : public ASpell {
    private:
    public:
        Polymorph();
        ~Polymorph();

        ASpell * clone()const;

};

#endif