#ifndef TARGETGENERATOR_HPP
#define TARGETGENERATOR_HPP
#include "ATarget.hpp"
#include <map>

class ATarget;

class TargetGenerator{
    private:
        std::map<std::string, ATarget*> _targets;

    public:
        TargetGenerator();
        ~TargetGenerator();

        void learnTargetType(ATarget* target);
        void forgetTargetType(const std::string &target);
        ATarget *createTarget(const std::string &target);

};

#endif