#include "NutrimentA.hpp"
#include "Bacterium.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "PoisonousBacterium.hpp"
#include <Application.hpp>

//Constructeur:
NutrimentA::NutrimentA(const Quantity quantity, const Vec2d& poscenter)
    :Nutriment(quantity, poscenter)
{}

//Getter:
j::Value const& NutrimentA::getConfig() const
{
    return getAppConfig()["nutriments"]["A"];
}

//Autres méthodes:
Quantity NutrimentA::eatenBy(Bacterium& bact)
{
    return bact.eatableQuantity(*this);
}

Quantity NutrimentA::eatenBy(SimpleBacterium& bact)
{
    return takeQuantity(bact.getMealQuantity());
}

Quantity NutrimentA::eatenBy(TwitchingBacterium& bact)
{
    return takeQuantity(bact.getMealQuantity());
}

Quantity NutrimentA::eatenBy(SwarmBacterium& bact)
{
    return takeQuantity(bact.getMealQuantity());
}

Quantity NutrimentA::eatenBy(PoisonousBacterium& bact)
{
    return takeQuantity(bact.getMealQuantity());
}
