#include "NutrimentA.hpp"
#include <Application.hpp>


NutrimentA::NutrimentA(const Quantity quantity, const Vec2d& poscenter)
    :Nutriment(quantity, poscenter)
{}

j::Value const& NutrimentA::getConfig() const
{
    return getAppConfig()["nutriments"]["A"];
}
