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
