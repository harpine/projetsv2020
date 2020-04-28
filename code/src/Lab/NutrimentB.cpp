#include "NutrimentB.hpp"
#include <Application.hpp>

//Constructeur:
NutrimentB::NutrimentB(const Quantity quantity, const Vec2d& poscenter)
    :Nutriment(quantity, poscenter)
{}

//Getter:
j::Value const& NutrimentB::getConfig() const
{
    return getAppConfig()["nutriments"]["B"];
}

//Autres méthodes:
Quantity NutrimentB::eatenBy(Bacterium& bact)
{
    return bact.eatableQuantity(*this);
}

Quantity NutrimentB::eatenBy(SimpleBacterium& bact)
{
    double factor(getConfig().["resistance factor"].toDouble())
    return takeQuantity(bact.getMealQuantity());
}

Quantity NutrimentB::eatenBy(TwitchingBacterium& bact)
{
    return takeQuantity(bact.getMealQuantity());
}

Quantity NutrimentB::eatenBy(SwarmBacterium& bact)
{
    return takeQuantity(bact.getMealQuantity());
}
