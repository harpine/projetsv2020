#include "NutrimentGenerator.hpp"
#include "Random/Random.hpp"
#include <Application.hpp>
#include "Lab.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"

NutrimentGenerator::NutrimentGenerator()
    :compteur_(sf::Time::Zero)
{}

void NutrimentGenerator::update(sf::Time dt)
{
    compteur_ += dt;

    if (compteur_ > sf::seconds(getAppConfig()["generator"]["nutriment"]["delay"].toDouble())) {

        compteur_ = sf::Time::Zero;
        Nutriment* nutriment(choose());
        getAppEnv().addNutriment(nutriment);
    }
}

Nutriment* NutrimentGenerator::choose()
{
    Vec2d tailleEnv(getApp().getLabSize());
    Vec2d center(normal(tailleEnv.x/2, (tailleEnv.x/4 *tailleEnv.x/4)),
                 normal(tailleEnv.y/2, (tailleEnv.y/4 *tailleEnv.y/4)));
    if (bernoulli(getAppConfig()["generator"]["nutriment"]["prob"].toDouble())) {
        Quantity quantity(uniform(getShortConfig().nutrimentA_min_qty,
                                  getShortConfig().nutrimentA_max_qty));
        return new NutrimentA(quantity, center);
    }
    Quantity quantity(uniform(getShortConfig().nutrimentB_min_qty,
                              getShortConfig().nutrimentB_min_qty));
    return new NutrimentB(quantity, center);
}

void NutrimentGenerator::reset()
{
    compteur_ = sf::Time::Zero;
}
