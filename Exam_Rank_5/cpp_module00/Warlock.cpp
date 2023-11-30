#include "Warlock.hpp"


Warlock::Warlock(const std::string &name, const std::string &title) : _name(name), _title(title){std::cout << name << ": This looks like another boring day." << std::endl;}

Warlock::~Warlock(){std::cout << this->getName() << ": My job here is done!" << std::endl;}

const std::string &Warlock::getName() const {return this->_name;}

const std::string &Warlock::getTitle() const {return this->_title;}

void Warlock::setTitle(const std::string &title){this->_title = title;}

void Warlock::introduce()const{std::cout << this->getName() << ": I am " << this->getName() << ", " << this->getTitle() << "!" << std::endl;}