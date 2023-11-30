#ifndef FWOOSH_HPPP
#define FWOOSH_HPPP
#include "ASpell.hpp"

class ASpell;

class Fwoosh : public ASpell {
    private:
    public:
        Fwoosh();
        ~Fwoosh();

        ASpell * clone()const;

};

#endif