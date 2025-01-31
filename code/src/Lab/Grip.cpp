#include "Grip.hpp"

//Constructeurs:
Grip::Grip(const Vec2d& poscenter, const double radius)
    :CircularBody(poscenter, radius)
{}

//Autres méthodes:
void Grip::move(const Vec2d& v)
{
    CircularBody::move(v);
}

