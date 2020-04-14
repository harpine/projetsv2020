#ifndef NUTRIMENTB_HPP
#define NUTRIMENTB_HPP

#include "Nutriment.hpp"

class NutrimentB : public Nutriment
{
public:
    //Constructeur:
    NutrimentB(const Quantity quantity, const Vec2d& poscenter);

    //Getter:
    virtual j::Value const& getConfig() const override;
};

#endif // NUTRIMENTB_HPP
