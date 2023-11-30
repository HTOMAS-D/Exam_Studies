#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator(){}
TargetGenerator::~TargetGenerator(){}

void TargetGenerator::learnTargetType(ATarget *target){
    if(_targets.find(target->getType()) == _targets.end()){
        _targets[target->getType()] = target->clone();
    }
}

void TargetGenerator::forgetTargetType(const std::string &type){
    if(_targets.find(type) != _targets.end()){
        delete _targets[type];
        _targets.erase(type);
    }
}

ATarget *TargetGenerator::createTarget(const std::string &target){
    if(_targets.find(target) != _targets.end()){
        return _targets[target]->clone();
    }
    return NULL;
}