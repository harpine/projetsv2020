#ifndef LAB_HPP
#define LAB_HPP
#include "CircularBody.hpp"
#include "../Application.hpp"
#include "PetriDish.hpp"

class Lab
{
public:
    Lab(); //à décommenter lors du codage de la boîte de Petri
    bool contains(const CircularBody& circularbody);

private:
    PetriDish petridish_;

};

#endif // LAB_HPP
