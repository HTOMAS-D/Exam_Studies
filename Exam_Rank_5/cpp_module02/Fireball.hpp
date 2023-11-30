#ifndef FIREBALL_HPPP
#define FIREBALL_HPPP
#include "ASpell.hpp"

class ASpell;

class Fireball : public ASpell {
    private:
    public:
        Fireball();
        ~Fireball();

        ASpell * clone()const;

};

#endif