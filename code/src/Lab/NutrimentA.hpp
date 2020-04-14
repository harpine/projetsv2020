#ifndef NUTRIMENTA_HPP
#define NUTRIMENTA_HPP

#include "Nutriment.hpp"

class NutrimentA : public Nutriment
{
public:
    //Constructeur:
    NutrimentA(const Quantity quantity, const Vec2d& poscenter);

    //Getter:
    virtual j::Value const& getConfig() const override;
};

#endif // NUTRIMENTA_HPP
