#ifndef NUTRIMENTB_HPP
#define NUTRIMENTB_HPP

#include "Nutriment.hpp"

class NutrimentB : public Nutriment
{
public:
    //constructeurs
    NutrimentB(const Quantity quantity, const Vec2d& poscenter);
    //méthodes
    //virtual void drawOn(sf::RenderTarget& target) const override;
    //virtual void update(sf::Time dt) override;
    virtual j::Value const& getConfig() const override;
};

#endif // NUTRIMENTB_HPP
