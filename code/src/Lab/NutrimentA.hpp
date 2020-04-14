#ifndef NUTRIMENTA_HPP
#define NUTRIMENTA_HPP

#include "Nutriment.hpp"

class NutrimentA : public Nutriment
{
public:
    //constructeurs
    NutrimentA(const Quantity quantity, const Vec2d& poscenter);

    //méthodes
    //virtual void drawOn(sf::RenderTarget& target) const override;
    //virtual void update(sf::Time dt) override;
    virtual j::Value const& getConfig() const override;
};

#endif // NUTRIMENTA_HPP
