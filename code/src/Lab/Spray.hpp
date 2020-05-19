#ifndef SPRAY_HPP
#define SPRAY_HPP
#include "CircularBody.hpp"
#include <Utility/Vec2d.hpp>


class Spray : public CircularBody
{
public:
    //Constructeurs et destructeurs:
    Spray(const Vec2d& poscenter);
    ~Spray();
    Spray(const Spray& other);
};

#endif // SPRAY_HPP
