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

    //Autres méthodes :

    //Redéfinition des méthodes virtuelles permettant de calculer
    //la quantité cédée par le nutriment
    virtual Quantity eatenBy(Bacterium& bact) override;
    virtual Quantity eatenBy(SimpleBacterium& bact) override;
    virtual Quantity eatenBy(TwitchingBacterium& bact) override;
    virtual Quantity eatenBy(SwarmBacterium &bact) override;
    virtual Quantity eatenBy(PoisonousBacterium& bact) override;
};

#endif // NUTRIMENTB_HPP
