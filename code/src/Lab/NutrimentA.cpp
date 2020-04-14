#include "NutrimentA.hpp"
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
