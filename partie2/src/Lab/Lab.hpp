#ifndef LAB_HPP
#define LAB_HPP
#include "CircularBody.hpp"
#include "../Application.hpp"
#include "PetriDish.hpp"

class Lab
{
public:
    Lab();
    bool contains(const CircularBody& circularbody);

private:
    PetriDish petridish_;

};

#endif // LAB_HPP
