#ifndef GRIP_HPP
#define GRIP_HPP

#include "CircularBody.hpp"
#include <Utility/Vec2d.hpp>

class Grip : public CircularBody
{
public:
    //Constructeurs:
    Grip(const Vec2d& poscenter, const double radius);

    //Autres méthodes:
    void move(const Vec2d& v);
    //Déplace le grapin d'un vecteur v
};

#endif // GRIP_HPP
