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

    //Autres méthodes :

    //Redéfinition des méthodes virtuelles permettant de calculer
    //la quantité cédée par le nutriment
    virtual Quantity eatenBy(Bacterium& bact) override;
    virtual Quantity eatenBy(SimpleBacterium& bact) override;
    virtual Quantity eatenBy(TwitchingBacterium& bact) override;
    virtual Quantity eatenBy(SwarmBacterium& bact) override;

};

#endif // NUTRIMENTA_HPP
