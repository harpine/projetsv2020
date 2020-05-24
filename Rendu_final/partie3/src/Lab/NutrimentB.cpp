#include "NutrimentB.hpp"
#include "../Application.hpp"

NutrimentB::NutrimentB(const Quantity quantity, const Vec2d& poscenter)
    :Nutriment(quantity, poscenter)
{}

j::Value const& NutrimentB::getConfig() const
{
    return getAppConfig()["nutriments"]["B"];
}
