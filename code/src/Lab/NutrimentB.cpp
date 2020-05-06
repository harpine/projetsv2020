#include "NutrimentB.hpp"
#include "Bacterium.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "PoisonousBacterium.hpp"
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

Quantity NutrimentB::eatenBy(SimpleBacterium& bact)           //?? pk créer une variable factor?? faire une modularisation -> manger avec params *bacterium et factor
{
    double factor(getConfig()["resistance factor"].toDouble());
    return takeQuantity(bact.getMealQuantity() / factor);
}

Quantity NutrimentB::eatenBy(TwitchingBacterium& bact)
{
    double factor(getConfig()["nutritive factor"].toDouble());
    return (takeQuantity(bact.getMealQuantity()) * factor);
}

Quantity NutrimentB::eatenBy(SwarmBacterium& bact)
{
    double factor(getConfig()["poison factor"].toDouble());
    return (-takeQuantity(bact.getMealQuantity()) * factor);
}

Quantity NutrimentB::eatenBy(PoisonousBacterium& bact)
{
    double factor(2.0);//(getConfig()["poison factor"].toDouble());
    return (-takeQuantity(bact.getMealQuantity() * factor));
}
